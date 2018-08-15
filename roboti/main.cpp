#include <fstream>
using namespace std;
ifstream f("roboti.in");
ofstream g("roboti.out");
short nr=0,m,n,k,l=1,i,j,tp[400],lin[400],col[400],dirl[]={-1,0,1,0},dirc[]={0,1,0,-1},tablou[22][22];
char c,car[21];
void curatare()
{
    for(int i1=1;i1<=n;i1++)
    for(int j1=1;j1<=n;j1++)
    if(tablou[i1][j1]>=2)
    {tablou[i1][j1]=0;nr-=2;}
}
int main()
{
       f>>n>>k;c=f.get();
       for(i=1;i<=n;i++)
       {
       	   for(j=1;j<=n;j++)
       	   {
               c=f.get();
               if(c=='U')
               	{lin[l]=i;col[l]=j;tp[l]=0;l++;tablou[i][j]=1;nr++;}
               if(c=='R')
            	{lin[l]=i;col[l]=j;tp[l]=1;l++;tablou[i][j]=1;nr++;}
              if(c=='D')
               	{lin[l]=i;col[l]=j;tp[l]=2;l++;tablou[i][j]=1;nr++;}
              if(c=='L')
               	{lin[l]=i;col[l]=j;tp[l]=3;l++;tablou[i][j]=1;nr++;}
       	   }
       	   c=f.get();
       }
       for(i=0;i<=n+1;i++)
      {
          tablou[0][i]=tablou[i][0]=tablou[n+1][i]=tablou[i][n+1]=-1;
      }
       for(i=1;i<=k;i++)
       {
            for(j=1;j<l;j++)
            {
                 if(tablou[lin[j]][col[j]]>=1)
                 {
                     tablou[lin[j]][col[j]]--;
                     lin[j]=lin[j]+dirl[tp[j]];
                     col[j]=col[j]+dirc[tp[j]];
                     if(tablou[lin[j]][col[j]]==-1)
                     {
                         tp[j]+=2;
                         tp[j]%=4;
                         lin[j]=lin[j]+2*dirl[tp[j]];
                         col[j]=col[j]+2*dirc[tp[j]];
                     }
                     tablou[lin[j]][col[j]]++;
                 }
            }
            for(j=1;j<l;j++)
            {
                if(tablou[lin[j]][col[j]]>=2)
                     {lin[j]=col[j]=0;}
            }
            curatare();
       }
       g<<nr<<'\n';
       for(i=1;i<=k;i++)
       {
           for(j=1;j<l;j++)
           {
                 if(tablou[lin[j]][col[j]]==1)
                 {
                     tablou[lin[j]][col[j]]=tp[j]+1;
                 }
           }
       }
       for(i=1;i<=n;i++)
       {
           for(j=1;j<=n;j++)
           {
               if(tablou[i][j]==0)
               {
                 car[j-1]='.';
               }
               if(tablou[i][j]==1)
               {
                 car[j-1]='U';
               }
                if(tablou[i][j]==2)
               {
                 car[j-1]='R';
               }
                if(tablou[i][j]==3)
               {
                   car[j-1]='D';
               }
                if(tablou[i][j]==4)
               {
                   car[j-1]='L';
               }
           }
           car[n]='\n';
           g<<car;
       }
       f.close();g.close();
       return 0;
}
