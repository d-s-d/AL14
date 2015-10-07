#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;

void testcase( int sz );

double ceil_to_double(const K::FT& x) {
	double a = std::floor(CGAL::to_double(x));
	while( a < x ) a += 1;
	while( a-1 >= x) a -= 1;
	return a;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cout << setiosflags(ios::fixed) << setprecision(0);
	int sz;
	cin >> sz;

	while( sz ) {
		testcase(sz);
		cin >> sz;
	}
	return 0;
}

void testcase( int sz )
{
	vector<Point> points;
	points.reserve(sz);
	for( int i = 0; i < sz; ++i )
	{
		Point p;
		cin >> p;
		points.push_back(p);
	}

	Triangulation t;
	t.insert(points.begin(), points.end());

	int m;
	cin >> m;

	for( int i = 0; i < m; ++i )
	{
		Point p;
		cin >> p;
		auto v = t.nearest_vertex(p);
		cout << CGAL::squared_distance(v->point(), p) << endl;
	}
}
