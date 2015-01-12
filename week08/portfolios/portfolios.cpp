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
	// general form: Ax >= b, l = (0,0,0...,0)
	Program qp(CGAL::LARGER, true, 0, false, 0);

	const int Ceq = 0,
				Req = 1;

	// Constraints:
	// -alpha^T * c >= -C_min
	// alpha^T * r >= R_min
	
	// read r and c
	for( int i = 0; i < n; ++i )
	{
		int c, r;
		cin >> c >> r;
		qp.set_a(i, Ceq, -c);
		qp.set_a(i, Req, r);
	}

	// read V
	for( int i = 0; i < n; ++i )
	{
		for( int j = 0; j <= i; ++j )
		{
			int v; // v_ij
			cin >> v;
			qp.set_d( i, j, 2*v );
		}
		for( int j = i+1; j < n; ++j )
		{
			int v;
			cin >> v;
		}
	}

	for( int i = 0; i < m; ++i )
	{
		int C, R, V;
		cin >> C >> R >> V;

		qp.set_b( Ceq, -C );
		qp.set_b( Req, R );
		
		Solution s = CGAL::solve_quadratic_program( qp, ET() );
		assert(s.solves_quadratic_program(qp));

		if( (s.status() != CGAL::QP_INFEASIBLE) &&
				(s.status() != CGAL::QP_UNBOUNDED) &&
				V >= CGAL::to_double(s.objective_value()) )
		{
			cout << "Yes.";
		}
		else
		{
			cout << "No.";
		}
		cout << endl;
	}
}
