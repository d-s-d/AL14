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

void testcase();

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) testcase();
	return 0;
}

void testcase() {
	int C,N,F;
	cin >> N >> C >> F;

	Graph G(N);
	vector<vector<string>* > buddy_traits;
	for( int i = 0; i < N; ++i ) {
		vector<string>* traits = new vector<string>();
		for( int j = 0; j < C; ++j ) {
			string str;
			cin >> str;
			traits->push_back(str);
		}
		sort(traits->begin(), traits->end());
		buddy_traits.push_back(traits);
	}

	for( int i = 1; i < N; ++i ) {
		for( int j = 0; j < i; ++j ) {
#ifdef AL_DEBUG
			cout << "comparing " << i << " to " << j << endl;
#endif
			vector<string> intersection(C);
			auto it = set_intersection(
					buddy_traits[i]->begin(),
					buddy_traits[i]->end(),
					buddy_traits[j]->begin(),
					buddy_traits[j]->end(),
					intersection.begin()
			);
			if((int)(it - intersection.begin()) > F) {
				add_edge(j,i,G);
			}
		}
	}

	vector<VertexDescriptor> matching(N);
	edmonds_maximum_cardinality_matching(G, &matching[0]);

	cout << (((int)matching_size(G, &matching[0])) >= N/2 ? "not optimal" : "optimal") << endl;
}
