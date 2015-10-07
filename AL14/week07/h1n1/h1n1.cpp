#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<CGAL/Triangulation_face_base_with_info_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<bool, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Tds::Face_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

void testcase( int sz );
bool face_dfs( Triangulation &t, Face_handle f, K::FT d );

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
	std::vector<Point> points;
	points.reserve(sz);
	for( int i = 0; i < sz; ++i )
	{
		Point p;
		std::cin >> p;
		points.push_back(p);
	}

	Triangulation t;
	t.insert(points.begin(), points.end());

	int m;
	cin >> m;
	for( int i = 0; i < m; ++i )
	{
		K::FT x,y,d;
		cin >> x >> y >> d;
		Point p(x, y);

		// get nearest vertex in t
		Point nearest_point = t.nearest_vertex(p)->point();
		// if nearest vertex is not too close
		if( CGAL::squared_distance(p, nearest_point) >= d )
		{
			// get the face containing point p
			Face_handle f = t.locate(p);
			// if face is NULL (outside affine hull)
			if( f == NULL )
			{
				cout << "y";
			}
			else
			{
				// only now is it necessary to deal with faces
				for( auto f_itr = t.all_faces_begin(); f_itr != t.all_faces_end(); ++f_itr )
				{
					f_itr->info() = false;
				}

				if( face_dfs( t, f, d ) )
				{	cout << "y"; }
				else
				{	cout << "n"; }
			}
		}
		else // nearest point to close
		{
			cout << "n";
		}

		// I guess the biggest difference between algorithmic research and software engineering
		// is that in algorithmic research you test for the general case and in software engineering
		// you test for the corner cases.
	}
	cout << endl;
}

bool face_dfs( Triangulation &t, Face_handle f, K::FT d )
{
	bool res = false;
	if( !f->info() ) 
	{
		f->info() = true;
		// if f is an infinite face
		if(t.is_infinite(f))
		{
			//cout << "found infinite face" << endl;
			res = true;
		}
		else
		{
			/*
			Point dual = t.dual(f); // construction :-(
			Point nearest = t.nearest_vertex(dual)->point();

			//cout << "Visiting face with dual: " << dual << endl;
			if( CGAL::squared_distance( nearest, dual ) >= d )
			{
			*/
				int neighbor = 3;
				// for each neighboring edge and not res
				do
				{
					neighbor--;
					Segment s = t.segment( f, neighbor );
					// if edge is larger or equal to 2*sqrt(d) 
					if( s.squared_length() >= 4*d )
					{
						//cout << "visiting neighbor: " << neighbor << endl;
						res = face_dfs( t, f->neighbor(neighbor), d );
					}
				} while( (neighbor > 0) && (!res) );
			//}
		}
	}
	return res;
}
