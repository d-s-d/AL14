// example: find the risk-optimal investment strategy
// in Swatch and Credit Suisse shares (data as in lecture)
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

void testcase_1(int a, int b);
void testcase_2(int a, int b);

int main()
{
	ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(0);
	
	size_t p;
	cin >> p;
	while( p )
	{
		int a, b;
		cin >> a >> b;
		if( p == 1 )
		{
			testcase_1( a, b );
		}
		else
		{
			testcase_2( a, b );
		}
		cin >> p;
	}
	return 0;
}

void output_solution( Solution &s, bool floor, bool neg )
{
	if(s.status() == CGAL::QP_INFEASIBLE)
	{
		cout << "no";
	}
	else if( s.status() == CGAL::QP_UNBOUNDED )
	{
		cout << "unbounded";
	}
	else
	{
		CGAL::Quotient<ET> obj_val = s.objective_value();

		double d_obj_val = 
			neg ? CGAL::to_double(-obj_val)
				: CGAL::to_double(obj_val);

		if( floor )
		{
			cout << (int)std::floor(d_obj_val);
		}
		else
		{
			cout << (int)std::ceil(d_obj_val);
		}
	}
	cout << std::endl;
}

void testcase_1( int a, int b )
{
	Program qp( CGAL::SMALLER, true, 0, false, 0 );

	const int x = 0;
	const int y = 1;

	int eq = 0;
	// constr. x + y <= 4
	qp.set_a(x, eq, 1);
	qp.set_a(y, eq, 1);
	qp.set_b(   eq, 4);
	eq++;

	// constr. 4x + 2y <= ab
	qp.set_a(x, eq, 4);
	qp.set_a(y, eq, 2);
	qp.set_b(   eq, a*b); 
	eq++;

	// constr. -x + y <= 1
	qp.set_a(x, eq, -1);
	qp.set_a(y, eq, 1);
	qp.set_b(   eq, 1);
	eq++;

	// max b*y - a*x*x
	// linear: b*y
	qp.set_c(y, -b);

	// quadratic terms
	qp.set_d(x, x, 2*a);

	Solution s = CGAL::solve_quadratic_program(qp, ET());
	assert(s.solves_quadratic_program(qp));
	output_solution(s, true, true);
}

void testcase_2( int a, int b )
{
	Program qp( CGAL::LARGER, false, 0, true, 0 );

	const int x = 0;
	const int y = 1;
	const int z = 2;
	
	int eq = 0;
	
	// constr. x + y >= -4
	qp.set_a( x, eq, 1 );
	qp.set_a( y, eq, 1 );
	qp.set_b(    eq, -4);
	eq++;

	// constr. 4x+2y+z*z >= -ab
	qp.set_a( x, eq, 4 );
	qp.set_a( y, eq, 2 );
	qp.set_a( z, eq, 1 );
	qp.set_b(    eq, -a*b);
	eq++;

	// constr. -x + y >= -1
	qp.set_a( x, eq, -1 );
	qp.set_a( y, eq, 1  );
	qp.set_b(    eq, -1 );
	eq++;

	qp.set_u(z, false, 0);
	qp.set_l(z, true, 0);

	// a*x^2 + b*y + z^2
	// linear terms
	qp.set_c( y, b );
	
	// quadratic terms
	qp.set_d( x, x, 2*a );
	qp.set_d( z, z, 2 );

	Solution s = CGAL::solve_quadratic_program(qp, ET());
	assert(s.solves_quadratic_program(qp));
	output_solution(s, false, false);
}
