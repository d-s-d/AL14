#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

void testcase( int sz );

int main()
{
	ios_base::sync_with_stdio(false);
	int sz;
	cin >> sz;

	while( sz ) {
		testcase(sz);
		cin >> sz;
	}
	return 0;
}

void testcase(int sz) {
	long a, b, g, h;

	cin >> a >> b >> g >> h;
	K::Point_2 p(a,b), q(g,h);
	K::Ray_2 l(p,q);
	int i = 0;
	long A1, B1, A2, B2;
	for( ; i < sz; ++i ) {
		cin >> A1 >> B1 >> A2 >> B2;

		K::Point_2 A(A1,B1), B(A2, B2);
		K::Segment_2 S(A,B);
		if( CGAL::do_intersect(l, S) )
		{
			break;
		}
	}
	if( i == sz )
	{
		cout << "no";
	}
	else
	{
		cout << "yes";
		for( i += 1 ; i < sz; ++i )
		{
			cin >> A1 >> B1 >> A2 >> B2;
		}
	}
	cout << endl;
}
