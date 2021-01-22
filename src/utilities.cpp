/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

vector <process_stats> stats;
bool cpuSort (process_stats, process_stats);
bool processNumSort (process_stats, process_stats);
bool ioTimeSort (process_stats, process_stats);
bool startTimeSort (process_stats, process_stats);


//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {

	//open file
	ifstream file;
	file.open(filename);

	//create new string, temp vector, and clear stats
	string line;
	vector<string> temp;
	stats.clear();

	//check for open file
	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	//ignore first row
	if (ignoreFirstRow == true) {
		getline(file, line);
	}

	//begin to read file
	stringstream stream(line);
	string str;
	while (getline(file, line)) {
		while (getline(stream, str, CHAR_TO_SEARCH_FOR)) {
			temp.push_back(str);
		}
		//check size of vector to be 4
		if (temp.size() == 4) {
			if ((std::count(temp.begin(), temp.end(), "")) == 0 &&
					(std::count(temp.begin(), temp.end(), " ")) == 0) {
				process_stats stat;
				stat.process_number = stoi(temp[0]);
				stat.start_time = stoi(temp[1]);
				stat.cpu_time = stoi(temp[2]);
				stat.io_time = stoi(temp[3]);
				stats.push_back(stat);
			}
		}
	}

	file.close();
	return SUCCESS;
}

bool cpuSort (process_stats x, process_stats y) {
	return (x.cpu_time < y.cpu_time);
}

bool processNumSort (process_stats x, process_stats y) {
	return (x.process_number < y.process_number);
}

bool startTimeSort(process_stats x, process_stats y) {
	return (x.start_time < y.start_time);
}

bool ioTimeSort(process_stats x, process_stats y) {
	return (x.io_time < y.io_time);
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

	switch (mySortOrder) {

		case CPU_TIME:
			std::sort(stats.begin(), stats.end(), cpuSort);
			break;

		case PROCESS_NUMBER:
			std::sort(stats.begin(), stats.end(), processNumSort);
			break;

		case IO_TIME:
			std::sort(stats.begin(), stats.end(), ioTimeSort);
			break;

		case START_TIME:
			std::sort(stats.begin(), stats.end(), startTimeSort);
			break;
	}
}

process_stats getNext() {
	process_stats myFirst;
	myFirst = stats.front();
	stats.erase(stats.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}


