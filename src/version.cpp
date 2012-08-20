#include <znc/version.h>

#undef VERSION_EXTRA
#define VERSION_EXTRA "-alpha1"

#ifdef VERSION_EXTRA
const char* ZNC_VERSION_EXTRA = VERSION_EXTRA;
#else
const char* ZNC_VERSION_EXTRA = "";
#endif

