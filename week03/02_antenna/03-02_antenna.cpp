#include<iostream>
#include<vector>
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_Circle;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Segment;
typedef K::Point_2 P;

double ceil_to_double(const K::FT& x) {
	double a = std::floor(CGAL::to_double(x));
	while( a < x ) a += 1;
	while( a-1 >= x) a -= 1;
	return a;
}

int main(void) {
	ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);
    int _n;

    cin >> _n;
    vector<P> points;
    long x,y;
    while(_n) {
        while(_n--) {
            cin >> x >> y;
            points.push_back(P(x,y));
        }
        Min_Circle mc(points.begin(), points.end(), true);
        Traits::Circle circle = mc.circle();
        cout << ceil_to_double(CGAL::sqrt(circle.squared_radius())) << endl;
        points.clear();
        cin >> _n;
    }
    return 0;
}
