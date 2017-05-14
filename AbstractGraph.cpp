#include "stdafx.h"
#include "MatrixGraph.h"
#include "AdjListGraph.h"

void test_1()
{
    char vertices[] = "ABCDE";
    Triple edges[] = { Triple(0,1,45), Triple(0,2,28), Triple(0,3,10),
        Triple(1,0,45), Triple(1,2,12), Triple(1,4,21),
        Triple(2,0,28), Triple(2,1,12), Triple(2,3,17), Triple(2,4,26),
        Triple(3,0,10), Triple(3,2,17), Triple(3,4,15),
        Triple(4,1,21), Triple(4,2,26), Triple(4,3,15) };

    MatrixGraph<char> graph1(vertices, 5, edges, 16);
    graph1.directed = false;
    MatrixGraph<char> graph17 = graph1.createComplete(vertices, 5);
    cout << graph17;
}
void test_2()
{
    char vertices[] = "ABCDE";
    Triple edges[] = { Triple(0,1,45), Triple(0,2,28), Triple(0,3,10),
        Triple(1,0,45), Triple(1,2,12), Triple(1,4,21),
        Triple(2,0,28), Triple(2,1,12), Triple(2,3,17), Triple(2,4,26),
        Triple(3,0,10), Triple(3,2,17), Triple(3,4,15),
        Triple(4,1,21), Triple(4,2,26), Triple(4,3,15) };

    MatrixGraph<char> graph1(vertices, 5, edges, 16);
    graph1.directed = false;

    cout << "Graph1 is " << (graph1.directed ? "directed." : "non-directed.") << endl;
    cout << graph1;
    cout << "Graph1's indegree is " << graph1.indegree(0) << endl;
    cout << "Graph1's outdegree is " << graph1.outdegree(0) << endl;
    cout << "Graph1's degree is " << graph1.degree(0) << endl;
}

void test_3()
{
    char vertices[] = "ABCDE";
    Triple edges[] = {
        Triple(0,1,10), Triple(0,3,30), Triple(0,4,99), Triple(1,2,50),
        Triple(1,3,40), Triple(2,4,10), Triple(3,2,20), Triple(3,4,60)
    };
    AdjListGraph<char> graphy(vertices, 5, edges, 8);
    graphy.directed = true;

    cout << graphy;
    AdjListGraph<char> graph18 = graphy.createComplete(vertices, 5);
    cout << graph18;
    cout << "GraphY is " << (graphy.directed ? "directed." : "non-directed.") << endl;
    cout << graphy;
    cout << "GraphY's indegree is " << graphy.indegree(0) << endl;
    cout << "GraphY's outdegree is " << graphy.outdegree(0) << endl;
    cout << "GraphY's degree is " << graphy.degree(0) << endl;
}
int main()
{
    test_1();
    test_2();
    test_3();
    return 0;
}
