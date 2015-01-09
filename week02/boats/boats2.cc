#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(int argc, char* argv[]) {
	pair<int, int> boat;
	vector<pair<int,int>> boats;

	int t, n, i, result, front, d;

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

		result = 0;
		if( n > 0 ) {
			front = boats[i].first;
			result = 1;
#ifdef ALDEBUG
			cout << "added boat " << i << endl;
#endif
			i += d;
			while( i < n ) {
				cur_length = boats[i++].second;
				front += cur_length;
				while( (i<n) && (boats[i].first < front) ) {
					if( boats[i].second < cur_length )
					i += 1;
				}
				if( front < boats[i].first )
					front = boats[i].first;
				result++;
#ifdef ALDEBUG
				cout << "added boat " << i << " front: " << front << endl;
#endif
			}
			i = n;
		}
		result = max(results[0], results[1]);
		cout << result << endl;

		t--;
	}
}
