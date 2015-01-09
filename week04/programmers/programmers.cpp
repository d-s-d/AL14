#include<climits>
#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/boyer_myrvold_planar_test.hpp>
#include<boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,undirectedS,
				no_property, property<vertex_index_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;

void testcase();

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
}

void testcase() {
	int V,E,u,v;
	cin >> V >> E;
	Graph G(V+1);

	for( int i = 0; i < E; ++i ) {
		cin >> u >> v;
#ifdef AL_DEBUG
		cout << u << " " << v << endl;
#endif
		add_edge( u, v, G );
	}

	for( u = 0; u < V; ++u ) {
		add_edge( u, V, G );
	}
	
	if( boyer_myrvold_planarity_test( G ) ) {
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}
