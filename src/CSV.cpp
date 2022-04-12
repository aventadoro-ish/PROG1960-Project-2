#include "CSV.h"
#define NPOS -1
#define BLANK_LINE buffer.find_first_not_of(' ', ref) == NPOS
#define LAST_CELL 2

CSV::CSV() {
	fileName = "NO FILE NAME ASSIGNED";
}

CSV::CSV(std::string fileExt) {

	setFileName(fileExt);
	importCSV();
}

CSV::~CSV() {

	delete[] arr;
}


std::string CSV::getFileName() { return fileName; }

std::string CSV::getArrVal(int x, int y) {
	return arr[x][y];
}

std::string* CSV::getRowData(int x) {
	return arr[x];
}
int CSV::getRowCount()const { return rowCount; }
int CSV::getColCount()const { return colCount; }

void CSV::setFileName(std::string newName) {
	std::ifstream file;

	file.open(newName);
	if (file.is_open()) {
		fileName = newName;
		file.close();
	}
	else {
		std::cout << "Error Opening File: " << fileName << std::endl;
	}
}
void CSV::setRowCount(int x) { rowCount = x; }
void CSV::setColCount(int y) { colCount = y; }
void CSV::setArrVal(int x, int y, std::string data) {
	arr[x][y] = data;
}

bool CSV::importCSV() {
	std::ifstream file;
	std::string buffer;
	std::string temp;
	int pos = 0;
	int ref = 0;
	int flag = 0;


	if (initArr(file) == false) return false;

	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "Error Opening File: " << fileName << std::endl;
		return false;
	}

	for (int x = 0; x < rowCount; x++) {
		ref = 0;
		flag = 0;
		if (file.eof()) {
			//std::cout << "EOF!\n";
			break;
		}
		std::getline(file, buffer);
		//std::cout << x << ": " << buffer << " -> ";
		if (buffer.length() == 0) {
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
			//std::cout << arr[x][y] << ", ";
		}
		//std::cout << "\n\n";
	}
	file.close();
}

bool CSV::initArr(std::ifstream& file) {

	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "Error Opening File: " << fileName << std::endl;
		return false;
	}
	countArrDimensions(file);
	file.close();
	//Initializing 2D Array
	arr = new std::string * [rowCount];
	for (int i = 0; i < rowCount; i++) {
		arr[i] = new std::string[colCount];
	}
}
void CSV::countArrDimensions(std::ifstream& file) {
	int tempColCount = 1;
	std::string buffer;

	while (!file.eof()) {
		std::getline(file, buffer);
		if (!buffer.empty()) {
			for (int i = 0; i < buffer.size(); i++) {//Counts the # of columns
				if (buffer[i] == ',') {
					tempColCount++;
				}
			}
			if (colCount < tempColCount) colCount = tempColCount + 1;
			rowCount++;
			buffer.erase();
			tempColCount = 0;
		}
	}
}