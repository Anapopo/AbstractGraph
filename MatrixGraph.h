#include "SeqList.h"
#include "Matrix.h"
#include "Triple.h"
#include "AbstractGraph.h"

template <class T>
class MatrixGraph : public AbstractGraph<T>
{
private:
    int n;
    SeqList<T> verlist;
    Matrix mat;
public:
    MatrixGraph();
    MatrixGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount);

    bool directed;
    int vertexCount();
    T& getVertex(int i);
    void setVertex(int i, T x);
    void removeVertex(int i);
    int insertVertex(T x);

    void insertEdge(int i, int j, int weight);
    void insertEdge(Triple edge);
    Triple getEdge(int i, int j);
    void removeEdge(int i, int j);
    void removeEdge(Triple edge);

    int cost();
    int weight(int i, int j);
    int next(int i, int j);
    int degree(int i);
    int indegree(int i);
    int outdegree(int i);
    int edgeCount();
    int minWeight();
    bool isComplete();
    Triple minWeightEdge();

    SeqList<T> getVerlist();
    Matrix getMatrix();
    bool isSubgraph(MatrixGraph<T> &graph);
    bool isSpanSubgraph(MatrixGraph<T> &graph);
    MatrixGraph<T> createComplete(T vertices[], int vertexCount);
    friend ostream& operator<<<>(ostream& out, MatrixGraph<T>&);
    MatrixGraph<T>& operator=(MatrixGraph<T> &graph);
    bool operator==(MatrixGraph<T> &graph);
};

template <class T>
MatrixGraph<T>::MatrixGraph() { this->n = 0; }

template <class T>
MatrixGraph<T>::MatrixGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount) :
    verlist(vertices, vertexCount), mat(vertexCount * 2)
{
    this->n = vertexCount;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            this->mat.set(i, j, (i == j ? 0 : MAX_WEIGHT));
    if (vertices != NULL && vertexCount > 0 && edges != NULL)
        for (int j = 0; j < edgeCount; j++)
            this->insertEdge(edges[j]);

}
template <class T>
int MatrixGraph<T>::vertexCount(){ return this->n; }

template <class T>
T& MatrixGraph<T>::getVertex(int i) { return this->verlist[i]; }

template <class T>
void MatrixGraph<T>::setVertex(int i, T x) { this->verlist[i] = x; }

template <class T>
int MatrixGraph<T>::weight(int i, int j) { return this->mat.get(i, j); }

template <class T>
ostream& operator<<<>(ostream& out, MatrixGraph<T> &graph)
{
    out << "Vertex Points:" << graph.verlist << "Matrix:" << endl;
    for (int i = 0; i < graph.n; i++)
    {
        int w;
        for (int j = 0; j < graph.n; j++)
            if ((w = graph.weight(i, j)) == MatrixGraph<T>::MAX_WEIGHT)
                out << setw(6) << "@";
            else out << setw(6) << w;
        out << endl;

    }
    return out;
}

template <class T>
void MatrixGraph<T>::insertEdge(int i, int j, int weight)
{
    if (i != j)
    {
        if (weight <= 0 || weight > MAX_WEIGHT)
            weight = MAX_WEIGHT;
        this->mat.set(i, j, weight);
    }
    else throw invalid_argument("i can not equal to j!");
}

template <class T>
void MatrixGraph<T>::insertEdge(Triple edge) { this->insertEdge(edge.row, edge.column, edge.value); }

template <class T>
void MatrixGraph<T>::removeEdge(int i, int j)
{
    if (i != j)
        this->mat.set(i, j, MAX_WEIGHT);
}

template <class T>
void MatrixGraph<T>::removeEdge(Triple edge)
{
    this->removeEdge(edge.row, edge.column);
}

template <class T>
int MatrixGraph<T>::insertVertex(T x)
{
    this->verlist.insert(x);
    this->n++;
    if (n > mat.getRows())
        this->mat.setRowsColumns(n * 2, n * 2);
    for (int i = 0; i < this->n - 1; i++)
        this->mat.set(i, n - 1, MAX_WEIGHT);
    for (int j = 0; j < n - 1; j++)
        this->mat.set(n - 1, j, MAX_WEIGHT);
    this->mat.set(n - 1, n - 1, 0);

    return n - 1;
}

template <class T>
void MatrixGraph<T>::removeVertex(int v)
{
    if (v <0 || v>n)
        return;
    this->verlist.remove(v);
    for (int i = 0; i < n; i++)
        for (int j = v + 1; j < this->n; j++)
            this->mat.set(i-1, j, mat.get(i,j));
    this->n--;
}

template <class T>
int MatrixGraph<T>::next(int i, int j)
{
    if (i >= 0 && i < n && j >= -1 && j < n && i != j)
        for (int k = j + 1; k < n; k++)
            if (weight(i, k) > 0 && weight(i, k) < MAX_WEIGHT)
                return k;
    return -1;
}

