#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int main(int argc, char* argv[]) {
    int* min_coins;
    int* coins;
    int n, i, i_c, i_tc, j;
    int n_c = 0, n_tc = 0, amount = 0;
		int coins_cap = 0, min_coins_cap = 0;
    int min_baseidx, min_idx;
    int base_min;

    // read number of test cases
    cin >> n;

		min_coins = new int[0];
		coins = new int[0];

    for( i = 0; i < n; ++i ) {
        cin >> n_c >> n_tc;

				if( n_c > coins_cap ) {
					delete coins;
					coins = new int[n_c];
					coins_cap = n_c;
				}

        for( i_c = 0; i_c < n_c; ++i_c ) {
            cin >> coins[i_c];
        }

        for( i_tc = 0; i_tc < n_tc; ++i_tc ) {
            cin >> amount;
						if( amount + 1 > min_coins_cap ) {
							min_coins_cap = amount + 1;
							delete min_coins;
							min_coins = new int[min_coins_cap];
						}
						for( j = 1; j < min_coins_cap; ++j )
							min_coins[j] = INT_MAX;
						min_coins[0] = 0;

            for( min_baseidx = 0; min_baseidx < amount; ++min_baseidx ) {
                base_min = min_coins[min_baseidx];
								if( base_min < INT_MAX ) {
									for( i_c = 0; i_c < n_c; ++i_c ) {
											min_idx = min_baseidx + coins[i_c];
											if( min_idx <= amount ) {
													min_coins[min_idx] = min(min_coins[min_idx], base_min + 1);
											}
									}
								}
            }

            if( min_coins[amount] < INT_MAX ) {
                cout << min_coins[amount] << endl;
            } else {
                cout << "not possible" << endl;
            }
        }
    }

    return 0;
}
