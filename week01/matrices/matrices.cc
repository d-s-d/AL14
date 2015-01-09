#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char* argv[]) {
	int t, tc, j, i1, i2, n, idx2, parity, e, sum;
	vector<int> p;
	vector<int> m;

	cin >> t;
	for( tc = 0; tc < t; ++tc ) {
		sum = 0;
		cin >> n;
		m.reserve(n*n);
		p.reserve(n);

		for( j = 0; j < n*n; ++j ) {
			cin >> m[j];
		}
	
		for( i1 = 0; i1 < n; ++i1 ) {
			for( j = 0; j < n; ++j ) {
				p[j] = 0;
			}

			for( i2 = i1; i2 < n; ++i2 ) {
				e = 0;
				idx2 = i2*n;
				for( j = 0; j < n; ++j ) {
					parity = (p[j] + m[idx2+j]) % 2;
					if( parity ) {
						e = j - e;
					} else {
						e = e + 1;
					}
					p[j] = parity;
					sum += e;
				}
			}
		}

		cout << sum << endl;
	}

	return 0;
}
