#include "../headers/bmpLoader.h"
#include "../headers/windowManager.h"
#include <iostream>

int main()
{

    Window* window = new Window();


    bool running = true;

    while (running)
    {
        if (!window->ProcessMessages())
        {
            std::cout << "Closing window!";
            running = false;
        }


        Sleep(10);
    }





    delete window;


    return 0;
}



