#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/boyer_myrvold_planar_test.hpp>

using namespace std;
using namespace boost;

typedef vector<vector<int> > AdjacencyList;
typedef vector<int> IntVector;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int> > Graph;

void testcase();

int main()
{
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;

	while(T--)
	{
		testcase();
	}
}

void testcase()
{
	int m;
	cin >> m;

	AdjacencyList votes(m, IntVector(m-1));

	for( int i = 0; i < m; ++i )
	{
		for( int j = 0; j < m-1; ++j )
		{
			int v;
			cin >> v;
			votes[i][j] = v;
		}
	}
	
	Graph G(m);
	int T = 0;

	while( T < m-1 )
	{
		for( int i = 0; i < m; ++i )
		{
			add_edge(i, votes[i][T], G);
		}
		if( boyer_myrvold_planarity_test(G) )
		{
			++T;
		}
		else
		{
			break;
		}
	}
	cout << T << endl;
}
