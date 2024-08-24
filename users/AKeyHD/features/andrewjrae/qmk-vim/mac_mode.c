#include "mac_mode.h"

#ifdef QMK_VIM_FOR_ALL

// When QMK_VIM_FOR_ALL is enabled, we allow the user to choose if mac support is enabled at startup or not
#    ifdef QMK_VIM_FOR_MAC
bool vim_for_mac = true;
#    else
bool vim_for_mac = false;
#    endif

#endif
