#ifndef _CONSTANTS_H_
#define _COSNTANTS_H_

#define ENGINE_NAME "Citadel"
#define ENGINE_VERSION_MAJOR 0
#define ENGINE_VERSION_MINOR 0
#define ENGINE_VERSION_PATCH 1
#define ENGINE_VERSION_TAG "-beta"

#define MACROTOSTRING(x) #x
#define TOSTRING(x) MACROTOSTRING(x)

#define ENGINE_VERSION TOSTRING(ENGINE_VERSION_MAJOR) "." TOSTRING(ENGINE_VERSION_MINOR) "." TOSTRING(ENGINE_VERSION_PATCH) ENGINE_VERSION_TAG

#endif