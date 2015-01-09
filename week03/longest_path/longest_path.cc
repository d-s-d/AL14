#include<iostream>
#include<vector>
#include<climits>

using namespace std;

struct Vertex {
	vector<int>* neighbors;

	Vertex() {neighbors = new vector<int>();}
	~Vertex() {
		// cout << "destructor was called" << endl;
		delete neighbors;}
};

struct Graph {
	vector<Vertex*> vertices;
	int max = 0;
};

int rec_path_length(Graph &graph, int cur, int callee) {
	int longest[2] = {0,0}, t, sum;

	Vertex* v = graph.vertices[cur];
	int n = v->neighbors->size();

	//cout << n << endl;
	for( int i = 0; i < n; ++i ) {
		int child = v->neighbors->at(i);
		if( child != callee ) {
			int pivot = rec_path_length( graph, child, cur );
			if( pivot > longest[0] ) {
				t = longest[0]; longest[0] = pivot; longest[1] = t;
			} else {
				if( pivot > longest[1] ) {
					longest[1] = pivot;
				}
			}
		}
	}

	//cout << "cur: " << cur << " longest :" << longest[0] << endl;
	sum = longest[0] + longest[1] + 1;
	if( sum > graph.max )
		graph.max = sum;
	return longest[0]+1;
}

int main(int argc, char* argv[]) {
	int u,v,n,n_t;
	Graph graph; graph.max = 0;
	// vector<Vertex>& vertices = graph.vertices;

	cin >> n_t;
	while( n_t > 0 ) {
		cin >> n;

		graph.vertices.reserve(n);
		for( int i = 0; i < n; ++i ) {
			graph.vertices[i] = new Vertex();
		}

		// cout << "got here" << endl;
		for( int i = 1; i < n; ++i ) {
			cin >> v >> u; // read an edge
			graph.vertices[v]->neighbors->push_back(u);
			graph.vertices[u]->neighbors->push_back(v);
		}

		// cout << "got here2" << endl;
		rec_path_length(graph, 0, 0);

		cout << graph.max << endl;

		// cleanup
		for( int i = 0; i < n; ++i ) {
			// i hate boilerplate code
			delete graph.vertices[i];
		}
		graph.vertices.clear();
		n_t--;
	}

	return 0;
}
