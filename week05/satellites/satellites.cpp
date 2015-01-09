#include<climits>
#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,undirectedS> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor VertexDescriptor;
typedef graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

void testcase();

const VertexDescriptor NULL_VERTEX = graph_traits<Graph>::null_vertex();

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
	return 0;
}

void visited_dfs(
		vector<int>& visited,
		int current,
		int Gnd,
		vector<VertexDescriptor> &matching,
		Graph &G)
{
	visited[current] = 1;
	AdjacencyIterator v_itr, v_end;

	if( current >= Gnd ) {
		for( boost::tie(v_itr, v_end) = adjacent_vertices(current, G);
				v_itr != v_end; ++v_itr)
		{
			if( matching[*v_itr] == current && !visited[*v_itr] ) {
				visited_dfs( visited, *v_itr, Gnd, matching, G );
			}
		}
	} else {
		for( boost::tie(v_itr, v_end) = adjacent_vertices(current, G);
				v_itr != v_end; ++v_itr)
		{
			if( matching[*v_itr] != current && !visited[*v_itr] ) {
				visited_dfs( visited, *v_itr, Gnd, matching, G );
			}
		}
	}
}

void print_line_vector(vector<int> &vec) {
	if( vec.size() > 0 ) {
		cout << vec[0];
		for( auto itr = vec.begin() + 1; itr != vec.end(); ++itr ) {
			cout << " " << *itr;
		}
	}
}

void testcase() {
	int Gnd,N,S,L;
	cin >> Gnd >> S >> L;

	N = Gnd+S;
	vector<int> visited(N, 0);
	Graph G(N);

	for( int i = 0; i < L; ++i ) {
		int g, s;
		cin >> g >> s;
#ifdef AL_DEBUG
		cout << "adding edge: " << g << "-" << Gnd+s << endl;
#endif
		add_edge(g, Gnd+s, G);
	}

	vector<VertexDescriptor> matching(N);
	edmonds_maximum_cardinality_matching(G, &matching[0]);

	// mark all ground stations not participating in the matching as visited
	for( int i = 0; i < Gnd; ++i ) {
		if( matching[i] == NULL_VERTEX ) {
			// i does not participate in a matching
			visited[i] = 1;
		}
	}

	// dfs
	for( int i = 0; i < Gnd; ++i ) {
		if( visited[i] ) {
			visited_dfs( visited, i, Gnd, matching, G );
		}
	}

	vector<int> Gnd_s, S_s;
	// count ground stations
	for( int i = 0; i < Gnd; ++i ) {
		if( !visited[i] ) {
			Gnd_s.push_back(i);
		}
	}

	// gound satellites
	for( int i = Gnd; i < N; ++i ) {
		if( visited[i] ) {
			S_s.push_back(i - Gnd);
		}
	}

	cout << Gnd_s.size() << " " << S_s.size() << endl;

	print_line_vector(Gnd_s);

	if( S_s.size() > 0 ) {
		cout << " ";
		print_line_vector(S_s);
	}
	cout << endl;
}
