#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<string.h>
#include<algorithm>
#include "ArgumentManager.h"
using namespace std;
struct book;
struct node;
struct list;
void init(list &l);
bool searchID(list &l, node *p);
node *getNode(book x);
void addHead(list &l, node *p);
void addTail(list &l, node *p);
void addPos(list&l, node *p, int pos);
void removehead(list &l);
void removetail(list &l);
void removemid(list &l, int pos);
void remove_pos(list &l, int pos);
void remove_id(list &l, string s);
void remove_name(list &l, string s);
void remove_au(list &l, string s);
void sortName(list &l);
void sortAu(list &l);
void readbook(ifstream &inf, book &b);
void readbooklist(ifstream &inf, list &l);
void xuat(book b, ofstream &ofs);

//declare struct book data
struct book
{
	string book_id;
	string book_name;
	string book_author;
};

// declare a node
struct node
{
	book data; //hold data of node (book)
	node *next; //pointer to link nodes
	node *prev;
};

// declare struct list of books
struct list
{
	node *head; //pointer of node at head
	node *tail; //pointer of node at tail
};

// list initialization  
void init(list &l)
{
	l.head = NULL; //
	l.tail = NULL;
}

// get a node
node *getNode(book x)
{
	node *p = new node;
	if (p == NULL)
	{
		return NULL;
	}
	p->data = x; //dua du lieu cua bien book x vao data
	p->next = NULL; // khoi tao node p nhung node p chua co lien ket den node nao het
	p->prev = NULL;
	return p;
}

//ham them 1 node book vao dau danh sach
void addHead(list &l, node *p)
{
	if (l.head == NULL) //if list is empty
		l.head = l.tail = p; // note p them vao cung chinh la dau va cuoi
	else
	{
		if (searchID(l, p) != true)
		{
			p->next = l.head; //cho con tro p tro den head
			l.head->prev = p;
			l.head = p; // cap nhat lai head la node p
		}
	}
}

// ham them 1 cai node book vao cuoi danh sach
void addTail(list &l, node *p)
{
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else
	{
		if(searchID(l,p)!=true)
		{
			l.tail->next = p; //cho con tro cua tail tro den node p
			p->prev = l.tail;
			l.tail = p; //cap nhat lai tail chinh la node  p
		}
	}
}
//search function - return true if same ID
bool searchID(list &l, node *p)
{
	int a = 0;
	for (node *k = l.head; k != NULL; k = k->next)
	{
		if (atoi(p->data.book_id.c_str()) == atoi(k->data.book_id.c_str())) //convert to int ID and compare
		{			
			a++;
		}
	}
	if (a > 0) return true;
}
//add book to a position
void addPos(list&l, node *p, int pos)
{
	if (searchID(l, p) != true)
	{
		int n = 0;
		for (node *k = l.head; k != NULL; k = k->next)
			n++;

		if (l.head == NULL || pos == 0)// add head
		{
			addHead(l, p);
		}
		else if (pos > n - 1||pos<0) //add tail
		{
			addTail(l, p);
		}
		else if (pos > 0 && pos <= n - 1)
		{
			int dem = 0;
			node *g = new node;
			for (node *k = l.head; k != NULL; k = k->next)
			{
				dem++;
				if (dem - 1 == pos)
				{
					node *h = getNode(p->data);

					h->next = k;
					g->next = h;
					k->prev = h;
					h->prev = g;
					break;
				}
				g = k;
			}
		}
	}				
}
//remove head
void removehead(list &l)
{
	if (l.head == NULL)
	{
		return;
	}
	else if (l.head == l.tail)
	{
		delete l.head;
		l.head = l.tail = NULL;
		return;
	}
	{
		node *p = l.head;
		l.head = l.head->next;
		l.head->prev = NULL;
		delete p;
	}
}

