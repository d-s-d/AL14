#include<iostream>
#include<vector>
#include<climits>

using namespace std;

typedef vector<vector<int> > AdjacencyList;
typedef vector<pair<int, int> > MinMaxList;

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

void get_depth( MinMaxList &min_max_depth, AdjacencyList &edges, int i )
{
	auto min_max = make_pair(INT_MAX, INT_MIN);

	for( int e: edges[i] )
	{
		auto next = min_max_depth[e];
		min_max.first = (next.second+1 < min_max.first) ? next.second+1 : min_max.first;
		min_max.second = (next.first+1 > min_max.second) ? next.first+1 : min_max.second;
	}
	min_max_depth[i] = min_max;
}

void testcase()
{
	int n, m, r, b;
	cin >> n >> m >> r >> b;
	r--; b--;
	AdjacencyList edges(n);

	for( int i = 0; i < m; ++i )
	{
		int u, v;
		cin >> u >> v;
		edges[--u].push_back(--v);
	}

	MinMaxList min_max_depth(n, make_pair(INT_MAX, INT_MIN));

	//initilize top entry
	min_max_depth[n-1] = make_pair(0,0);
	
	for( int i = n - 2; i > -1; --i )
	{
		get_depth( min_max_depth, edges, i );
	}

	int sherlock = min_max_depth[r].first;
	int moriaty = min_max_depth[b].first;

	int winner;
	if( sherlock < moriaty )
	{
		winner = 0;
	}
	else if( sherlock == moriaty )
	{
		if( sherlock % 2 == 0 )
		{
			winner = 1;
		}
		else
		{
			winner = 0;
		}
	}
	else
	{
		winner = 1;
	}
	cout << winner << endl;
}
