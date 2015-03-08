#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::_priv::displayMgr
    @ingroup _priv
    @brief private: create and manage the app window and GL context
    
    The display manager object manages application window and
    GL context creation, and usually processes host window system
    events (such as input events) and forwards them to Oryol.
*/
#if (ORYOL_WINDOWS || ORYOL_MACOS || ORYOL_LINUX)
#include "Gfx/glfw/glfwDisplayMgr.h"
namespace Oryol {
namespace _priv {
class displayMgr : public glfwDisplayMgr { };
} }
#elif ORYOL_EMSCRIPTEN
#include "Gfx/emsc/emscDisplayMgr.h"
namespace Oryol {
namespace _priv {
class displayMgr : public emscDisplayMgr { };
} }
#elif ORYOL_ANDROID
#include "Gfx/egl/eglDisplayMgr.h"
namespace Oryol {
namespace _priv {
class displayMgr : public eglDisplayMgr { };
} }
#elif ORYOL_IOS
#include "Gfx/ios/iosDisplayMgr.h"
namespace Oryol {
namespace _priv {
class displayMgr : public iosDisplayMgr { };
} }
#elif ORYOL_PNACL
#include "Gfx/pnacl/pnaclDisplayMgr.h"
namespace Oryol {
namespace _priv {
class displayMgr : public pnaclDisplayMgr { };
} }
#else
#include "Gfx/Core/displayMgrBase.h"
namespace Oryol {
namespace _priv {
class displayMgr : public displayMgrBase { };
} }
#endif
 