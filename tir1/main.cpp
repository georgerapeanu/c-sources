#include <fstream>
using namespace std;
ifstream f("tir1.in");
ofstream g("tir1.out");
long long H, F, D, G;
bool solve(long long H,long long G,long long D,long long F){
    if(F == 0){
        return (H == 0 && D == 0) || (D == 0 && G != 0);
    }
    if(G == 0){
        return (D == 0 && H == 0) || (H == 0 && F != 0);
    }
    if(H / G != D / F){
        return 0;
    }
    if(H % G == 0){
        return (D % F == 0);
    }
    if(D % F == 0){
        return (H % G == 0);
    }
    return solve(G,H % G,F,D % F);
}
int main()
{
    f>>H>>F>>D>>G;
    g << (solve(H,G,D,F) ? "da":"nu");
    f.close();g.close();
    return 0;
}
