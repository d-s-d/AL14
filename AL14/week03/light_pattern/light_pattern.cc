#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


//This uses fewer arithmetic operations than any other known  
//implementation on machines with fast multiplication.
//It uses 12 arithmetic operations, one of which is a multiply.
static unsigned bitcount (unsigned int n)
{
    unsigned int m1 = (~(unsigned int)0) / 3;
    unsigned int m2 = (~(unsigned int)0) / 5;
    unsigned int m4 = (~(unsigned int)0) / 17;
    unsigned int h01 = (~(unsigned int)0) / 255;

    n -= (n >> 1) & m1;             //put count of each 2 bits into those 2 bits
    n = (n & m2) + ((n >> 2) & m2); //put count of each 4 bits into those 4 bits 
    n = (n + (n >> 4)) & m4;        //put count of each 8 bits into those 8 bits 

    return (n * h01) >> (32-8);
    // returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}

int main(int argc, char* argv[]) {
	int t, pattern, n, k, mask, block_count;
	vector<int> blocks, best_inv, best_notinv;
	char bit;

	cin >> t;
	while( t > 0 ) {
		cin >> n >> k >> pattern;
		
		mask = (1<<k)-1;
		block_count = n/k;
		blocks.reserve(block_count);
		best_inv.reserve(block_count);
		best_notinv.reserve(block_count);

		for( int i = 0; i < block_count; ++i ) {
			int block = 0;
			for( int j = k-1; j >= 0; --j ) {
				cin >> bit;
				if( bit == '1' ) 
					block += (1<<j);
			}
			blocks[i] = block;
		}

#ifdef ALDEBUG
		cout << "pattern: " << pattern << endl;
		cout << "block count: " << block_count << endl;
		cout << "mask: " << mask << endl;
		for_each( blocks.begin(), blocks.begin()+block_count, [](const int& v)->void {cout << v << endl;} );
#endif

		best_inv[0] = bitcount( ((~blocks[0]) ^ pattern) & mask);
		best_notinv[0] = bitcount( (blocks[0] ^ pattern) & mask);

#ifdef ALDEBUG
		cout << "best_inv[0]: " << best_inv[0] << endl;
		cout << "best_notinv[0]: " << best_notinv[0] << endl;
#endif
		for( int i = 1; i < block_count; ++i ) {
			int ham_dist = bitcount( (blocks[i] ^ pattern) & mask);

			best_inv[i] = min( best_inv[i-1] + (k-ham_dist), best_notinv[i-1] + (k-ham_dist) + 1 ); 
			best_notinv[i] = min( best_inv[i-1] + ham_dist + 1, best_notinv[i-1] + ham_dist );
		}

		cout << min( best_inv[block_count-1]+1, best_notinv[block_count-1] ) << endl; 
		t--;
	}
}
