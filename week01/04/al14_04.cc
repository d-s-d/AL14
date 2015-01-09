#include<iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int t, i, l, m, n;
    int k, u, r_min, k_min, u_min, v, r_n, r_m;

    cin >> t; // read # of testcases

    for( i = 0; i < t; i++ ) {
        cin >> l >> m >> n;
        k = k_min = l/n;
        r_min = r_n = l - k_min * n; 
        u_min = 0;
        v = 0;
        while( (r_min > 0) && (k >= 0) && (v < n) ) {
            u = r_n/m;
            r_m = r_n - u*m;
            if( r_m < r_min ) {
                u_min = u;
                k_min = k;
                r_min = r_m;
            }
            v++;
            r_n = r_n + n; k--;
        }
        cout << u_min << " " << k_min << " " << r_min << endl;
    }

    return 0;
}
