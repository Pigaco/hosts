#include <iostream>
#include <string>
#include <bitset>

#include "../host.h"
#include <main.hpp>
#include <buttons.hpp>
#include <PlayerManager.hpp>
#include <QSerialPortInfo>
#include <QCoreApplication>

using std::cout;
using std::endl;
using std::cin;

int init(int playerCount);
int destroy();

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

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    int playerCount = 2;

    cout << "Arduino Debugger" << endl;
    cout << "================" << endl;
    cout << " q     exit" << endl;
    cout << " tst   send test (hello) packet without check" << endl;
    cout << " rd    try to read one byte from all players" << endl;
    cout << " rdl   read as long as data (!= 0) is coming" << endl;
    cout << " hel   send a hello packet to every player and check" << endl;
    cout << " rdy   print the READY state of all players" << endl;
    cout << " rei   re-initialize the host (fast restart)" << endl;
    cout << " dbg   turn debug on/off (prints every received packet)" << endl;
    cout << " spl   lists all available serial ports through QSerialPortInfo::availablePorts" << endl << endl;
    cout << "Compiled with piga host library version " << HOST_VERSION_MAJOR
         << "." << HOST_VERSION_MINOR << "." << HOST_VERSION_MINI << endl << endl;

    init(playerCount);

    bool end = false;
    std::string input;

    while(!end) 
    {
        app.processEvents();
        cout << ">> ";
        std::cin.clear();
        std::getline(cin, input);
        cout << "COMMAND: \"" << input << "\"" << endl;

        if(input == "q" || input == "quit" || input == "exit") {
            end = true;
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
        } else if(input == "dbg") {
            cout << "Toggle Debug from " << Arduino::debug << " to " << !Arduino::debug << endl;
            Arduino::debug = !Arduino::debug;
        } else if(input == "rdy") {
            getPlayerMgr()->printReady();
        } else if(input == "spl") {
            QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
            cout << "Available Serial Ports:" << endl;
            for(QSerialPortInfo &port : availablePorts)
            {
                cout << "  - \"" << port.portName().toStdString() << "\" (\"" << port.systemLocation().toStdString() << "\")" << endl;
            }
        }
    }

    destroy();

    return 0;
}
