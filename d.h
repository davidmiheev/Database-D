// author:Miheev David
#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

const int	SIZE_BUFFER = 1e7;
const int	DEQ_MAXELEM = 1024;
const int	BTREE_DEG = 10;
using namespace	std;

template < typename T > T min(T a, T b)
{
	return a >= b ? b : a;
}
template < typename T > T max(T a, T b)
{
	return a >= b ? a : b;
}

class Exception {
	public:
	const char *reason;
		Exception():
			reason("") 
    {}

		Exception(const char *cause):
			reason(cause)           
    {}
};

class Student {
	char * name;
	int    num_group;
	char * info;

public:
		Student():
			name        (0),
			num_group   (0),
			info        (0) 
        {}

		Student(const char *s, const int n, const char *inf):
			name          (new char[strlen(s) + 1]),
			num_group     (n),
			info          (new char[strlen(inf) + 1]) 
        {
		    strcpy(name, s);
		    strcpy(info, inf);
        }

        Student(const Student & s):
	        name(new char[strlen(s.name) + 1]),
		    num_group(s.num_group),
		    info(new char[strlen(s.info) + 1])
        {
		    strcpy(name, s.name);
		    strcpy(info, s.info);
	    }

	Student & operator = (const Student & s){
		if (this != &s) {
			if (name)
				delete[] name;
			if (info)
				delete[] info;
			name = new char [strlen(s.name) + 1];
			num_group = s.num_group;
			info = new char [strlen(s.info) + 1];
			strcpy(name, s.name);
			strcpy(info, s.info);
		}
		return *this;
	}

	bool operator > (const Student & b) {
		if (strcmp(name, b.get_name()) > 0)
			return true;
		else
			return false;
	}

	bool operator <= (const Student & b) {
		return !(*this > b);
	}

	bool operator == (const Student & b) {
		if (strcmp(name, b.get_name()) == 0 && num_group == b.get_num())
			return true;
		else
			return false;
	}

	const char * get_name() const {
		return name;
	}
	int	get_num() const {
		return num_group;
	}
	const char *get_info() const {
		return info;
	}
	void set_info (const char *s) {
		strcpy(info, s);
	}
	void print() {
		if (name != 0)
			cout << "name: "
			<< name
			<< " "
			<< num_group
			<< " group \n"
			<< "\n+---------information---------+\n\n"
			<< info
			<< endl
			<< "\n+-----------------------------+\n";
		else
			cout << "student not found\n";
	}

	~Student() {
		if (name)
			delete[] name;
		if (info)
			delete[] info;
		name = 0;
		info = 0;
	}
};


class		SListItem {
public:
	SListItem * next;
	Student		v;

	SListItem():
		next          (0),
		v             () 
    {}

	SListItem(const char *s, const int n, const char *info):
			next          (0),
			v             (s, n, info) 
            {}
                
    SListItem(const SListItem & b):
	    next(b.next),
	    v(b.v) 
        {}

	virtual ~ SListItem() {
	}
};

class SList {
public:
	SListItem * first, * cur;
    SList():
	    first(new SListItem),
	    cur(0) 
    {}

	int	IsEmpty() {
		return (cur == 0);
	}

	void GotoFirst() {
		cur = first->next;
	}

	int	GetCur(Student * v) throw(Exception) {
		if (cur == 0)
			throw(Exception("list is empty"));
		*v = cur->v;
		return 0;
	}

	int	GotoNext() {
		if (cur == 0 || cur->next == 0)
			return 1;
		cur = cur->next;
		return 0;
	}

	void AddAfter(const char *s, const int n, const char *info) {
		SListItem * i;
		i =	new	SListItem(s, n, info);
		if(cur == 0x00)
				first->next = cur = i;
		else {
			i->next = cur->next;
			cur->next = i;
			if (i->next == 0x00)
				cur = i;
		}
	}

	void print() {
		int		err = 1;
		Student		v;
		for(GotoFirst(), err = IsEmpty(); !err; err = GotoNext()) {
			GetCur(&v);
			v.print();
		}

	    cout <<	endl;
	}

	int remove() {
		SListItem * tmp;
		if(cur->next) {
			tmp = cur->next;
			cur->next = tmp->next;
			delete tmp;
			return	1;
		}
		return	0;
	}

	~SList() {
		for (cur = first; remove(););
		delete		cur;
		cur = 0;
	}
};

