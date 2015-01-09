#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(int argc, char* argv[]) {
	pair<int, int> boat;
	vector<pair<int,int>> boats;

	int t, n, i, result, front, d;
	int results[2];

	cin >> t;
	while( t > 0 ) {
		cin >> n;
		boats.reserve(n);
		for( i = 0; i < n; ++i ) {
			cin >> boat.second >> boat.first;
			boats[i] = boat;
		}

		sort(boats.begin(), boats.begin()+n);

#ifdef ALDEBUG
		for( i = 0; i < n; ++i ) {
			cout << boats[i].first << " " << boats[i].second << endl;
		}
#endif

		results[0] = 0;
		results[1] = 0;
		if( n > 0 ) {
			for( d = 1; d >= -1; d-=2 ) {
				if( d < 0 ) i = n-1;
				else        i = 0;
				front = boats[i].first;
				results[(d+2)/2] = 1;
#ifdef ALDEBUG
				cout << "added boat " << i << endl;
#endif
				i += d;
				while( (i >= 0) && (i < n) ) {
					front += d*boats[i].second;
					if( d*front < d*boats[i].first )
						front = boats[i].first;
					results[(d+2)/2]++;
#ifdef ALDEBUG
					cout << "added boat " << i << " front: " << front << endl;
#endif
					while( (i>=0) && (i<n) && (d*boats[i].first < d*front) )
						i += d;
				}
				i = n;
			}
		}
		result = max(results[0], results[1]);
		cout << result << endl;

		t--;
	}
}
