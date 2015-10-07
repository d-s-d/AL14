#include<iostream>
#include<vector>
#include<climits>

using namespace std;

typedef vector<int> IntVector;
typedef vector<IntVector > Graph;

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

pair<int, int> longest_path( Graph &g, int origin, int start, int depth )
{
	auto res = make_pair(start, depth);
	// for all neighbors
	for( int n: g[start] )
	{
		if( n != origin )
		{
			auto longest = longest_path( g, start, n, depth + 1 );
			if( longest.second > res.second )
			{
				res = longest;
			}
		}
	}
	return res;	
}

void testcase()
{
	int n;
	cin >> n;

	Graph g(n);
	for( int i = 0; i < n-1; ++i )
	{
		int u, v;
		cin >> u >> v;
		g.at(u).push_back(v);
		g.at(v).push_back(u);
	}

	auto furthest = longest_path( g, -1, 0, 1 );
	auto longest = longest_path( g, -1, furthest.first, 1 );
	cout << longest.second << endl;
}
