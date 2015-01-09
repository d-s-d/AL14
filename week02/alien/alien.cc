#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct { int first; int second; int access_order; bool included; } Ival;

int main(int argc, char* argv[]) {
	int t, i, n, m, included_intervals, front, max_h = 0;
	Ival interval;
	vector<Ival> ivals;
	cin >> t;

	while( t > 0 ) {
		ivals.clear();
		cin >> n >> m;

		included_intervals = 0;
		max_h = 0;
		for( i = 0; i < n; ++i ) {
			cin >> interval.first >> interval.second;
			interval.included = false;
			interval.access_order = 0;
			ivals.push_back(interval);
		}

		sort(ivals.begin(), ivals.end(), [](const Ival &i1, const Ival &i2) -> bool {
			return i1.first < i2.first;
		});

		front = 0;
		for( i = 0; i < n; ++i ) {
			Ival ival = ivals[i];
			if( ival.second <= front ) {
				included_intervals += 1;
				ival.included = true;
			} else {
				front = ival.second;
			}
			if( (ival.first <= max_h+1) && (max_h < ival.second) ) {
				max_h = ival.second;
			}
			ival.access_order = i;
			ivals[i] = ival;
		}

		sort(ivals.begin(), ivals.end(), [](const Ival &i1, const Ival &i2) -> bool {
			return (i1.second > i2.second) ||
			((i1.second == i2.second) && (i1.access_order > i2.access_order));
		});

		front = m+1;
		for_each( ivals.begin(), ivals.end(),
			[&front, &included_intervals](Ival &ival) -> void {
			if( (ival.first >= front) ) {
				if( !(ival.included) )
					included_intervals += 1;
			} else {
				front = ival.first;
			}
		});

		if( max_h != m )
			included_intervals = n;
		cout << n - included_intervals << endl;
		t--;
	}
	return 0;
}
