#include <iostream>
using namespace std;
template <typename T>
struct Elem
{
	// Любые данные
	T data;
	Elem* next, * prev;
};
template <typename T>
class List
{
	// Голова хвост
	Elem<T>* Head, * Tail;
	int Count;
public:
	List();
	List(const List&);
	~List();
	int GetCount();
	Elem<T>* GetElem(int);
	void DelAll();
	void Del(int);
	void Del();
	void DelRange(int, int);
	void AddTail();
	void AddTail(T);
	void AddHead(T);
	void AddHead();
	void Print();
	void Print(int pos);
	List& operator = (const List&);
	List operator + (const List&);
	bool operator == (const List&);
	bool operator != (const List&);
	bool operator <= (const List&);
	bool operator >= (const List&);
	bool operator < (const List&);
	bool operator > (const List&);
	List operator - ();
};
template <typename T>
List<T>::List()
{
	Head = Tail = 0;
	Count = 0;
}
template <typename T>
List<T>::List(const List& L)
{
	Head = Tail = 0;
	Count = 0;
	Elem<T>* temp = L.Head;
	while (temp != 0)
	{
		AddTail(temp->data);
		temp = temp->next;
	}
}
template <typename T>
List<T>::~List()
{
	DelAll();
}
template <typename T>
Elem<T>* List<T>::GetElem(int pos)
{
	Elem<T>* temp = Head;
	//Позиция от 1 до Count?
	if (pos < 1 || pos > Count)
	{
		//Неверная позиция
		cout << "Incorrect position !!!\n";
		return ;
	}
	int i = 1;
	while (i < pos && temp != 0)
	{
		temp = temp->next;
		i++;
	}
	if (temp == 0)
		return 0;
	else
		return temp;
}
template <typename T>
void List<T>::AddHead()
{
	Elem<T>* temp = new Elem<T>;
	temp->prev = 0;
	int n;
	cout << "Input new number: ";
	cin >> n;
	temp->data = n;
	temp->next = Head;
	if (Head != 0)
		Head->prev = temp;
	if (Count == 0)
		Head = Tail = temp;
	else
		Head = temp;
	Count++;
}
template <typename T>
void List<T>::AddHead(T n)
{
	Elem<T>* temp = new Elem<T>;
	temp->prev = 0;
	temp->data = n;
	temp->next = Head;
	if (Head != 0)
		Head->prev = temp;
	if (Count == 0)
		Head = Tail = temp;
	else
		Head = temp;
	Count++;
}
template <typename T>
void List<T>::AddTail()
{
	Elem<T>* temp = new Elem<T>;
	temp->next = 0;
	int n;
	cout << "Input new number: ";
	cin >> n;
	temp->data = n;
	temp->prev = Tail;
	if (Tail != 0)
		Tail->next = temp;
	if (Count == 0)
		Head = Tail = temp;
	else
		Tail = temp;
	Count++;
}
template <typename T>
void List<T>::AddTail(T n)
{
	Elem<T>* temp = new Elem<T>;
	temp->next = 0;
	temp->data = n;
	temp->prev = Tail;
	if (Tail != 0)
		Tail->next = temp;
	if (Count == 0)
		Head = Tail = temp;
	else
		Tail = temp;
	Count++;
}
template <typename T>
void List<T>::Del()
{
	int n;
	cout << "Input position: ";
	cin >> n;
	if (n < 1 || n > Count)
	{
		cout << "Incorrect position !!!\n";
		return;
	}
	int i = 1;
	Elem<T>* Del = Head;
	while (i <= n)
	{
		//Доходим до элемента, который удаляется
		Del = Del->next;
		i++;
	}
	//Доходим до элемента, который предшествует 
	//удаляемому
	Elem<T>* PrevDel = Del->prev;
	//Доходим до элемента, который следует за удаляемым
	Elem<T>* AfterDel = Del->next;
	if (PrevDel != 0 && Count != 1)
		PrevDel->next = AfterDel;
	if (AfterDel != 0 && Count != 1)
		AfterDel->prev = PrevDel;
	if (n == 1)
		Head = AfterDel;
	if (n == Count)
		Tail = PrevDel;
	delete Del;
	Count--;
}
template <typename T>
void List<T>::Del(int n)
{
	if (n < 1 || n > Count)
	{
		cout << "Incorrect position !!!\n";
		return;
	}
	int i = 1;
	Elem<T>* Del = Head;
	while (i < n)
	{
		//Доходим до элемента, который удаляется
		Del = Del->next;
		i++;
	}
	//Доходим до элемента, который предшествует
	//удаляемому
	Elem<T>* PrevDel = Del->prev;
	//Доходим до элемента, который следует за
	//удаляемым
	Elem<T>* AfterDel = Del->next;
	if (PrevDel != 0 && Count != 1)
		PrevDel->next = AfterDel;
	if (AfterDel != 0 && Count != 1)
		AfterDel->prev = PrevDel;
	if (n == 1)
		Head = AfterDel;
	if (n == Count)
		Tail = PrevDel;
	delete Del;
	Count--;
}
template <typename T>
void List<T>::DelRange(int pos1, int pos2)
{
	if (pos1 < 1 || pos2 < pos1 || pos2 > Count)
	{
		cout << "Incorrect positions!\n";
		return;
	}

	int i = 1;
	Elem<T>* DelStart = Head;
	while (i < pos1 && DelStart)
	{
		//Доходим до элемента, который удаляется
		DelStart = DelStart->next;
		i++;
	}

	Elem<T>* DelEnd = DelStart;
	while (i < pos2 && DelEnd)
	{
		//Доходим до элемента, который удаляется
		DelEnd = DelEnd->next;
		i++;
	}

	if (!DelStart || !DelEnd)
	{
		cout << "Failed to find specified positions!\n";
		return;
	}

	Elem<T>* PrevDels = DelStart->prev;
	Elem<T>* AfterDele = DelEnd->next;

	if (PrevDels)
		PrevDels->next = AfterDele;
	else
		Head = AfterDele;

	if (AfterDele)
		AfterDele->prev = PrevDels;
	else
		Tail = PrevDels;

	Elem<T>* current = DelStart;
	while (current && current != AfterDele)
	{
		Elem<T>* next = current->next;
		delete current;
		current = next;
		Count--;
	}
		if (Count == 0)
		Head = Tail = nullptr;
}

