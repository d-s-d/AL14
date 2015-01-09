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
	int L,P;
	cin >> L >> P;

	Graph G(L);

	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	Vertex src = add_vertex(G),
				 trg = add_vertex(G);
	vector<int> source_in(L, 0);
	vector<int> target_out(L, 0);
	vector<int> cycle_cap(L, 0);

	for( int i = 0; i < L; ++i )
	{
		int g,d;
		cin >> g >> d;
		source_in[i] = g;
		target_out[i] = d;
	}

	for( int i = 0; i < P; ++i )
	{
		int f, t, min, max;
		cin >> f >> t >> min >> max;
		if( f != t )
		{
			addEdge( f, t, max - min, capacity, rev_edge, G );
			source_in[t] += min;
			target_out[f] += min;
		}
	}

	int total_target_cap = 0;
	for( int i = 0; i < L; ++i )
	{
		addEdge( src, i, source_in[i], capacity, rev_edge, G );
		addEdge( i, trg, target_out[i], capacity, rev_edge, G );
		total_target_cap += target_out[i];
	}

	long flow = push_relabel_max_flow(G, src, trg);
	if( flow == total_target_cap )
	{
		cout << "yes";
	}
	else
	{
		cout << "no";
	}
	cout << endl;
}
