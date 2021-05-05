#include "fiboxor.h"

void init(int q) {

}

int query(int k,long long l,long long r) {
    l--;

    l %= 3;
    r %= 3;


    return (l == 1) ^ (r == 1);
}
