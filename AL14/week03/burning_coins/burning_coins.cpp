#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

typedef vector<int> IntVector;
typedef vector<IntVector > IntTable;

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

int getMax( int i, int j, const IntVector &values, IntTable& cache, int sign )
{
	int new_sign = -sign;

	if( cache.at(i).at(j) == -1 )
	{
		if( i + 1 == j )
		{
			cache.at(i).at(j) = sign * max(sign * values.at(i), sign * values.at(j));
		}
		else 
		{
			int addend_i = ( sign == 1 ) ? values.at(i) : 0;
			int addend_j = ( sign == 1 ) ? values.at(j) : 0;
			cache.at(i).at(j) = sign * max(
					sign * (getMax(i+1, j  , values, cache, new_sign ) + addend_i),
					sign * (getMax(  i, j-1, values, cache, new_sign ) + addend_j)
					);
		}
	}
	return cache.at(i).at(j);
}

void testcase()
{
	int n;
	int res = 0;
	cin >> n;

	IntVector values(n);

	for( int i = 0; i < n; ++i )
	{
		int v;
		cin >> v;
		values.at(i) = v;
	}

	if( n == 1 )
	{
		res = values.at(0);
	}
	else
	{
		IntTable cache( n, IntVector(n, -1) );
		res = getMax(0, n-1, values, cache, 1);
	}
	cout << res << endl;
}
