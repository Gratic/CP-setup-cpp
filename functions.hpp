#include <bits/stdc++.h>

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

#define F first
#define S second
#define PB push_back
#define MP make_pair

using namespace std;

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