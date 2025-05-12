#include "WinGame.h"

namespace Luna
{
    void WinGame::Init() 
    {
    }

    void WinGame::Update()
    {
        if (input->KeyDown(VK_ESCAPE))
            window->Close();
    } 

    void WinGame::Draw()
    {    
    } 

    void WinGame::Finalize()
    {
    }
}