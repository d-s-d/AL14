#include<climits>
#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>
#include<boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS,
				no_property, property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long, property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;


void addEdge( int from, int to, long c,
	EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G)
{
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;
}

void testcase();

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
	return 0;
}

void testcase()
{
	int n, // intersections
			m, // streets/edges
			k, // police stations
			l; // photographs
	cin >> n >> m >> k >> l;
	Graph G(2*n);

	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);

	Vertex src = add_vertex(G),
				 trg = add_vertex(G);
	const int offset = n;
	const int c = 1;

	for( size_t i = 0; i < k; ++i )
	{
		int pStation;
		cin >> pStation;
		addEdge(src, pStation, c, capacity, rev_edge, G);
		addEdge(offset + pStation, trg, c, capacity, rev_edge, G);
	}

	for( size_t i = 0; i < l; ++i )
	{
		int photo;
		cin >> photo;
		addEdge(photo, offset + photo, c, capacity, rev_edge, G);
	}

	for( size_t i = 0; i < m; ++i )
	{
		int u, v;
		cin >> u >> v;
		addEdge(u, v, INT_MAX, capacity, rev_edge, G);
		addEdge(offset + u, offset + v, c, capacity, rev_edge, G);
	}

	long flow = push_relabel_max_flow(G, src, trg);
	cout << flow << endl;
}
