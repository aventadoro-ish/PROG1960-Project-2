#pragma once
#include "utils.h"
#include "KeyNav.h"
#include "Scheduler.h"

int mainMenu();
std::string selectPairings();
std::string selectParams();

using namespace std;

int main() {
    std::cout << "Class Grouping Project v0.0.1!\n";

    CSV pairs(selectPairings());
    CSV params(selectParams());

        mainMenu();




    //}




}
int mainMenu() {
    int cmd = 0;
    clearEx(3);
    std::cout << "1. Import CSV\n";
    std::cout << "2. Generate Schedule\n";
    std::cout << "3. View Event List\n";
    std::cout << "4. Edit Event List\n";
    std::cout << "5. View Parameters List\n";
    std::cout << "6. Edit Parameters List\n";
    KeyNav cursor(0, 3);
    while (cmd == 0) {
        cmd = cursor.menuKeyParser(_getch());
    }
    switch (cursor.getCursY() - 3) {
    case 1:
        //Change CSV
        return 1;
    case 2:
        //Generate Schedule
        return 2;
    case 3:
        //View Event List
        return 3;
    case 4:
        //Edit Event List
    case 5:
        //View Parameters List
        break;
    case 6:
        //Edit Parameters List
        break;
    }
}
std::string selectPairings() {
    std::string usrFile;
    int cmd = 0;
    clearEx(3);
    std::cout << "Events1.csv\n";
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
        return "Events 1.csv";
    case 2:
        return "Events2.csv";
    case 3:
        return "Events3.csv";
    case 4:
        return "Events4.csv";
    case 5:
        return "Events5.csv";
    case 6:
        cin >> usrFile;
        return usrFile;
    }
}
std::string selectParams() {
    std::string usrFile;
    int cmd = 0;
    clearEx(3);
    std::cout << "Parm1.csv\n";
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
            return "Parm1.csv";
        case 2:
            return "Parm2.csv";
        case 3:
            return "Parm3.csv";
        case 4:
            return "Parm4.csv";
        case 5:
            return "Parm5.csv";
        case 6:
            cin >> usrFile;
            return usrFile;
        }
}