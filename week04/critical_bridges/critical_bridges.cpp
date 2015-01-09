#include<climits>
#include<iostream>
#include<algorithm>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/biconnected_components.hpp>
#include<boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

namespace boost
{
  struct edge_component_t
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  }
  edge_component;
}

typedef adjacency_list<vecS,vecS,undirectedS,
				no_property, property<edge_component_t, std::size_t> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;
typedef property_map<Graph, edge_component_t>::type ComponentMap;

void testcase();

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
}

typedef struct EdgeComponent {
	int u,v,c;
} EdgeCompT;

void testcase() {
	int V,E,e_1,e_2;
	Edge e;
	Graph G;
	cin >> V >> E;

	ComponentMap components = get( edge_component, G );
	for( int i = 0; i < E; ++i ) {
		cin >> e_1 >> e_2;
		add_edge( e_1, e_2, G );
	}

	vector<pair<Edge,int>> edgeComponents;
	vector<pair<int, int> > criticalEdges;
	// calculate connected components
	std::size_t C = biconnected_components( G, components );
	EdgeIterator ei, ei_end;
	for( tie(ei, ei_end) = edges(G); ei != ei_end; ++ei ) {
		edgeComponents.push_back( make_pair(*ei,components[*ei]) );
#ifdef AL_DEBUG
		cout << source( *ei, G ) << " " << target( *ei, G ) << " c: " <<
			components[*ei] << endl;
#endif
	}
	// order edges by their component number
	sort( edgeComponents.begin(), edgeComponents.end(),
			[] (const pair<Edge,int> &a, const pair<Edge,int> &b) -> bool {
				return a.second < b.second;
			});
	// output all edges which appear only once
	std::size_t Occur = 0;
	pair<Edge, int> last;
	if( edgeComponents.size() > 0 ) {
		last = edgeComponents[0];
		Occur = 1;
		for( auto iter = edgeComponents.begin()+1; iter != edgeComponents.end();
				++iter )
		{
			if( (last.second != (*iter).second) )
			{
				int u = source(last.first, G);
				int v = target(last.first, G);

				if( (Occur == 1) &&
						(source(last.first, G) != target(last.first,G)) )
				{
					if( v > u )
					{
						criticalEdges.emplace_back(u,v);
					}
					else
					{
						criticalEdges.emplace_back(v,u);
					}
				}
				Occur = 1;
			}
			else
			{
				Occur++;
			}
			last = *iter;
		}
		if( Occur == 1 )
		{
			int u = source(last.first, G);
			int v = target(last.first, G);
			if( v > u )
			{
				criticalEdges.emplace_back(u,v);
			}
			else
			{
				criticalEdges.emplace_back(v,u);
			}
		}
	}

	// sort edges lexicographically 
	sort( criticalEdges.begin(), criticalEdges.end() );

	cout << criticalEdges.size() << endl;
	for( auto iter = criticalEdges.begin(); iter != criticalEdges.end(); ++iter ) {
		cout << iter->first << " " << iter->second << endl;
	}
}
