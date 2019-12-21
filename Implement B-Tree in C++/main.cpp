//Thuy Nguyen 1834037 - cosc3478
//coding base on Malik's Book

#include <iostream>
#include <string>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

 
class bTreeNode
{
public:
	int bTreeOrder; //degree
	int recCount; //number of num put into the tree
	int *list; //array hold the list number of a node
	bTreeNode **children; // array hold addresses of list children
	bTreeNode(int order);
	friend class bTree;
};
bTreeNode::bTreeNode(int t)
{
	bTreeOrder = t;
	list = new int [2 * t - 1];
	children = new bTreeNode *[2 * t];
	recCount = 0;
}
 
class bTree
{
	bTreeNode *root;
	int t;
public:
	bool search(const int& searchItem);
	void insert(const int& insertItem);
	void inOrder(ofstream &ofs);
	void printLevel(int level, ofstream &ofs);
	bTree(int _t)
	{
		root = NULL; t = _t;
	}
	int level(const int& searchItem);
	int treeHeight();
private:
	void searchNode(bTreeNode *current, const int& item, bool& found, int& location);
	void insertBTree(bTreeNode  *current, const int& insertItem, int& median, bTreeNode * &rightChild, bool& isTaller);
	void insertNode(bTreeNode  *current,const int& insertItem,bTreeNode * &rightChild,int insertPosition);
	void splitNode(bTreeNode  *current,const int& insertItem,bTreeNode * rightChild,int insertPosition,bTreeNode * &rightNode,int &median);
	void recInorder(bTreeNode  *current, ofstream &ofs);
	void recPrintLevel(bTreeNode  *current, int levelExpected, ofstream &ofs);
	void recTreeHeight(bTreeNode *current, int &height);
};

//search function------------------------------------------------------
bool bTree::search(const int& searchItem)
{
	bool found = false;
	int location;
	bTreeNode  *current;
	current = root;
	while (current != NULL && !found)
	{
		searchNode(current, searchItem, found, location);

		if (!found)
		{
			current = current->children[location];
		}
	}
	return found;
} //end search

//return level of node---------------------------------------------------
int bTree::level(const int& searchItem)
{
	bool found = false;
	int location;
	int level = 1;
	bTreeNode  *current;
	current = root;
	while (current != NULL && !found)
	{
		searchNode(current, searchItem, found, location);

		if (!found)
		{
			//move to next child, then level increases
			current = current->children[location]; level++;
		}
	}
	return level;
} //end level

 
void bTree::searchNode (bTreeNode *current, const int& item, bool& found, int& location)
{
	location = 0;

	while (location < current->recCount && item > current->list[location])
		location++;
	if (location < current->recCount && item == current->list[location])
		found = true;
	else
		found = false;
} //end searchNode

//insert number into the tree------------------------------------------ 
void bTree::insert(const int& insertItem)
{
	bool isTaller = false;
	int median;
	bTreeNode  *rightChild;
	insertBTree(root, insertItem, median, rightChild, isTaller);
	if (isTaller) //the tree is initially empty or the root
				  //was split by the function insertBTree
	{
		bTreeNode  *tempRoot;
		tempRoot = new bTreeNode(t) ;
		tempRoot->recCount = 1;
		tempRoot->list[0] = median;
		tempRoot->children[0] = root;
		tempRoot->children[1] = rightChild;

		root = tempRoot;
	}
} //insert
 
void bTree::insertBTree(bTreeNode  *current,const int& insertItem,int& median,bTreeNode * &rightChild,bool& isTaller)
{
	int position;
	isTaller = false;

	if (current == NULL)
	{
		median = insertItem;
		rightChild = NULL;
		isTaller = true;
	}
	else
	{
		bool found;
		searchNode(current, insertItem, found, position);
		if (found)
			return;
		else
		{
			int newMedian;

			bTreeNode  *newChild;

			insertBTree(current->children[position], insertItem,
				newMedian, newChild, isTaller);

			if (isTaller)
			{
				if (current->recCount < t - 1)
				{
					isTaller = false;
					insertNode(current, newMedian,
						newChild, position);
				}
				else
					splitNode(current, newMedian, newChild,
						position, rightChild, median);
			}
		}
	}
} //insertBTree

