#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>
#include<iostream>
#include<algorithm>


using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2_traits_2<K>  Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 Point;

struct City
{
	Point _coord;
	K::FT _squared_radius;

	City( const Point& p, const K::FT& squared_radius)
		:_coord(p), _squared_radius(squared_radius)
	{
	}

	bool operator <(const City& rhs) const
	{
		return rhs._squared_radius < _squared_radius;
	}
};

void testcase( int n );

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
	int T, n;
	cin >> T;
	cin >> n;

	while( T-- ) {
		testcase(n);
		cin >> n;
	}
	return 0;
}

void testcase( int n )
{
	int m = n - 1; // number of cities not counting the first
	vector<City> cities;
	int x_center, y_center;
	cin >> x_center >> y_center;
	Point p_first(x_center, y_center);
	cities.reserve(m);

	// read cities
	for( int i = 0; i < m; ++i )
	{
		int x, y;
		cin >> x >> y;
		Point p_city(x, y);
		cities.emplace_back( p_city, CGAL::squared_distance(p_first, p_city));
	}

	K::FT cost = 0;
	if( m > 1 )
	{
		int i = 0;
		// sort cities
		sort( cities.begin(), cities.end() );

		Min_circle mc;
		mc.insert(cities[0]._coord);
		K::FT last_radius, cur_radius = mc.circle().squared_radius();
		// add cities to min circle until circle radius is larger than distance
		while( (i < m-2) && (cur_radius < cities[i+1]._squared_radius))
		{
			++i;
			last_radius = cur_radius;	
			mc.insert(cities[i]._coord);
			cur_radius = mc.circle().squared_radius();
		}
		// postcondition: i+1 now points to the first city where the
		// out circle and the first circle overlap
		// we have to decide which solution is best for the outer circle
		// containing only i cities.
		if( i == m-1 ) // && ( cur_radius < cities[i]._squared_radius ) )
		{
			cost = cities[m-1]._squared_radius;
		}
		else if(i == 0)
		{
			cost = cur_radius;
		}
		else
		{
			cost = min( cur_radius, max( last_radius, cities[i]._squared_radius ) );
		}
	}
	cout << ceil_to_double(cost) << endl;
}