class ListDeq {
private:
	const int	m_MaxElem;
	int		    m_Begin;
	int		    m_End;
	int		    m_NumElem;
	SList       *m_Elements[DEQ_MAXELEM];

public:
	ListDeq():
		m_MaxElem     (DEQ_MAXELEM),
		m_Begin       (0),
		m_End         (DEQ_MAXELEM - 1),
		m_NumElem     (0) 
        {}

	/*
	 * ListDeq(int maxElem): m_MaxElem(maxElem), m_Begin(0),
	 * m_End(maxElem-1), m_NumElem(0), m_Elements(new SList[m_MaxElem]) {
	 * }
	 */

	ListDeq(const ListDeq & d):
		m_MaxElem     (d.m_MaxElem),
		m_Begin       (d.m_Begin),
		m_End         (d.m_End),
		m_NumElem     (d.m_NumElem) 
    {
		for (int i = 0; i < DEQ_MAXELEM; i++)
			m_Elements[i] = d.m_Elements[i];
	}


	~ListDeq() {}

private:

	int nextIndex(int i) const {
		if (i < m_MaxElem - 1)
			return i + 1;
		else
			return 0;
	}

	int prevIndex(int i) const {
		if (i > 0)
			return i - 1;
		else
			return m_MaxElem - 1;
	}

		public:
	void pushFront(SList * p) throw(Exception) {
		if (m_NumElem >= m_MaxElem)
			throw Exception("Deq overflow");
		m_Begin = prevIndex(m_Begin);
		m_Elements[m_Begin] = p;
        ++m_NumElem;
	}

	void pushBack(SList * p) throw(Exception) {
		if (m_NumElem >= m_MaxElem)
			throw Exception("Deq overflow");
		m_End =	nextIndex(m_End);
		m_Elements[m_End] = p;
		++m_NumElem;
	}

	SList * popFront() throw(Exception) {
		if (m_NumElem <= 0)
			throw Exception("Deq empty");
		int	i = m_Begin;
		m_Begin = nextIndex(m_Begin);
		--m_NumElem;
		return	m_Elements[i];
	}

	SList * popBack() throw(Exception) {
		if (m_NumElem <= 0)
			throw Exception("Deq empty");
		int	i = m_End;
		m_End =	prevIndex(m_End);
		--m_NumElem;
		return	m_Elements[i];
	}

	SList * front() throw(Exception) {
		if (m_NumElem <= 0)
			throw Exception("Deq empty");
		return	m_Elements[m_Begin];
	}

	const SList * front() const throw(Exception) {
		if (m_NumElem <= 0)
			throw Exception("Deq empty");
		return	m_Elements[m_Begin];
	}

	SList * back() throw(Exception) {
		if (m_NumElem <= 0)
			throw Exception("Deq empty");
		return	m_Elements[m_End];
	}

	const SList * back() const throw(Exception) {
		if (m_NumElem <= 0)
			throw Exception("Deq empty");
		return	m_Elements[m_End];
	}

	void printBack () {
		int	i = 1;
		while(i <= m_NumElem) {
			cout << "(" << i << ") ";
			SList * l;
			l =	popBack();
			l->print();
			pushFront(l);
			i++;
		}
	}

	void printFront() {
		int	i = 1;
		while(i <= m_NumElem) {
			cout << "(" << i << ") ";
			SList *l;
			l =	popFront ();
			l->print();
			pushBack(l);
			i++;
		}
	}

	int	search(const char *s){
		SList *l;
		Student	p;

		for(int i = 0; i < m_NumElem; i++) {
			l = popFront();
			l->GetCur(&p);
			if (strncmp(s, p.get_name(), 1) == 0) {
				int err;
				for(l->GotoFirst(), err = l->IsEmpty(); !err; err = l->GotoNext()) {
					l->GetCur(&p);
					if (strcmp(s, p.get_name()) == 0) {
						pushBack(l);
						p.print();
						return 1;
					}
				}
			}
            
			pushBack(l);
		}

		return 0;

	}


	void add(const Student & s) {
		if (m_NumElem == 0) {
			SList * l = new SList;
			pushFront(l);
			front()->AddAfter(s.get_name(), s.get_num(), s.get_info());
		} else {
			SList * l;
			Student	p;
			int		i;
			for(i = 0; i < m_NumElem; i++) {
				l = popFront();
				l->GetCur(&p);
				if (strncmp(s.get_name(), p.get_name(), 1) == 0) {
					l->AddAfter(s.get_name(), s.get_num(), s.get_info());
					pushBack(l);
					return;
				}
				pushBack(l);
			}
			if (i == m_NumElem) {
				l = new SList;
				pushFront(l);
				front()->AddAfter(s.get_name(), s.get_num(), s.get_info());
			}
		}
	}

