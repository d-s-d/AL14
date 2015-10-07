#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

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
  std::vector<K::Point_2> pts;
  pts.reserve(sz);
  for (std::size_t i = 0; i < sz; ++i) {
    K::Point_2 p;
    std::cin >> p;
    pts.push_back(p);
  }
  // construct triangulation
  Triangulation t;
  t.insert(pts.begin(), pts.end());

	K::FT min_dist = -1;
  // output all edges
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
	{
		K::FT dist = t.segment(*e).squared_length();
		if( (dist < min_dist) || (min_dist < 0) )
		{
			min_dist = dist;
		}
	}
  std::cout << ceil_to_double(CGAL::sqrt(min_dist)/2.0*100.0) << std::endl;
}
