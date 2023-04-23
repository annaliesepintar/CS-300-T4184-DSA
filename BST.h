#ifndef _BST_H_
# define _BST_H_

#include <iostream>
#include <String>
#include <vector>

using namespace std;

struct Course {

	string courseName;
	string courseNumber;
	int numPrerequisites;
	vector<string> prerequisites;

	Course() {

		numPrerequisites = 0;

	}
};

struct Node {

	Course courses;
	Node* left;
	Node* right;

	Node() {

		left = nullptr;
		right = nullptr;

	}

	Node(Course aCourse) : Node() {

		courses = aCourse;

	}

};

class BinarySearchTree {

private:

	Node* root;
	void addNode(Node* node, Course courses);
	void inOrder(Node* node);

public:

	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Course courses);
	void Search(string courseNum);

};


#endif