template <typename T>
void List<T>::Print(int pos)
{
	//Позиция от 1 до Count?
	if (pos < 1 || pos > Count)
	{
		//Неверная позиция
		cout << "Incorrect position !!!\n";
		return;
	}
	Elem<T>* temp;
	//Определяем с какой стороны
	//быстрее двигаться
	if (pos <= Count / 2)
	{
		//Отсчет с головы
		temp = Head;
		int i = 1;
		while (i < pos)
		{
			// Двигаемся до нужного элемента
			temp = temp->next;
			i++;
		}
	}
	else
	{
		//Отсчет с хвоста
		temp = Tail;
		int i = 1;
		while (i <= Count - pos)
		{
			//Двигаемся до нужного элемента
			temp = temp->prev;
			i++;
		}
	}
	//Вывод элемента
	cout << pos << " element: ";
	cout << temp->data << "\n";
}
template <typename T>
void List<T>::Print()
{
	if (Count != 0)
	{
		Elem<T>* temp = Head;
		while (temp != 0)
		{
			cout << temp->data << "\n";
			temp = temp->next;
		}
	}
}
template <typename T>
void List<T>::DelAll()
{
	while (Count != 0)
		Del(1);
}
template <typename T>
int List<T>::GetCount()
{
	return Count;
}
template <typename T>
List<T>& List<T>::operator = (const List<T>& L)
{
	if (this == &L)
		return *this;
	this->~List();
	Elem<T>* temp = L.Head;
	while (temp != 0)
	{
		AddTail(temp->data);
		temp = temp->next;
	}
	return *this;
}
template <typename T>
List<T> List<T>::operator + (const List<T>& L)
{
	List Result(*this);
	Elem<T>* temp = L.Head;
	while (temp != 0)
	{
		Result.AddTail(temp->data);
		temp = temp->next;
	}
	return Result;
}
template <typename T>
bool List<T>::operator == (const List<T>& L)
{
	if (Count != L.Count)
		return false;
	Elem<T>* t1, * t2;
	t1 = Head;
	t2 = L.Head;
	while (t1 != 0)
	{
		if (t1->data != t2->data)
			return false;
		t1 = t1->next;
		t2 = t2->next;
	}
	return true;
}
template <typename T>
bool List<T>::operator != (const List& L)
{
	if (Count != L.Count)
		return true;
	Elem<T>* t1, * t2;
	t1 = Head;
	t2 = L.Head;
	while (t1 != 0)
	{
		if (t1->data != t2->data)
			return true;
		t1 = t1->next;
		t2 = t2->next;
	}
	return false;
}
template <typename T>
bool List<T>::operator >= (const List& L)
{
	if (Count > L.Count)
		return true;
	if (*this == L)
		return true;
	return false;
}
template <typename T>
bool List<T>::operator <= (const List& L)
{
	if (Count < L.Count)
		return true;
	if (*this == L)
		return true;
	return false;
}
template <typename T>
bool List<T>::operator > (const List& L)
{
	if (Count > L.Count)
		return true;
	return false;
}
template <typename T>
bool List<T>::operator < (const List& L)
{
	if (Count < L.Count)
		return true;
	return false;
}
template <typename T>
List<T> List<T>::operator - ()
{
	List<T> Result;
	List<char> rr;
	Elem<T>* temp = Head;
	while (temp != 0)
	{
		Result.AddHead(temp->data);
		temp = temp->next;
	}
	return Result;
}
//Тестовый пример
void main()
{
	List <int> L;
	const int n = 10;
	int a[n] = { 0,1,2,3,4,5,6,7,8,9 };
	//Добавляем элементы, стоящие на четных 
	//индексах, в голову, на нечетных - в хвост
	for (int i = 0; i < n; i++) {

		L.AddHead(a[i]);
	}
	
	//Распечатка списка
	cout << "List L:\n";
	L.Print();
	cout << "\n\n";
	
	L.DelRange(7,8);
	L.Print();
}