void bTree ::insertNode
(bTreeNode  *current,
	const int& insertItem,
	bTreeNode * &rightChild,
	int insertPosition)
{
	int index;

	for (index = current->recCount; index > insertPosition; index--)
	{
		current->list[index] = current->list[index - 1];
		current->children[index + 1] = current->children[index];
	}

	current->list[index] = insertItem;
	current->children[index + 1] = rightChild;
	current->recCount++;
} 

 
void bTree ::splitNode
(bTreeNode  *current,
	const int& insertItem,
	bTreeNode * rightChild,
	int insertPosition,
	bTreeNode * &rightNode,
	int &median)
{
	rightNode = new bTreeNode(t) ;

	int mid = (t - 1) / 2;

	if (insertPosition <= mid) //new item goes in the first
								  //half of the node
	{
		int index = 0;
		int i = mid;

		while (i < t - 1)
		{
			rightNode->list[index] = current->list[i];
			rightNode->children[index + 1] =
				current->children[i + 1];
			index++;
			i++;
		}

		current->recCount = mid;
		insertNode(current, insertItem, rightChild,
			insertPosition);
		(current->recCount)--;

		median = current->list[current->recCount];

		rightNode->recCount = index;
		rightNode->children[0] =
			current->children[current->recCount + 1];
	}
	else //new item goes in the second half of the node
	{
		int i = mid + 1;
		int index = 0;

		while (i < t - 1)
		{
			rightNode->list[index] = current->list[i];
			rightNode->children[index + 1] =
				current->children[i + 1];
			index++;
			i++;
		}

		current->recCount = mid;
		rightNode->recCount = index;

		median = current->list[mid];
		insertNode(rightNode, insertItem, rightChild,
			insertPosition - mid - 1);
		rightNode->children[0] =
			current->children[current->recCount + 1];
	}
} 
//return treeHeight-----------------------------------------------
int bTree::treeHeight()
{
	int height = 0;
	recTreeHeight(root, height);
	return height;
}
void bTree::recTreeHeight(bTreeNode *current, int &height)
{
	if (current != NULL)
	{
		recTreeHeight(current->children[0], height);

		for (int i = 0; i < current->recCount; i++)
		{
			if (level(current->list[i]) > height)
				height = level(current->list[i]);

			recTreeHeight(current->children[i + 1], height);
		}
	}
}
//print inorder traversal ----------------------------------------
void bTree::inOrder(ofstream &ofs)
{
	recInorder(root, ofs);
} // end inOrder
 
void bTree::recInorder(bTreeNode  *current, ofstream &ofs)
{
	if (current != NULL)
	{
		recInorder(current->children[0], ofs);

		for (int i = 0; i < current->recCount; i++)
		{
			ofs << current->list[i] << " ";

			recInorder(current->children[i + 1], ofs);
		}
	}
} //end recInorder

//print by level-------------------------------------------------------
void bTree::printLevel(int level, ofstream &ofs)
{
	recPrintLevel(root, level, ofs);
}
void bTree::recPrintLevel(bTreeNode  *current, int levelExpected, ofstream &ofs)
{
	if (current != NULL)
	{
		recPrintLevel(current->children[0], levelExpected, ofs);

		for (int i = 0; i < current->recCount; i++)
		{
			if (level(current->list[i])==levelExpected)
			{
				ofs << current->list[i] << " ";				 
			}
			recPrintLevel(current->children[i + 1], levelExpected, ofs);
		}
	}
} //end recPrintLevel

//return degree ---------------------------------------------------------
int readDegree(ifstream &ifs, string command)
{
	ifs.open(command);
	string line; int degree = 0;
	while (getline(ifs, line))
	{
		if (line.find("Degree") != string::npos)
		{
			degree = stoi(line.substr(line.find("=") + 1)); break;
		}
	}
	ifs.close();
	const int a = degree;
	return a;
}
//fill up the tree from input ----------------------------------------------
void readInput_intoTree(ifstream &ifs, string input, bTree &tree)
{
	ifs.open(input);
	int num;
	while (ifs >> num)
	{
		tree.insert(num);
	}
	ifs.close();
}

void printAll(ifstream &ifs, ofstream &ofs, string command, string output, bTree tree)
{
	string line; string temp; int num; 
	ifs.open(command); ofs.open(output);
	while (getline(ifs, line))
	{
		if (line.find("Inorder") != string::npos)
		{
			tree.inOrder(ofs);
			ofs << endl;
		}
		else if (line.find("Level") != string::npos)
		{
			num = stoi(line.substr(line.find("el") + 3));	
			if (num<1 || num>tree.treeHeight())
			{
				ofs << "empty" << endl;
			}
			else
			{
				tree.printLevel(num, ofs);
				ofs << endl;
			}		
		}
	}
}



//int main()
//{
//	string command = "command71.txt";
//	string input = "input71.txt";
//	string output = "aaa.txt";

	//============================================================
int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	ifstream ifs;
	ofstream ofs;
	int const &degree = readDegree(ifs, command);
	//cout << degree << endl;
	
	bTree b(degree);

	readInput_intoTree(ifs, input, b);

	//b.inOrder();
	printAll(ifs, ofs, command, output, b);


	//system("pause");
	return 0;
}