	int	del_in_Deq(const char *s) {
		SList *l;
		Student	p;
		for(int i = 0; i < m_NumElem; i++) {
			l = popFront();
			l->GotoFirst();
			if (l->IsEmpty())
				delete		l;
			else {
				l->GetCur(&p);
				if (strncmp(s, p.get_name(), 1) == 0) {
					int		err = 0;
					for(l->cur = l->first; !err; err = l->GotoNext()) {
						if (l->cur->next) {
							p = l->cur->next->v;
							if (strcmp(s, p.get_name()) == 0)
								l->remove();
						}
					}
				}
                
				l->GotoFirst();
				if (!(l->IsEmpty()))
					pushBack(l);
				else
					delete l;
			}
		}

		if (m_NumElem == 0)
			return 1;

		return 0;
	}

	void clear() {
		if (m_NumElem > 0) {
			for (int i = m_Begin; i <= m_End; i++)
				delete m_Elements[i];
		}
		m_Begin = 0;
		m_End = m_MaxElem - 1;
		m_NumElem = 0;
	}

	ListDeq & operator = (ListDeq & d) {
		if (this != &d) {
			clear();
			int		i = 1;
			while (i <= d.m_NumElem) {
				i++;
				SList * l = new SList, *t;
				Student	s;
				int	err;
				t = d.popFront();
				for (t->GotoFirst(), err = t->IsEmpty(); !err; err = t->GotoNext()) {
					t->GetCur(&s);
					l->AddAfter(s.get_name(), s.get_num(), s.get_info());
				}

				l->GotoFirst();
				if (!l->IsEmpty())
					pushBack(l);
				else
					delete l;
				d.pushBack(t);
			}
		}
		return *this;
	}

	int		size       () const {
		return m_NumElem;
	}
	int		maxSize    () const {
		return m_MaxElem;
	}

};

class Pair {
public:
	int         x;
	ListDeq     y;

	Pair():
		x(0),
		y() 
    {}

	Pair & operator = (Pair & p) {
		if (this != &p) {
			x = p.x;
			y = p.y;
		}
		return *this;
	}

	void printkey() {
		cout << x << " ";
	}

	void print() {
		cout << "+----------+\n";
		y.printFront();
		cout << "key: " << x << endl;
		cout << "+----------+\n";
	}

	void clear() {
		x = 0;
		y.clear();
	}

	~Pair() {}

};

class BTreeNode {
	public:
	BTreeNode * parent;
	BTreeNode * son[2 * BTREE_DEG + 1];
	Pair        value[2 * BTREE_DEG];
	int		    n;

	BTreeNode():
		parent        (0),
		n             (0) 
    {
		for (int i = 0; i < 2 * BTREE_DEG + 1; i++)
			son[i] = 0;
	}

	~BTreeNode() {
		parent = 0;
		n = 0;
		for (int i = 0; i < 2 * BTREE_DEG + 1; i++)
			son[i] = 0;
	}

};

class BTree {
	BTreeNode      *header;
	int		        numNode;

public:
		BTree():
		header        (new BTreeNode),
		numNode       (0) 
    {}

	int	search(BTreeNode * node, int key, BTreeNode ** res) {
		if (node == 0x00)
			return 0;
		*res = node;
		if (binsearch(node, key) == -1)
			return 1;
		else
			return search(node->son[binsearch(node, key)], key, res);
	}

	void add(const Student & s, int key) {
		BTreeNode      *res;
		Pair		pair;
		pair.x = key;
		pair.y.add(s);
		if(header->son[0] == 0x00) {
			BTreeNode * root = new BTreeNode;
			header->son[0] = root;
			root->parent = header;
			++numNode;
		}
		if(!search(root(), pair.x, &res))
			insert(res, pair);
		else {
			pair.clear();
			int	m, t;
			for (m = res->n - 1, t = 0; m - t > -1;) {
				if (res->value[(int)((t + m) / 2)].x == key) {
					if (!res->value[(int)((t + m) / 2)].y.search(s.get_name()))
						res->value[(int)((t + m) / 2)].y.add(s);
					return;
				}
				if (res->value[(int)((t + m) / 2)].x > key)
					m = (int)(m + t) / 2 - 1;
				if (res->value[(int)((t + m) / 2)].x < key)
					t = (int)(m + t) / 2 + 1;
			}
		}
	}

