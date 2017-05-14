#include "LinkedMatrix.h"
#include "AbstractGraph.h"

template <class T>
class AdjListGraph:public AbstractGraph<T>
{
public:
    int n;
    bool directed;
    SeqList<T> verlist;
    LinkedMatrix adjlist;

    AdjListGraph();
    AdjListGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount);
    AdjListGraph(AdjListGraph& graph);

    int cost();
    int minWeight();
    bool isComplete();
    int degree(int i);
    int indegree(int i);
    int outdegree(int i);
    Triple minWeightEdge();
    int weight(int i, int j);
    int next(int i, int j = -1);

    int vertexCount();
    T& getVertex(int i);
    int insertVertex(T x);
    void setVertex(int i, T x);
    void removeVertex(int i);

    int edgeCount();
    void removeEdge(int i, int j);
    void insertEdge(int i, int j, int weight);

    SeqList<T> getVerlist();
    LinkedMatrix getAdjList();

    bool isSubgraph(AdjListGraph<T> &graph);
    bool isSpanSubgraph(AdjListGraph<T> &graph);
    AdjListGraph<T> createComplete(T vertices[], int vertexCount);
    friend ostream& operator<<<>(ostream&, AdjListGraph<T>&);
    AdjListGraph<T>& operator=(AdjListGraph<T> &graph);
    bool operator==(AdjListGraph<T> &graph);
};

template <class T>
AdjListGraph<T>::AdjListGraph() { this->n = 0; }

template <class T>
AdjListGraph<T>::AdjListGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount)
    :verlist(vertices, vertexCount), adjlist(vertexCount, vertexCount, edges, edgeCount)
{
    this->n = vertexCount;
}

template <class T>
ostream& operator<<<>(ostream& out, AdjListGraph<T>& graph)
{
    out << "Vertex Points:" << graph.verlist << "AdjList:"<< endl << graph.adjlist;
    return out;
}

template <class T>
void AdjListGraph<T>::insertEdge(int i, int j, int weight)
{
    if (i != j)
    {
        if (weight < 0 || weight >= MAX_WEIGHT)
            weight = 0;
        this->adjlist.set(i, j, weight);
    }
    else throw invalid_argument("args error!");
}

template <class T>
void AdjListGraph<T>::removeEdge(int i, int j)
{
    if (i != j)
        this->adjlist.set(i, j, 0);
}

template <class T>
int AdjListGraph<T>::vertexCount() { return this->n; }

template <class T>
T& AdjListGraph<T>::getVertex(int i) { return this->verlist[i]; }

template <class T>
SeqList<T> AdjListGraph<T>::getVerlist() { return this->verlist; }

template <class T>
LinkedMatrix AdjListGraph<T>::getAdjList() { return this->adjlist; }

template <class T>
int AdjListGraph<T>::weight(int i, int j)
{
    if (i == j) return 0;
    int w = this->adjlist.get(i,j);
    return (w != 0) ? w : MAX_WEIGHT;
}

template <class T>
int AdjListGraph<T>::insertVertex(T x)
{
    this->verlist.insert(x);
    this->n++;
    this->adjlist.setRowsColumns(n, n);
    return (this->n - 1);
}

template <class T>
void AdjListGraph<T>::removeVertex(int i)
{
    if (i >= 0 && i < this->n)
    {
        this->verlist.remove(i);
        SortedSinglyList<Triple>* list = this->adjlist.rowlist[i];
        for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
            this->removeEdge(p->data.symmetry());
        this->n--;
        this->adjlist.rowlist.remove(i);
        list->~SortedSinglyList<Triple>();
        this->adjlist.setRowsColumns(n, n);

        for (int j = 0; j < n; j++)
        {
            list = this->adjlist.rowlist[j];
            for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
            {
                if (p->data.row > i)
                    p->data.row--;
                if (p->data.column > i)
                    p->data.column--;
            }
        }
    }
    else throw out_of_range("args error!");
}

