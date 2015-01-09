#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include<boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,undirectedS,
				no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void testcase();

template <class T>
class TestBackInsertIterator : 
    public iterator<output_iterator_tag,void,void,void,void>
{
protected:
  T* container;
	Graph* g;

public:
  typedef T container_type;
  explicit TestBackInsertIterator (T& x, Graph& g) : container(&x), g(&g) {}
  TestBackInsertIterator<T>& operator= (const Edge& value)
    { cout << "inserted 1: " << target(value,*g) << endl;
			container->push_back(value); return *this; }
  TestBackInsertIterator<T>& operator= (Edge&& value)
    { cout << "inserted: " << source(value, *g) << "," << target(value,g) << endl;
      container->push_back(std::move(value)); return *this; }
  TestBackInsertIterator<T>& operator* ()
    { return *this; }
  TestBackInsertIterator<T>& operator++ ()
    { return *this; }
  TestBackInsertIterator<T> operator++ (int)
    { return *this; }
};


int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
}

void testcase() {
	int V,E;
	cin >> V >> E;
	Graph G(V);
	WeightMap wMap = get(edge_weight, G);
	for( int i = 0; i < E; ++i ) {
		int u,v,c;
		Edge e;
		cin >> u >> v >> c;
		tie( e, tuples::ignore ) = add_edge(u,v,G);
		wMap[e] = c;
	} // for

	vector<Edge> mst;
	vector<int> dist(V);
	auto backIter = TestBackInsertIterator<vector<Edge> >(mst, G);
	//kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
	kruskal_minimum_spanning_tree(G, backIter);
	dijkstra_shortest_paths(G, 0, distance_map(&dist[0]));
	int totalWeight = 0, maxDist = 0;
	for(auto iter = mst.begin(); iter != mst.end(); iter++) {
		totalWeight += wMap[*iter];
	}
	for(auto d = dist.begin(); d != dist.end(); ++d) {
		if(*d > maxDist) {
			maxDist = *d;
		}
	}

	cout << totalWeight << " " << maxDist << endl;
}
