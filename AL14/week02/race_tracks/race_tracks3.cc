#include<iostream>
#include<queue>
#include<vector>

#define INDEX(x,y) ((x*sy + y)*50)
#define INDEX_S(x,y,vx,vy) (INDEX(x,y) + (vx+3)*7 + vy + 3)
#define BOUND_CHECK(X,Y,SX,SY) ((X>-1)&&(X<SX)&&(Y>-1)&&(Y<SY))

using namespace std;

typedef struct {
	int x;
	int y;
	int vx;
	int vy;
	int length;
} QueueEntry;

int main( int argc, char* argv[] ) {
	queue<QueueEntry> q;
	vector<bool> grid;
	QueueEntry cur_entry, new_entry;

	char new_x, new_y, x, y, vx, vy;
	int sx, sy, bx, by, ex, ey, ox1, ox2, oy1, oy2;
	int t, p;
	int solution;
	long node;

	cin >> t;
	
	while( t > 0 ) {
		solution = -1;
		queue<QueueEntry>().swap(q);
		//while(!q.empty()) q.pop();

		cin >> sx >> sy;
		cin >> bx >> by >> ex >> ey;
		cin >> p;

		grid.assign(sx * sy * 50, false);

		while( p > 0 ) {
			cin >> ox1 >> oy1 >> ox2 >> oy2;
			for( x = ox1; x <= ox2; ++x ) {
				for( y = oy1; y <= oy2; ++y ) {
					grid[INDEX(x,y)] = true;
				}
			}
			p--;
		}

		node = grid[INDEX(ex, ey)];
		if( !node ) {
			if( bx != ex || by != ey ) {
				cur_entry = {bx, by, 0, 0, 0};
				q.push(cur_entry);

				while( !q.empty() && (solution<0) ) {
					cur_entry = q.front(); q.pop();
					if( !grid[INDEX_S(cur_entry.x, cur_entry.y,
								cur_entry.vx, cur_entry.vy)] ) {
						grid[INDEX_S(cur_entry.x, cur_entry.y,
								cur_entry.vx, cur_entry.vy)] = true;
						for( vx = max(-3, cur_entry.vx - 1); vx <= min( 3, cur_entry.vx + 1 );
								++vx ) {
							for( vy = max(-3, cur_entry.vy - 1); vy <= min( 3, cur_entry.vy + 1 );
									++vy ) {
								new_x = cur_entry.x + vx;
								new_y = cur_entry.y + vy;
								if (BOUND_CHECK(new_x, new_y, sx, sy)) {
								
									if( (new_x == ex) && (new_y == ey) ) {
										solution = cur_entry.length+1;
										break;
									}

									if( !grid[INDEX(new_x, new_y)] &&
											!grid[INDEX_S(new_x, new_y, vx, vy)] ) {
										new_entry = {new_x, new_y, vx, vy, cur_entry.length+1};
										q.push(new_entry);
									}
								} // new_x, new_y bounds
							}
						}
					}
				} // while q not empty
			} else {
				solution = 0;
			}
		}

		if( solution < 0 ) {
			cout << "No solution." << endl;
			// not possible
		} else {
			cout << "Optimal solution takes " << solution << " hops." << endl;
			// reachable within solution steps
		}


		t--;
	}

	return 0;
}
