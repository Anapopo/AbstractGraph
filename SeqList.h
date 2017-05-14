#pragma once
#include <iostream>
using namespace std;
#include <exception>

template <class T>
class SeqList
{
private:
    void init(T value[], int n);
public:
    T *element;
    int length;
    int n;
    SeqList(int length = 32);
    SeqList(int length, T x);
    SeqList(T values[], int n);
    ~SeqList();

    bool empty();
    int count();
    bool contain(SeqList<T>& list);
    T& operator[](int i);
    friend ostream& operator<<<>(ostream&, SeqList<T>&);
    bool operator==(SeqList<T>&);
    SeqList<T>& SeqList<T>::operator=(SeqList<T>& list);
    void insert(int i, T x);
    T& get(int i);
    virtual void insert(T x);
    T remove(int i);
    void removeAll();
    virtual int search(T key, int start = 0);

    SeqList(SeqList<T> &list);
};

template <class T>
SeqList<T>::SeqList(int length)
{
    this->element = new T[length];
    this->length = length;
    this->n = 0;
}

template <class T>
SeqList<T>::SeqList(int length, T x)
{
    this->element = new T[length];
    this->length = this->n = length;
    for (int i = 0; i < this->n; i++)
        this->element[i] = x;
}

template <class T>
SeqList<T>::SeqList(T values[], int n)
{
    this->init(values, n);
}

template <class T>
void SeqList<T>::init(T values[], int n)
{
    this->length = n * 2;
    this->element = new T[this->length];
    this->n = n;
    for (int i = 0; i < n; i++)
        this->element[i] = values[i];
}

template <class T>
SeqList<T>::~SeqList()
{
    delete[] this->element;
}

template <class T>
T& SeqList<T>::get(int i)
{    
    if (i >= 0 && i < n)
        return this->element[i];
    throw out_of_range("can not find the specify i!");
}

template <class T>
bool SeqList<T>::empty() { return this->n == 0; }

template <class T>
int SeqList<T>::count() { return this->n; }

template <class T>
T& SeqList<T>::operator[](int i) { return this->get(i); }

template <class T>
bool SeqList<T>::contain(SeqList<T>& list)
{    
    bool flag = true;
    for (int i = 0; i < list.count(); i++)
        if (this->search(list[i]) == -1)
            flag = false;
    return flag;
}

template <class T>
ostream& operator<<<>(ostream& out, SeqList<T>& list)
{
    out << "(";
    if (list.n > 0)
        out << list.element[0];
    for (int i = 1; i < list.n; i++)
        out << "," << list.element[i];
    out << ")" << endl;
    return out;
}

template <class T>
void SeqList<T>::insert(int i, T x)
{
    if (i < 0) i = 0;
    if (i > this->n) i = this->n;
    T* temp = this->element;
    if (this->n == this->length)
    {
        this->length *= 2;
        this->element = new T[this->length];
        for (int j = 0; j < i; j++)
            this->element[j] = temp[j];
    }
    for (int j = this->n - 1; j >= i; j--)
        this->element[j + 1] = temp[j];
    if (temp != this->element)
        delete[] temp;
    this->element[i] = x;
    this->n++;
}

template <class T>
void SeqList<T>::insert(T x) { insert(this->n, x); }

template <class T>
T SeqList<T>::remove(int i)
{
    if (this->n > 0 && i >= 0 && i < n)
    {
        T old = this->element[i];
        for (int j = i; j < this->n; j++)
            this->element[j] = element[j + 1];
        this->n--;
        return old;
    }
    throw out_of_range("can not find the specify i!");
}

template <class T>
void SeqList<T>::removeAll()
{
    this->n = 0;
    delete[] this->element;
}

template <class T>
int SeqList<T>::search(T key, int start)
{
    for (int i = start; i < this->n; i++)
        if (this->element[i] == key)
            return i;
    return -1;
}

template <class T>
bool SeqList<T>::operator==(SeqList<T>& list)
{
    if (this->n != list.count()) return false;

    for (int i = 0; i < this->n; i++)
        if (this->element[i] != list.get(i))
            return false;
    return true;
}

template <class T>
SeqList<T>& SeqList<T>::operator=(SeqList<T>& list)
{
    if (this->length <= list.n)
    {
        this->n = list.n;
        for (int i = 0; i < this->n; i++)
            this->element[i] = list.element[i];
        return *this;
    }
    this->~SeqList();
    this->init(list.element, list.count());
    return *this;
}

template <class T>
SeqList<T>::SeqList(SeqList<T> &list) { this->init(list.element, list.count()); }
