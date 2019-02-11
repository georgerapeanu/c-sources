#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream f("countfefete.in");
ofstream g("countfefete.out");
int N;
int TT[200005], R[200005];
int V[200005], ans;
int Nb[200005][35];
int Len[200005];
pair <int, int> Ord[200005];
bool Act[200005];
int Power[200005];
const int MOD = 1000000007;
vector <int> G[200005];
inline void Add(int& x, int y)
{
    x += y;
    if(x >= MOD)
        x -= MOD;
}
void precalcPower()
{
    Power[0] = 1;
    for(int i = 1; i <= 200000; i++)
    {
        Power[i] = 2 * Power[i - 1];
        if(Power[i] >= MOD)
            Power[i] -= MOD;
    }

}
void Read()
{
    f >> N;
    for(int i = 1; i <= N; i++)
    {
        f >> V[i];
        Ord[i] = make_pair(V[i], i);
    }
    sort(Ord + 1, Ord + N + 1);
    for(int i = 1; i < N; i++)
    {
        int x, y;
        f >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}
int Father(int x)
{
    int init = x;
    while(x != TT[x])
    {
        x = TT[x];
    }
    while(init != x)
    {
        int next = TT[init];
        TT[init] = x;
        init = next;
    }
    return x;
}

void Unite(int x, int y)
{
    if(x == y)
        return;
    if(R[x] < R[y])
    {
        for(int j = 0; j <= 30; j++)
        {
            int s = Power[Len[x]] - Nb[x][j];
            if(s < 0)
                s += MOD;
            int aux = (1LL * Nb[y][j] * s) % MOD;
            s = Power[Len[y]] - Nb[y][j];
            if(s < 0)
                s += MOD;
            Add(aux, (1LL * Nb[x][j] * s) % MOD);
            Nb[y][j] = aux;
        }
        TT[x] = y;
        Len[y] += Len[x];
    }
    else
    {
        swap(x, y);
        for(int j = 0; j <= 30; j++)
        {
            int s = Power[Len[x]] - Nb[x][j];
            if(s < 0)
                s += MOD;
            int aux = (1LL * Nb[y][j] * s) % MOD;
            s = Power[Len[y]] - Nb[y][j];
            if(s < 0)
                s += MOD;
            Add(aux, (1LL * Nb[x][j] * s) % MOD);
            Nb[y][j] = aux;
        }
        //swap(x, y);
        TT[x] = y;
        Len[y] += Len[x];
        swap(x, y);
    }
    if(R[x] == R[y])
        R[x]++;
}
void Solve(int node)
{
    Act[node] = 1;
    Len[node] = 1;
    TT[node] = node;
    R[node] = 1;
    for(int i = 0; i <= 30; i++)
    {
        if((V[node] & (1 << i)) != 0)
            Nb[node][i] = 1;
    }
    int val = V[node];
    for(int i = 0; i < G[node].size(); i++)
    {
        int neighb = G[node][i];
        if(Act[neighb] == 0)
            continue;
        int f = Father(neighb), f2 = Father(node);
        if(f == f2)
            continue;
        for(int j = 0; j <= 30; j++)
        {
            if((val & (1 << j)) != 0)
            {
                int s = Power[Len[f2]] - 1 - Nb[f2][j];
                if(s < 0)
                    s += MOD;
                int s2 = Power[Len[f]] - 1 - Nb[f][j];
                if(s2 < 0)
                    s2 += MOD;
                s = (1LL * s * s2) % MOD;
                Add(ans, (1LL * s * Power[j]) % MOD);
                s = Nb[f2][j];
                s2 = Nb[f][j];
                s = (1LL * s * s2) % MOD;
                Add(ans, (1LL * s * Power[j]) % MOD);
            }
            else
            {
                int s = Power[Len[f2]] - 1 - Nb[f2][j];
                if(s < 0)
                    s += MOD;
                int s2 = Nb[f][j];
                s = (1LL * s * s2) % MOD;
                Add(ans, (1LL * s * Power[j]) % MOD);
                s = Nb[f2][j];
                s2 = Power[Len[f]] - 1 - Nb[f][j];
                if(s2 < 0)
                    s2 += MOD;
                s = (1LL * s * s2) % MOD;
                Add(ans, (1LL * s * Power[j]) % MOD);
            }
        }
        Unite(f, f2);
    }
}

int main()
{
    Read();
    precalcPower();
    for(int i = N; i >= 1; i--)
    {
        Solve(Ord[i].second);
    }
    g << ans << "\n";
    return 0;
}
