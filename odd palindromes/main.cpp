#include <iostream>
#include <cstring>
using namespace std;
int K;
int F[26][1000005],rez;
char C[1000005];
int main() {
    cin>>K;
    cin.getline(C+1,1000005);
    cin.getline(C+1,1000005);
    int len=strlen(C+1);
    for(int i=1;i<=len;i++)
    {
        for(char a='a';a<='z'&&i!=1;a++)
            F[a-'a'][i]+=F[a-'a'][i-2];
        F[C[i]-'a'][i]++;
    }
    for(int i=1;i<=len&&rez<len-i+1;i++)
    {
        int poz=i;
        for(int l=1<<20;l&&poz+2*l-i>rez;l>>=1)
            if(poz+l<=len)
            {
                int maxa=0,maxb=0;
                for(char b='a';b<='z';b++)
                    maxa=max(maxa,F[b-'a'][poz+l-(poz+l)%2]-F[b-'a'][i-(i%2==0 ? 2:1)]);
                for(char c='a';c<='z';c++)
                    maxb=max(maxb,F[c-'a'][(poz+l)-((poz+l)%2==0 ? 1:0)]-F[c-'a'][max(0,i-(i%2==1 ? 2:1))]);
                if(poz+l-i+1-maxa-maxb<=K)poz+=l;
            }
        rez=max(rez,poz-i+1);
    }
    cout<<rez;
    return 0;
}
