#include <iostream>
#include "Node.h"
template <class T>
class SinglyList
{
public:
    Node<T> *head;
    SinglyList();
    SinglyList(T values[], int n);
    SinglyList(SinglyList<T> &list);
    ~SinglyList();

    bool empty();
    int count();
    T& get(int i);
    void printAll();

    void set(int i,T x);
    Node<T>* search(T value);
    Node<T>* insert(T x);
    Node<T>* insert(int i, T x);
    SinglyList<T> insert(int i, SinglyList<T> &list);

    T remove(int i);
    void removeAll();
    SinglyList<T> remove(int i, int n);
    void removeAll(SinglyList<T> &pattern);
    void replaceAll(SinglyList<T> &pattern, SinglyList<T> &list);
    bool contain(SinglyList<T> &list);
    SinglyList<T> sub(int i, int n);

    SinglyList<T> operator+(SinglyList<T> &list);
    void operator+=(SinglyList<T> &list);
    bool operator==(SinglyList<T> &list);
    bool operator!=(SinglyList<T> &list);
    void operator=(SinglyList<T> &list);
};

template <class T>
SinglyList<T>::SinglyList() { this->head = new Node<T>(); }

template <class T>
SinglyList<T>::SinglyList(T values[], int n)
{
    this->head = new Node<T>();
    Node<T> *rear = this->head;
    for (int i = 0; i<n; i++)
    {
        rear->next = new Node<T>(values[i]);
        rear = rear->next;
    }
}

template <class T>
SinglyList<T>::SinglyList(SinglyList<T> &list)
{
    this->head = new Node<T>();
    Node<T> *rear = this->head;
    Node<T> *other = list.head->next;

    while(other)
    {
        rear->next = new Node<T>(other->data, rear->next);
        rear = rear->next;
        other = other->next;
    }
}

template <class T>
SinglyList<T>::~SinglyList()
{
    this->removeAll();
    delete this->head;
}

template <class T>
bool SinglyList<T>::empty() { return (this->head->next == nullptr); }

template <class T>
int SinglyList<T>::count()
{
    int count = 0;
    Node<T> *start = this->head;
    while (start->next)
    {
        count++;
        start = start->next;
    }
    return count;
}

template <class T>
T& SinglyList<T>::get(int i)
{
    if (i < 0) i = 0;
    Node<T> *current = this->head->next;
    for (int j = 0; current != nullptr && j < i; j++) current = current->next;
    if (current) return current->data;
    throw std::out_of_range("Your get() function can not find the specify element.");
}

template <class T>
Node<T>* SinglyList<T>::insert(int i, T x)
{
    Node<T> *front = this->head;
    for (int j = 0; front->next != nullptr && j < i; j++) front = front->next;
    front->next = new Node<T>(x, front->next);
    return front->next;
}

template <class T>
Node<T>* SinglyList<T>::insert(T x)
{
    Node<T> *front = this->head;
    while (front->next) front = front->next;
    front->next = new Node<T>(x);
    return front->next;
}

template <class T>
void SinglyList<T>::set(int i, T x)
{
    Node<T> *front = this->head;
    for (int j = 0;front->next != nullptr && j < i; j++) front = front->next;
    front->next->data = x;
}

template<class T>
Node<T>* SinglyList<T>::search(T value)
{
    Node<T> *front = this->head;
    while (front->next && front->next->data != value) front = front->next;
    return (front->next && front->next->data == value) ? front : nullptr;
}

template <class T>
void SinglyList<T>::printAll()
{
    std::cout << "(";
    Node<T> *front = this->head;
    while (front->next)
    {
        std::cout << front->next->data;
        if (front->next->next) std::cout << ",";
        front = front->next;
    }
    std::cout << ")length:" << this->count() << std::endl;
}

template <class T>
T SinglyList<T>::remove(int i)
{
    Node<T> *front = this->head;
    for (int j = 0; front->next && j < i; j++) front = front->next;
    if (i >= 0 && front->next)
    {
        Node<T> *temp = front->next;
        T old = front->next->data;
        front->next = front->next->next;
        delete temp;
        return old;
    }
    throw std::out_of_range("Your get() function can not find the specify element.");
}

template <class T>
void SinglyList<T>::removeAll()
{
    Node<T>* front = head;
    while (front->next)
    {
        Node<T>* temp = front->next;
        front->next = front->next->next;
        delete temp;
    }
    head->next = nullptr;
}

template <class T>
void SinglyList<T>::removeAll(SinglyList<T> &pattern)
{
    Node<T> *remember = this->head;
    Node<T> *current = this->head->next;
    Node<T> *rear = pattern.head->next;
    while (current)
    {
        if (current->data == rear->data)
        {
            rear = rear->next;
            current = current->next;
        }
        else
        {
            remember = remember->next;
            rear = pattern.head->next;
            current = remember->next;
        }
        if (!rear)
        {
            current = remember;
            rear = pattern.head->next;
            while (rear)
            {
                Node<T> *temp = current->next;
                current->next = current->next->next;
                delete temp;
                rear = rear->next;
            }
            current = current->next;
            rear = pattern.head->next;
        }
    }
}