	void del(int key) {
		BTreeNode * res;
		if(header->son[0] == 0x00)
				return;
		if(search(root(), key, &res))
				B_delete(res, key);
	}

	void Delete(const char *s, int n) {
		BTreeNode      *res;
		if(search(root(), n, &res)) {
			int	m, t;
			for(m = res->n - 1, t = 0; m - t > -1;) {
				if (res->value[(int)((t + m) / 2)].x == n) {
					if (res->value[(int)((t + m) / 2)].y.del_in_Deq(s))
						del(n);
					break;
				}
				if(res->value[(int)((t + m) / 2)].x > n)
						m = (int)(m + t) / 2 - 1;
				if (res->value[(int)((t + m) / 2)].x < n)
					    t = (int)(m + t) / 2 + 1;
			}
		}
	}

private:
	int	binsearch(BTreeNode * node, int key){
		int		m         , t;
		for             (m = node->n - 1, t = 0; m - t > -1;) {
			if (node->value[(int)((t + m) / 2)].x == key)
				return -1;

			if (node->value[(int)((t + m) / 2)].x > key)
				m = (int)(m + t) / 2 - 1;

			if (node->value[(int)((t + m) / 2)].x < key)
				t = (int)(m + t) / 2 + 1;
		}

				return	t;

	}

	void split(BTreeNode * node) {
		int	k;
		if  (node->parent->n == 0)
			k =	0;
		else
			k =	binsearch(node->parent, node->value[BTREE_DEG - 1].x);
		BTreeNode * tmp = node;
		Pair p = node->value[BTREE_DEG - 1];
		BTreeNode * n_1 = new BTreeNode;
		BTreeNode * n_2 = new BTreeNode;
		for(int j = node->parent->n + 1; j > k + 1; j--)
					node->parent->son[j] = node->parent->son[j - 1];
				n_1->parent = node->parent;
				n_2         ->parent = node->parent;
		for             (int j = 0; j < BTREE_DEG; j++)
					n_1         ->son[j] = node->son[j];
		for             (int j = BTREE_DEG; j < 2 * BTREE_DEG + 1; j++)
					n_2         ->son[j - BTREE_DEG] = node->son[j];
		for             (int j = 0; j < BTREE_DEG; j++) {
			if (n_1->son[j])
				n_1->son[j]->parent = n_1;
		}
		for             (int j = BTREE_DEG; j < 2 * BTREE_DEG + 1; j++) {
			if (n_2->son[j - BTREE_DEG])
				n_2->son[j - BTREE_DEG]->parent = n_2;
		}
		for (int j = 0; j < BTREE_DEG - 1; j++) {
			insert(n_1, node->value[j]);
			insert(n_2, node->value[2 * BTREE_DEG - j - 1]);
		}
		insert(n_2, node->value[BTREE_DEG]);
		++numNode;

		n_1->parent->son[k] = n_1;
		n_1->parent->son[k + 1] = n_2;

		delete		tmp;

		insert(n_1->parent, p);

	}

	void insert(BTreeNode * node, Pair & pair) {
		int		i = 0;
		if              (node->n > 0)
					i =		binsearch(node, pair.x);
		else
					i =		0;
		if              (i >= 0) {
			if (node->n == 0) {
				node->value[0] = pair;
				pair.clear();
			} else {
				for (int j = node->n; j > i; j--)
					node->value[j] = node->value[j - 1];
				node->value[i] = pair;
				pair.clear();
			} ++(node->n);
		}
		if ((node->n) == 2 * BTREE_DEG) {
			if (node->parent != header)
				split(node);
			else {
				BTreeNode *root = new BTreeNode;

				root->son[0] = node;
				root->son[0]->parent = root;
				node->parent = root;
				++numNode;
				root->parent = header;
				header->son[0] = root;
				split(root->son[0]);

			}
		}
	}

	int	binsearch_1(BTreeNode * node, int key){
		int	m, t;

		for(m = node->n - 1, t = 0; m - t > -1;) {

			if (node->value[(int)((t + m) / 2)].x == key)
				return (int)((t + m) / 2);

			if (node->value[(int)((t + m) / 2)].x > key)
				m = (int)(m + t) / 2 - 1;

			if (node->value[(int)((t + m) / 2)].x < key)
				t = (int)(m + t) / 2 + 1;

		}

				return       -1;

	}

