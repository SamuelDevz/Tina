#include "All.h"

namespace Luna
{
    class WinGame : public Game
    {
    public:
        void Init() override;
        void Update() override;
        void Draw() override;
        void Finalize() override;
    };
}