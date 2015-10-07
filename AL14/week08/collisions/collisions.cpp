#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Triangulation_vertex_base_with_info_2.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<iostream>
#include<algorithm>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<bool, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;
typedef K::Point_2 Point;

void testcase( int sz, int d );

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
	int T, n, d;
	cin >> T;

	for( int i = 0; i < T; ++i )
	{
		cin >> n >> d;
		testcase( n, d );
	}
	return 0;
}

void testcase( int sz, int d )
{
	double dist = d;
	dist *= dist;

	vector<Point> points;
	points.reserve(sz);

	for( int i = 0; i < sz; ++i )
	{
		int x, y;
		cin >> x >> y;
		points.push_back( Point( x, y ) );
	}

	Triangulation t;
	t.insert( points.begin(), points.end() );
	for( auto v_itr = t.finite_vertices_begin(); v_itr != t.finite_vertices_end();
			++v_itr )
	{
		v_itr->info() = false;
	}

	int count = 0;
	for( auto e_itr = t.finite_edges_begin(); e_itr != t.finite_edges_end();
			++e_itr )
	{
		if( t.segment(e_itr).squared_length() < dist )
		{
			auto v1 = e_itr->first->vertex((e_itr->second+1)%3),
			v2 = e_itr->first->vertex((e_itr->second+2)%3);

			//cout << "v1: " << v1->point() << "  v2: " << v2->point() << endl; 
			if( !v1->info() )
			{
				count++;
				v1->info() = true;
			}
			if( !v2->info() )
			{
				count++;
				v2->info() = true;
			}
		}
	}
	cout << count << endl;
}
