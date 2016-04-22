#include "guiKmChat.h"
#include "chat.h"
#include "client.h"
#include "debug.h"
#include "gettime.h"
#include "keycode.h"
#include "settings.h"
#include "porting.h"
#include "client/tile.h"
#include "fontengine.h"
#include "log_types.h"
#include "gettext.h"
#include <string>

#include "xCGUITTFont.h"

#define PROMPT_TOP_INDENT 0
#define PROMPT_BOT_INDENT 10

inline u32 clamp_u8(s32 value)
{
	return (u32) MYMIN(MYMAX(value, 0), 255);
}


GUIKmChat::GUIKmChat(
		gui::IGUIEnvironment* env,
		gui::IGUIElement* parent,
		s32 id,
		ChatBackend* backend,
		Client* client
):
	IGUIElement(gui::EGUIET_ELEMENT, env, parent, id,
			core::rect<s32>(0,0,100,100)),
	m_chat_backend(backend),
	m_client(client),
	m_screensize(v2u32(0,0)),
	m_animate_time_old(0),
	m_open(false),
	m_close_on_return(false),
	m_rows(0),
	m_height(0),
    m_width(0),
	m_open_inhibited(0),
	m_cursor_blink(0.0),
	m_cursor_blink_speed(0.0),
	m_cursor_height(0.0),
	m_background(NULL),
	m_background_color(255, 0, 0, 0),
	m_font(NULL),
	m_fontsize(0, 0)
{
	m_animate_time_old = getTimeMs();

	// load background settings
	s32 backgrount_alpha = g_settings->getS32("km_chat_alpha");
	m_background_color.setAlpha(clamp_u8(backgrount_alpha));

    v3f console_color = g_settings->getV3F("km_chat_color");
    m_background_color.setRed(clamp_u8(myround(console_color.X)));
    m_background_color.setGreen(clamp_u8(myround(console_color.Y)));
    m_background_color.setBlue(clamp_u8(myround(console_color.Z)));
    
	int font_size = g_settings->getS32("km_chat_font_size");
    setFont(font_size);
        
    int rows = g_settings->getS32("km_chat_rows");
    setRows(rows);
    
    // set default cursor options
	setCursor(true, true, 2.0, 0.1);
    
    parent->sendToBack(this);
}

void GUIKmChat::setFont(int font_size) {
    if(font_size < 2) font_size = 2;
    if(font_size > 200) font_size = 200;
    
    m_font = g_fontengine->getFont(font_size, FM_Mono);
    
	if (m_font == NULL)
	{
		errorstream << "GUIKmChat: Unable to load mono font ";
	}
	else
	{
		core::dimension2d<u32> dim = m_font->getDimension(L"M");
		m_fontsize = v2u32(dim.Width, dim.Height);
		m_font->grab();
	}
    
	m_fontsize.X = MYMAX(m_fontsize.X, 1);
	m_fontsize.Y = MYMAX(m_fontsize.Y, 1);
    
    if (font_size != g_settings->getS32("km_chat_font_size")) {
        g_settings->set("km_chat_font_size", std::to_string(font_size));
    }
}

void GUIKmChat::setRows(int rows) {
    if(rows < 1) rows = 1;
    if(rows > 500) rows = 500;
    
    m_rows = rows;
    
    if (rows != g_settings->getS32("km_chat_rows")) {
        g_settings->set("km_chat_rows", std::to_string(rows));
    }
}

GUIKmChat::~GUIKmChat()
{
	if (m_font)
		m_font->drop();
}

void GUIKmChat::open()
{
    m_open = true;
    m_client->sendChatOpened(true);
}

void GUIKmChat::close()
{
	m_open = false;
    m_client->sendChatOpened(false);
}

bool GUIKmChat::isOpen() const
{
	return m_open;
}

bool GUIKmChat::isOpenInhibited() const
{
	return m_open_inhibited > 0;
}

