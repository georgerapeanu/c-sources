#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;

class InputReader {
private:
    FILE *inFile;
    static const int SIZE = 1 << 17;
    char buf[SIZE]; int ptx;

    inline void advance(void) {
        if (++ptx == SIZE) {
            ptx = 0;
            fread(buf, SIZE, 1, inFile);
        }
    }
public:
    InputReader(const char *fileName) {
        inFile = fopen(fileName, "r");
        ptx = 0; fread(buf, SIZE, 1, inFile);
    }

    InputReader &operator >>(int &val) {
        val = 0;

        while (buf[ptx] < '0' || buf[ptx] > '9')
            advance();

        while (buf[ptx] >= '0' && buf[ptx] <= '9') {
            val = val * 10 + (buf[ptx] - '0');
            advance();
        }

        return *this;
    }
} in("pscfft.in");
ofstream out("pscfft.out");

const int EXP = 22;
const int DIM = 1000009;
const int CNS = 500005;

int arr[DIM], pre[DIM / 2], sol[DIM / 2];

int _p, _n;
void build(int d, int s2, int s) {
    if (_p == CNS + _n)
        return;

    if (s2 == 1) {
        arr[++_p] = d;
        return;
    }

    for (int i = 0; i < s; ++i)
        build((d + i) % s, s2 / s, s);
}

int main(void) {
    int t;
    in >> t;

    while (t--) {
        int n, s;
        in >> n >> s;

        long long s2 = s;
        while (s2 - n <= CNS)
            s2 *= s;

        _p = 0; _n = n;
        build(0, s2, s);

        in >> sol[1];
        for (int i = 2, l = 0; i <= n; ++i) {
            in >> sol[i];

            while (l && sol[i] != sol[l + 1])
                l = pre[l];
            if (sol[i] == sol[l + 1])
                ++l;
            pre[i] = l;
        }

        int pos = 1e9;
        for (int i = 1, l = 0; i <= _p && pos == 1e9; ++i) {
            while (l && arr[i] != sol[l + 1])
                l = pre[l];
            if (arr[i] == sol[l + 1])
                ++l;

            if (l == n)
                pos = i - n;
        }

        if (pos == 1e9)
            out << -1 << "\n";
        else
            out << pos << "\n";
    }

    return 0;
}
