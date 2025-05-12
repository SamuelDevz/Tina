#pragma once

#include "Window.h"
#include "Input.h"
#include "Export.h"

namespace Luna
{
    class DLL Game
    {
    protected:
        static Window*   & window;
        static Input*    & input;
        static double    & frameTime;

    public:
        Game() noexcept;
        virtual ~Game();

        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Finalize() = 0;

        virtual void Draw() {}
        virtual void Display() {}
        virtual void OnPause() { Sleep(10); }
    };
}