//remove tail
void removetail(list &l)
{
	if (l.head == NULL)
	{
		return;
	}
	if (l.head->next == NULL)
	{
		removehead(l);
		return;
	}
	for(node *k = l.head; k!=NULL; k = k->next)
		if(k->next == l.tail)
	{
			delete l.tail;
			k->next = NULL;
			l.tail = k;
			return;
	}
}
//
void removemid(list &l, int pos)
{
	int count = 0;
	node *p = new node;
	node *q = new node;

	for (node *k = l.head; k != NULL; k = k->next)
	{
		count++;
		if (pos == count - 1)
		{
			p = k->prev;
			q = k->next;
			delete k;
			p->next = q;
			q->prev = p;
			break;
		}
	}
}

//remove node function - postion
void remove_pos(list &l, int pos)
{
	{
		int count = 0;
		for (node *k = l.head; k != NULL; k = k->next)
			count++;
		
		{
			if (pos == 0)
			{
				removehead(l);
			}

			if (pos == count - 1)
			{
				removetail(l);
			}
			if (pos > 0 && pos < count - 1)
			{
				removemid(l, pos);
			}
		}
	}

}
// remove by book ID
void remove_id(list &l, string s)
{
	int count = 0;
	for (node *p = l.head; p != NULL; p = p->next)
		count++;

	for (int i = 0; i < count; i++)
	{
		int pos = 0;
		for (node *k = l.head; k != NULL; k = k->next)
		{
			pos++;
			if (stoi(k->data.book_id) == stoi(s))
			{
				remove_pos(l, pos - 1);
				break;
			}
		}
	}
}
// remove by book name
void remove_name(list &l, string s)
{
	int count = 0;
	for (node *p = l.head; p != NULL; p = p->next)
		count++;

	for (int i = 0; i < count; i++)
	{
		int pos = 0;
		for (node *k = l.head; k != NULL; k = k->next)
		{
			pos++;
			if (k->data.book_name == s)
			{
				remove_pos(l, pos - 1);
				break;
			}
		}
	}
}
//remove by book author
void remove_au(list &l, string s)
{
	int count = 0;
	for (node *p = l.head; p != NULL; p = p->next)
		count++;

	for (int i = 0; i < count; i++)
	{
		int pos = 0;
		for (node *k = l.head; k != NULL; k = k->next)
		{
			pos++;
			if (k->data.book_author == s)
			{
				remove_pos(l, pos - 1);
				break;
			}
		}
	}
}

//sort by ID
void sortID(list &l) 
{
	for (node *p = l.head; p != l.tail; p = p->next)
		{
			for(node *q = p ->next; q != NULL; q = q ->next)
			{
				if (atoi(p->data.book_id.c_str()) > atoi(q->data.book_id.c_str()))
				{
					swap(p->data, q->data);
				}
			}
		}		
}

//sort by book_name
//void sortName(list &l)
//{
//	for (node *p = l.head; p != l.tail; p = p->next)
//	{
//		for (node *q = p->next; q != NULL; q = q->next)
//		{
//			if (p->data.book_name>q->data.book_name)
//			{
//				swap(p->data, q->data);
//			}
//		}
//	}
//}
void sortName(list &l)
{
	int swapped;
	node *p;
	node *q = NULL;
	if (l.head == NULL)
		return;
	do
	{
		swapped = 0;
		p = l.head;
		while (p->next != q)
		{
			if (p->data.book_name > p->next->data.book_name)
			{
				swap(p->data, p->next->data);
				swapped = 1;
			}
			p = p->next;
		}
		q = p;
	} while (swapped);
}

//sort by book_author
//void sortAu(list &l)
//{
//	for (node *p = l.head; p != NULL; p = p->next)
//	{
//		for (node *q = p->next; q != NULL; q = q->next)
//		{
//			if (p->data.book_author > q->data.book_author)
//			{
//				swap(p->data, q->data);
//			}
//		}
//	}
//}
void sortAu(list &l)
{
	int swapped;
	node *p;
	node *q = NULL;
	if (l.head == NULL)
		return;
	do
	{
		swapped = 0;
		p = l.head;
		while (p->next != q)
		{
			if (p->data.book_author > p->next->data.book_author)
			{
				swap(p->data, p->next->data);
				swapped = 1;
			}
			p = p->next;
		}
		q = p;
	} while (swapped);
}


