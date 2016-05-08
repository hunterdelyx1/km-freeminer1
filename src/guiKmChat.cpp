/*
GUIKmChat.cpp
Copyright (C) 2013 celeron55, Perttu Ahola <celeron55@gmail.com>
*/

/*
This file is part of Freeminer.

Freeminer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Freeminer  is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Freeminer.  If not, see <http://www.gnu.org/licenses/>.
*/

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
#define PROMPT_BOT_INDENT 50

inline u32 clamp_u8(s32 value)
{
	return (u32) MYMIN(MYMAX(value, 0), 255);
}


GUIKmChat::GUIKmChat(
		gui::IGUIEnvironment* env,
		gui::IGUIElement* parent,
		s32 id,
		ChatBackend* backend,
		Client* client,
		IMenuManager* menumgr
):
	IGUIElement(gui::EGUIET_ELEMENT, env, parent, id,
			core::rect<s32>(0,0,100,100)),
	m_chat_backend(backend),
	m_client(client),
	m_menumgr(menumgr),
	m_screensize(v2u32(0,0)),
	m_animate_time_old(0),
	m_open(false),
	m_close_on_enter(false),
	m_height(0),
	m_desired_height(0),
	m_desired_height_fraction(0.0),
	m_height_speed(5.0),
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

	// load the background texture depending on settings
	v3f chat_color = g_settings->getV3F("km_chat_color");
	m_background_color.setRed(clamp_u8(myround(chat_color.X)));
	m_background_color.setGreen(clamp_u8(myround(chat_color.Y)));
	m_background_color.setBlue(clamp_u8(myround(chat_color.Z)));

	m_font = g_fontengine->getFont(FONT_SIZE_UNSPECIFIED, FM_Mono);

	int font_size = g_settings->getS32("km_chat_font_size");
	setFont(font_size);
		
	int rows = g_settings->getS32("km_chat_rows");
	setRows(rows);
	
	// set default cursor options
	setCursor(true, true, 2.0, 0.1);
	
	parent->sendToBack(this);
}

GUIKmChat::~GUIKmChat()
{
	if (m_font)
		m_font->drop();
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

void GUIKmChat::open()
{
	m_open = true;
	Environment->setFocus(this);
	m_client->sendChatOpened(true);
}

bool GUIKmChat::isOpen() const
{
	return m_open;
}

bool GUIKmChat::isOpenInhibited() const
{
	return m_open_inhibited > 0;
}

void GUIKmChat::close()
{
	m_open = false;
	Environment->removeFocus(this);
	m_client->sendChatOpened(false);
}

void GUIKmChat::replaceAndAddToHistory(std::wstring line)
{
	ChatPrompt& prompt = m_chat_backend->getPrompt();
	prompt.addToHistory(prompt.getLine());
	prompt.replace(line);
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

// OLD
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
			s32 cursor_len = prompt.getCursorLength();
			video::IVideoDriver* driver = Environment->getVideoDriver();
			s32 x = (1 + cursor_pos) * m_fontsize.X;
			core::rect<s32> destrect(
				x,
				y + m_fontsize.Y * (1.0 - m_cursor_height),
				x + m_fontsize.X * MYMAX(cursor_len, 1),
				y + m_fontsize.Y * (cursor_len ? m_cursor_height+1 : 1)
			);
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
		//std::wstring wrtext = .submit();
		//m_client->typeChatMessage(wide_to_narrow(wrtext));
		auto & prompt = m_chat_backend->getPrompt();
		prompt.addToHistory(prompt.getLine());
		m_client->typeChatMessage(wide_to_utf8(prompt.replace(L"")));

		if (m_close_on_enter) {
			closeConsole();
			//Environment->removeFocus(this);
		}

		return true;
	}
#endif
	return false;
}

