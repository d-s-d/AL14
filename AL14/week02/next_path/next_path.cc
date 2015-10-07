#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
#include<utility>

using namespace std;

struct Vertex {
	vector<int>* neighbors;
	int visits;
};

typedef pair<int,int> QueueEntry;

int main(int argc, char* argv[]) {
	vector<Vertex> vertices;
	queue<QueueEntry> q;
	int n_t, n = 0, m, s, t, _s, _t, solution, line = 1, current_line;

	cin >> n_t; // number of testcases
	line++;
	
	while( n_t > 0 ) {
		current_line = line;
		cin >> n >> m; // no of vertices, of edges
		cin >> s >> t; // source and target
		line += 2;

		n++;
		vertices.reserve(n);
		for( int j = 0; j < n; ++j ) {
			vertices[j] = {new vector<int>(), 0};
		}

		for( int j = 0; j < m; ++j ) {
			cin >> _s >> _t; line++;
			vertices[_s].neighbors->push_back(_t);
		}

		solution = -1;
		while(!q.empty()) q.pop();
		
		q.push(make_pair(s, 0));

		while( !q.empty() ) {
			QueueEntry current = q.front();
			Vertex v = vertices[current.first]; q.pop();
			v.visits++;
			vertices[current.first] = v;
			if( (current.first == t) && (2 == v.visits) ) {
				solution = current.second;
				break;
			}
			if( v.visits <= 2 ) {
				for_each(v.neighbors->begin(), v.neighbors->end(),
						[&q, &vertices, &current](int _v) {
					Vertex neighbor = vertices[_v];
					if( neighbor.visits < 2 ) {
						q.push(make_pair(_v, current.second+1));
					}
				}); 
			}
		}

		//cout << current_line << ": ";
		if( solution < 0 ) {
			cout << "no" << endl;
		} else {
			cout << solution << endl;
		}
		for( int j = 0; j < n; ++j ) {
			delete vertices[j].neighbors;
		}
		n_t--;
	}

	return 0;
}
