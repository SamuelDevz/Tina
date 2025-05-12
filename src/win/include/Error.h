#pragma once

#include "Types.h"
#include "Export.h"

namespace Luna
{
    class DLL Error
    {
    private:
        int32 hrCode;
        string funcName;
        string fileName;
        int32 lineNum;
        
    public:
        Error() noexcept;
        Error(const int32 hr, 
            const string_view func, 
            const string_view file, 
            const int32 line) noexcept;            
        string ToString() const;
    };

    #ifndef ThrowIfFailed
    #define ThrowIfFailed(x)                                               \
    {                                                                      \
        int32 hr = (x);                                                    \
        if(FAILED(hr)) { throw Error(hr, __func__, __FILE__, __LINE__); }  \
    }
    #endif
}