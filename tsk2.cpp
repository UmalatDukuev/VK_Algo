/*

Дан невзвешенный неориентированный граф.
В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами.
Требования: сложность O(V+E).
Формат ввода.
v: кол-во вершин (макс. 50000),
n: кол-во ребер (макс. 200000),
n пар реберных вершин,
пара вершин u, w для запроса.
Формат вывода.
Количество кратчайших путей от u к w.
*/


#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Graph {
    std::vector<std::vector<int> > matrix;

public:
    explicit Graph(int NumbOfVerts)
        : matrix(NumbOfVerts) {};
    std::vector<int> getVertices(int vertex) const;
    void AddEdge(int start, int end);
    size_t getSize() const { return matrix.size(); }
};

void Graph::AddEdge(int start, int end)
{
    assert(0 <= start && start < matrix.size());
    assert(0 <= end && end < matrix.size());
    matrix[start].push_back(end);
    matrix[end].push_back(start);
}

std::vector<int> Graph::getVertices(int vertex) const
{
    return matrix[vertex];
}

int ShorterPath(const Graph& graph, int start, int end)
{
    std::queue<int> Queue;
    std::vector<int> Dist(graph.getSize(), 10000 * 10000);
    std::vector<int> Shorter(graph.getSize(), 0);

    Queue.push(start);
    Dist[start] = 0;
    Shorter[start] = 1;
    while (!Queue.empty()) {
        std::queue<int> NextCurr;
        while (!Queue.empty()) {
            int currVert = Queue.front();
            Queue.pop();
            std::vector<int> CurrVert = graph.getVertices(currVert);
            for (int i = 0; i < CurrVert.size(); ++i) {
                if (Dist[currVert] + 1 < Dist[CurrVert[i]]) {
                    Dist[CurrVert[i]] = Dist[currVert] + 1;
                    NextCurr.push(CurrVert[i]);
                }
                if (Dist[CurrVert[i]] == Dist[currVert] + 1) {
                    Shorter[CurrVert[i]] += Shorter[currVert];
                }
            }
        }
        Queue = NextCurr;
    }
    return Shorter[end];
}

int main()
{
    int v = 0, n = 0, start = 0, end = 0, result = 0;
    std::cin >> v >> n;
    Graph Graph(v);
    for (int i = 0; i < n; i++) {
        std::cin >> start >> end;
        Graph.AddEdge(start, end);
    }
    std::cin >> start >> end;
    result = ShorterPath(Graph, start, end);
    std::cout << result << std::endl;
    return 0;
}