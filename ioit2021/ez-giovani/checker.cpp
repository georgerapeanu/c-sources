#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

static void score(int x, const char *const y) {
    cout << x << endl;
    cerr << y << endl;
    exit(0);
}

static void require(bool b, const char *const y) {
    if (!b) score(0, y);
}

double get_error(double x, double aprox) { return abs(aprox) > 1 ? abs(x / aprox - 1) : abs(x - aprox); }

int main(int argc, char **argv) {
    ifstream fin(argv[1]), fok(argv[2]), fout(argv[3]);

    auto get_double = [&]() {
        double ret;
        require((bool)(fout >> ret), "Incomplete or malformed output file.");
        require(!isinf(ret), "The output contains infinite values.");
        require(!isnan(ret), "The output contains 'not a number' (NaN) values.");
        return ret;
    };

    double x = 0, max_error = 0;
    while (fok >> x) max_error = max(max_error, get_error(x, get_double()));

    int sc = 0;
    char str[256] = {};

    if (max_error > 1e-5) {
        sc = 0;
        sprintf(str, "Wrong answer! Maximum error: %.8lf", max_error);
    } else {
        sc = 1;
        sprintf(str, "OK! Maximum error: %.8lf", max_error);
    }

    score(sc, str);
}
