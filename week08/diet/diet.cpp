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

void testcase( int n, int m )
{
	Program lp( CGAL::SMALLER, true, 0, false, 0 );

	for( int i = 0; i < n; ++i )
	{
		int min, max;
		cin >> min >> max;
		lp.set_b(i,    max);
		lp.set_b(n+i, -min);
	}

	for( int j = 0; j < m; ++j )
	{
		int p;
		cin >> p;
		lp.set_c(j, p);
		for( int i = 0; i < n; ++i )
		{
			int c;
			cin >> c;
			lp.set_a(j, i,    c);
			lp.set_a(j, n+i, -c);
		}
	}

	Solution s = CGAL::solve_linear_program(lp, ET());
	assert(s.solves_linear_program(qp));

	if( (s.status() == CGAL::QP_INFEASIBLE) ||
			(s.status() == CGAL::QP_UNBOUNDED) )
	{
		cout << "No such diet.";
	}
	else
	{
		CGAL::Quotient<ET> obj_val = s.objective_value();
		cout << (int)std::floor(CGAL::to_double(obj_val));
	}
	cout << endl;
}
