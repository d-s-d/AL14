#include<iostream>
#include<algorithm>
#include<vector>
#include<limits>
#include<set>

#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std; 
using namespace boost;

typedef adjacency_list < vecS, vecS, directedS,
	no_property, no_property > Graph;
typedef graph_traits< Graph >::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator Edge_iter;

typedef vector<int> IntVector;
typedef vector<IntVector > AdjacencyList;

void testcase( int n, int m );

int main()
{
	ios_base::sync_with_stdio(false);
	int T, n ,m;
	cin >> T;
	cin >> n >> m;

	while( T-- ) {
		testcase(n, m);
		cin >> n >> m;
	}
	return 0;
}

const bool DEBUG = false;

void testcase( int n, int m )
{
	// read the adjency list
	//
	Graph G(n);
	for( int i = 0; i < m; ++i )
	{
		int u, v;
		cin >> u >> v;
		add_edge(--u, --v, G);
	} // post cond.: graph contains all edges

	IntVector costs;
	costs.reserve(n);

	for( int i = 0; i < n; ++i )
	{
		int c;
		cin >> c;
		costs.push_back(c);
	} // post cond.: costs is a mapping from v. index to cost

	int cost = 0;
	IntVector component(n);
	int component_count = strong_components(G, &component[0]);

	if( component_count > 0 )
	{
		set<int> no_in_edges_set;
		
		for( int i = 0; i < component_count; ++i )
		{
			no_in_edges_set.insert(no_in_edges_set.end(), i);
		}

		Edge_iter e_itr, e_itr_end;
		for( tie(e_itr, e_itr_end) = edges(G); e_itr != e_itr_end; ++e_itr )
		{
			int u = source(*e_itr, G),
					v = target(*e_itr, G);
			if( component[u] != component[v] )
			{
				no_in_edges_set.erase(component[v]);
			}
		} // post cond.: no_in_edges_set contains all component numbers which have no in edges

		vector<IntVector > comp2vertices(component_count);
		for( int i = 0; i < n; ++i )
		{
			comp2vertices[component[i]].push_back(i);
		} // post condition: comp2vertices is a mapping from comp. number to vertices

		// now, let's loop over all components having no in edges 
		while( !no_in_edges_set.empty() )
		{
			auto comp_itr = no_in_edges_set.begin();
			int comp = *comp_itr;
			no_in_edges_set.erase(comp_itr);
			
			int _min_cost = numeric_limits<int>::max();
			for( int v: comp2vertices[comp] ) 
			{
				int current_cost = costs[v];
				_min_cost = min( current_cost, _min_cost );
			} // post cond.: _min_cost is the min. cost of all vertices in component comp.

			cost += _min_cost;
		} // post condition: no_in_edges_set is empty
	}
	else
	{
		cost = *min_element( costs.begin(), costs.end() );
	}// post cond.: cost is the total cost

	cout << cost << endl;
}