template<class T>
void SinglyList<T>::operator+=(SinglyList<T> &list)
{
    Node<T> *rear = this->head;
    while (rear->next)
        rear = rear->next;
    rear->next = list.head->next;
    list.head->next = nullptr;
}

template <class T>
void SinglyList<T>::operator=(SinglyList<T> &list)
{
    this->head = new Node<T>();
    Node<T> *rear = this->head;
    Node<T> *other = list.head->next;
    while (other)
    {
        rear->next = new Node<T>(other->data, rear->next);
        rear = rear->next;
        other = other->next;
    }
}

template <class T>
bool SinglyList<T>::operator==(SinglyList<T> &list)
{
    if (this->head == list.head) return true;
    Node<T> *p = this->head->next;
    Node<T> *q = list.head->next;
    while (p&&q)
    {
        if (p->data != q->data) return false;
        p = p->next;
        q = q->next;
    }
    return (!p && !q) ? true : false;
}

template <class T>
bool SinglyList<T>::operator!=(SinglyList<T> &list)
{
    if (this->head == list.head) return false;
    Node<T> *p = this->head->next;
    Node<T> *q = list.head->next;
    while (p&&q)
    {
        if (p->data != q->data) return true;
        p = p->next;
        q = q->next;
    }
    return (!p && !q) ? false : true;
}

template <class T>
bool SinglyList<T>::contain(SinglyList<T> &list)
{
    Node<T> *rear = list.head->next;
    while (rear)
    {
        if (!this->search(rear->data)) return false;
        rear = rear->next;
    }
    return true;
}

template <class T>
SinglyList<T> SinglyList<T>::sub(int i, int n)
{
    SinglyList<T> list;
    int length = this->count();
    if (i < 0 || i >= length) return list;
    if ((length - i) < n) n = (length - i);
    Node<T> *start = this->head->next;
    for (int j = 0; start != nullptr && j < i; j++) start = start->next;
    Node<T> *rear = list.head;
    while (n)
    {
        rear->next = new Node<T>(start->data);
        rear = rear->next;
        start = start->next;
        n--;
    }
    return list;
}

template <class T>
SinglyList<T> SinglyList<T>::insert(int i, SinglyList<T> &list)
{
    SinglyList<T> raw(*this);
    SinglyList<T> extra(list);
    Node<T> *start = raw.head;
    if (i > 0 && start->next != nullptr) {
        for (int j = 0; start != nullptr && j < i; j++)
            start = start->next;
    }
    Node<T> *temp = start->next;
    start->next = extra.head->next;
    extra.head->next = nullptr;
    Node<T> *p = start->next;
    while (p->next) p = p->next;
    p->next = temp;
    return raw;
}

template <class T>
SinglyList<T> SinglyList<T>::operator+(SinglyList<T> &list)
{
    SinglyList<T> raw(*this);
    Node<T> *rear = raw.head;
    while (rear->next) rear = rear->next;
    Node<T> *current = list.head;
    while (current->next)
    {
        if (!raw.search(current->next->data))
        {
            rear->next = new Node<T>(current->next->data);
            rear = rear->next;
        }
        current = current->next;
    }
    return raw;
}

template <class T>
SinglyList<T> SinglyList<T>::remove(int i, int n)
{
    SinglyList<T> list;
    Node<T> *front = this->head;
    for (int j = 0; front != nullptr && j < i; j++) front = front->next;
    Node<T> *rear = list.head;
    rear->next = front->next;
    Node<T> *temp = front;
    while (n)
    {
        front = front->next;
        n--;
    }
    rear->next = temp->next;
    temp->next = front->next;
    front->next = nullptr;
    return list;
}

template <class T>
void SinglyList<T>::replaceAll(SinglyList<T> &pattern, SinglyList<T> &list)
{
    Node<T> *remember = this->head;
    Node<T> *current = this->head->next;
    Node<T> *rear = pattern.head->next;
    Node<T> *replace = list.head->next;
    while (current)
    {
        if (current->data == rear->data)
        {
            current = current->next;
            rear = rear->next;
        }
        else 
        {
            remember = remember->next;
            rear = pattern.head->next;
            current = remember->next;
        }
        if (!rear)
        {
            current = remember;
            rear = pattern.head->next;
            while (rear) 
            {
                Node<T> *temp = current->next;
                current->next = current->next->next;
                delete temp;
                rear = rear->next;
            }
            while (replace) 
            {
                current->next = new Node<T>(replace->data, current->next);
                current = current->next;
                replace = replace->next;
            }
            remember = current;
            current = current->next;
            replace = list.head->next;
            rear = pattern.head->next;
        }
    }
}
