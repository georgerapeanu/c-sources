#include <bits/stdc++.h>

using namespace std;

ifstream in("cars.in");
ifstream ok("cars.ok");
ifstream out("cars.out");

const double MX = 0.0001;

int main()
{
    int n, m;
    in >> n >> m;

    int i;
    for(i = 1; i <= n + m; i ++)
    {
        double a, b;
        ok >> a;
        out >> b;

        if(fabsl(a - b) > MX)
            cout << fixed << setprecision(8) << a << " " << b << "\n";
    }


    return 0;
}
