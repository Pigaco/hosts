#include <iostream>
#include <string>
#include <bitset>

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

bool readCommand(int playerCount) {
    bool success = false;

    char buffer[1];
    buffer[0] = 0;
    bool read;
    int code = 0;
    for(int i = 0; i < playerCount; ++i) {
        code = getPlayerMgr()->read(buffer, 1, read, i);
        cout << "Reading Player " << i << " (Success: " << read << "; code: " << code
             << "). Binary Data: " << std::bitset<8>(buffer[0]) << ", decimal data: " << buffer[0] << endl;

        if(read) {
            success = true;
        }
    }

    return success;
}

int main()
{
    int playerCount = 2;

    init(playerCount);

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
        } else if(input == "rd") {
            readCommand(playerCount);
        } else if(input == "rei") {
            cout << "Destroying the host and re-initializing everything. " << endl;
            destroy();
            init(playerCount);
        } else if(input == "rdl") {
            while(readCommand(playerCount));
        } else if(input == "hel") {
            getPlayerMgr()->sendHello(-1, true);
        }
    }

    destroy();

    return 0;
}