void GUIKmChat::setCursor(
	bool visible, bool blinking, f32 blink_speed, f32 relative_height)
{
	if (visible)
	{
		if (blinking)
		{
			// leave m_cursor_blink unchanged
			m_cursor_blink_speed = blink_speed;
		}
		else
		{
			m_cursor_blink = 0x8000;  // on
			m_cursor_blink_speed = 0.0;
		}
	}
	else
	{
		m_cursor_blink = 0;  // off
		m_cursor_blink_speed = 0.0;
	}
	m_cursor_height = relative_height;
}

void GUIKmChat::draw()
{
	if(!IsVisible)
		return;
    
    reformatChat();

	video::IVideoDriver* driver = Environment->getVideoDriver();

	// Check screen size
	v2u32 screensize = driver->getScreenSize();
	if (screensize != m_screensize)
	{       
		m_screensize = screensize;
        m_width  = 0.65 * m_screensize.X;
		reformatChat();
	}

	// Animation
	u32 now = getTimeMs();
	animate(now - m_animate_time_old);
	m_animate_time_old = now;

	// Draw console elements if visible
	if (m_open)
	{
        drawPrompt();
		drawMessageText();
	} else {
        drawNewMessageText();
    }
    
	gui::IGUIElement::draw();
}

void GUIKmChat::reformatChat()
{
	s32 cols = m_width / m_fontsize.X - 2; // make room for a margin (looks better)

	if (cols <= 0)
		cols = 0;
        
	m_chat_backend->reformatChat(cols, m_rows);
}

void GUIKmChat::recalculateKmChatPosition()
{
	s32 line_height = m_fontsize.Y;

	core::rect<s32> rect(0, m_screensize.Y - ((m_rows + 1) * line_height +  + PROMPT_TOP_INDENT + PROMPT_BOT_INDENT), m_width, m_screensize.Y);
	DesiredRect = rect;
	recalculateAbsolutePosition(false);
}

void GUIKmChat::animate(u32 msec)
{
    recalculateKmChatPosition();

	// blink the cursor
	if (m_cursor_blink_speed != 0.0)
	{
		u32 blink_increase = 0x10000 * msec * (m_cursor_blink_speed / 1000.0);
		if (blink_increase == 0)
			blink_increase = 1;
		m_cursor_blink = ((m_cursor_blink + blink_increase) & 0xffff);
	}

	// decrease open inhibit counter
	if (m_open_inhibited > msec)
		m_open_inhibited -= msec;
	else
		m_open_inhibited = 0;
}

void GUIKmChat::drawMessageText()
{
	if (m_font == NULL)
		return;
        
    video::IVideoDriver* driver = Environment->getVideoDriver();
	irr::gui::CGUITTFont *font = static_cast<irr::gui::CGUITTFont*>(m_font);

	ChatBuffer& buf = m_chat_backend->getChatBuffer();

	for (u32 row = 0; row < buf.getRows(); ++row)
	{
		const ChatFormattedLine& line = buf.getFormattedLine(row);

		s32 line_height = m_fontsize.Y;
		s32 y = m_screensize.Y - ((m_rows - row + 1) * line_height + 2 *  + PROMPT_TOP_INDENT + PROMPT_BOT_INDENT);
        
        driver->draw2DRectangle(
            m_background_color,
            core::rect<s32>(0, y, m_width, y + line_height),
            &AbsoluteClippingRect);
        
		if (line.fragments.empty())
			continue;
            
		if (y + line_height < 0)
			continue;
                
		for (u32 i = 0; i < line.fragments.size(); ++i)
		{
			const ChatFormattedFragment& fragment = line.fragments[i];
			s32 x = (fragment.column + 1) * m_fontsize.X;
			core::rect<s32> destrect(
				x, y, x + m_fontsize.X * fragment.text.size(), y + m_fontsize.Y);

			font->draw(
				fragment.text.c_str(),
				destrect,
				fragment.text.getColors(),
				false,
				false,
				&AbsoluteClippingRect);
		}
	}
}

