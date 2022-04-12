#pragma once
#include "utils.h"
#include "KeyNav.h"
#include "Scheduler.h"
#include "Pairings.h"
#include "Parameters.h"
#include "playground.h"

int mainMenu();

using namespace std;

int main() {
	//playground();
	cout << "\n\n\n";
	return mainMenu();

}

int mainMenu() {
	// open params
	std::string paramFileName;
	
	
	for (;;) {
		try {
			cout << "Enter parameter filename: ";
			cin >> paramFileName;
			Parameters para = Parameters(paramFileName);
			break;


		} catch (const std::exception& e) {
			cout << e.what() << "\nRetry? (y/n) ";
			char c;
			cin >> c;
			if (!(c == 'y' || c == 'Y')) return 0;
			cin.ignore(1000, '\n');
		}
	}
	
	
	// open pairings
	std::string pairFile;
	{
		
		for (;;) {
			try {
				cout << "Enter pairings filename: ";
				cin >> pairFile;
				CSV pairCSV(pairFile);
				Pairings pairings = Pairings(pairCSV);
				break;


			} catch (const std::exception& e) {
				cout << e.what() << "\nRetry? (y/n) ";
				char c;
				cin >> c;
				if (!(c == 'y' || c == 'Y')) return 0;
				cin.ignore(1000, '\n');
			}
		}
	}

	clearEx(3);
	Parameters para1 = Parameters(paramFileName);
	clearEx(3);
	CSV pairCSV1(pairFile);
	Pairings pairings1 = Pairings(pairCSV1);

	clearEx(0);
	cout << "\n\n\n";
	cout << "Edit parameters?\n\n1. Yes\n2. No ";
	int editSel;
	cin >> editSel;
	cin.ignore(1000, '\n');
	if (editSel == 1) {
		while (para1.editor());
	}

	clearEx(3);
	cout << "Edit events?\n\n1. Yes\n2. No\n\n";
	cin >> editSel;
	cin.ignore(1000, '\n');
	if (editSel == 1) {
		while (pairings1.editor());
	}
	



	

	clearEx(3);
	cout << "How many schedule variants to output? (recomended 1-4) ";
	int scheduleVariants;
	cin >> scheduleVariants;

	Scheduler sch = Scheduler(&para1);
	Event** evts = pairings1.getEventListPtr();
	for (int i = 0; i < pairings1.getNEvents(); i++) {
		sch.appendEvent(*evts[i]);
	}
	sch.setErrorStream(std::cout);

	sch.validateInput();

	sch.syncAttendantReferences();

	for (int i = 0; i < scheduleVariants; i++) {
		sch.generateSchedule(1);
	}
	





	return 0;
}