template <class T>
int MatrixGraph<T>::indegree(int i)
{
    int sum = 0;
    for (int x = 0; x < this->n; x++)
    {   
        if (this->mat.get(x, i) == MatrixGraph<T>::MAX_WEIGHT)
            continue;
        sum += this->mat.get(x,i) > 1 ? 1 : 0;
    }
    return sum;
}

template <class T>
int MatrixGraph<T>::outdegree(int i)
{
    int sum = 0;
    for (int x = 0; x < this->n; x++)
    {
        if (this->mat.get(i,x) == MatrixGraph<T>::MAX_WEIGHT)
            continue;
        sum += this->mat.get(i,x) > 1 ? 1 : 0;
    }
    return sum;
}

template <class T>
int MatrixGraph<T>::degree(int i)
{
    return (!directed) ? indegree(i) : (indegree(i) + outdegree(i));
}

template <class T>
int MatrixGraph<T>::edgeCount()
{
    int sum = 0;
    for (int i = 0; i < this->n; i++)
        for (int j = i + 1; j < this->n; j++)
        {
            if (mat.get(i, j) == MatrixGraph<T>::MAX_WEIGHT)
                continue;
            sum += mat.get(i, j) > 1 ? 1 : 0;
        }
    return sum;
}

template <class T>
int MatrixGraph<T>::cost()
{
    int sum = 0;
    for (int i = 0; i < this->n; i++)
        for (int j = i + 1; j < this->n; j++)
        {
            if (mat.get(i, j) == MatrixGraph<T>::MAX_WEIGHT)
                continue;
            sum += mat.get(i,j);
        }
    return sum;
}

template <class T>
int MatrixGraph<T>::minWeight()
{
    int min = mat.get(0,1);
    for (int i = 0; i < this->n; i++)
        for (int j = i + 1; j < this->n; j++)
        {
            if (mat.get(i, j) == MatrixGraph<T>::MAX_WEIGHT)
                continue;
            if (mat.get(i, j) < min) 
                min = mat.get(i,j);
        }
    return min;
}

template <class T>
Triple MatrixGraph<T>::minWeightEdge()
{   
    int min_i=0, min_j=0, min_weight=mat.get(0,1);
    
    for (int i = 0; i < this->n; i++)
        for (int j = i + 1; j < this->n; j++)
        {
            if (mat.get(i, j) == MatrixGraph<T>::MAX_WEIGHT)
                continue;
            if (mat.get(i, j) < min_weight)
            {
                min_i = i;
                min_j = j;
                min_weight = mat.get(i, j);
            }
                
        }
    return Triple(min_i, min_j, min_weight);
}

template <class T>
bool MatrixGraph<T>::isComplete()
{
    return (this->edgeCount() == n * (n - 1)) ? true : false;
}

template <class T>
MatrixGraph<T> MatrixGraph<T>::createComplete(T vertices[], int vertexCount)
{
    MatrixGraph<T> graph;
    for (int x = 0; x < vertexCount; x++)
        graph.insertVertex(vertices[x]);
    
    for (int i = 0; i < vertexCount; i++)
        for (int j = 0; j < vertexCount; j++)
            graph.insertEdge(i, j, (i == j) ? 0 : 1);
    return graph;
}

template <class T>
Triple MatrixGraph<T>::getEdge(int i, int j) { return Triple(i, j, weight(i, j)); }

template <class T>
SeqList<T> MatrixGraph<T>::getVerlist() { return this->verlist; }

template <class T>
Matrix MatrixGraph<T>::getMatrix() { return this->mat; }

template <class T>
MatrixGraph<T>& MatrixGraph<T>::operator=(MatrixGraph<T> &graph)
{
    if (this != &graph)
    {
        this->n = graph.vertexCount();
        this->mat = Matrix(this->n * 2);
        this->verlist = SeqList<T>(graph.getVerlist());

        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
                this->mat.set(i, j, (i == j ? 0 : MAX_WEIGHT));


        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
                this->mat.set(i, j, graph.weight(i, j));
    }
    return this;
}

template <class T>
bool MatrixGraph<T>::operator==(MatrixGraph<T> &graph)
{
    return (graph.getVerlist() == this->verlist && this->mat == graph.getMatrix() ) ? true : false;
}

template <class T>
bool MatrixGraph<T>::isSubgraph(MatrixGraph<T> &graph)
{
    return (graph.getVerlist().contain(this->verlist) && graph.getMatrix().contain(this->mat) ) ? true : false;
}

template <class T>
bool MatrixGraph<T>::isSpanSubgraph(MatrixGraph<T> &graph)
{
    return (graph.getVerlist() == this->verlist && graph.getMatrix().contain(this->mat)) ? true : false;
}
