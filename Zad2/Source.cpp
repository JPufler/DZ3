#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <thread>
#include <limits> // for numeric_limits
#include <set>
#include <chrono>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

using namespace std;
using namespace std::chrono;

typedef int vertex_t;
typedef double weight_t;
const int ROW = 20;
const int COLUMN = 40;
const weight_t max_weight = numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef vector<vector<neighbor> > adjacency_list_t;


void DijkstraComputePaths(vertex_t source,
    const adjacency_list_t& adjacency_list,
    vector<weight_t>& min_distance,
    vector<vertex_t>& previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    set<pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
        const vector<neighbor>& neighbors = adjacency_list[u];
        for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
            neighbor_iter != neighbors.end();
            neighbor_iter++)
        {
            if (neighbor_iter->target < 0 || neighbor_iter->target > 800)
            {
                continue;
            }
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) {
                vertex_queue.erase(make_pair(min_distance[v], v));

                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(make_pair(min_distance[v], v));

            }

        }
    }
}


list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const vector<vertex_t>& previous)
{
    list<vertex_t> path;
    for (; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}


void print(adjacency_list_t& adjacency_list, int pointA, int pointB, int pointX) {
    int n = 0;
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COLUMN; ++j)
        {
            if (n == pointA)
            {
                cout << 'A';
            }
            else if (n == pointX)
            {
                cout << 'X';
            }
            else if (n == pointB)
            {
                cout << 'B';
            }
            else if (n == 0 || n == 1 || (n - 1) % COLUMN == COLUMN-1)
            {
                if (adjacency_list[n + 1][0].weight == 1)
                {
                    std::cout << '-';
                }
                else
                {
                    std::cout << '*';
                }

            }
            else if (adjacency_list[n - 1][2].weight == 1)
            {
                std::cout << '-';
            }
            else
            {
                std::cout << '*';
            }
            n++;
        }
        std::cout << endl;
    }
}

int main()
{
    adjacency_list_t adjacency_list(801);

    //izrada tablice
    int n = 0;
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COLUMN; ++j)
        {
            if (n - COLUMN >= 0)
            {
                adjacency_list[n].push_back(neighbor(n - 1, 1));
                adjacency_list[n].push_back(neighbor(n - COLUMN, 1));
            }
            else
            {
                adjacency_list[n].push_back(neighbor(n - 1, 1));
                adjacency_list[n].push_back(neighbor(n - COLUMN, INT_MAX));
            }
            if (n + COLUMN < ROW * COLUMN)
            {
                adjacency_list[n].push_back(neighbor(n + 1, 1));
                adjacency_list[n].push_back(neighbor(n + COLUMN, 1));
            }
            else
            {
                adjacency_list[n].push_back(neighbor(n + 1, 1));
                adjacency_list[n].push_back(neighbor(n + COLUMN, INT_MAX));
            }
            
            n++;
        }
    }

    //izrada rubova tablice
    for (int i = COLUMN-1; i < COLUMN*ROW-1; i += COLUMN)
    {
        adjacency_list[i][2].weight = INT_MAX;
        adjacency_list[i + 1][0].weight = INT_MAX;
    }

    //izrada zidova
    for (int i = 9; i < 600; i += 20)
    {
        adjacency_list[i + 1][0].weight = INT_MAX;
        adjacency_list[i - 1][2].weight = INT_MAX;
        adjacency_list[i + 40][1].weight = INT_MAX;
        if (i - 40 > 0)
        {
            adjacency_list[i - 40][3].weight = INT_MAX;
        }
    }

    int pointA = 0, pointB = 0, temp;

    //unos tocaka
    std::cout << "Unesite stupac tocke A: ";
    std::cin >> temp;
    pointA += temp - 1;
    std::cout << "Unesite redak tocke A: ";
    std::cin >> temp;
    pointA += (temp - 1) * 40;
    std::cout << "Unesite stupac tocke B: ";
    std::cin >> temp;
    pointB += temp - 1;
    std::cout << "Unesite redak tocke B: ";
    std::cin >> temp;
    pointB += (temp - 1) * 40;

    
    vector<weight_t> min_distance;
    vector<vertex_t> previous;
    DijkstraComputePaths(pointA, adjacency_list, min_distance, previous);
    list<vertex_t> path = DijkstraGetShortestPathTo(pointB, previous);

    //ispis putanje
    for (auto it = path.begin(); it != path.end(); ++it)
    {
        system("CLS");
        print(adjacency_list, pointA, pointB, *it);
        std::cout << "Udaljenost od A do B: " << min_distance[pointB] << endl;
        this_thread::sleep_for(milliseconds(100));
    }
    std::cout << endl;

    return 0;
}