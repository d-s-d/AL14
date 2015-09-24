#include<iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int t, ds, d, h, window;

    cin >> t;

    while(t)
    {
        cin >> ds;
        window = 1;
        for(d = 0; d < ds && d < window; d++)
        {
            cin >> h;
            if( d + h > window )
            {
                window = d + h;
            }
        }
        cout << d << endl;
        // read remaining dominos
        for(; d < ds; d++)
        {
            cin >> h;
        }
        t--;
    }
}
