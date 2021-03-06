#include "SinglyList.h"

template <class T>
class SortedSinglyList : public SinglyList<T>
{
private:
    bool asc;
public:
    SortedSinglyList(bool asc = true);
    SortedSinglyList(T values[], int n, bool asc = true);
    void set(int i, T x);
    Node<T>* insert(T x);
    Node<T>* search(T key);
    void removeFirst(T key);
    friend ostream& operator<<<>(ostream&, SortedSinglyList<T>&);
};

template <class T>
SortedSinglyList<T>::SortedSinglyList(bool asc) {this->asc = asc;}

template <class T>
SortedSinglyList<T>::SortedSinglyList(T values[], int n, bool asc)
{
    this->asc = asc;
    for (int i = 0; i < n; i++)
        this->insert(values[i]);
}

template <class T>
void SortedSinglyList<T>::set(int i, T x) { throw logic_error("You can not use set()!"); }

template <class T>
Node<T>* SortedSinglyList<T>::insert(T x)
{
    Node<T>* front = head, *p = head->next;
    while (p != nullptr && (asc ? x >= p->data : x <= p->data))
    {
        front = p;
        p = p->next;
    }
    Node<T>* q = new Node<T>(x,p);
    front->next = q;
    return q;
}

template <class T>
void SortedSinglyList<T>::removeFirst(T key)
{
    Node<T>* front = head, *p = head->next;
    while (p != nullptr && (asc ? key > p->data:key < p->data))
    {
        front = p;
        p = p->next;
    }
    if (p != nullptr&&key == p->data)
    {
        front->next = p->next;
        delete p;
    }
}

template <class T>
ostream& operator<<<>(ostream& out, SortedSinglyList<T>& list)
{
    out << "(";
    Node<T> *front = list.head;
    while (front->next)
    {
        out << front->next->data;
        if (front->next->next) out << ",";
        front = front->next;
    }
    out << ")" << endl;
    return out;
}

template <class T>
Node<T>* SortedSinglyList<T>::search(T key)
{
    Node<T> *front = this->head;
    if (asc ? (front->next && key < front->next->data) : (front->next && key  > front->next->data)) return nullptr;
    while (front->next)
    {
        if (front->next->data == key)
            return front->next;
        front = front->next;
    }
    return nullptr;
}
