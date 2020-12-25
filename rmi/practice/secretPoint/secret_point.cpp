#include "secret_point.h"
#include <cmath>

void find_secret_point() {
    long double r1 = get_distance(0, 0);
    long double r2 = get_distance(0, 1e4);
    long double r3 = get_distance(1e4,0);
    
    long double y = (r1 * r1 - r2 * r2 + 1e8) / 2e4;
    long double x = (r1 * r1 - r3 * r3 + 1e8) / 2e4;

    the_secret_point_is(x,y);
}
