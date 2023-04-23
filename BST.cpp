#include <iostream>
#include <String>
#include <vector>
#include <iomanip>

#include "BST.h"

using namespace std;

//default constructor
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

//Destructor
BinarySearchTree::~BinarySearchTree() {

}

void BinarySearchTree::InOrder() {

	this->inOrder(root);

}

/*
* This function inserts nodes into the tree
*/
void BinarySearchTree::Insert(Course courses) {

	//if root equals null
	if (root == nullptr) {

		//root is new node courses
		root = new Node(courses);

	}
	//else if root is not null
	else {

		//add node to tree
		this->addNode(root, courses);

	}

}

/*
* This function adds nodes where the belong in the tree
*/
void BinarySearchTree::addNode(Node* node, Course courses) {

	//if course number of node is greater than course number
	if (node->courses.courseNumber.compare(courses.courseNumber) > 0) {

		//if left of node equals null
		if (node->left == nullptr) {

			//left node equals new code courses
			node->left = new Node(courses);

		}
		//else if left of node does not equal null
		else {

			//go down left side of tree
			this->addNode(node->left, courses);

		}

	}
	// else if courseNumber is not greater than node course number
	else {

		//if right of node equals null
		if (node->right == nullptr) {

			//right node equals new code courses
			node->right = new Node(courses);

		}
		//else if right of node does not equal null
		else {

			//go down right side of tree
			this->addNode(node->right, courses);

		}
	}
}

/*
* This function searches through the tree for a specific course
*/
void BinarySearchTree::Search(string num) {

	//current node equals root node
	Node* thisNode = root;

	//does the course exist in the tree already
	bool courseExists = false;

	//lower to upper
	for (int a = 0; a < 4; ++a) {

		num[a] = toupper(num[a]);

	}
	
	//while this node is null
	while (thisNode != nullptr) {

		//if course number number matches num
		if (thisNode->courses.courseNumber.compare(num) == 0) {

			//display course info
			cout << thisNode->courses.courseNumber << ", ";
			cout << thisNode->courses.courseName << endl;

			cout << "Prerequisites: ";
			for (int b = 0; b < thisNode->courses.prerequisites.size(); ++b) {

				cout << thisNode->courses.prerequisites.at(b);

				if (b != thisNode->courses.prerequisites.size() - 1) {

					cout << ", ";

				}

			}

			cout << endl;

			//course does exist
			courseExists = true;

			break;

		}

		//if the course number is less than the course number of the current node
		if (num.compare(thisNode->courses.courseNumber) < 0) { 

			//this node is now the left node of this node
			thisNode = thisNode->left;    

		}
		//else if the course number is greater than the course number of the current node
		else {  

			//this node is now the right node of this node
			thisNode = thisNode->right; 

		}

	}

	//print course not found message if course is not found
	if (courseExists == false) {

		cout << num << " not found" << endl;

	}


}


/*
* This function prints a course list in order
*/
void  BinarySearchTree::inOrder(Node* node) {

	//if node does not equal null
	if (node != nullptr) {

		//call function inOrder for left of node
		inOrder(node->left);

		//display course info
		cout << node->courses.courseNumber << ", ";
		cout << node->courses.courseName;
		cout << endl;

		//call function inOrder for right of node
		inOrder(node->right);

	}
}
