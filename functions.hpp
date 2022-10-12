#include <bits/stdc++.h>
using namespace std;

#define d(x) cerr << #x << "=" << x << endl;

#define fl(i, n) for(i = 0; i < n; ++i)
#define fle(i, n) for(i = 0; i <= n; ++i)
#define fgt(i, n) for(i = 0; i > n; ++i)
#define fgte(i, n) for(i = 0; i >= n; ++i)

#define Fl(i, k, n) for(i = k; i < n; ++i)
#define Fle(i, k, n) for(i = k; i <= n; ++i)
#define Fgt(i, k, n) for(i = k; i > n; ++i)
#define Fgte(i, k, n) for(i = k; i >= n; ++i)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef tuple<double,double,double> Edge;
typedef vector<Edge> Edges;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple

/**
 *  COUNTER
 * */
template <typename K, typename V>
class Counter
{
private:
    /* data */
    unordered_map<K, V> container;
    vector<K> keys_vector;
    void trigger_if_new_key(K key);
public:
    Counter(/* args */);
    void add(K key, V value);
    V count(K key);
    vector<K> keys();
    ~Counter();
};

template <typename K, typename V> Counter<K,V>::Counter(/* args */)
{
}

template <typename K, typename V> Counter<K,V>::~Counter()
{
}

template <typename K, typename V> void Counter<K,V>::trigger_if_new_key(K key)
{
    if(container.find(key) == container.end())
    {
        container[key] = V();
        keys_vector.PB(key);
    }
}

template <typename K, typename V> void Counter<K,V>::add(K key, V value)
{
    trigger_if_new_key(key);

    container[key] += value;
}

template <typename K, typename V> V Counter<K,V>::count(K key)
{
    trigger_if_new_key(key);

    return container[key];
}

template <typename K, typename V> vector<K> Counter<K,V>::keys()
{
    return keys_vector;
}

/**
 *  GEOMETRY
 * */
struct Point {
    double x;
    double y;

    Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }

    bool operator<(Point &p)
    {
        if(x == p.x)
        {
            return y < p.y;
        }

        return x < p.x;
    }

    bool operator==(Point &p)
    {
        return x == p.x && y == p.y;
    }

    bool operator!=(Point &p)
    {
        return !((*this) == p);
    }

    void print()
    {
        cout << "(" << x << "," << y << ")";
    }
};

bool isLeft(Point startLine, Point endLine, Point pointToTest)
{
     return ((endLine.x - startLine.x)*(pointToTest.y - startLine.y) - (endLine.y - startLine.y)*(pointToTest.x - startLine.x)) > 0;
}

bool isRight(Point startLine, Point endLine, Point pointToTest)
{
     return ((endLine.x - startLine.x)*(pointToTest.y - startLine.y) - (endLine.y - startLine.y)*(pointToTest.x - startLine.x)) < 0;
}

bool isColinear(Point startLine, Point endLine, Point pointToTest)
{
    return ((endLine.x - startLine.x)*(pointToTest.y - startLine.y) - (endLine.y - startLine.y)*(pointToTest.x - startLine.x)) == 0;
}

vector<Point> convexhull2d(vector<Point> points)
{
    sort(points.begin(), points.end());
    
    Point pOnHull = points[0];
    vector<Point> ch = vector<Point>();
    
    do
    {
        ch.PB(pOnHull);
        Point endpoint = points[0];

        int i, size = points.size();
        fl(i, size)
        {
            if(endpoint == pOnHull || isLeft(ch.back(), endpoint, points[i]))
            {
                endpoint = points[i];
            }
        }

        pOnHull = endpoint;
        
    } while (ch.front() != pOnHull);
    
    return ch;
}

/**
 * Graph
 */

// Nodes is defined by a vector<int> vi
// edges is vector of tuple <source, destination, cost>

Edges edges_from(int node, const Edges& edges)
{
    Edges matches;
    std::copy_if(edges.begin(), edges.end(), std::back_inserter(matches), [&](Edge edge) {
        return get<0>(edge) == node;
    });

    return matches;
}

Edges edges_to(int node, const Edges& edges)
{
    Edges matches;
    std::copy_if(edges.begin(), edges.end(), std::back_inserter(matches), [&](Edge edge) {
        return get<1>(edge) == node;
    });

    return matches;
}

void dfs(const int& current_node, const vi& nodes, const Edges& edges, vector<bool>& visited, int depthLimit = -1)
{
    if(depthLimit != -1 && depthLimit == 0) return;
    if(nodes.size() == 0) return;

    // work
    cout << current_node << endl;

    for(auto& edge : edges_from(current_node, edges))
    {
        int next_node = get<1>(edge);
        if(!visited[next_node])
        {
            visited[next_node] = true;
            dfs(next_node, nodes, edges, visited, depthLimit - 1);
        }
    }
}

void bfs(const int& starting_node, const vi& nodes, const Edges& edges, vector<bool>& visited)
{
    if(nodes.size() == 0) return;

    visited[starting_node] = true;

    queue<int> q;
    q.push(starting_node);

    while(!q.empty())
    {
        int current_node = q.front();
        q.pop();

        // work
        cout << current_node << endl;

        for(auto& edge : edges_from(current_node, edges))
        {
            int next_node = get<1>(edge);
            if(!visited[next_node])
            {
                visited[next_node] = true;
                q.push(next_node);
            }
        }
    }
}

unordered_map<int, pair<int, double>> dijkstra(const int& starting_node, const vi& nodes, const Edges& edges)
{
    int void_node = -1;
    int unreachable = 1e8;
    unordered_map<int, pair<int, double>> distances;

    vector<bool> visited = vector<bool>(nodes.size(), false);

    for(auto& node : nodes)
    {
        distances[node] = MP(void_node, unreachable);
    }

    distances[starting_node].S = 0;

    // cmp : first element comes last if its before in the list (weak ordering)
    auto cmp = [](pair<int, double> a, pair<int, double> b){ return a.S > b.S; };
    priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(cmp)> pq(cmp);

    pq.push(MP(starting_node, 0));

    while(!pq.empty())
    {
        int current_node = (pq.top()).F;
        pq.pop();
        
        if(visited[current_node]) continue;

        visited[current_node] = true;

        for(auto& edge: edges_from(current_node, edges))
        {
            int to = get<1>(edge);
            double cost = get<2>(edge);

            if(distances[to].S > distances[current_node].S + cost)
            {
                distances[to].S = distances[current_node].S + cost;
                distances[to].F = current_node;
            }
            
            pq.push(MP(to, distances[to].S));
        }
    }

    return distances;
}