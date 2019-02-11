#include <fstream>
using namespace std;
ifstream f("pscfft.in");
ofstream g("pscfft.out");
int Old[5000005], len;
int V[5000005], X[5000005], N, S, P[5000005];
void Read()
{
    f >> N >> S;
    for(int i = 1; i <= N; i++)
    {
        f >> V[i];
    }
}

void Replace()
{
    int newl = 0;
    for(int i = 1; i <= len; i++)
        Old[i] = X[i];
    for(int k = 0; k < S; k++)
    {
        for(int i = 1; i <= len; i++)
            X[++newl] = (Old[i] + k) % S;

    }
    len = newl;
    for(int i = 1; i <= len; i++)
        Old[i] = X[i];
}

void buildP()
{
    int q = 0;
    P[1] = 0;
    for(int i = 2; i <= N; i++)
    {
        while(q && V[q + 1] != V[i])
        {
            q = P[q];
        }
        if(V[q + 1] == V[i])
            ++q;
        P[i] = q;
    }
}

void solve()
{
    int q = 0;
    for(int i = 1; i <= len; i++)
    {
        while(q && V[q + 1] != X[i])
            q = P[q];
        if(V[q + 1] == X[i])
            ++q;
        if(q == N)
        {
            g << i - N << "\n";
            return;
        }
    }
    g << "-1\n";
}

int main()
{
    int T;
    f >> T;
    while(T--)
    {
        Read();
        buildP();
        for(int i = 1; i <= S; i++)
            X[i] = i - 1;
        len = S;
        while(len < 1000000)
            Replace();
        solve();
    }
    return 0;
}
