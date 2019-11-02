#include<fstream>
#include<queue>
#include<algorithm>
#include<iostream>
#include <cstdlib>
using namespace std;

ofstream g("sec.out");


long long int v[4000005],t,cerinta,stiva[4000005];
long long int catesecv=0,s[4000005];


class InParser
{
private:
    FILE *fin;
    char *buff;
    int sp;

    char read_ch()
    {
        ++sp;
        if (sp == 4096)
        {
            sp = 0;
            fread(buff, 1, 4096, fin);
        }
        return buff[sp];
    }

public:
    InParser(const char* nume)
    {
        fin = fopen(nume, "r");
        buff = new char[4096]();
        sp = 4095;
    }

    InParser& operator >> (int &n)
    {
        char c;
        while (!isdigit(c = read_ch()) && c != '-');
        int sgn = 1;
        if (c == '-')
        {
            n = 0;
            sgn = -1;
        }
        else
        {
            n = c - '0';
        }
        while (isdigit(c = read_ch()))
        {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }

    InParser& operator >> (long long &n)
    {
        char c;
        n = 0;
        while (!isdigit(c = read_ch()) && c != '-');
        long long sgn = 1;
        if (c == '-')
        {
            n = 0;
            sgn = -1;
        }
        else
        {
            n = c - '0';
        }
        while (isdigit(c = read_ch()))
        {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }
};
int main()
{
    InParser f("sec.in");
    f>>t>>cerinta;

    for(int z=1; z<=t; z++)
    {
        long long    int n,k,cnt=0,catesecv=0;
        f>>n>>k;
        for(int i=1; i<=n; i++)
        {
            f>>v[i];
            s[i]=0;
            v[i+n]=v[i];


        }
        if(cerinta==2)
        {
            /*
                              for(int i=1;i<=n-k+1;i++)
                                             {int maxim=-10000000;
                                                                for(int j=i;j<=n;j++)
                                                                                   {
                                                                                                          if(v[j]>maxim) maxim=v[j];
                                                                                                                                 if(j-i+1>=k) catesecv+=maxim;
                                                                                                                                                    }
                                                                                                                                                                   }
                                                                                                                                                                                  g<<catesecv<<" ";
                                                                                                                                                                                                 catesecv=0;
                                                                                                                                                                                                                */
            for(int i=1; i<=n; i++)
            {
                while(v[i]>v[stiva[cnt]]&&cnt>0)
                    cnt--;
                cnt++;
                stiva[cnt]=i;
                s[cnt]=s[cnt-1]+v[i]*(i-stiva[cnt-1]);

                if(i>=k)
                {

                    long long int coord=i-k+1;
                    long long  int st=1;
                    long long  int dr=cnt;
                    long long int rasp=-1;
                    while(st<=dr)
                    {
                        int mij=(st+dr)/2;
                        if(stiva[mij]<=coord)
                        {
                            rasp=mij;
                            st=mij+1;

                        }
                        else dr=mij-1;
                    }
                    if(rasp==-1)
                    {
                        catesecv=catesecv+s[1]-v[stiva[1]]*(stiva[1]-coord);
                    }
                    else
                        catesecv=catesecv+s[rasp]+v[stiva[rasp+1]]*(coord-stiva[rasp]);

                }


            }
            g<<catesecv<<'\n';
        }




        else
        {




            for(int i=1; i<=n; i++)
            {   //cout<<v[i]<<" ";
                while(v[i]>=v[stiva[cnt]]&&cnt>0)
                {
                    cnt--;
                }
                stiva[++cnt]=i;
                s[cnt]=s[cnt-1]+v[i]*(i-stiva[cnt-1]);
            }

            for(int i=n+1; i<=2*n; i++)
            {
                while(v[i]>=v[stiva[cnt]]&&cnt>0)
                {
                    cnt--;
                }
                stiva[++cnt]=i;
                //if(cnt==1) s[cnt]=v[stiva[cnt]]*(n+i);
                //else s[cnt]=s[cnt-1]+v[i]*((i-stiva[cnt-1]+n)%n);
                s[cnt]=s[cnt-1]+v[i]*(i-stiva[cnt-1]);
                int coord=i-k+1;
                int st=1,dr=cnt,mij;
                int rasp=-1;

                while(st<=dr)
                {
                    mij=(st+dr)/2;
                    if(stiva[mij]<=coord)
                    {
                        rasp=mij;
                        st=mij+1;
                    }
                    else dr=mij-1;

                }

                if(rasp==-1)
                {
                    catesecv=catesecv+s[1]-v[stiva[1]]*(stiva[1]-coord);
                    catesecv=catesecv-v[stiva[1]]*(i-n);

                }
                else
                {
                    catesecv=catesecv+s[rasp]+v[stiva[rasp+1]]*(coord-stiva[rasp]);

                    catesecv=catesecv-v[stiva[1]]*(i-n);
                }




            }
            catesecv=catesecv-(n-1)*v[stiva[1]];
            g<<catesecv<<'\n';

        }
    }
}