	void B_delete(BTreeNode * node, int key) {
		if ((node->n) >= BTREE_DEG || node == header->son[0]) {
			if (node->son[0] == 0x00) {
				int k = binsearch_1(node, key);
						node->value[k].clear();
				for(int j = k; j < node->n - 1; j++)
						node->value[j] = node->value[j + 1];
						node->value[node->n - 1].clear();
						node->n--;
			} else {
				int i = 0;
				int	k = binsearch_1(node, key);
				if(node->son[k]->n >= BTREE_DEG)
						i =	1;
				if(node->son[k + 1]->n >= BTREE_DEG)
						i =	2;
				BTreeNode *tmp;
				int	k1;
				ListDeq	p;
				switch(i) {
				case 0:
					join(node, k);
					search(root(), key, &tmp);
					B_delete(tmp, key);
					break;
				case 1:
					tmp = node->son[k];
					while (tmp->son[0])
						tmp = tmp->son[tmp->n];
					k1 = tmp->value[tmp->n - 1].x;
					p = tmp->value[tmp->n - 1].y;
					B_delete(tmp, k1);
					node->value[k].x = k1;
					node->value[k].y.clear();
					node->value[k].y = p;
					p.clear();
					break;
				case 2:
					tmp = node->son[k + 1];
					while (tmp->son[0])
						tmp = tmp->son[0];
					k1 = tmp->value[0].x;
					p = tmp->value[0].y;
					B_delete(tmp, k1);
					node->value[k].x = k1;
					node->value[k].x = k1;
					node->value[k].y.clear();
					node->value[k].y = p;
					p.clear();
					break;
				}
			}
		} else {
			BTreeNode *tmp = node;
			while (tmp->n == BTREE_DEG - 1 && tmp != header->son[0])
				tmp = tmp->parent;
			int	k = binsearch(tmp, key), i = 0;
			if (k > 0 && tmp->son[k - 1]->n >= BTREE_DEG)
				i = 1;
			if (k < tmp->n && tmp->son[k + 1]->n >= BTREE_DEG)
				i = 2;
			switch (i) {
			case 0:
				if (k < tmp->n)
					join(tmp, k);
				else
					join(tmp, k - 1);
				break;
			case 1:
				insert(tmp->son[k], tmp->value[k - 1]);
				tmp->value[k - 1].clear();
				for (int j = k - 1; j < tmp->n - 1; j++)
					tmp->value[j] = tmp->value[j + 1];
				tmp->value[tmp->n - 1].clear();
				tmp->n--;
				insert(tmp, tmp->son[k - 1]->value[tmp->son[k - 1]->n - 1]);
				tmp->son[k - 1]->value[tmp->son[k - 1]->n - 1].clear();
				tmp->son[k - 1]->n--;
				for (int j = tmp->son[k]->n + 1; j >= 0; j--)
					tmp->son[k]->son[j + 1] = tmp->son[k]->son[j];
				tmp->son[k]->son[0] = tmp->son[k - 1]->son[tmp->son[k - 1]->n];
				if (tmp->son[k]->son[0])
					tmp->son[k]->son[0]->parent = tmp->son[k];
				tmp->son[k - 1]->son[tmp->son[k - 1]->n] = 0;
				break;
			case 2:
				insert(tmp->son[k], tmp->value[k]);
				tmp->value[k].clear();
				for (int j = k; j < tmp->n - 1; j++)
					tmp->value[j] = tmp->value[j + 1];
				tmp->value[tmp->n - 1].clear();
				tmp->n--;
				insert(tmp, tmp->son[k + 1]->value[0]);
				tmp->son[k + 1]->value[0].clear();
				for (int j = 0; j < tmp->son[k + 1]->n - 1; j++)
					tmp->son[k + 1]->value[j] = tmp->son[k + 1]->value[j + 1];
				tmp->son[k + 1]->n--;
				tmp->son[k]->son[tmp->son[k]->n] = tmp->son[k + 1]->son[0];
				if (tmp->son[k]->son[tmp->son[k]->n])
					tmp->son[k]->son[tmp->son[k]->n]->parent = tmp->son[k];
				for (int j = 0; j < tmp->son[k + 1]->n + 1; j++)
					tmp->son[k + 1]->son[j] = tmp->son[k + 1]->son[j + 1];
				break;
			}

			search(root(), key, &tmp);
			B_delete(tmp, key);
		}
	}

