enum {
    STR_READY
};

#include "lang_en.h"
#include "lang_de.h"

I18n_register(I18n_getInstance(), Lang_EN);
I18n_register(I18n_getInstance(), Lang_DE);
