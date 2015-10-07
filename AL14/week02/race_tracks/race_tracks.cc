#include<iostream>
#include<queue>
#include<vector>

using namespace std;

#define OBSTACLE_BIT ((long)1<<49)
#define NODE_BIT(X,Y) ((long)1<<((X+3)*7+(Y+3)))
#define IS_NOT_VISITED(NODE, VX, VY) ((NODE & NODE_BIT(VX,VY))==0)
#define SET_VISITED(NODE, VX, VY) (NODE | NODE_BIT(VX,VY))
#define IS_NOT_OBSTACLE(NODE) ((NODE & OBSTACLE_BIT)==0)
#define BOUND_CHECK(X,Y,SX,SY) ((X>-1)&&(X<SX)&&(Y>-1)&&(Y<SY))

typedef struct {
	char x;
	char y;
	char vx;
	char vy;
	int  length;
} QueueEntry;

int main(int argc, char* argv[]) {
	queue<QueueEntry> q;
	vector<long> grid;
	QueueEntry cur_entry, new_entry;

	char new_x, new_y, x, y, vx, vy, dx, dy;
	int sx, sy, bx, by, ex, ey, ox1, ox2, oy1, oy2;
	int t, p;
	int solution, idx;
	long node;
	cin >> t;

	while( t > 0 ) {
		solution = -1;
		while(!q.empty()) q.pop();
		cin >> sx >> sy; 
		cin >> bx >> by >> ex >> ey;
		cin >> p;

		grid.assign(((int)sx)*((int)sy), (long) 0);
		while( p > 0 ) {
			cin >> ox1 >> oy1 >> ox2 >> oy2;
			for( x = ox1; x <= ox2; ++x ) {
				for( y = oy1; y <= oy2; ++y ) {
					grid[((int)x)*sy + y] = OBSTACLE_BIT;
				}
			}
			p--;
		}

		node = grid[((int)ex)*sy + ey];
		if( IS_NOT_OBSTACLE(node) ) {
			if( bx != ex || by != ey ) {
				cur_entry = {(char)bx, (char)by, 0, 0, 0};
				q.push(cur_entry);

				while( !q.empty() && (solution < 0) ) {
					cur_entry = q.front(); q.pop();
					idx = ((int)cur_entry.x)*sy + cur_entry.y;
					node = grid[idx];
					grid[idx] = SET_VISITED(node, cur_entry.vx, cur_entry.vy);
					for( dx = -1; (dx < 2) && (solution < 0); ++dx ) {
						for( dy = -1; dy < 2; ++dy ) {

							vx = cur_entry.vx + dx;
							vy = cur_entry.vy + dy;
							if( (vx > -4) && (vx < 4) && (vy > -4) && (vy < 4)) {
								new_x = cur_entry.x + vx;
								new_y = cur_entry.y + vy;
								
								if( (new_x == ex) && (new_y == ey) ) {
									solution = cur_entry.length+1;
									break;
								}

								if (BOUND_CHECK(new_x, new_y, sx, sy)) {
									node = grid[((int)new_x)*sy + new_y];
									if( IS_NOT_OBSTACLE(node) &&
											IS_NOT_VISITED(node, vx, vy) ) {
										new_entry = {new_x, new_y, vx, vy, cur_entry.length+1};
										q.push(new_entry);
									}
								}
							}
						}
					}
				} // !q.empty() && solution < 0
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
