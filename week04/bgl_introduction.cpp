#include<climits>
#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/strong_components.hpp>
#include<boost/tuple/tuple.hpp>
using namespace std;
using namespace boost;
typedef adjacency_list<vecS,vecS,directedS,
				no_property,
				property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator
	EdgeIterator;
typedef property_map<Graph, edge_weight_t>::type
	WeightMap;
void testcase();
int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
}
void testcase() {
	int V,E,s;
	cin >> V >> E >> s;
	Graph G(V);
	WeightMap weight_map = get(edge_weight, G);
	for( int i = 0; i < E; ++i ) {
		int u,v,c;
		Edge e;
		cin >> u >> v >> c;
		tie( e, tuples::ignore ) =
			add_edge(v,u,G);
		weight_map[e] = c;
	} // for
	vector<int> scc(V);
	int nscc = strong_components(G, &scc[0]);
	vector<int> is_max(nscc, true);
	EdgeIterator ebeg, eend;
	for( tie(ebeg, eend) = edges(G); ebeg != eend;
			++ebeg) {
		int u = source(*ebeg, G), v = target(*ebeg, G);
		if( scc[u] != scc[v] ) is_max[scc[u]] = false;
	}
	int max_count = count(
			is_max.begin(), is_max.end(), true);
	if( max_count != 1) {
		cout << "NO\n";
		return;
	}
	vector<int> dist(V);
	dijkstra_shortest_paths(
			G,s,distance_map(&dist[0]));
	int res = INT_MAX;
	for( int u = 0; u < V; ++u )
		if( is_max[scc[u]] )
			res = min( res, dist[u] );
	cout << res << "\n";
} //testcase()
