#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

void testcase( int m, int n );

int main()
{
	ios_base::sync_with_stdio(false);
	cout << setiosflags(ios::fixed) << setprecision(0);
	int T;

	cin >> T;
	while( T )
	{
		int x, y;
		vector<Point> pts;
		for( int i = 0; i < 3; ++i )
		{
			cin >> x >> y;
			pts.push_back( Point(x, y) );
		}

		cout << CGAL::right_turn(pts[0], pts[1], pts[2])<< endl;
		cin >> T;
	}
}
