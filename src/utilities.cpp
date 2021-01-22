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

std::vector <process_stats> stats;
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

	//clears vector and opens file
	stats.clear();
	ifstream file;
	file.open(filename);

	//if file is open, enter if block
	if (file.is_open()) {

		string line;
		while (getline(file, line)) {

			//if ignoreFirstRow == true then discard the first row
			//else move to while loop
			if (ignoreFirstRow) {
				ignoreFirstRow = false;
			} else {

				string str;
				vector<string> temp;
				stringstream stream(line);

				while (getline(stream, str, CHAR_TO_SEARCH_FOR)) {
					temp.push_back(str);
				}

				//checks size of temp to be exactly 4
				if (temp.size() == 4) {

					// if there is no space or a space, process stat
					if ((count(temp.begin(), temp.end(), "")) == 0 &&
							(count(temp.begin(), temp.end(), " ")) == 0) {
						process_stats stat;
						stat.process_number = stoi(temp[0]);
						stat.start_time = stoi(temp[1]);
						stat.cpu_time = stoi(temp[2]);
						stat.io_time = stoi(temp[3]);
						stats.push_back(stat);
					}
				}
			}
		}
	//file not open, return could not open
	} else {
		return COULD_NOT_OPEN_FILE;
	}

	//close file and return success when done
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
			sort(stats.begin(), stats.end(), cpuSort);
			break;

		case PROCESS_NUMBER:
			sort(stats.begin(), stats.end(), processNumSort);
			break;

		case IO_TIME:
			sort(stats.begin(), stats.end(), ioTimeSort);
			break;

		case START_TIME:
			sort(stats.begin(), stats.end(), startTimeSort);
			break;

		default:
			break;
	}
}

//return the first struct in the vector
//then deletes it from the vector
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


