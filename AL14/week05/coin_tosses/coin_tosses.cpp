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

void testcase() {

	int N, // total number of nodes (excluding source and target)
			P, // number of players
			R; // number of rounds
	cin >> P >> R;
	N = P + R;
	Graph G(N);

	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
	
	Vertex src, trg;
	src = add_vertex(G);
	trg = add_vertex(G);
	for( int i = 0; i < R; ++i ) {
		int a,b,c;
		cin >> a >> b >> c;
		a += R;
		b += R;
		addEdge(src, i, 1, capacity, rev_edge, G);
		switch( c ) {
			case 0: // unclear
				addEdge(i, a, 1, capacity, rev_edge, G);
				addEdge(i, b, 1, capacity, rev_edge, G);
			break;
			case 1: // a has won
				addEdge(i, a, 1, capacity, rev_edge, G);
			break;
			case 2: // b has won
				addEdge(i, b, 1, capacity, rev_edge, G);
			break;
		};
	}

	int total_score = 0;
	for( int i = R; i < N; ++i ) {
		int c;
		cin >> c;
		if( c > 0 ) addEdge(i, trg, c, capacity, rev_edge, G);
		total_score += c;
	}

	float flow = push_relabel_max_flow(G, src, trg);

#ifdef AL_DEBUG
	cout << "flow is    : " << flow << endl;
	cout << "total_score: " << total_score << endl;
#endif

	if((int)flow == total_score && total_score == R) {
		cout << "yes" << endl;
	} else {
		cout << "no" << endl; // additional checks might be required (according to solution)
	}
}
