#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<array>
#include"ArgumentManager.h"
using namespace std;

//quick sort
void swap(int *arr, int first, int second)
{
	int temp;
	temp = arr[first];
	arr[first] = arr[second];
	arr[second] = temp;
}
int partition_d(int *arr, int first, int last)
{
	int pivot;
	int index, smallIndex;
	swap(arr, first, (first + last) / 2);
	pivot = arr[first];
	smallIndex = first;
	for (index = first + 1; index <= last; index++)
		if (arr[index] > pivot)
		{
			smallIndex++;
			swap(arr, smallIndex, index);
		}
	swap(arr, first, smallIndex);
	return smallIndex;
}
void recQuickSort_d(int *arr, int first, int last)
{
	int pivotLocation;
	if (first < last)
	{
		pivotLocation = partition_d(arr, first, last);
		recQuickSort_d(arr, first, pivotLocation - 1);
		recQuickSort_d(arr, pivotLocation + 1, last);
	}
}
void quick_sort_d(int *arr, int len)
{
	recQuickSort_d(arr, 0, len - 1);
}
//////////////////////////////////////

int partition_a(int *arr, int first, int last)
{
	int pivot;
	int index, smallIndex;
	swap(arr, first, (first + last) / 2);
	pivot = arr[first];
	smallIndex = first;
	for (index = first + 1; index <= last; index++)
		if (arr[index] < pivot)
		{
			smallIndex++;
			swap(arr, smallIndex, index);
		}
	swap(arr, first, smallIndex);
	return smallIndex;
}
void recQuickSort_a(int *arr, int first, int last)
{
	int pivotLocation;
	if (first < last)
	{
		pivotLocation = partition_a(arr, first, last);
		recQuickSort_a(arr, first, pivotLocation - 1);
		recQuickSort_a(arr, pivotLocation + 1, last);
	}
}
void quick_sort_a(int *arr, int len)
{
	recQuickSort_a(arr, 0, len - 1);
}




//shell sort
void intervalInsertionSort_a(int *arr, int length, int begin, int inc)
{
	for (int begin = inc; begin < length; begin++)
	{
		for (int j = begin; j >= inc && arr[j] < arr[j - inc]; j -= inc)
		{
			int temp = arr[j];
			arr[j] = arr[j - inc];
			arr[j - inc] = temp;
		}
	}
}
void shell_sort_a(int *arr, int length)
{
	int inc;
	for (inc = 1; inc < (length - 1) / 9; inc = 3 * inc + 1);
	do
	{
		for (int begin = 0; begin < inc; begin++)
		{
			intervalInsertionSort_a(arr, length, begin, inc);
		}
		inc = inc / 3;
	} while (inc > 0);
}
void intervalInsertionSort_d(int *arr, int length, int begin, int inc)
{
	for (int begin = inc; begin < length; begin++)
	{
		for (int j = begin; j >= inc && arr[j] > arr[j - inc]; j -= inc)
		{
			int temp = arr[j];
			arr[j] = arr[j - inc];
			arr[j - inc] = temp;
		}
	}
}
void shell_sort_d(int *arr, int length)
{
	int inc;
	for (inc = 1; inc < (length - 1) / 9; inc = 3 * inc + 1);
	do
	{
		for (int begin = 0; begin < inc; begin++)
		{
			intervalInsertionSort_d(arr, length, begin, inc);
		}
		inc = inc / 3;
	} while (inc > 0);
}


void shell_sort_de(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i += 1)
		{
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] < temp; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = temp;
		}
	}
}
void shell_sort_as(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i += 1)
		{
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = temp;
		}
	}
}


