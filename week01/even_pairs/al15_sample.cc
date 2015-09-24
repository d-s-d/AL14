#include<iostream>

using namespace std;

int main(int argcs, char* argv[]) {
    long n_tc, j, p_j, e = 0, sum = 0;
    // read length of testcase
    cin >> n_tc;

    // loop through items
    // for each item
    for( j = 1; j <= n_tc; ++j ) {
        cin >> p_j;
        if( p_j % 2 == 1 ) {
            e = (j-1) - e;
        } else {
            e = e + 1;
        }
        sum += e;
    }

    cout << sum << endl;

    return 0;
}
