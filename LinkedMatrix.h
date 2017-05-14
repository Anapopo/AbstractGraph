#include "Triple.h"
#include "SeqList.h"
#include "SortedSinglyList.h"

class LinkedMatrix
{
private:
    int rows, columns;
    void init(int rows, int columns);
public:
    SeqList<SortedSinglyList<Triple>*> rowlist;
    LinkedMatrix(int rows=0);
    LinkedMatrix(int rows, int columns);
    LinkedMatrix(int rows, int columns, Triple elem[], int n);
    LinkedMatrix(LinkedMatrix& mat);
    ~LinkedMatrix();

    int get(int i, int j);
    int getRows();
    int getColumns();
    void set(int i, int j, int x);
    void set(Triple e);
    friend ostream& operator<<(ostream& out, LinkedMatrix&);
    LinkedMatrix& operator=(LinkedMatrix& mat);
    void setRowsColumns(int rows, int columns);
};

void LinkedMatrix::init(int rows, int columns)
{
    if (rows >= 0 && columns >= 0)
    {
        this->rows = rows;
        this->columns = columns;
        for (int i = 0; i < rows; i++)
            this->rowlist.insert(new SortedSinglyList<Triple>(true));
    }
    else throw invalid_argument("args error!");
}

LinkedMatrix::LinkedMatrix(int rows) {this->init(rows, rows);}

LinkedMatrix::LinkedMatrix(int rows, int columns) {this->init(rows, columns);}

LinkedMatrix::LinkedMatrix(int rows, int columns, Triple elem[], int n)
{
    this->init(rows, columns);
    for (int i = 0; i < n; i++)
        this->set(elem[i]);
}

LinkedMatrix::~LinkedMatrix()
{
    for (int i = 0; i < this->rows; i++)
        this->rowlist[i]->~SortedSinglyList<Triple>();
}

ostream& operator<<(ostream& out, LinkedMatrix &mat)
{
    for (int i = 0; i < mat.rows; i++)
        out << i << "->" << (*mat.rowlist[i]);
    return out;
}

int LinkedMatrix::get(int i, int j)
{
    if (i >= 0 && i < this->rows&&j >= 0 && j < this->columns)
    {
        Node<Triple> *find = (*this->rowlist[i]).search(Triple(i,j,0));
        return find == nullptr ? 0 : find->data.value;
    }
    throw out_of_range("args error!");
}

int LinkedMatrix::getRows() { return this->rows; }

int LinkedMatrix::getColumns() { return this->columns; }

void LinkedMatrix::set(int i, int j, int x)
{
    if (i >= 0 && i < this->rows&&j >= 0 && j < this->columns)
    {
        SortedSinglyList<Triple> *list = this->rowlist[i];
        if (x == 0)
            list->removeFirst(Triple(i,j,x));
        else
        {
            Node<Triple> *find = list->search(Triple(i,j,x));
            if (find != nullptr)
                find->data.value = x;
            else list->insert(Triple(i,j,x));
        }
    }
    else throw out_of_range("args error!");
}

void LinkedMatrix::set(Triple e) {this->set(e.row, e.column, e.value);}

void LinkedMatrix::setRowsColumns(int rows, int columns)
{
    if (rows > this->rows)
        for (int i = this->rows; i < rows; i++)
            this->rowlist.insert(new SortedSinglyList<Triple>());
    this->rows = rows;
    this->columns = columns;
}

LinkedMatrix::LinkedMatrix(LinkedMatrix& mat)
{
    this->rows = mat.getRows();
    this->columns = mat.getColumns();

    for (int i = 0; i < mat.getRows(); i++)
        this->rowlist.insert(new SortedSinglyList<Triple>(true));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            this->set(i, j, mat.get(i, j));
    
        
}
LinkedMatrix& LinkedMatrix::operator=(LinkedMatrix& mat)
{
    if (this != &mat)
    {
        this->~LinkedMatrix();
        this->rows = mat.getRows();
        this->columns = mat.getColumns();

        for (int i = 0; i < mat.getRows(); i++)
            this->rowlist.insert(new SortedSinglyList<Triple>(true));

        for (int i = 0; i < mat.getRows(); i++)
            for (int j = 0; j < mat.getColumns(); j++)
                this->set(i, j, mat.get(i, j));
        return *this;
    }
}