bool GUIKmChat::OnEvent(const SEvent& event)
{

	ChatPrompt &prompt = m_chat_backend->getPrompt();

	if(event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown)
	{
		KeyPress kp(event.KeyInput);
		
		if ( (kp == EscapeKey || kp == CancelKey) && ((int)event.KeyInput.Key == (int)event.KeyInput.Char) )
		{
			close();
			
			m_open_inhibited = 1; // so the ESCAPE button doesn't open the "pause menu"
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
			prompt.addToHistory(prompt.getLine());
			std::wstring text = prompt.replace(L"");
			m_client->typeChatMessage(wide_to_utf8(text));
			
			close();
			return true;
		}
		else if(event.KeyInput.Key == KEY_UP && event.KeyInput.Char == 0)
		{
			// Up pressed
			// Move back in history
			prompt.historyPrev();
			return true;
		}
		else if(event.KeyInput.Key == KEY_DOWN && event.KeyInput.Char == 0)
		{
			// Down pressed
			// Move forward in history
			prompt.historyNext();
			return true;
		}
		else if((event.KeyInput.Key == KEY_LEFT || event.KeyInput.Key == KEY_RIGHT) && event.KeyInput.Char == 0)
		{
			// Left/right pressed
			// Move/select character/word to the left depending on control and shift keys
			ChatPrompt::CursorOp op = event.KeyInput.Shift ?
				ChatPrompt::CURSOROP_SELECT :
				ChatPrompt::CURSOROP_MOVE;
			ChatPrompt::CursorOpDir dir = event.KeyInput.Key == KEY_LEFT ?
				ChatPrompt::CURSOROP_DIR_LEFT :
				ChatPrompt::CURSOROP_DIR_RIGHT;
			ChatPrompt::CursorOpScope scope = event.KeyInput.Control ?
				ChatPrompt::CURSOROP_SCOPE_WORD :
				ChatPrompt::CURSOROP_SCOPE_CHARACTER;
			prompt.cursorOperation(op, dir, scope);
			return true;
		}
		else if(event.KeyInput.Key == KEY_HOME && event.KeyInput.Char == 0)
		{
			// Home pressed
			// move to beginning of line
			prompt.cursorOperation(
				ChatPrompt::CURSOROP_MOVE,
				ChatPrompt::CURSOROP_DIR_LEFT,
				ChatPrompt::CURSOROP_SCOPE_LINE);
			return true;
		}
		else if(event.KeyInput.Key == KEY_END && event.KeyInput.Char == 0)
		{
			// End pressed
			// move to end of line
			prompt.cursorOperation(
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
			prompt.cursorOperation(
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
			prompt.cursorOperation(
				ChatPrompt::CURSOROP_DELETE,
				ChatPrompt::CURSOROP_DIR_RIGHT,
				scope);
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_A && event.KeyInput.Control)
		{
			// Ctrl-A pressed
			// Select all text
			prompt.cursorOperation(
				ChatPrompt::CURSOROP_SELECT,
				ChatPrompt::CURSOROP_DIR_LEFT, // Ignored
				ChatPrompt::CURSOROP_SCOPE_LINE);
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_C && event.KeyInput.Control)
		{
			// Ctrl-C pressed
			// Copy text to clipboard
			if (prompt.getCursorLength() <= 0)
				return true;
			std::wstring wselected = prompt.getSelection();
/*
			std::string selected(wselected.begin(), wselected.end());
*/
			auto selected = wide_to_utf8(wselected);

			Environment->getOSOperator()->copyToClipboard(selected.c_str());
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_V && event.KeyInput.Control)
		{
			// Ctrl-V pressed
			// paste text from clipboard
			if (prompt.getCursorLength() > 0) {
				// Delete selected section of text
				prompt.cursorOperation(
					ChatPrompt::CURSOROP_DELETE,
					ChatPrompt::CURSOROP_DIR_LEFT, // Ignored
					ChatPrompt::CURSOROP_SCOPE_SELECTION);
			}
			IOSOperator *os_operator = Environment->getOSOperator();
			const c8 *text = os_operator->getTextFromClipboard();
			if (!text)
				return true;

			prompt.input(utf8_to_wide(std::string(text)));

/*
			std::basic_string<unsigned char> str((const unsigned char*)text);
			prompt.input(std::wstring(str.begin(), str.end()));
*/
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_X && event.KeyInput.Control)
		{
			// Ctrl-X pressed
			// Cut text to clipboard
			if (prompt.getCursorLength() <= 0)
				return true;
			std::wstring wselected = prompt.getSelection();
			std::string selected(wselected.begin(), wselected.end());
			Environment->getOSOperator()->copyToClipboard(selected.c_str());
			prompt.cursorOperation(
				ChatPrompt::CURSOROP_DELETE,
				ChatPrompt::CURSOROP_DIR_LEFT, // Ignored
				ChatPrompt::CURSOROP_SCOPE_SELECTION);
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_U && event.KeyInput.Control)
		{
			// Ctrl-U pressed
			// kill line to left end
			prompt.cursorOperation(
				ChatPrompt::CURSOROP_DELETE,
				ChatPrompt::CURSOROP_DIR_LEFT,
				ChatPrompt::CURSOROP_SCOPE_LINE);
			return true;
		}
		else if(event.KeyInput.Key == KEY_KEY_K && event.KeyInput.Control)
		{
			// Ctrl-K pressed
			// kill line to right end
			prompt.cursorOperation(
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
			prompt.nickCompletion(names, backwards);
			return true;
		}
		else if(event.KeyInput.Char != 0 && !event.KeyInput.Control)
		{
			#if (defined(linux) || defined(__linux) || defined(__FreeBSD__)) and IRRLICHT_VERSION_10000 < 10900
				wchar_t wc = L'_';
				mbtowc( &wc, (char *) &event.KeyInput.Char, sizeof(event.KeyInput.Char) );
				prompt.input(wc);
			#else
				prompt.input(event.KeyInput.Char);
			#endif
			return true;
		}
		//kmfreeminer
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

void GUIKmChat::setVisible(bool visible)
{
	m_open = visible;
	IGUIElement::setVisible(visible);
	if (!visible) {
		m_height = 0;
		recalculateKmChatPosition();
	}
}

