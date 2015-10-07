#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

typedef pair<int, int> Boat;

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

void testcase()
{
	Boat boat;
	int n;
	cin >> n;

	vector<Boat> boats(n);
	for( int i = 0; i < n; ++i )
	{
		// first: position, second: length
		// in input: length, position
		cin >> boat.second >> boat.first;
		boats[i] = boat;
	}

	sort(boats.begin(), boats.end());

	int upper = boats[0].first;
	int i = 1;
	int count = 1;
	while( i < n )
	{
		if( boats[i].first >= upper )
		{
			int j = i;
			int _upper = numeric_limits<int>::max();
			int _max_i = i;
			while( (j < n) && (_upper >= boats[j].first ) )
			{
				int _max = max(
						boats[j].first, // position 
						upper + boats[j].second // length
						);
				if( _max < _upper )
				{
					_upper = _max;
					_max_i = j + 1;
				}
				++j;
			}
			upper = _upper;
			i = _max_i;
			++count;
		}
		else
		{
			++i;
		}
	}
	cout << count << endl;
}

