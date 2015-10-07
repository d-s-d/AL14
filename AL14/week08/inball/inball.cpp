#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

// choose exact floating-point type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

using namespace std;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase( int n, int m );

int main()
{
	ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(0);
	
	size_t n, m;
	cin >> n >> m;
	while( n && m )
	{
		testcase( n, m );
		cin >> n >> m;
	}
	return 0;
}

void testcase( int n, int d )
{
	// unbounded linear problem
	Program lp(CGAL::SMALLER, false, 0, false, 0);
	// maximize radius
	lp.set_c(d, -1);
	// set lower bound on radius r >= 0
	lp.set_l(d, true, 0);

	for( int i = 0; i < n; ++i )
	{
		// a_i^T C + r||a_i|| <= b

		// all entries a are < 2^10, hence
		// a < 2^20 n is of the order 10^3 < 2^10
		// hence, int should be enough
		int b, sum = 0;
		for( int j = 0; j < d; ++j )
		{
			int a;
			cin >> a;
			lp.set_a( j, i, a );
			sum += a * a;
		}
		lp.set_a( d, i, sqrt(sum) );
		cin >> b;
		lp.set_b( i, b );
	}

	Solution s = CGAL::solve_linear_program(lp, ET());
	assert( s.solves_linear_program(lp) );

	if( s.is_infeasible() )
	{
		cout << "none";
	}
	else if( s.is_unbounded() )
	{
		cout << "inf";
	}
	else
	{
		cout << (int) std::floor(-CGAL::to_double(s.objective_value()));
	}
	cout << endl;
}
