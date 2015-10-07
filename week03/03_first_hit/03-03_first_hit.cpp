#include<iostream>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Segment;
typedef K::Point_2 P;
typedef K::FT F;

double floor_to_double(const K::FT& x)
{
	double a = std::floor(CGAL::to_double(x));
	while( a > x ) a -= 1;
	while( a+1 <= x) a += 1;
	return a;
}

int main(void) {
    int _t, _n;

    ios_base::sync_with_stdio(false);
	cout << setiosflags(ios::fixed) << setprecision(0);
    cin >> _n;

    Ray ray;

    double a,b,c,d;
    double r,s,t,u;
    while(_n) {
        cin >> a >> b >> c >> d;
        P origin(a,b);
        ray = Ray(origin, P(c,d));

        K::FT min_dist = -1, current_dist;
        P min_point, current_point;


        while(_n--) {
            cin >> r >> s >> t >> u;
            Segment segment(P(r, s), P(t, u));
            auto intersection = CGAL::intersection(ray, segment);
            if( intersection ) {
                if( const P* intersection_point =
                        boost::get<P>(&*intersection)) {
                    current_dist = CGAL::squared_distance(*intersection_point, origin);
                    current_point = *intersection_point;
                } else if( const Segment* intersection_segment
                        = boost::get<Segment>(&*intersection)) {
                   auto dist1 = 
                       CGAL::squared_distance(intersection_segment->source(), origin),
                        dist2 =
                       CGAL::squared_distance(intersection_segment->target(), origin);
                   if(dist1 < dist2) {
                       current_point = intersection_segment->source();
                       current_dist = dist1;
                   } else {
                       current_point = intersection_segment->target();
                       current_dist = dist2;
                   }
                }

                if((current_dist < min_dist) || (min_dist < 0)) {
                    min_dist = current_dist;
                    min_point = current_point;
                }
            }
        }
        if( min_dist < 0 ) {
            cout << "no";
        } else {
            cout << floor_to_double(min_point.x()) << " " <<
                floor_to_double(min_point.y());
        }
        cout << endl;
        cin >> _n;
    }
    return 0;
}
