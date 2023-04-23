/*Author: Li Pintar
* Date: 04/21/2023
* Course: CS-300
* 
* This program reads course data from a file, parses the information, creates a sample schedule, and displays course information. 
* The data structure used for the course data is a binary search tree.
* 
*/

#include <iostream>
#include <String>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "BST.h"

using namespace std;

//prototypes 
bool validateFile(ifstream&);
void menu();
void loadData(ifstream&);
bool preRequIsValid(vector<string> , string);

//access binary search tree class
BinarySearchTree course;

int main()
{
	//course number 
	string courseNum;

	//user menu choice
	char userChoice;

	//file entered by user
	ifstream courseDataFile;

	userChoice = '0';

	cout << "Course Planner" << endl;

	cout << endl;

	//while user does not choose to exit program
	while (userChoice != '4') {

		//display menu
		menu();

		cout << endl;

		cout << "Enter menu choice: " << endl;

		//get menu choice from user
		cin >> userChoice;

		cin.ignore(1000, '\n');

		switch (userChoice) {
		//load data from file
		case '1':

			validateFile(courseDataFile);

			break;

		//print course list
		case '2':

			cout << endl;
			cout << "Sample Schedule: " << endl;
			cout << endl;

			course.InOrder();

			cout << endl;

			break;

		//print course selected by user
		case '3':

			cout << endl;
			cout << "Enter course number: ";

			cin >> courseNum;

			cout << endl;

			course.Search(courseNum);

			cout << endl;

			break;

		//exit program
		case '4':

			break;

		//user inputs something beyond the options presented
		default:

			cout << endl;
			cout << userChoice << " is not a valid option." << endl;
			cout << endl;

			break;

		}
	}

}

/*
* This function gets the file name from the user, opens the file, verifies that the files opens correctly, 
* and calls the load data function to load data into the binary search tree.
*/
bool validateFile(ifstream& userFile) {

	//name of course data file
	string fileName;

	//prompt user to enter file name
	cout << "\nEnter course data file name:" << endl;

	//get the name of the file from user
	cin >> fileName;

	//open file entered by user
	userFile.open(fileName.c_str());

	//if user file does not open
	if (userFile.fail()) {

		//display error message
		cout << "\nErrror: File " << fileName << " could not be opened." << endl;

		return 1;

	}

	//call function to load data structure
	loadData(userFile);	

	//close file
	userFile.close();

	return true;


}

/*
* This function displays the menu choices
*/
void menu() {

	cout << "1. Load Data Structure" << endl;

	cout << "2. Print Course List" << endl;

	cout << "3. Print Course Information" << endl;

	cout << "4. Exit" << endl;

}

/*
* This function reads the data from the file, ensures the data is valid, and inserts it into the binary search tree
*/
void loadData(ifstream& userFile) {

	string data;

	string thisCourse;

	vector<string> validCourses;


	//while the last line of the file has not been reached
	while (!userFile.fail()) {

		string token;

		stringstream ss(thisCourse);

		getline(userFile, thisCourse);

		//if a string is found
		if (getline(ss, token, ',')) {

			//push token to the back of vector of valid courses
			validCourses.push_back(token);	
		}

	}

	//read file from beginning
	userFile.clear();
	userFile.seekg(0, ios::beg);

	//while there are no errors while reading the file
	while (userFile.good()) {

		Course temp;

		getline(userFile, data);

		//if the end of the file has not been reached
		if (!data.empty()) {

			string token;	

			stringstream ss(data);

			//if a string is found
			if (getline(ss, token, ',')) {
				
				//course number is first segment of the parsed string
				temp.courseNumber = token;	

				//if a string is found
				if (getline(ss, token, ',')) {

					//course name is the next segment of the parsed string
					temp.courseName = token;	

					//while another parsed string segment is found
					while (getline(ss, token, ',')) {

						//if the prerequesite is valid
						if (preRequIsValid(validCourses, token) == true) {

							//push token to the back of this courses list of prerequisites
							temp.prerequisites.push_back(token);

						}
						else {

							continue;

						}

					}

				}

			}

		}

		//if course info has both a course namd and course number
		if (!temp.courseName.empty() && !temp.courseNumber.empty()) {
			
			//insert it into the binary search tree
			course.Insert(temp);

		}

	}



}

/*
* This function ensures prerequisites are valid courses
*/
bool preRequIsValid(vector<string> courses, string token) {

	//is the prerequisite a valid course
	bool courseIsValid = false;


	//ffor the size of courses lisr
	for (int currentCourse = 0; currentCourse < courses.size(); ++currentCourse) {

		//if token matches current course
		if (token.compare(courses.at(currentCourse)) == 0) {

			//prerequisie is a valid course
			courseIsValid = true;

			//return true
			return courseIsValid;

		}

	}

	//return false
	return courseIsValid;
}

