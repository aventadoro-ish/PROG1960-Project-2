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

}