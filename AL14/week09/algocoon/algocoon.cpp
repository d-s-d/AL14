#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;

typedef vector<int> IntVector;

void testcase( int n, int m );

int main()
{
	ios_base::sync_with_stdio(false);
	//cout << setiosflags(ios::fixed) << setprecision(0);
	int T, n ,m;
	cin >> T;
	cin >> n >> m;

	while( T-- ) {
		testcase(n, m);
		cin >> n >> m;
	}
	return 0;
}

// Custom add_edge, also creates reverse edges with corresponding capacities.
void addEdge(int u, int v, long c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(u, v, G);
	tie(reverseE, tuples::ignore) = add_edge(v, u, G);
	capacity[e] = c;
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;
}

void testcase( int n, int m ) 
{
	Graph G(n);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	// build the graph
	for( int i = 0; i < m; ++i )
	{
		int u, v, c;
		cin >> u >> v >> c;
		addEdge( u, v, c, capacity, rev_edge, G );
	}

	int min_sink, min_source;
	long min_flow = INT_MAX;
	
	for( int i = 1; i < n; ++i )
	{
		long source_flow = push_relabel_max_flow( G, i, 0 );
		long sink_flow = push_relabel_max_flow( G, 0, i );
	
		if( source_flow < min_flow )
		{
			min_source = i;
			min_sink = 0;
			min_flow = source_flow;
		}

		if( sink_flow < min_flow )
		{
			min_sink = i;
			min_source = 0;
			min_flow = sink_flow;
		}
	}

	push_relabel_max_flow( G, min_source, min_sink );
	queue<int> q;
	vector<bool> visited(n, false);
	q.push( min_source );
	visited[min_source] = true;
	
	while( !q.empty() )
	{
		int u = q.front();
		q.pop();

		graph_traits<Graph>::out_edge_iterator ei, e_end;
		for( tie(ei, e_end) = out_edges( u, G ); ei != e_end; ++ei )
		{
			const int v = target(*ei, G);
			if( !visited.at(v) )
			{
				if( res_capacity[*ei] != 0 )
				{
					q.push(v);
					visited.at(v) = true;
				}
			}
		}
	}

	cout << min_flow << endl; // total cost
	cout << count(visited.begin(), visited.end(), true) << " ";
	for( int i = 0; i < n; ++i )
	{
		if( visited[i] )
		{
			cout << i << " ";
		}
	}
	cout << endl;
}