template <class T>
void AdjListGraph<T>::setVertex(int i, T x) { this->verlist.insert(i, x); }

template <class T>
int AdjListGraph<T>::next(int i, int j = -1)
{
    if (i >= 0 && i < n && j >= -1 && j < n && i!- j)
    {
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[i];
        for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
            if (p->data.column > j)
                return p->data.column;
    }
    return -1;
}

template <class T>
int AdjListGraph<T>::outdegree(int i)
{
    int sum = 0;
    SortedSinglyList<Triple> *list = this->adjlist.rowlist[i];
    for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
        sum += p->data.value > 1 ? 1 : 0;
    return sum;
}

template <class T>
int AdjListGraph<T>::indegree(int i)
{    
    int sum = 0;
    for (int j = 0; j < n; j++)
    {
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[j];
        for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
            if (p->data.column == i) sum++;
    }
    return sum;
}

template <class T>
int AdjListGraph<T>::degree(int i)
{   
    return (!directed) ? indegree(i) : (indegree(i) + outdegree(i));
}

template <class T>
int AdjListGraph<T>::edgeCount()
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[i];
        sum += list->count();
    }
    return sum;
}

template <class T>
int AdjListGraph<T>::cost()
{
    int cost = 0;
    for (int i = 0; i < n; i++)
    {
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[i];
        for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
            cost += p->data.value;
    }
    return cost;
}

template <class T>
int AdjListGraph<T>::minWeight()
{
    int min = MAX_WEIGHT;
    for (int i = 0; i < n; i++)
    {
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[i];
        for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
            if (p->data.value < min)
                min = p->data.value;
    }
    return min;
}

template <class T>
Triple AdjListGraph<T>::minWeightEdge()
{
    int min_i = 0, min_j = 0, min_weight = MAX_WEIGHT;
    for (int i = 0; i < n; i++)
    {
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[i];
        for (Node<Triple>* p = list->head->next; p != nullptr; p = p->next)
            if (p->data.value < min)
            {
                min_i = i;
                min_j = p->data.column;
                min_weight = p->data.value;
            }
    }
    return Triple(min_i, min_j, min_weight);
}

template <class T>
bool AdjListGraph<T>::isComplete()
{    
    return (this->edgeCount() == n * (n - 1)) ? true : false;
}

template <class T>
AdjListGraph<T> AdjListGraph<T>::createComplete(T vertices[], int vertexCount)
{
    AdjListGraph<T> graph;
    for (int x = 0; x < vertexCount; x++)
        graph.insertVertex(vertices[x]);

    for (int i = 0; i < vertexCount; i++)
        for (int j = 0; j < vertexCount; j++)
        {
            if (i == j) continue;
            graph.insertEdge(i, j, 1);
        }
            
    return graph;
}

template <class T>
AdjListGraph<T>::AdjListGraph(AdjListGraph& graph)
{
    this->n = graph.n;
    this->verlist = graph.verlist;
    this->adjlist = graph.adjlist;
}

template <class T>
AdjListGraph<T>& AdjListGraph<T>::operator=(AdjListGraph<T> &graph)
{
    if (this != &graph)
    {
        this->~AdjListGraph();
        this->n = graph.vertexCount();
        this->verlist = graph.verlist;
        this->adjlist = graph.adjlist;
        return *this;
    }
    return *this;
}

template <class T>
bool AdjListGraph<T>::operator==(AdjListGraph<T> &graph)
{
    return (this->verlist == graph.getVertexList() && this->adjlist == graph.adjlist);
}

template <class T>
bool AdjListGraph<T>::isSubgraph(AdjListGraph<T> &graph)
{
    return graph.verlist.contain(this->verlist) && graph.adjlist.rowlist.contain(this->adjlist.rowlist);
}

template <class T>
bool AdjListGraph<T>::isSpanSubgraph(AdjListGraph<T> &graph)
{
    return this->verlist == graph.getVerlist() && graph.getAdjList().rowlist.contain(this->adjlist.rowlist);
}