//merge sort
struct node
{
	int data;
	node *next;
};
class list
{
private:
	node *head;
	node *tail;
public:
	list();
	bool is_empty()
	{
		return (head == NULL);
	}
	int count()
	{
		int count = 0;
		for (node *p = head; p != NULL; p = p->next)
			count++;
		return count;
	}
	void addHead(int n);
	void addTail(int n);
	void printList();
	void printNode(ofstream &ofs, int pos);
	void divide_list(node *first1, node *&first2);
	void recMergeSort(node * &head, string s);
	void mergeSort(string s);
	node *mergeList(node *first1, node *first2, string s)
	{
		node *lastSmall; //pointer to the last node of
		//the merged list
		node *newHead; //pointer to the merged list
		if (first1 == NULL) //the first sublist is empty
			return first2;
		else if (first2 == NULL) //the second sublist is empty
			return first1;
		else
		{
			if (s == "descending")
			{
				if (first1->data > first2->data) //compare the first nodes
				{
					newHead = first1;
					first1 = first1->next;
					lastSmall = newHead;
				}
				else
				{
					newHead = first2;
					first2 = first2->next;
					lastSmall = newHead;
				}
				while (first1 != NULL && first2 != NULL)
				{
					if (first1->data > first2->data)
					{
						lastSmall->next = first1;
						lastSmall = lastSmall->next;
						first1 = first1->next;
					}
					else
					{
						lastSmall->next = first2;
						lastSmall = lastSmall->next;
						first2 = first2->next;
					}
				}//end while
			}
			else
			{
				if (first1->data < first2->data) //compare the first nodes
				{
					newHead = first1;
					first1 = first1->next;
					lastSmall = newHead;
				}
				else
				{
					newHead = first2;
					first2 = first2->next;
					lastSmall = newHead;
				}
				while (first1 != NULL && first2 != NULL)
				{
					if (first1->data < first2->data)
					{
						lastSmall->next = first1;
						lastSmall = lastSmall->next;
						first1 = first1->next;
					}
					else
					{
						lastSmall->next = first2;
						lastSmall = lastSmall->next;
						first2 = first2->next;
					}
				}//end while
			}

			if (first1 == NULL) //first sublist is exhausted first
				lastSmall->next = first2;
			else //second sublist is exhausted first
				lastSmall->next = first1;
			return newHead;
		}
	}//end mergeList
};

list::list()
{
	head = tail = nullptr;
}

void list::addHead(int n)
{
	node *temp = new node;
	temp->data = n;
	if (head == NULL)
	{
		head = tail = temp;
		tail->next = NULL;
	}
	else
	{
		temp->next = head;
		head = temp;
	}
}
void list::addTail(int n)
{
	if (head == NULL) addHead(n);
	else
	{
		node *temp = new node;
		temp->data = n;
		tail->next = temp;
		tail = temp;
		temp->next = nullptr;
	}
}

void list::printList()
{
	node *p = head;
	{
		while (p != nullptr)
		{
			cout << p->data << " ";
			p = p->next;
		}
	}
}
void list::printNode(ofstream &ofs, int pos)
{
	int n = 0;
	for (node *p = head; p != NULL; p = p->next)
	{
		n++;
		if (pos == n - 1)
		{
			ofs << p->data << " ";
		}
	}
}
//devidelist
void list::divide_list(node *first1, node *&first2)
{
	node *middle, *current;
	if (first1 == NULL) //list is empty
		first2 = NULL;
	else if (first1->next == NULL) //list has only one node
		first2 = NULL;
	else
	{
		middle = first1;
		current = first1->next;
		if (current != NULL) //list has more than two nodes
			current = current->next;
		while (current != NULL)
		{
			middle = middle->next;
			current = current->next;
			if (current != NULL)
				current = current->next;
		} //end while
		first2 = middle->next; //first2 points to the first
		//node of the second sublist
		middle->next = NULL; //set the link of the last node
		//of the first sublist to NULL
	} //end else
} //end divideList
void list::recMergeSort(node *&head, string s)
{
	node *otherHead = new node;
	if (head != NULL) //if the list is not empty
		if (head->next != NULL) //if the list has more than one node
		{
			divide_list(head, otherHead);
			recMergeSort(head, s);
			recMergeSort(otherHead, s);
			head = mergeList(head, otherHead, s);
		}
} //end recMergeSort
void list::mergeSort(string s)
{
	recMergeSort(head, s);
	if (head == NULL)
		tail = NULL;
	else
	{
		tail = head;
		while (tail->next != NULL)
			tail = tail->next;
	}
} //end mergeSort

