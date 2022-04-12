#pragma once
#include "utils.h"
#include "KeyNav.h"
#include "Scheduler.h"
#include "Pairings.h"
#include "Parameters.h"
#include "playground.h"

int mainMenu();
std::string selectPairings();
std::string selectParams();

using namespace std;

int main() {
    playground();

    /*std::cout << "Class Grouping Project v0.0.1!\n";

    std::string paramFile;
    std::string pairFile;

    cin >> paramFile;
    cin >> pairFile;
    CSV pairCSV(pairFile);

    Pairings pairObj(pairCSV);
    Parameters paramObj(paramFile);

    bool menu = true;
    while(menu = true){


    }


}