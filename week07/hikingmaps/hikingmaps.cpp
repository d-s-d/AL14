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
		int m, n;
		cin >> m >> n;
		testcase(m, n);
		T--;
	}
}

bool triangle_contains_point( Point& point, vector<Point> &t )
{
	bool outside = false;
	for( int i = 0; i < 6; i += 2 )
	{
		outside = CGAL::right_turn( t[i], t[i+1], point );
		if( outside )
		{
			break;
		}
	}
	return !outside;
}

bool is_fully_covered( vector<int> &covering )
{
	for( int i: covering )
	{
		if( i == 0 )
		{
			return false;
		}
	}
	return true;
}

// returns the indices of the legs contained in t
// the index of p_i p_{i+1} is i
void get_contained_legs( vector<int> &legs, vector<Point> &points, vector<Point> &t )
{
	bool last = triangle_contains_point( points[0], t );
	for( int j = 1; j < points.size(); ++j ) 
	{
		bool current = triangle_contains_point( points[j], t );
		if( current && last )
		{
			legs.push_back(j-1);
			//DEBUG
			//cout << "leg " << j-1 << " is contained. " << endl;
		}
		last = current;
	}
}

void testcase( int m, int n )
{
	vector<Point> points;
	vector<vector<int> > triangleToLegs(n);
	//vector<int> triangleCovering(n-1, 0);
	vector<int> triangleCovering(m-1, 0);
	vector<Point> triangle(6);
	points.reserve(m);


	//cout << endl << "#### BEGIN TESTCASE (" << m << ", " << n << ")" << endl;
	for( int i = 0; i < m; ++i )
	{
		int x, y;
		cin >> x >> y;
		Point p(x,y);
		points.push_back( p );
		// DEBUG
		// cout << "added point " << p << endl;
	}

	for( int i = 0; i < n; ++i )
	{
		for( int j = 0; j < 6; ++j )
		{
			int x, y;
			cin >> x >> y;
			triangle[j] = Point(x, y);
		}

		// ensure correct orientiation
		for( int j = 0; j < 6; j += 2 )
		{
			// assumption, all other point lie on the same side
			// we want them to lie on the left side
			if( CGAL::right_turn( triangle[j], triangle[j+1],
						triangle[(j+2)%6] ) )
			{
				std::swap( triangle[j], triangle[j+1] );
			}
		}

		get_contained_legs( triangleToLegs[i], points, triangle );

		/*
		cout << "triangle " << i << " contains the following legs ";
		for( int l: triangleToLegs[i] )
		{
			cout << l << " ";
		}
		cout << endl;*/
	}

	// from here on, the problem can be solved using a simple scanline approach,
	// ... simple

	int min_dist = INT_MAX, l = 0, r = 0;
	// min_dist cannot be below 1
	bool covered = false;
	while( (r < n) && (min_dist > 1) )
	{
		//cout << "window is " << l << " " << r << endl;
		// move the right such that all edges are covered
		do 
		{
			// cover legs that are covered by triangle r
			for( int i: triangleToLegs[r] ) 
			{
				triangleCovering[i]++;
			}
			covered = is_fully_covered( triangleCovering );
			r++;
		} while( !covered && (r < n) );

		if( !covered )
		{
			//cout << "hit right " << n << endl;
			break;
		}

		do
		{
			// cover legs that are covered by triangle r
			for( int i: triangleToLegs[l] ) 
			{
				triangleCovering[i]--;
			}
			covered = is_fully_covered( triangleCovering );
			l++;
		} while( covered && (l < r) );
		
		//cout << "got this far" << endl;
		// it is fully covered now
		if( (r-l+1) < min_dist )
		{
			min_dist = r-l+1;
		}
	}
	cout << min_dist << endl;
}
