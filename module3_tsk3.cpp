/*
Требуется отыскать самый выгодный маршрут между городами.
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Graph {
    std::vector<std::vector<std::pair<int, int>>> matrix;

public:
    explicit Graph(int NumbOfVerts)
        : matrix(NumbOfVerts) {};
    std::vector<std::pair<int, int>> getVertices(int vertex) const;
    void AddEdge(int start, int end, int weight);
    size_t getSize() const { return matrix.size(); }
};

std::vector<std::pair<int, int>> Graph::getVertices(int vertex) const
{
    return matrix[vertex];
}

void Graph::AddEdge(int start, int end, int weight)
{
    assert(0 <= start && start < matrix.size());
    assert(0 <= end && end < matrix.size());
    matrix[start].push_back({ end, weight });
    matrix[end].push_back({ start, weight });
}

int ShorterPath(const Graph& graph, int start, int end)
{
    std::queue<int> Queue;
    Queue.push(start);
    std::vector<int> Dist(graph.getSize(), 10000 * 10000);
    Dist[start] = 0;
    
    while (!Queue.empty()) {
        std::queue<int> NextCurr;
        while (!Queue.empty()) {
            int curr = Queue.front();
            Queue.pop();
            std::vector<std::pair<int, int>> CurrVert = graph.getVertices(curr);
            for (int i = 0; i < CurrVert.size(); ++i) {
                if (Dist[curr] + CurrVert[i].second < Dist[CurrVert[i].first]) {
                    NextCurr.push(CurrVert[i].first);
                    Dist[CurrVert[i].first] = Dist[curr] + CurrVert[i].second;
                }
            }
        }
        Queue = NextCurr;
    }
    return Dist[end];
}

int main()
{
    int N = 0, M = 0, start = 0, end = 0, time = 0, result = 0;
    std::cin >> N >> M;
    Graph Graph(N);
    for (int i = 0; i < M; i++) {
        std::cin >> start >> end >> time;
        Graph.AddEdge(start, end, time);
    }
    std::cin >> start >> end;
    std::cout << ShorterPath(Graph, start, end) << std::endl;
    return 0;
};