#ifndef GUIKmChat_HEADER
#define GUIKmChat_HEADER

#include "irrlichttypes_extrabloated.h"
#include "chat.h"
#include "config.h"

#include "xCGUITTFont.h"

class Client;

class GUIKmChat : public gui::IGUIElement
{
public:
	GUIKmChat(gui::IGUIEnvironment* env,
			gui::IGUIElement* parent,
			s32 id,
			ChatBackend* backend,
			Client* client);
	virtual ~GUIKmChat();

	// Open the console (height = desired fraction of screen size)
	// This doesn't open immediately but initiates an animation.
	// You should call isOpenInhibited() before this.
	void open();

	bool isOpen() const;

	// Check if the console should not be opened at the moment
	// This is to avoid reopening the consol`e immediately after closing
	bool isOpenInhibited() const;
	// Close the console, equivalent to openConsole(0).
	// This doesn't close immediately but initiates an animation.
	void close();
	// Close the console immediately, without animation.

	// Change how the cursor looks
	void setCursor(
		bool visible,
		bool blinking = false,
		f32 blink_speed = 1.0,
		f32 relative_height = 1.0);

	void setPrompt(const std::wstring& input);

	// Irrlicht draw method
	virtual void draw();

	bool canTakeFocus(gui::IGUIElement* element) { return false; }

	bool getAndroidUIInput();

	virtual bool OnEvent(const SEvent& event);

private:
	void reformatChat();
	void recalculateKmChatPosition();

    void setFont(int font_size);
    void setRows(int rows);
    
	// These methods are called by draw
	void animate(u32 msec);
    
    void drawMessageText();
    
	void drawBackground();
	void drawPrompt();
    
    void drawNewMessageText();

	virtual void setVisible(bool visible);
private:
	// pointer to the chat backend
	ChatBackend* m_chat_backend;

	// pointer to the client
	Client* m_client;

	// current screen size
	v2u32 m_screensize;

	// used to compute how much time passed since last animate()
	u32 m_animate_time_old;

	// should the console be opened or closed?
	bool m_open;
	// close console on return or not
	bool m_close_on_return;
    
    // current console height [rows]
	s32 m_rows;
    
	// current console height [pixels]
	s32 m_height;
    
	// current console width [pixels]
	s32 m_width;
    
    // current console width [pixels]
	s32 m_top_indent;
    
	// if nonzero, opening the console is inhibited [milliseconds]
	u32 m_open_inhibited;

	// cursor blink frame (16-bit value)
	// cursor is off during [0,32767] and on during [32768,65535]
	u32 m_cursor_blink;
	// cursor blink speed [on/off toggles / second]
	f32 m_cursor_blink_speed;
	// cursor height [line height]
	f32 m_cursor_height;

	// background texture
	video::ITexture* m_background;
	// background color (including alpha)
	video::SColor m_background_color;

	// font
	gui::IGUIFont* m_font;
	v2u32 m_fontsize;
};


#endif

