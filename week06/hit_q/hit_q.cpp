#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

void testcase( int sz );

double floor_to_double(const K::FT& x)
{
	double a = std::floor(CGAL::to_double(x));
	while( a > x ) a -= 1;
	while( a+1 <= x) a += 1;
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
	long x, y, a, b;
	cin >> x >> y >> a >> b;
	Point O(x,y), A(a,b);
	K::Ray_2 r(O,A);
	Point R_min;
	K::FT min_dist = -1;
	
	// search for the min sq. distance over all input obstacles
	for( int i = 0; i < sz; ++i )
	{
		long X1, Y1, X2, Y2; 
		K::FT dist;
		Point R;
		
		cin >> X1 >> Y1 >> X2 >> Y2;
		Segment s(Point(X1,Y1), Point(X2, Y2));
		auto intersec = CGAL::intersection(r, s);
		if( intersec ) {
			if( const Point* intersec_point = boost::get<Point>(&*intersec) )
			{
				dist = CGAL::squared_distance(*intersec_point, O);
				R = *intersec_point;
			}
			else if ( const Segment* intersec_seg = boost::get<Segment>(&*intersec) )
			{
				auto _dist1 = CGAL::squared_distance(intersec_seg->source(), O),
						 _dist2 = CGAL::squared_distance(intersec_seg->target(), O);
				if( _dist1 > _dist2 )
				{
					R = intersec_seg->target();
					dist = _dist2;
				}
				else
				{
					R = intersec_seg->source();
					dist = _dist1;
				}
			}

			if( (dist < min_dist) || (min_dist < 0) )
			{
				R_min = R;
				min_dist = dist; 
			}
		}
	}

	if( min_dist < 0 )
	{
		cout << "no";
	}
	else
	{
		cout << floor_to_double(R_min.x()) << " " << floor_to_double(R_min.y());
	}
	cout << endl;
}
