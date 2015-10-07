#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<iostream>
#include<algorithm>

#define MIN2(A,B)       ((A)<(B)?(A):(B))
#define MIN3(A,B,C)     (MIN2(MIN2((A),(B)),(C)))
#define MIN4(A,B,C,D)   (MIN2(MIN3((A),(B),(C)),(D)))
#define MIN5(A,B,C,D,E) (MIN2(MIN4((A),(B),(C),(D)),(E)))
#define SQUARE(A) ((A)*(A))

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
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

double time_to_die( K::FT distance )
{
	distance = CGAL::sqrt(distance);
	if( distance < 0.5 ) 
	{
		distance = 0.5;
	}
	return ceil_to_double( CGAL::sqrt( distance - 0.5 ) );
}

K::FT minimum_squared_distance_to_dish( long L, long B, long R, long T, Point &p )
{
	K::FT min_dist = MIN4(p.x()-L, R-p.x(), T-p.y(), p.y()-B);
	return min_dist * min_dist;
}

void testcase( int sz )
{
	long L, B, R, T;
	int median = sz/2;

	cin >> L >> B >> R >> T;

	if( sz > 2 )
	{
		vector<Point> points;
		vector<K::FT> distances;
		points.reserve(sz);
		distances.reserve(sz);

		for( int i = 0; i < sz; ++i )
		{
			Point p;
			cin >> p;
			points.push_back(p);
		}

		Triangulation triag;
		triag.insert( points.begin(), points.end() );

		for( auto v_itr = triag.finite_vertices_begin(); v_itr != triag.finite_vertices_end();
				++v_itr )
		{
			K::FT min_dist = -1;
			auto e_itr = triag.incident_edges(v_itr->handle());
			do
			{
				if(!triag.is_infinite(e_itr))
				{
					auto seg = triag.segment( e_itr );
					auto dist = seg.squared_length();
					if( (dist < min_dist) || (min_dist == -1) )
					{
						min_dist = dist;
					}
				}
				e_itr++;
			} while( e_itr != triag.incident_edges(v_itr->handle()) ); 

			K::FT min_dish = minimum_squared_distance_to_dish( L, B, R, T, v_itr->point() );
			min_dist = MIN2( min_dish, min_dist/4 );

			distances.push_back(min_dist);
		}

		sort(distances.begin(), distances.end());
		cout << time_to_die( distances[0] ) << " ";
		cout << time_to_die( distances[median] ) << " ";
		cout << time_to_die( distances[sz-1] ) << endl;
	}
	else 
	{
		K::FT t;
		if( sz == 1 )
		{
			Point p;
			cin >> p;
			auto min_dist = minimum_squared_distance_to_dish( L, B, R, T, p );
			t = time_to_die( min_dist );
		}
		else // sz == 2
		{
			Point p1, p2;
			cin >> p1 >> p2;
			auto dish1 = minimum_squared_distance_to_dish( L, B, R, T, p1 );
			auto dish2 = minimum_squared_distance_to_dish( L, B, R, T, p1 );
			auto dist = CGAL::squared_distance( p1, p2 );
			
			dist = MIN3( dish1, dish2, dist );
			t = time_to_die( dist ); 
		}
		cout << t << " " << t << " " << t << endl;
	}
}
