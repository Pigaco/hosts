#include <iostream>
#include <string>

#include "../host.h"
#include <main.hpp>
#include <buttons.hpp>
#include <PlayerManager.hpp>

using std::cout;
using std::endl;
using std::cin;

int init(int playerCount);
int destroy();

#define HELPTEXT "q   exit the program \n" \
    "h   this help text\n" \
    "led <player> <number> <intensity> set led level \n" \
    "inp print inputs.\n"

int main()
{
    init(2);

    bool end = false;
    std::string input;

    while(!end) 
    {
        cout << ">> ";
        cin >> input;
        cout << "COMMAND: \"" << input << "\"" << endl;

        if(input == "q" || input == "quit" || input == "exit") {
            end = true;
        } else if(input == "h" || input == "?" || input == "help") {
            cout << HELPTEXT << endl;
        } else if(input == "tst") {
            cout << "Sending TEST (Hello) packet" << endl;
            char hello[1];
            hello[0] = 2;
            getPlayerMgr()->send(hello, 1);
        }
    }

    destroy();

    return 0;
}
