#include<iostream>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Segment;
typedef K::Point_2 P;
typedef K::FT F;

int main(void) {
    int _t, _n;

    ios_base::sync_with_stdio(false);
    cin >> _n;

    Ray ray;

    double a,b,c,d;
    double r,s,t,u;
    while(_n) {
        cin >> a >> b >> c >> d;
        ray = Ray(P(a,b), P(c,d));
        while(_n--) {
            cin >> r >> s >> t >> u;
            // cout << r << s << t << u << endl; 
            if( CGAL::do_intersect(ray, Segment(P(r,s), P(t,u))) )
                break;
        }
        if(_n > -1) {
            cout << "yes";
            while(_n--) {
                cin >> r >> s >> t >> u;
            }
        } else {
            cout << "no";
        }
        cout << endl;
        cin >> _n;
    }
    return 0;
}
