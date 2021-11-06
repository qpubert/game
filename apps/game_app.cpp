#include "game_lib/game.hpp"

#include <iostream>

using namespace std;

int main()
{
    try
    {
        Game game("This is my window title");
        game.run();
    }
    catch (std::exception const &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}