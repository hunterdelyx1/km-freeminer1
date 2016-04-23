#include "settings.h"

void set_km_default_settings(Settings *settings) {
	settings->setDefault("http_get_host", "");

	settings->setDefault("km_chat_rows", "20");
	settings->setDefault("km_chat_font_size", "26");
	
	settings->setDefault("km_chat_color", "(0,0,0)");
	settings->setDefault("km_chat_alpha", "180");
	
	settings->setDefault("km_chat_nmsg_time", "15.0");

}
