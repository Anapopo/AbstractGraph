#pragma once
template <class T>
class AbstractGraph
{
protected:
    const static int MAX_WEIGHT = 0x0000ffff;
    virtual int vertexCount() = 0;
    virtual T& getVertex(int i) = 0;
    virtual int weight(int i, int j) = 0;

public:
    void DFSTraverse(int i);
    void BFSTraverse(int i);
    void minSpanTree();
    void shortestPath(int v);
    void shortestPath();
private:
    void depthfs(int i, SeqList<bool> &visited);
    void breadthfs(int i, SeqList<bool> &visited);
};
