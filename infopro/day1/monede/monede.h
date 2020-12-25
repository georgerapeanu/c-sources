#include <vector>
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

/* Implementarea metodelor clasei Raport */

Raport::Raport(int A, int B) : a(A), b(B) {}

Raport::Raport() : Raport(0, 1) {}

Raport &Raport::operator+=(const Raport &rhs) {
    a = ((long long)a * rhs.b + (long long)b * rhs.a) % 1000000007;
    b = ((long long)b * rhs.b) % 1000000007;
    return *this;
}

Raport &Raport::operator-=(const Raport &rhs) {
    a = ((long long)a * rhs.b - (long long)b * rhs.a) % 1000000007;
    if (a < 0)
        a += 1000000007;
    b = ((long long)b * rhs.b) % 1000000007;
    return *this;
}

Raport &Raport::operator*=(const Raport &rhs) {
    a = ((long long)a * rhs.a) % 1000000007;
    b = ((long long)b * rhs.b) % 1000000007;
    return *this;
}

Raport &Raport::operator/=(const Raport &rhs) {
    a = ((long long)a * rhs.b) % 1000000007;
    b = ((long long)b * rhs.a) % 1000000007;
    return *this;
}

bool Raport::operator==(const Raport &rhs) const {
    return ((long long)a * rhs.b - (long long)b * rhs.a) % 1000000007 == 0;
}

bool Raport::operator!=(const Raport &rhs) const { return !(*this == rhs); }

Raport operator+(Raport a, const Raport &b) { return a += b; }

Raport operator-(Raport a, const Raport &b) { return a -= b; }

Raport operator*(Raport a, const Raport &b) { return a *= b; }

Raport operator/(Raport a, const Raport &b) { return a /= b; }
