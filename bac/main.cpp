#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("bac.in","r");
FILE *g=fopen("bac.out","w");
int K,L,N,M,i,h,m,nr,minut,tmp,j,k;
vector <int> A;
vector <int> B;
int main()
{
    fscanf(f,"%d %d",&K,&L);
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d:%d",&h,&m);
        A.push_back(h*60+m);
    }
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d:%d",&h,&m);
        B.push_back(h*60+m);
    }
    while(M&&N)
    {
        nr++;
        if(A[0]<B[0])
        {
            minut=A[0];
            tmp=1;
            A.erase(A.begin());
            j=k=0;
            N--;
            while(1)
            {
                minut+=K+L;
                if(tmp)
                {
                    while(B[k]<minut&&k<M)
                    {
                        k++;
                    }
                    if(k>=M)
                        break;
                    M--;
                    minut=B[k];
                    B.erase(B.begin()+k);
                }
                else
                {
                    while(A[j]<minut&&j<N)
                    {
                        j++;
                    }
                    if(j>=N)
                        break;
                    N--;
                    minut=A[j];
                    A.erase(A.begin()+j);
                }
                tmp^=1;
            }

        }
        else
        {
           minut=B[0];
            tmp=0;
            B.erase(B.begin());
            j=k=0;
            M--;
            while(1)
            {
                minut+=K+L;
                if(tmp)
                {
                    while(B[k]<minut&&k<M)
                    {
                        k++;
                    }
                    if(k>=M)
                        break;
                    M--;
                    minut=B[k];
                    B.erase(B.begin()+k);
                }
                else
                {
                    while(A[j]<minut&&j<N)
                    {
                        j++;
                    }
                    if(j>=N)
                        break;
                    N--;
                    minut=A[j];
                    A.erase(A.begin()+j);
                }
                tmp^=1;
            }
        }
    }
    nr+=M+N;
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
