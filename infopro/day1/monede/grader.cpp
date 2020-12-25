#include <bits/stdc++.h>

using std::vector;

/* Declaratia tipului de date Raport */
class Raport {
  public:
    int a, b;

    Raport(int, int);
    Raport();

    Raport &operator+=(const Raport &);
    Raport &operator-=(const Raport &);
    Raport &operator*=(const Raport &);
    Raport &operator/=(const Raport &);

    bool operator==(const Raport &rhs) const;
    bool operator!=(const Raport &rhs) const;
};

Raport operator+(Raport, const Raport &);
Raport operator-(Raport, const Raport &);
Raport operator*(Raport, const Raport &);
Raport operator/(Raport, const Raport &);

/* Declaratiile functiilor ce trebuie sa le implementati */

void init(int, const Raport[]);

Raport solve(int a, int b);

const int MAX_N = 1000000;
Raport v[MAX_N];

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);

    for(int i = 0; i < N; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        v[i] = Raport(a, b);
    }

    init(N, v);

    for(int i = 0; i < Q; ++i) {
        int a, b, x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);
        Raport res = solve(a, b);
        if(res == Raport(x, y))
            printf("Test %d: Correct\n", i + 1);
        else
            printf("Test %d: Incorrect %d %d\n", i + 1,res.a,res.b);
    }

    return 0;
}

