#pragma once
#include "Engine.hpp"
#include "InGameState.hpp"

int main()
{   

    Engine eng;
    State* initState = new InGameState();
    eng.PushState(initState);
    while (eng.IsRunning())
    {
        eng.Update();
    }
    
    return 0;
}