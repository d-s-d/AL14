#include<iostream>
#include<algorithm>
#include<vector>
#include<limits>

using namespace std;

typedef vector<int> IntVector;

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
	return 0;
}

int minimum_change(int amount, IntVector &coins, IntVector &cache)
{
	const int max_int = numeric_limits<int>::max();
	if( amount < 0 )
	{
		return max_int;
	}
	if( cache[amount] < 0 )
	{
		int _min = max_int;
		for( int c: coins )
		{
			_min = min( _min, minimum_change( amount - c, coins, cache ));
		}
		if( _min != max_int )
		{
			_min++;
		}
		cache[amount] = _min;
	}
	return cache[amount];
}

void testcase()
{
	int n_coins, n_tests;
	cin >> n_coins >> n_tests;

	IntVector coins(n_coins, 0);
	for( int i = 0; i < n_coins; ++i )
	{
		int c;
		cin >> c;
		coins[i] = c;
	}

	IntVector test_values(n_tests, 0);

	for( int i = 0; i < n_tests; ++i )
	{
		int t;
		cin >> t;
		test_values[i] = t;
	}

	int max_test = *max_element(test_values.begin(), test_values.end());

	IntVector cache(max_test+1, -1);
	cache[0] = 0;
	for( int t: test_values )
	{
		int change = minimum_change(t, coins, cache);
		if( change == numeric_limits<int>::max() )
		{
			cout << "not possible";
		}
		else
		{
			cout << change;
		}
		cout << endl;
	}
}

