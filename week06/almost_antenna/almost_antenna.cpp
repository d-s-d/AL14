#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

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
	vector<K::Point_2> points;

	for( int i = 0; i < sz; ++i )
	{
		long x, y;
		cin >> x >> y;
		points.push_back(K::Point_2(x,y));
	}

	Min_circle min_circle(points.begin(), points.end(), true);
	Traits::Circle circle = min_circle.circle();
	if( circle.squared_radius() > 0 )
	{
		long min_radius = ceil_to_double(CGAL::sqrt(circle.squared_radius()));
		auto itr_sp_begin = min_circle.support_points_begin();
		auto itr_sp_end = min_circle.support_points_end();
		int n_sp = itr_sp_end - itr_sp_begin; 
		if( n_sp < 4 )
		{
			// find minimum over all sets of points
			for( auto itr_sp = itr_sp_begin; itr_sp != itr_sp_end; ++itr_sp )
			{
				points.erase(std::find(points.begin(), points.end(), *itr_sp));
				Min_circle _min_circle(points.begin(), points.end(), true);
				Traits::Circle _circle = _min_circle.circle();
				if( _circle.squared_radius() > 0 )
				{
					long _min_radius = ceil_to_double(CGAL::sqrt(_circle.squared_radius()));
					if( _min_radius < min_radius )
					{
						min_radius = _min_radius;
					}
				}
				else
				{
					min_radius = 0;
				}
				points.push_back(*itr_sp);
			}
		}
		cout << min_radius << endl;
	}
	else
	{
		
	}
}