void GUIKmChat::drawNewMessageText()
{
	if (m_font == NULL)
		return;
        
    video::IVideoDriver* driver = Environment->getVideoDriver();
	irr::gui::CGUITTFont *font = static_cast<irr::gui::CGUITTFont*>(m_font);

	ChatBuffer& buf = m_chat_backend->getRecentBuffer();
    buf.scrollBottom();
    
	for (u32 row = 0; row < buf.getRows(); ++row)
	{
		const ChatFormattedLine& line = buf.getFormattedLine(row);
        
		if (line.fragments.empty())
			continue;

		s32 line_height = m_fontsize.Y;
		s32 y = m_screensize.Y - ((m_rows - row + 1) * line_height + 2 *  + PROMPT_TOP_INDENT + PROMPT_BOT_INDENT);
        
        driver->draw2DRectangle(
            m_background_color,
            core::rect<s32>(0, y, m_width, y + line_height),
            &AbsoluteClippingRect);
            
		if (y + line_height < 0)
			continue;
                
		for (u32 i = 0; i < line.fragments.size(); ++i)
		{
			const ChatFormattedFragment& fragment = line.fragments[i];
			s32 x = (fragment.column + 1) * m_fontsize.X;
			core::rect<s32> destrect(
				x, y, x + m_fontsize.X * fragment.text.size(), y + m_fontsize.Y);

			font->draw(
				fragment.text.c_str(),
				destrect,
				fragment.text.getColors(),
				false,
				false,
				&AbsoluteClippingRect);
		}
	}
}

void GUIKmChat::drawPrompt()
{
	if (m_font == NULL)
		return;

    video::IVideoDriver* driver = Environment->getVideoDriver();

	s32 line_height = m_fontsize.Y;
	s32 y = m_screensize.Y - (line_height +  + PROMPT_TOP_INDENT + PROMPT_BOT_INDENT);

	ChatPrompt& prompt = m_chat_backend->getPrompt();
	std::wstring prompt_text = prompt.getVisiblePortion();

    driver->draw2DRectangle(
        m_background_color,
        core::rect<s32>(0, y, m_width, y + line_height),
        &AbsoluteClippingRect);

	// FIXME Draw string at once, not character by character
	// That will only work with the cursor once we have a monospace font
	for (u32 i = 0; i < prompt_text.size(); ++i)
	{
		wchar_t ws[2] = {prompt_text[i], 0};
		s32 x = (1 + i) * m_fontsize.X;
		core::rect<s32> destrect(
			x, y, x + m_fontsize.X, y + m_fontsize.Y);

		m_font->draw(
			ws,
			destrect,
			video::SColor(255, 255, 255, 255),
			false,
			false,
			&AbsoluteClippingRect);
	}

	// Draw the cursor during on periods
	if ((m_cursor_blink & 0x8000) != 0)
	{
		s32 cursor_pos = prompt.getVisibleCursorPosition();
		if (cursor_pos >= 0)
		{
			video::IVideoDriver* driver = Environment->getVideoDriver();
			s32 x = (1 + cursor_pos) * m_fontsize.X;
			core::rect<s32> destrect(
				x,
				y + (1.0-m_cursor_height) * m_fontsize.Y,
				x + m_fontsize.X,
				y + m_fontsize.Y);
			video::SColor cursor_color(255,255,255,255);
			driver->draw2DRectangle(
				cursor_color,
				destrect,
				&AbsoluteClippingRect);
		}
	}
}

void GUIKmChat::setPrompt(const std::wstring& input) {
	m_chat_backend->getPrompt().cursorOperation(
			ChatPrompt::CURSOROP_DELETE,
			ChatPrompt::CURSOROP_DIR_LEFT,
			ChatPrompt::CURSOROP_SCOPE_LINE);
	for (unsigned int i = 0; i < input.size(); i++) {
		m_chat_backend->getPrompt().input(input[i]);
	}
}

