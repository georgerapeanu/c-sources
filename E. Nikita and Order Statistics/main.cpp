#include <bits/stdc++.h>

using namespace std;

struct FFTSolver {
    using Complex = complex<double>;
    const double kPi = 4.0 * atan(1.0);

    long long __lg(long long n) { return n == 1 ? 0 : 1 + __lg(n / 2);  }

    long long rev_bit(long long num, long long lg) {
        long long ret = 0;
        for (long long i = 0; i < lg; ++i)
            if (num & (1 << i))
                ret |= (1 << (lg - i - 1));
        return ret;
    }

    vector<Complex> fft(vector<Complex> V, bool invert) {
        long long n = V.size(), lg = __lg(n);
        assert((1 << lg) == n);

        for (long long i = 0; i < n; ++i) {
            long long rev = rev_bit(i, lg);
            assert(rev_bit(rev, lg) == i);

            if (i < rev)
                swap(V[i], V[rev]);
        }

        for (long long step = 2; step <= n; step *= 2) {
            const double ang = 2 * kPi / step;
            Complex eps(cos(ang), sin(ang));
            if (invert) eps = conj(eps);

            Complex aux;
            for (long long i = 0; i < n; i += step) {
                Complex w = 1;
                for (long long a = i, b = i + step / 2; b < i + step; ++a, ++b) {
                    Complex aux = w * V[b];
                    V[b] = V[a] - aux;
                    V[a] = V[a] + aux;
                    w *= eps;
                }
            }
        }

        return V;
    }
    vector<Complex> transform(vector<Complex> V) {
        long long n = V.size();
        vector<Complex> ret(n);
        Complex div_x = Complex(0, 1) * (4.0 * n);

        for (long long i = 0; i < n; ++i) {
            long long j = (n - i) % n;
            ret[i] = (V[i] + conj(V[j]))
                * (V[i] - conj(V[j]))
                / div_x;
        }

        return ret;
    }

    vector<long long> Multiply(vector<long long> A, vector<long long> B) {
        long long n = A.size() + B.size() - 1;
        vector<long long> ret(n);
        while (n != (n & -n)) ++n;

        A.resize(n); B.resize(n);
        vector<Complex> V(n);
        for (long long i = 0; i < n; ++i) {
            V[i] = Complex(A[i], B[i]);
        }

        V = fft(V, false);
        V = transform(V);
        V = fft(V, true);

        for (long long i = 0; i < (long long)ret.size(); ++i)
            ret[i] = round(real(V[i]));
        return ret;
    }
};

long long N,X;
long long S[200005];
vector<long long> A;
vector<long long> Ap;

int main() {

    scanf("%I64d %I64d",&N,&X);
    for(long long i = 1;i <= N;i++){
        scanf("%I64d",&S[i]);
        S[i] = S[i - 1] + (S[i] < X);
    }

    A.resize(4 * S[N] + 1);
    Ap.resize(4 * S[N] + 1);

    for(auto &it:A) it = 0;
    for(auto &it:Ap) it = 0;

    for(int i = 0;i <= N;i++){
        A[S[N] + S[i]]++;
        Ap[S[N] - S[i]]++;
    }

    vector<long long> rez = FFTSolver().Multiply(A,Ap);


    rez[2 * S[N]] = 0;
    for(auto it:A){
        rez[2 * S[N]] += 1LL * it * (it - 1) / 2;
    }

    for(int i = 2 * S[N];i <= 2 * S[N] + N;i++){
        cout << (i < (int)rez.size() ? rez[i] : 0) << " ";
    }

    return 0;
}
