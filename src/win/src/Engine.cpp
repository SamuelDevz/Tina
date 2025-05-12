#include "Engine.h"
#include "KeyCodes.h"
#include "WinInclude.h"
#include <windows.h>
#include <timeapi.h>
#include <format>
using std::format;

namespace Luna 
{
    Window*   Engine::window    = nullptr;
    Input*    Engine::input     = nullptr;
    Game*     Engine::game      = nullptr;
    double    Engine::frameTime = {};
    bool      Engine::paused    = false;
    Timer     Engine::timer;

    Engine::Engine() noexcept
    {
        window = new Window();
    }

    Engine::~Engine() noexcept
    {
        delete game;
        delete input;
        delete window;
    }

    int Engine::Start(Game * game)
    {
        this->game = game;

        window->Create();

        input = new Input();

        SetWindowLongPtr(window->Id(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(EngineProc));

        timeBeginPeriod(1);

        int exitCode = Loop();

        timeEndPeriod(1);

        return exitCode;
    }

    double Engine::FrameTime()
    {
    #ifdef _DEBUG
        static double totalTime{};
        static uint32 frameCount{};
    #endif

        frameTime = timer.Reset();

    #ifdef _DEBUG
        totalTime += frameTime;

        frameCount++;

        if (totalTime >= 1.0)
        {
            SetWindowText(window->Id(), 
                format("{}    FPS: {}    Frame Time: {:.3f} (ms)",
                    window->Title().c_str(), frameCount, frameTime * 1000).c_str()
            );

            frameCount = 0;
            totalTime -= 1.0;
        }
    #endif

        return frameTime;
    }

    int Engine::Loop()
    {
        timer.Start();
        MSG msg{};

        game->Init();

        do
        {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                if (input->KeyPress(VK_PAUSE))
                    (paused) ? Resume() : Pause();

                if (!paused)
                {
                    frameTime = FrameTime();
                    game->Update();
                    game->Draw();
                }
                else
                {
                    game->OnPause();
                }
            }
        } while (msg.message != WM_QUIT);

        game->Finalize();    

        return int32(msg.wParam);
    }

    LRESULT CALLBACK Engine::EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (msg == WM_PAINT)
            game->Display();

        return CallWindowProc(Input::InputProc, hWnd, msg, wParam, lParam);
    }
}