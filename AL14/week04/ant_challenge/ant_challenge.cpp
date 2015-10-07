#include<iostream>
#include<vector>
#include<algorithm>
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

class MinBackInsertIterator : 
    public std::iterator<output_iterator_tag,void,void,void,void>
{
	protected:
		Graph* targetGraph;
		Graph* sourceGraph;
		WeightMap tWMap;
		WeightMap wMap;

	public:
		explicit MinBackInsertIterator (Graph* _target, Graph* _source,
				WeightMap _targetWM, WeightMap _sourceWM) : targetGraph(_target), sourceGraph(_source),
		tWMap( _targetWM ), wMap( _sourceWM ) {}
		MinBackInsertIterator& operator= (const Edge& value)
			{ 
				Edge e;
				bool exists = false;
				if(num_edges(*targetGraph) > 0) {
					tie(e, exists) = edge(source(value,*sourceGraph),
						target(value,*sourceGraph), *targetGraph);
				} 
				if(exists) {
#ifdef AL_DEBUG
					cout << "Edge exists (" << source(e, *targetGraph) << ", " <<
						target(e, *targetGraph) << ", " << tWMap[e] << ") -> ";
#endif
					tWMap[e] = min(wMap[value], tWMap[e]);
#ifdef AL_DEBUG
					cout << tWMap[e] << endl;
#endif
				} else {
					tie( e, tuples::ignore ) =
						add_edge( source(value, *sourceGraph ), target(value, *sourceGraph ),
								*targetGraph);
					tWMap[e] = wMap[value];
				}
				return *this;
			}
		MinBackInsertIterator& operator= (Edge&& value)
			{ *this=value;
					cout << "num edges: " << num_edges(*targetGraph) << endl;
				return *this; }
		MinBackInsertIterator& operator* ()
			{ return *this; }
		MinBackInsertIterator& operator++ ()
			{ return *this; }
		MinBackInsertIterator operator++ (int)
			{ return *this; }
};


int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
	return 0;
}

void testcase() {
	int V,E,S,A,B;

	cin >> V >> E >> S >> A >> B;
#ifdef AL_DEBUG
	cout << " " << V << " " << E << " " << S << " " << A << " " << B << endl;
#endif
	vector<Graph*> speciesGraphs(S);
	vector<WeightMap> weightMaps(S);
	Graph finalNetwork(V);

	for( int i = 0; i < S; ++i ) {
		speciesGraphs[i]= new Graph(V);
		weightMaps[i] = get(edge_weight, *(speciesGraphs[i]));
	}
	
	for( int i = 0; i < E; ++i ) {
		int v1,v2, s_weight;
		cin >> v1 >> v2;
		for( int s = 0; s < S; ++s ) {
			cin >> s_weight;
			Edge e;
			tie(e,tuples::ignore) = add_edge(v1, v2, *speciesGraphs[s]);
			(weightMaps[s])[e] = s_weight;
		}
	}

	for( int i = 0; i < S; ++i ) {
		int h;
		cin >> h; // ?? what to do with the hives? Nothing.
	}

	vector<int> dist(V);
	for( int i = 0; i < S; ++i ) {
		MinBackInsertIterator backIter(&finalNetwork, speciesGraphs[i],
				get(edge_weight, finalNetwork), weightMaps[i]);
		kruskal_minimum_spanning_tree(*speciesGraphs[i], backIter);
	}

	dijkstra_shortest_paths(finalNetwork, A, distance_map(&dist[0]));
	cout << dist[B] << endl;

	//cleanup
	for( int i = 0; i < S; ++i ) {
		delete speciesGraphs[i];
	}
}
