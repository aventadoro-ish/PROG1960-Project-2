#pragma once
#include "utils.h"
#include "KeyNav.h"
#include "Scheduler.h"
#include "Pairings.h"
#include "Parameters.h"

int mainMenu();
std::string selectPairings();
std::string selectParams();

using namespace std;

int main() {
    std::cout << "Class Grouping Project v0.0.1!    ------ Use Arrow Keys To Navigate & Enter To Select\n";
    int menu = 0;


    CSV parFile;
    Pairings parings;
    //parFile = CSV(selectPairings());
    //parings = Pairings(parFile);
    while (menu == 0) {
        switch (mainMenu()) {
        case 1:
            //Generate Schedule
            break;
        case 2:
            clearEx(3);
            parFile = CSV(selectPairings());
            parings.~Pairings();
            parings = Pairings(parFile);
            break;
        case 3:
            parings.editor();
            break;
        case 4:
            selectParams();
        case 5:
            //Edit Param List
            break;
        case -1:
            menu = -1;
            break;

        }
    }
}

int mainMenu() {
    int cmd = 0;
    clearEx(3);
    std::cout << "1. Generate Schedule\n";
    std::cout << "2. Change Event File\n";
    std::cout << "3. Edit Event List\n";
    std::cout << "\n";
    std::cout << "5. Edit Parameters List\n";
    KeyNav cursor(0, 3);
    while (cmd == 0) {
        cmd = cursor.menuKeyParser(_getch());
    }
    if (cmd == 2) {
        return -1;
    }
    return (cursor.getCursY() - 2);

}
std::string selectPairings() {
    std::string usrFile;
    int cmd = 0;
    clearEx(3);
    std::cout << "parings_example.csv\n";
    std::cout << "Events2.csv\n";
    std::cout << "Events3.csv\n";
    std::cout << "Events4.csv\n";
    std::cout << "Events5.csv\n";
    std::cout << "Enter File Ext.\n";
    KeyNav cursor(0, 3);
    while (cmd == 0) {
        cmd = cursor.menuKeyParser(_getch());
    }
    switch (cursor.getCursY() - 2) {
    case 1:
        return "parings_example.csv";
    case 2:
        return "Events2.csv";
    case 3:
        return "Events3.csv";
    case 4:
        return "Events4.csv";
    case 5:
        return "Events5.csv";
    case 6:
        moveCursor(0, 10);
        cin >> usrFile;
        return usrFile;
    }
}
std::string selectParams() {
    std::string usrFile;
    int cmd = 0;
    clearEx(3);
    std::cout << "param_example.csv\n";
    std::cout << "Parm2.csv\n";
    std::cout << "Parm3.csv\n";
    std::cout << "Parm4.csv\n";
    std::cout << "Parm5.csv\n";
    std::cout << "Enter File Ext.\n";
    KeyNav cursor(0, 3);
    while (cmd == 0) {
        cmd = cursor.menuKeyParser(_getch());
    }
    switch (cursor.getCursY() - 2) {
        case 1:
            return "param_example.csv";
        case 2:
            return "Parm2.csv";
        case 3:
            return "Parm3.csv";
        case 4:
            return "Parm4.csv";
        case 5:
            return "Parm5.csv";
        case 6:
            moveCursor(0, 10);
            cin >> usrFile;
            return usrFile;
        }
}