#include "brperm.h"
#include <cstring>
#include <iostream>
using namespace std;

char s[(int)5e5 + 10] = {};

int main() {
    cin >> s;
    init(strlen(s), s);

    int x, y;
    while (cin >> x >> y)
        cout << query(x, y) << '\n';

    return 0;
}
