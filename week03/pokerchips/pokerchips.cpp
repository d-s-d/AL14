#include<vector>
#include<iostream>
#include<climits>
#include<algorithm>
#include<map>

using namespace std;

typedef vector<int> IntVector;
typedef vector<IntVector > Color_map;
typedef map<vector<int>, int> Result_cache;

void testcase();

int main(void)
{
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;

	while(T--)
	{
		testcase();
	}
}

int get_next_elem_in_set( int k, int s, int n, const IntVector& stack_state )
{
	while( (k < n) && ( ((s & (1 << k)) == 0) || stack_state[k] == 0 ) )
		k++;
	return k;
}

int search_max(const Color_map &colors, const IntVector stack_state, Result_cache &result_cache)
{
	IntVector next_state;
	int result = 0;
	int n = stack_state.size();

	auto cached = result_cache.find(stack_state);
	if( cached == result_cache.end() )
	{
		for( int s = 0; s < (1 << n); ++s )
		{
			next_state = stack_state;
			// select a subset s
			int set_color = 0;
			int count = 0;
			int color;
			int k = 0;
			k = get_next_elem_in_set( k, s, n, stack_state );
			while( k < n )
			{
				color = colors[k][stack_state[k]-1];
				set_color = (set_color == 0) ? color : set_color;
				if( set_color != color )
				{
					count = 0;
					break;
				}
				
				count++;
				next_state[k]--;
				k = get_next_elem_in_set( ++k, s, n, stack_state );
				//cout << "chosen " << k << endl;
			}
			if( count > 0 )
			{
				int _result = search_max( colors, next_state, result_cache )
					+ (( count > 1 ) ? (1 << (count - 2)) : 0 );
				if( result < _result )
				{
					result = _result;
				}
			}
		}
		result_cache.insert(make_pair(stack_state, result));
	}
	else
	{
		result = cached->second;
	}
	return result;
}

void testcase()
{
	int n; // number of stacks
	int res = 0;
	cin >> n;
	IntVector stack_state(n);
	Color_map colors;
	for( int i = 0; i < n; ++i )
	{
		int m;
		cin >> m;
		stack_state[i] = m;
		if( m )
		{
			colors.push_back(IntVector(m));
		}
		else
		{
			colors.push_back(IntVector());
		}
	}

	// read colors
	for( int i = 0; i < n; ++i )
	{
		for( int j = 0; j < stack_state[i]; ++j )
		{
			int c;
			cin >> c;
			colors[i][j] = c;
		}
	}

	// count non-zero stacks
	int non_empty = n - count( stack_state.begin(), stack_state.end(), 0 );

	if( non_empty > 1 )
	{
		Result_cache result_cache;
		res = search_max(colors, stack_state, result_cache);
	}
	cout << res << endl;
}
