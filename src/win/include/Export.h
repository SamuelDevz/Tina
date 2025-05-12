#pragma once

#if defined(ENGINE_EXPORTS)
    #define DLL __declspec(dllexport)
#else
    #if defined(EXPORT)
        #define DLL __declspec(dllimport)
    #else
        #define DLL
    #endif
#endif

// disables dll-interface message for STL members
#pragma warning(disable: 4251)