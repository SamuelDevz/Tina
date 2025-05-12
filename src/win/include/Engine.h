#pragma once

#include "Export.h"
#include "Window.h"
#include "Input.h"
#include "Timer.h"
#include "Game.h"

namespace Luna
{
    class DLL Engine
    {
    private:
        static Timer timer;
        static bool paused;

        double FrameTime();
        int Loop();

    public:
        static Window*   window;
        static Input*    input;
        static Game*     game;
        static double    frameTime;

        Engine() noexcept;
        ~Engine() noexcept;

        int Start(Game * game);
        
        static void Pause() noexcept;
        static void Resume() noexcept;

        static LRESULT CALLBACK EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    };

    inline void Engine::Pause() noexcept
    { paused = true; timer.Stop(); }

    inline void Engine::Resume() noexcept
    { paused = false; timer.Start(); }
}