bool GUIKmChat::getAndroidUIInput() {
#ifdef __ANDROID__
	if (porting::getInputDialogState() == 0) {
		std::string text = porting::getInputDialogValue();
		std::wstring wtext = narrow_to_wide(text);
		//errorstream<<"GUIKmChat::getAndroidUIInput() text=["<<text<<"] "<<std::endl;
		m_chat_backend->getPrompt().input(wtext);
		std::wstring wrtext = m_chat_backend->getPrompt().submit();
		m_client->typeChatMessage(wide_to_narrow(wrtext));

		if (m_close_on_return) {
			close();
			Environment->removeFocus(this);
		}

		return true;
	}
#endif
	return false;
}

bool GUIKmChat::OnEvent(const SEvent& event)
{
	if(event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown)
	{
		KeyPress kp(event.KeyInput);
		// Key input
		if (kp == EscapeKey || kp == CancelKey)
		{
			close();
			Environment->removeFocus(this);
			// the_game will open the pause menu
			return true;
		}
		else if(event.KeyInput.Key == KEY_PRIOR && event.KeyInput.Char == 0 && !event.KeyInput.Control)
		{
			m_chat_backend->scrollPageUp();
			return true;
		}
		else if(event.KeyInput.Key == KEY_NEXT && event.KeyInput.Char == 0 && !event.KeyInput.Control)
		{
			m_chat_backend->scrollPageDown();
			return true;
		}
		else if(event.KeyInput.Key == KEY_RETURN)
		{
			std::string text = wide_to_narrow(m_chat_backend->getPrompt().submit());
			m_client->typeChatMessage(text);

            Environment->removeFocus(this);
			return true;
		}
		else if(event.KeyInput.Key == KEY_UP && event.KeyInput.Char == 0)
		{
			// Up pressed
			// Move back in history
			m_chat_backend->getPrompt().historyPrev();
			return true;
		}
		else if(event.KeyInput.Key == KEY_DOWN && event.KeyInput.Char == 0)
		{
			// Down pressed
			// Move forward in history
			m_chat_backend->getPrompt().historyNext();
			return true;
		}
		else if(event.KeyInput.Key == KEY_LEFT && event.KeyInput.Char == 0)
		{
			// Left or Ctrl-Left pressed
			// move character / word to the left
			ChatPrompt::CursorOpScope scope =
				event.KeyInput.Control ?
				ChatPrompt::CURSOROP_SCOPE_WORD :
				ChatPrompt::CURSOROP_SCOPE_CHARACTER;
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_MOVE,
				ChatPrompt::CURSOROP_DIR_LEFT,
				scope);
			return true;
		}
		else if(event.KeyInput.Key == KEY_RIGHT && event.KeyInput.Char == 0)
		{
			// Right or Ctrl-Right pressed
			// move character / word to the right
			ChatPrompt::CursorOpScope scope =
				event.KeyInput.Control ?
				ChatPrompt::CURSOROP_SCOPE_WORD :
				ChatPrompt::CURSOROP_SCOPE_CHARACTER;
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_MOVE,
				ChatPrompt::CURSOROP_DIR_RIGHT,
				scope);
			return true;
		}
		else if(event.KeyInput.Key == KEY_HOME && event.KeyInput.Char == 0)
		{
			// Home pressed
			// move to beginning of line
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_MOVE,
				ChatPrompt::CURSOROP_DIR_LEFT,
				ChatPrompt::CURSOROP_SCOPE_LINE);
			return true;
		}
		else if(event.KeyInput.Key == KEY_END && event.KeyInput.Char == 0)
		{
			// End pressed
			// move to end of line
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_MOVE,
				ChatPrompt::CURSOROP_DIR_RIGHT,
				ChatPrompt::CURSOROP_SCOPE_LINE);
			return true;
		}
		else if(event.KeyInput.Key == KEY_BACK)
		{
			// Backspace or Ctrl-Backspace pressed
			// delete character / word to the left
			ChatPrompt::CursorOpScope scope =
				event.KeyInput.Control ?
				ChatPrompt::CURSOROP_SCOPE_WORD :
				ChatPrompt::CURSOROP_SCOPE_CHARACTER;
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_DELETE,
				ChatPrompt::CURSOROP_DIR_LEFT,
				scope);
			return true;
		}
		else if(event.KeyInput.Key == KEY_DELETE && (event.KeyInput.Char == 0 || event.KeyInput.Char == 127))
		{
			// Delete or Ctrl-Delete pressed
			// delete character / word to the right
			ChatPrompt::CursorOpScope scope =
				event.KeyInput.Control ?
				ChatPrompt::CURSOROP_SCOPE_WORD :
				ChatPrompt::CURSOROP_SCOPE_CHARACTER;
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_DELETE,
				ChatPrompt::CURSOROP_DIR_RIGHT,
				scope);
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_V && event.KeyInput.Control)
		{
			// Ctrl-V pressed
			// paste text from clipboard
			IOSOperator *os_operator = Environment->getOSOperator();
			const c8 *text = os_operator->getTextFromClipboard();
			if (text)
			{
				std::wstring wtext = narrow_to_wide(text);
				m_chat_backend->getPrompt().input(wtext);
			}
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_U && event.KeyInput.Control)
		{
			// Ctrl-U pressed
			// kill line to left end
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_DELETE,
				ChatPrompt::CURSOROP_DIR_LEFT,
				ChatPrompt::CURSOROP_SCOPE_LINE);
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_K && event.KeyInput.Control)
		{
			// Ctrl-K pressed
			// kill line to right end
			m_chat_backend->getPrompt().cursorOperation(
				ChatPrompt::CURSOROP_DELETE,
				ChatPrompt::CURSOROP_DIR_RIGHT,
				ChatPrompt::CURSOROP_SCOPE_LINE);
			return true;
		}
		else if(event.KeyInput.Key == KEY_TAB)
		{
			// Tab or Shift-Tab pressed
			// Nick completion
			std::list<std::string> names = m_client->getConnectedPlayerNames();
			bool backwards = event.KeyInput.Shift;
			m_chat_backend->getPrompt().nickCompletion(names, backwards);
			return true;
		}
        else if((event.KeyInput.Key == KEY_PLUS or event.KeyInput.Key == KEY_MINUS) && event.KeyInput.Control)
		{
            if(event.KeyInput.Key == KEY_PLUS) {
                setFont(g_settings->getS32("km_chat_font_size") + 1);
            }
            else {
                setFont(g_settings->getS32("km_chat_font_size") - 1);
            }
            
            reformatChat();
            recalculateKmChatPosition();
        }
        else if((event.KeyInput.Key == KEY_PRIOR or event.KeyInput.Key == KEY_NEXT) && event.KeyInput.Control)
		{
            if(event.KeyInput.Key == KEY_PRIOR) {
                setRows(g_settings->getS32("km_chat_rows") + 1);
            }
            else {
                setRows(g_settings->getS32("km_chat_rows") - 1);
            }
            
            reformatChat();
            recalculateKmChatPosition();
        }
		else if(event.KeyInput.Char != 0 && !event.KeyInput.Control)
		{
			#if (defined(linux) || defined(__linux) || defined(__FreeBSD__)) and IRRLICHT_VERSION_10000 < 10900
				wchar_t wc = L'_';
				mbtowc( &wc, (char *) &event.KeyInput.Char, sizeof(event.KeyInput.Char) );
				m_chat_backend->getPrompt().input(wc);
			#else
				m_chat_backend->getPrompt().input(event.KeyInput.Char);
			#endif
			return true;
		}
	}
	else if(event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		if(event.MouseInput.Event == EMIE_MOUSE_WHEEL)
		{
			s32 rows = myround(-3.0 * event.MouseInput.Wheel);
			m_chat_backend->scroll(rows);
		}
	}

	return Parent ? Parent->OnEvent(event) : false;
}

