#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

void testcase( int sz );

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

double ceil_to_double(const K::FT& x) {
	double a = std::floor(CGAL::to_double(x));
	while( a < x ) a += 1;
	while( a-1 >= x) a -= 1;
	return a;
}

void testcase( int sz ) {
	vector<K::Point_2> points;
	
	for( int i = 0; i < sz; ++i )
	{
		long x, y;
		cin >> x >> y;
		K::Point_2 p(x,y);
		points.push_back(p);
	}

	Min_circle min_circle(points.begin(), points.end(), true);
	Traits::Circle circle = min_circle.circle();
	cout << ceil_to_double((CGAL::sqrt(circle.squared_radius()))) << endl;
}
