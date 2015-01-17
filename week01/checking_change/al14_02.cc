#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int main(int argc, char* argv[]) {
    vector<int> min_coins;
    vector<int> coins;
    int n, i, i_c, i_tc;
    int n_c = 0, n_tc = 0, amount = 0;
    int min_baseidx, min_idx;
    int base_min;

    // read number of test cases
    cin >> n;

    for( i = 0; i < n; ++i ) {
        cin >> n_c >> n_tc;

        coins.reserve(n_c);
        for( i_c = 0; i_c < n_c; ++ i_c ) {
            cin >> coins[i_c];
        }

        for( i_tc = 0; i_tc < n_tc; ++i_tc ) {
            cin >> amount;
            min_coins.assign(amount + 1, INT_MAX);
            min_coins[0] = 0;

            for( min_baseidx = 0; min_baseidx < amount; ++min_baseidx ) {
                base_min = min_coins[min_baseidx];
                for( i_c = 0; i_c < n_c; ++i_c ) {
                    min_idx = min_baseidx + coins[i_c];
                    if( (base_min < INT_MAX) && (min_idx <= amount) ) {
                        min_coins[min_idx] = min(min_coins[min_idx], base_min + 1);
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
