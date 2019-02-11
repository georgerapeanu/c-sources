#include <fstream>
#define Nmax 500005

using namespace std;

ifstream f("pscfft.in");
ofstream g("pscfft.out");

int n,t,v[2*Nmax],B[Nmax],crt,pos,lg,nxtLG,pr[Nmax],s;

int modul(int x){
    if (x>=s) return x-s;
    return x;
}

int nextCH(){
    pos++;
    if (pos>lg){
        pos = 1;
        crt++;
        if (crt==s){
            crt = 1;
            lg = nxtLG;
        }
    }
    v[++nxtLG] = modul(v[pos]+crt);
    return v[nxtLG];
}

int main()
{
    f>>t;
    while (t--){
        f>>n>>s;
        for (int i=0;i<s;i++) v[i+1] = i;
        for (int i=1;i<=n;i++) f>>B[i];
        lg = s;
        nxtLG = s;
        crt = 1;
        pos = 0;

        int k = 0;
        for (int i=2;i<=n;i++){
            while (k!=0 && B[k+1]!=B[i]) k = pr[k];
            if (B[k+1]==B[i]) k++;
            pr[i] = k;
        }

        while (nxtLG<1e6) nextCH();

        k = 0;
        int ok = 0;
        for (int i=1;i<=1e6;i++){
            while (k!=0 && B[k+1]!=v[i]) k = pr[k];
            if (B[k+1]!=v[i]) k = 0;
            else k++;
            if (k==n){
                g<<i-k<<'\n';
                ok = 1;
                break;
            }
        }
        if (!ok) g<<"-1\n";
    }

    return 0;
}
