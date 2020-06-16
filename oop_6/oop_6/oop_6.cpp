#include <iostream>
#include <string>
#pragma warning(disable : 4996)

using namespace std;

template <class T>
struct Node {
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template<class T>
class Stack
{
	template<class T>
	friend class Iterator;
public:
	int count;
	Node<T>* head;
	Node<T>* tail;

	Stack();
	Stack(const T& obj);
	~Stack();

	void AddHead(T);
	void AddTail(T);
	void DeleteHead();
	void DeleteTail();
	void show();
	void ShowCount();

	Iterator<T> begin() { return head; }
	Iterator<T> end() { return tail; }
};

template<class T>
class Iterator
{
	Stack<T>* q;
	Node<T>* current;
public:

	Iterator();
	Iterator(Stack<T>* obj);

	bool begin();
	bool end();
	bool operator++();
	bool operator--();
	bool operator == (T data);

	T operator *();

	Node<T>* ReturnHead() { return q->head; }
	Node<T>* ReturnTail() { return q->tail; }

	void quickSort(Stack<T>* obj);
	void _quickSort(Node<T>* l, Node<T>* h);
	void swap(T* a, T* b);

	Node<T>* partition(Node<T>* l, Node<T>* h);
};

template<class T>
class Algoritm
{
public:
	static void qsort(Node<T>* head, Node<T>* tail)
	{
		_quickSort(tail, head);
	}

	template<typename T>
	static void _quickSort(Node<T>* l, Node<T>* h)
	{
		if (h != NULL && l != h && l != h->prev)
		{
			Node<T>* p = partition(l, h);
			_quickSort(l, p->next);
			_quickSort(p->prev, h);
		}
	}

	template<typename T>
	static Node<T>* partition(Node<T>* l, Node<T>* h)
	{
		auto x = h->data;
		// similar to i = l-1 for array implementation  
		auto* i = l->next;

		// Similar to "for (int j = l; j <= h- 1; j++)"  
		for (auto* j = l; j != h; j = j->prev)
		{
			if (j->data <= x)
			{
				// Similar to i++ for array  
				i = (i == NULL) ? l : i->prev;

				swap(&(i->data), &(j->data));
			}
		}
		i = (i == NULL) ? l : i->prev; // Similar to i++  
		swap(&(i->data), &(h->data));
		return i;
	}

	template<typename T>
	static void swap(T* a, T* b)
	{
		T temp = *a;
		*a = *b;
		*b = temp;
	}

	static void FindElement(Node<T>* head, Node<T>* tail, string props)
	{
		if (head != nullptr)
		{
			bool result = false;

			for (auto* j = head; j != tail; j = j->next)
			{
				if (j->data == props)
				{
					cout << endl << j->data << endl;
					cout << endl;
					result = true;
				}
			}

			if (tail->data == props) {
				cout << endl << tail->data << endl;
				cout << endl;
				result = true;
			}

			if (result == false)
				cout << "There is no such Sotrudnik" << endl;
		}
		else
			cout << endl << "The list if empty" << endl;
	}

	template<typename T>
	static Node<T>* FindElement2(Node<T>* head, Node<T>* tail, string props)
	{
		if (head != nullptr)
		{
			bool result = false;

			for (auto* j = tail; j != head; j = j->prev)
			{
				if (j->data == props)
				{
					return j;
				}
			}
			Node<T>* j = head;
			if (result == false)
			{
				if (j->data == props)
				{
					return j;
				}
				else
				{
					return NULL;
					cout << endl << "Not found" << endl;
				}
			}
		}
		else
		{
			cout << endl << "The list is empty" << endl;
		}
	}

	static void DeleteElement(Node<T>* head, Node<T>* tail, string props)
	{
		auto current = head;

		Node<T>* temp = nullptr;
		Node<T>* findedelement = FindElement2(head, tail, props);

		if (findedelement == tail)
		{
			auto temp = findedelement->prev;
			temp->next = NULL;
			tail = temp;
			free(findedelement);
		}
		else if (findedelement != nullptr)
		{
			Node<T>* prev = findedelement->next;
			Node<T>* next = findedelement->prev;
			if (prev != NULL)
				prev->prev = findedelement->prev; 
			if (next != NULL)
				next->next = findedelement->next; 
			free(findedelement); 
		}
	}
};

class Sotrudnik {
public:
	string Name;
	string Doljn;
	int staj;

	Sotrudnik() { }

