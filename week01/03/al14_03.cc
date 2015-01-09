#include<iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int i, j;
    float sum, addend;

    // read # test cases
    cin >> i;

    while(i > 0) {
        cin >> j;
        sum = 0.0;
        while(j > 0) {
            cin >> addend;
            sum += addend;
            --j;
        }
        cout << sum << endl;
        --i;
    }
    return 0;
}