//function read data of a book from txt
void readbook(ifstream &inf, book &b)
{
	getline(inf, b.book_id, ','); 
	b.book_id = b.book_id.substr(b.book_id.find(":") + 1);
	
	getline(inf, b.book_name, ',');
	b.book_name = b.book_name.substr(b.book_name.find(":") + 1);

	getline(inf, b.book_author);		
	b.book_author = b.book_author.substr(b.book_author.find(":") +1  );	
}
//doc danh sach cac book tu file txt
void readbooklist(ifstream &inf, list &l)
{
	while (!inf.eof())
	{
		book b;
		readbook(inf, b);
		//tao 1 node book
		if (b.book_id != "," && b.book_name != "," && b.book_author != "")
		{
		node *p = getNode(b);
		//them book (them node p) vao danh sach lien ket cac book
		addTail(l, p); 
		}
	}
}
//xuat de test du lieu
void xuat(book b, ofstream &ofs)
{
	ofs << "book_id:" << b.book_id << ", book_name:" << b.book_name << ", book_author:" << b.book_author << endl;
}
//xuat danh sach books
void xuatdanhsachbook(list l, ofstream &ofs)
{
	
	{
		for (node *k = l.head; k != NULL; k = k->next)
		{
			xuat(k->data, ofs);
		}
	}
	
}
//============================================================
int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");
//int main()
//{
//	string input = ("input28.txt");
//	string output = ("out.txt");
//	string command = ("command28.txt");

	list l;
	init(l);
	ifstream inf;
	inf.open(input);
	readbooklist(inf, l);

	string **arr = new string*[100];
	for (int i = 0; i < 100; i++)
		arr[i] = new string[1];

	string line;
	ifstream ifs;
	int j = 0;
	ifs.open(command);

	while (getline(ifs, line))
	{
		if (!line.empty())
		{
			*arr[j] = line;
			j++;
		}
	}

	book b;
	int pos;
	for (int i = 0; i < j; i++)
	{
		if (arr[i]->find("add pos:") == 0)
		{
			
			/*size_t s = arr[i]->find("s:");
			size_t e = arr[i]->find("book_id", s);
			string p = arr[i]->substr(s + 2, e - 8);
			pos = atoi(p.c_str());*/

			string a = arr[i]->substr(arr[i]->find("book_author"));
			b.book_author = a.substr(12);
			string n = arr[i]->substr(arr[i]->find("book_name"));
			b.book_name = n.substr(10, n.length() - a.length() - 12);
			string c = arr[i]->substr(arr[i]->find("book_id"));
			b.book_id = c.substr(8, c.length() - n.length() - 10);
			string d = arr[i]->substr(arr[i]->find("pos:"));
			pos = stoi(d.substr(4, d.length() - c.length() - 5));

			addPos(l, getNode(b), pos);
			
		}
		if (arr[i]->find("remove book_id:") == 0)
		{
			string s;
			s = arr[i]->substr(arr[i]->find(":") + 1);
			remove_id(l, s);
		}
		if (arr[i]->find("remove book_name:") == 0)
		{
			string s;
			s = arr[i]->substr(arr[i]->find(":") + 1);
			remove_name(l, s);
		}
		if (arr[i]->find("remove book_author:") == 0)
		{
			string s;
			s = arr[i]->substr(arr[i]->find(":") + 1);
			remove_au(l, s);
		}
		if (arr[i]->find("remove pos:") == 0)
		{
			string s;
			s = arr[i]->substr(arr[i]->find(":") + 1);
			int pos = (int)atoi(s.c_str());
			remove_pos(l, pos);
		}
		if (arr[i]->find("sort book_id") == 0)
		{
			sortID(l);
		}
		if (arr[i]->find("sort book_name") == 0)
		{
			sortName(l);
		}
		if (arr[i]->find("sort book_author") == 0)
		{
			sortAu(l);
		}
	}

	ofstream ofs;
	ofs.open(output);
	xuatdanhsachbook(l, ofs);
	
	ofs.close();
	ifs.close();
	inf.close();
	//deallocate arr
	for (int i = 0; i < j; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;

	return 0;
}