//number of integers
int number_of_integers(ifstream &ifs, string input)
{
	int n = 0, num = 0;
	ifs.open(input);
	while (ifs >> num) { n++; }
	ifs.close();
	return n;
}
// store in list
list store_into_list(ifstream &ifs, string input)
{
	list l;
	int x;
	node *p = new node;
	ifs.open(input);
	while (ifs >> x)
	{
		l.addTail(x);
	}
	ifs.close();
	return l;
}
//store in array
int *store_into_array(ifstream &ifs, string input)
{
	int i = 0;
	int *big_arr = new int[number_of_integers(ifs, input)];
	ifs.open(input);
	while (!ifs.eof())
	{
		ifs >> big_arr[i];
		i++;
	}
	ifs.close();
	return big_arr;
}
// read command
string read_command(ifstream &ifs, string input)
{
	string command, line;
	ifs.open(input);
	while (getline(ifs, line))
	{
		if (!line.empty())
			command = line;
	}
	ifs.close();
	return command;
}
//store position
int size(string s)
{
	int n = 0;
	stringstream ss;
	ss << s;
	string temp;
	int found;
	while (!ss.eof())
	{
		ss >> temp;
		if (stringstream(temp) >> found) n++;
		temp = "";
	}
	return n;
}
int *position(string s)
{
	int i = 0;
	stringstream ss;
	ss << s;
	string temp;
	int found;
	int *arr = new int[size(s)];
	while (!ss.eof())
	{
		ss >> temp;
		if (stringstream(temp) >> found)
		{
			arr[i] = found; i++;
		}
		temp = "";
	}
	return arr;
}
void read_sort(ifstream &ifs, string input, string &sort, string &order)
{
	string s;
	ifs.open(input);
	ifs >> sort; ifs >> s; ifs >> order;
	ifs.close();
}


//int main()
//{
//	string input = "input39.txt";
//	string command = "command39.txt";
//	string output = "aaa.txt";

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	ifstream ifs;
	ofstream ofs;
	ofs.open(output);
	string command_line = read_command(ifs, command); // string command
	string sort = "", order = "";
	read_sort(ifs, command, sort, order); // read sort type, order type
	int *position_arr = position(command_line);//array of position
	int m = size(command_line); //size of position array

	if (sort == "quick")
	{
		int *big_arr = store_into_array(ifs, input);
		int n = number_of_integers(ifs, input);
		if (order == "descending") quick_sort_d(big_arr, n);
		else quick_sort_a(big_arr, n);

		for (int i = 0; i < m; i++)
		{
			if (position_arr[i] < n && position_arr[i] >= 0)
				ofs << big_arr[position_arr[i]] << " ";
		}
		ofs.close();
	}

	else if (sort == "shell")
	{
		int *big_arr = store_into_array(ifs, input);
		int n = number_of_integers(ifs, input);
		if (order == "descending") shell_sort_de(big_arr, n);
		else shell_sort_as(big_arr, n);
		for (int i = 0; i < m; i++)
		{
			if (position_arr[i] < n && position_arr[i] >= 0)
				ofs << big_arr[position_arr[i]] << " ";
		}
		ofs.close();
	}

	else if (sort == "merge")
	{
		list l = store_into_list(ifs, input);
		l.mergeSort(order);
		for (int i = 0; i < m; i++)
		{
			if (position_arr[i] < l.count() && position_arr[i] >= 0)
				l.printNode(ofs, position_arr[i]);
		}
		ofs.close();
	}

	ifs.close();
	return 0;
}