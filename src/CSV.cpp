#include "CSV.h"
#define NPOS -1

CSV::CSV(std::string fileExt) {
	fileName = fileExt;
}
CSV::~CSV() {}

std::string CSV::getFileName() { return fileName; }

std::string CSV::getArrVal(int x, int y) {
	return arr[x][y];
}
std::string* CSV::getRow(int x) {
	return arr[x];
}


bool CSV::initArr(std::ifstream& file) {
	int tempColCount = 1;
	std::string buffer;

	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "Error Opening File: " << fileName << std::endl;
		return false;
	}
	//Counting Rows & Columns
	while (!file.eof()){
		std::getline(file, buffer);
		if (!buffer.empty()) {
			for (int i = 0; i < buffer.size(); i++) {//Counts the # of columns
				if (buffer[i] == ',') {
					tempColCount++;
				}
			}
			if (colCount < tempColCount) colCount = tempColCount;
			rowCount++;
			buffer.erase();
			tempColCount = 0;
		}
	}
	colCount++;
	file.close();
	//Initializing 2D Array
	arr = new std::string * [rowCount];
	for (int i = 0; i < rowCount; i++) {
		arr[i] = new std::string[colCount];
	}

}

bool CSV::importCsv(){
	std::ifstream file;
	std::string buffer;
	int pos = 0;
	int ref = 0;


	if (initArr(file) == false) return false;

	file.open(fileName);

	for (int x = 0; x < rowCount; x++) {
		std::getline(file, buffer);

		//Detect Blank Lines
		if ((buffer.size() == 0)) {
			x--;
			continue;
		}
		//Import Info
		for (int y = 0; y < colCount; y++) {
			if ((pos = buffer.find_first_of(",")) != NPOS) {
				arr[x][y] = buffer.substr(0, pos);
				buffer.erase(0, pos + 1);
			}
			else if ((pos = buffer.size()) > 0) {
				arr[x][y] = buffer.substr(0, pos);
				buffer.erase(0, pos);
			}
			else {
				arr[x][y] = "";
			}

		}
	}
	file.close();
	}

	


	//for (int i = rowCount-1; i >= 0; i--) {
	//	delete[] arr[i];
	//}
	//delete[] arr;


void CSV::printArr() {
	try {
		for (int i = 0; i < rowCount; i++) {
			for (int ii = 0; ii < colCount; ii++){
				std::cout << arr[i][ii] << " ";
			}
			std::cout << std::endl;
		}
	}
	catch (...) {
		std::cout << "Array uninitialized.";
	}
}