	void join(BTreeNode * node, int k) {
		insert(node->son[k], node->value[k]);

		for (int j = node->son[k]->n; j < node->son[k + 1]->n + node->son[k]->n + 1; j++)
			node->son[k]->son[j] = node->son[k + 1]->son[j - node->son[k]->n];
		for (int j = node->son[k]->n; j < node->son[k + 1]->n + node->son[k]->n + 1; j++) {
			if (node->son[k]->son[j])
				node->son[k]->son[j]->parent = node->son[k];
		}

		for (int j = 0; j < node->son[k + 1]->n; j++)
			insert(node->son[k], node->son[k + 1]->value[j]);
		for (int j = 0; j < node->son[k + 1]->n; j++)
			node->son[k + 1]->value[j].clear();

		delete	node->son[k + 1];
		node->value[k].clear();

		for (int j = k; j < node->n - 1; j++) {
			node->value[j] = node->value[j + 1];
			node->son[j + 1] = node->son[j + 2];
		}

		if (node->n > 1)
			node->value[node->n - 1].clear();
        
		node->n--;
        
		if (node->n == 0) {
			BTreeNode * tmp = 0;
			tmp = header->son[0];
			header->son[0] = node->son[0];
			header->son[0]->parent = header;
			if (tmp)
				delete	tmp;
		}
	}

public:

	//================================visualisation of tree == == == == == == == == == == == == == == == == == == == =

		void showtree( /* BTreeNode *subroot */ ) {
		if (header->son[0] == 0)
			cout << "---" << endl;
		else {
			int	h = 0, level = 0;
			BTreeNode * tmp = root();

			while(tmp->son[0] != 0) {
				h++;
				tmp = tmp->son[0];
			}

			vector<int> * v = new vector<int>[h + 1], u(SIZE_BUFFER);

			for (level = 0; level <= h; level++) {
				v[level] = u;
				levelprint(root(), level, &v[level]);
			}

			for (level = 0; level <= h; level++) {
				if (level == 0)
					cout << "+-----B-tree visualisation-----+\n" << endl;
				for (int i = 0; v[level][i] != 0; i += v[level][i] + 1) {
					cout << "( ";
					for (int j = 0; j < v[level][i]; j++) {
						if (j < v[level][i] - 1)
							cout << v[level][j + i + 1] << " | ";
						else
							cout << v[level][j + i + 1] << " )  ";
					}

				}

				if (level < h)
					cout << endl << endl;

				else
					cout << endl << "\n+------------------------------+" << endl;

			} 
            
            delete[] v;
		}
	}

	void levelprint(BTreeNode * subroot, int level, vector<int> * v){
		if (level == 0) {
			int j;
			for (j = 0; v->at(j) != 0; j += v->at(j) + 1);
			for (int i = j; i < j + subroot->n + 1; i++) {
				if (i == j)
					v->at(i) = subroot->n;
				else
					v->at(i) = subroot->value[i - j - 1].x;
			}
            
		} else {
			level--;
			for (int i = 0; i < subroot->n + 1; i++)
				levelprint(subroot->son[i], level, v);
		}
	}

	void print(BTreeNode * subroot) {

		if (subroot == 0x00) {
			cout << "null" << endl;
			return;
		}
		for (int i = 0; i < subroot->n; i++) {

			subroot->value[i].print();

			if (i == 0)
				print(subroot->son[0]);
            
			print(subroot->son[i + 1]);
		}
	}

	//=========================================================================

	void clear(BTreeNode * subroot) {
		if (subroot == 0x00)
			return;

		for (int i = 0; i < subroot->n; i++) {
			subroot->value[i].clear();
			if (i == 0)
				clear(subroot->son[0]);
            
			clear(subroot->son[i + 1]);
		}
	}

	int	size() {
		return numNode;
	}

	BTreeNode * root() {
		return header->son[0];
	}

private:
	void clean(BTreeNode * subroot, int k){
		if (subroot->son[0] == 0x00) {
			BTreeNode * tmp = subroot;
			subroot->parent->son[k] = 0x00;
			--numNode;
			delete	tmp;
		} else {
			for (int i = subroot->n; i >= 0; i--) {
				if (subroot->son[i] != 0x00)
					clean(subroot->son[i], i);
			}
		}
	}

public:
	    ~BTree() {
		while (header->son[0]) {
			clean(header, 0);	/* showtree(); */
		}

		delete	header;
	}

};



#endif
