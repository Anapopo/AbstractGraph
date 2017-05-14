template <class T>
class Node
{
public:
    T data;
    Node<T> *next;

    Node() { this->next = nullptr; }

    Node(T data, Node<T> *next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};
