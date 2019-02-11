#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
ifstream f("fft2d.in");
ofstream g("fft2d.out");
int F, T;
int Power[35];
long long ans;
pair <int, int> B[100005];
int Dig[35];
struct Trie
{
    vector <pair <int, int> > V;
    Trie * next[2], * from;
    Trie()
    {
        next[0] = NULL;
        next[1] = NULL;
        from = NULL;
        //V.clear();
    }
};
Trie * Root;
Trie * Q[100005];
int K;
void precalcPower()
{
    Power[0] = 1;
    for(int i = 1; i <= 30; i++)
        Power[i] = Power[i - 1] * 2;
}
void Read()
{
    f >> F >> T;
    for(int i = 1; i <= T; i++)
    {
        f >> B[i].first >> B[i].second;
    }
    sort(B + 1, B + T + 1);
}
void Desc(int x)
{
    for(int i = 1; i <= F - 1; i++)
        Dig[i] = 0;
    int cnt = 0;
    while(x > 0)
    {
        Dig[++cnt] = x % 2;
        x /= 2;
    }

}

int binS(Trie * node, int val, int val2)
{
    int left = 0, right = (node -> V.size()) - 1, mid, sol = -1, sol2 = -1;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(node -> V[mid].first >= val)
        {
            sol = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    left = 0;right = (node -> V.size()) - 1;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(node -> V[mid].first <= val2)
        {
            sol2 = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    if(sol == -1 || sol2 == -1)
        return 0;
    int ret = node -> V[sol2].second;
    if(sol > 0)
        ret -= node -> V[sol - 1].second;
    return ret;
}
void insert(Trie * node, int h, int dig)
{
    if(F - dig == h + 1)
    {
        int val = 0, val2 = 0, rev = 0;
        for(int i = 1; i <= dig; i++)
        {
            rev = rev * 2 + Dig[i];
            val = val * 2 + Dig[i];
            val2 = val2 * 2 + Dig[i];
        }
        for(int i = dig + 1; i <= F - 1; i++)
        {
            rev = rev * 2 + Dig[i];
            val = val * 2;
            val2 = val2 * 2 + 1;
        }
        Trie * x = node -> from;
        int sum = 0;
        while(x != NULL)
        {
            sum += binS(x, val, val2);
            x = x -> from;
        }
        sum = Power[h] - sum;
        ans += 1LL * sum * Power[F - 1 - h];
        node -> V.push_back(make_pair(rev, sum));
        if(node -> V.size() == 1)
        {
            Q[++K] = node;
        }
        return;
    }
    if(node -> next[Dig[dig]] == NULL)
    {
        node -> next[Dig[dig]] = new Trie;
        (node -> next[Dig[dig]]) -> from = node;
    }
    insert(node -> next[Dig[dig]], h, dig - 1);
}

void Add()
{
    int point = 1;
    for(int h = 0; h <= 30; h++)
    {
        while(point <= T && B[point].first == h)
        {
            Desc(B[point].second);
            insert(Root, h, F - 1);
            ++point;
        }
        for(int i = 1; i <= K; i++)
        {
            sort(Q[i] -> V.begin(), Q[i] -> V.end());
            for(int j = 1; j < Q[i] -> V.size(); j++)
            {
                Q[i] -> V[j].second += Q[i] -> V[j - 1].second;
            }
        }
        K = 0;
    }
}
int main()
{
    Root = new Trie;
    Read();
    precalcPower();
    Add();
    long long p = 1;
    for(int i = 1; i <= 2 * F - 2; i++)
        p *= 2LL;
    g << p - ans << "\n";
    return 0;
}