	Sotrudnik(string lName, string pNumber, int y) {
		Name = lName;
		Doljn = pNumber;
		staj = y;
	}

	Sotrudnik(const Sotrudnik& obj) {
		Name = obj.Name;
		Doljn = obj.Doljn;
		staj = obj.staj;
	}

	Sotrudnik& operator =(const Sotrudnik& obj) {
		if (&obj != this) {
			Name = obj.Name;
			Doljn = obj.Doljn;
			staj = obj.staj;
		}
		return *this;
	}

	friend bool operator <=(const Sotrudnik& a, const Sotrudnik& b);
	friend bool operator == (Sotrudnik& obj, string prop);
	friend bool operator == (Sotrudnik& obj, Sotrudnik& prop);
	friend bool operator != (Sotrudnik& obj, Sotrudnik& prop);

	friend ostream& operator << (ostream& out, const Sotrudnik& obj);
	friend istream& operator >> (istream& in, Sotrudnik& obj);
};

//Implementation of the Stack class
template<class T>
Stack<T>::Stack()
{
	head = NULL;
	tail = NULL;
}

template<class T>
Stack<T>::Stack(const T& obj)
{
	head = new Node<T>;
	head->data = obj.data;
	head->next = NULL;
}

template<class T>
Stack<T>::~Stack()
{
	if (head) {
		while (head != NULL) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
}

template<class T>
void Stack<T>::AddHead(T data)
{
	Node<T>* temp = new Node<T>;
	temp->next = head;
	temp->data = data;
	temp->prev = 0;

	if (head != 0)
		head->prev = temp;

	if (count == 0)
		head = tail = temp;
	else
		head = temp;

	++count;
}

template<class T>
void Stack<T>::AddTail(T data)
{
	Node<T>* temp = new Node<T>;
	temp->next = 0;
	temp->data = data;
	temp->prev = tail;

	if (tail != 0)
		tail->next = temp;

	if (count == 0)
		head = tail = temp;
	else
		tail = temp;

	++count;
}

template<class T>
void Stack<T>::DeleteTail()
{
	try {
		if (!tail)
			throw "Stack is empty.";

		Node<T>* temp = tail;

		if (count == 1) {
			head = tail = NULL;
			delete temp;
		}
		else {
			tail = tail->prev;
			tail->next = 0;
			delete temp;
		}
		--count;
	}
	catch (char* str) {
		cout << str << endl;
	}
}

template<class T>
void Stack<T>::DeleteHead()
{
	try {
		if (!head)
			throw "Stack is empty.";

		Node<T>* temp = head;

		if (count == 1) {
			head = tail = NULL;
			delete temp;
		}
		else {
			head = head->next;
			head->prev = 0;
			delete temp;
		}
		--count;
	}
	catch (char* str) {
		cout << str << endl;
	}
}

template<class T>
void Stack<T>::show()
{
	if (head) {
		if (tail == nullptr)
		{
			tail = head;
		}
		else if (head == nullptr)
		{
			head = tail;
		}

		Node<T>* temp = head;
		while (temp->next != NULL)
		{
			try
			{
				cout << temp->data << endl;
				temp = temp->next;
			}
			catch (const std::exception&)
			{

			}
		}
		cout << temp->data << endl;
	}
	else
		cout << "Stack is empty." << endl;

	cout << endl;
}

template<class T>
void Stack<T>::ShowCount()
{
	cout << "Count of elements: " << count << endl;
}

//Implementation of the Iterator class
template<class T>
Iterator<T>::Iterator()
{
	q = new Stack<T>;
	current = NULL;
}

template<class T>
Iterator<T>::Iterator(Stack<T>* obj)
{
	q = obj;
}

template<class T>
bool Iterator<T>::begin()
{
	if (q->head) {
		current = q->head;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::end()
{
	if (q->tail) {
		current = q->tail;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::operator++()
{
	if (current->next) {
		current = current->next;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::operator--()
{
	if (current->prev) {
		current = current->prev;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::operator==(T data)
{
	if (current->data != data)
		return true;
	else
		return false;
}

template<class T>
T Iterator<T>::operator*()
{
	if (current)
		return current->data;
}

// operator overloading
bool operator == (Sotrudnik& obj, string prop)
{
	if (obj.Name.empty())
	{
		return false;
	}

	char s1[20];
	itoa(obj.staj, s1, 10);

	if (obj.Name == prop || obj.Doljn == prop || s1 == prop)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator == (Sotrudnik& obj, Sotrudnik& prop)
{
	if (obj.Name.empty() || prop.Name.empty())
	{
		return false;
	}

	if (obj.Name == prop.Name || obj.Doljn == prop.Doljn || obj.staj == prop.staj)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator != (Sotrudnik& obj, Sotrudnik& prop)
{
	if (obj.Name.empty() || prop.Name.empty())
	{
		return true;
	}

	if (obj.Name == prop.Name || obj.Doljn == prop.Doljn || obj.staj == prop.staj)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool operator<=(const Sotrudnik& a, const Sotrudnik& b)
{
	return a.staj <= b.staj ? true : false;
}

ostream& operator<<(ostream& out, const Sotrudnik& obj)
{
	out << "Name: " << obj.Name << "\nDoljnost: " << obj.Doljn << "\nstaj: " << obj.staj;
	return out;
}

istream& operator>>(istream& in, Sotrudnik& obj)
{
	flushall();
	cout << "\nName: ";
	in >> obj.Name;

	cout << "Doljnost: ";
	in >> obj.Doljn;

	cout << "Staj: ";
	in >> obj.staj;
	return in;
}

int main()
{
	Stack<Sotrudnik>* temp = new Stack<Sotrudnik>;
	Iterator<Sotrudnik> iter(temp);

	Sotrudnik objSotrudnik;

	int choice = 1;
	cout << "1 - AddHead; 2 - AddTail; 3 - DeleteHead; 4 - DeleteTail; \n5 - Show (iter++); 6 - Show (iter--); 7 - getElement;" << endl;
	cout << "8 - Sort; 9 - Searching; 10 - Delete" << endl;
	cout << "\nYour choice: ";
	cin >> choice;
	while (choice >= 1 & choice <= 11) {
		switch (choice)
		{
		case 1: {
			cin >> objSotrudnik;
			temp->AddHead(objSotrudnik);
			break;
		}
		case 2: {
			cin >> objSotrudnik;
			temp->AddTail(objSotrudnik);
			break;
		}
		case 3: {
			temp->ShowCount();
			temp->DeleteHead();
			temp->ShowCount();
			break;
		}
		case 4: {
			temp->ShowCount();
			temp->DeleteTail();
			temp->ShowCount();
			break;
		}
		case 5: {
			int count = 0;

			try {
				if (iter.begin() != true)
					throw "Stack is empty.";

				do {
					cout << count + 1 << " Sotrudnik" << endl;
					cout << *iter << endl;
					cout << "\n";
					++count;
				} while ((++iter) == true);
			}
			catch (char* str) {
				cout << str << endl;
			}

			break;
		}
		case 6:
		{
			int count = temp->count;

			try {
				if (iter.end() != true)
					throw "Stack is empty.";

				do {
					cout << count << " Sotrudnik" << endl;
					cout << *iter << endl;
					cout << "\n";
					--count;
				} while ((--iter) == true);
			}
			catch (char* str) {
				cout << str << endl;
			}

			break;
		}
		case 7: {
			int Sotrudnik = 0;
			cout << "Get sotrudnik: ";
			cin >> Sotrudnik;

			if (Sotrudnik > temp->count)
				cout << "Your choise isn't correct." << endl;
			else {
				if (iter.begin() == true) {
					if (Sotrudnik == 1)
						cout << "\nResult\n" << *iter << endl;
					else {
						for (int i = 0; i < Sotrudnik; ++i)
							++iter;

						cout << "\nResult\n" << *iter << endl;
					}
				}
			}
			break;
		}
		case 8: {
			cout << "\nThe result of sorting\n" << endl;

			Algoritm<Sotrudnik> example;
			example.qsort(iter.ReturnHead(), iter.ReturnTail());
			temp->show();
			break;
		}
		case 9: {
			string data;
			Algoritm<Sotrudnik> example;

			cout << "\nEntering the staj: ";
			cin >> data;

			example.FindElement(iter.ReturnHead(), iter.ReturnTail(), data);
			break;
		}
		case 10: {
			string data;
			Algoritm<Sotrudnik> example;

			cout << "\nEntering the staj: ";
			cin >> data;

			cout << "\nThe result of delete\n" << endl;
			example.DeleteElement(iter.ReturnHead(), iter.ReturnTail(), data);
			temp->show();

			break;
		}
		}
		cout << "\nYour choice: ";
		cin >> choice;
	}
}