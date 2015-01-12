#ifndef FOUNDATION_SIMENGINE
#define FOUNDATION_SIMENGINE

#include <stdint.h>

#define SAFE_DELETE(a) { if( (a) != NULL ) { delete (a); (a) = NULL; } }

#endif // include guard