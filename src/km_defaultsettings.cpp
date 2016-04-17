#include "settings.h"

void set_km_default_settings(Settings *settings) {
    settings->setDefault("http_get_host", "");

    settings->setDefault("km_chat_height", "5");
    settings->setDefault("km_chat_width", "");
}
