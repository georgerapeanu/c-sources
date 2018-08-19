#include <cstdio>
///#include <iostream>
#include <algorithm>
using namespace std;
FILE *f = fopen("sir.in","r");
FILE *g = fopen("sir.out","w");
int N,X,Y,Z;
int V[100005];
int prefmini[100005];
int prefmaxi[100005];
int st,dr;
void update(int x,int y){
    if(y - x < dr - st){
        return ;
    }
    if(y - x > dr - st){
        st = x;
        dr = y;
        return ;
    }
    if(x > st){
        st = x;
        dr = y;
    }
}
void solve(int st,int dr){
    //cerr << st << " " << dr << "\n";
    if(dr - st + 1 < X){
        return ;
    }
    if(st == dr){
        update(st,dr);
        return ;
    }
    int mid = (st + dr) / 2;
    solve(st,mid);
    solve(mid + 1,dr);
    prefmini[mid] = 1 << 30;
    prefmaxi[mid] = 0;
    for(int i = mid + 1;i <= dr;i++){
        prefmini[i] = min(prefmini[i - 1],V[i]);
        prefmaxi[i] = max(prefmaxi[i - 1],V[i]);
    }
    int maxi = 0,mini = 1 << 30;
    for(int i = mid;i >= st;i--){
        maxi = max(maxi,V[i]);
        mini = min(mini,V[i]);
        while(dr > mid && max(maxi,prefmaxi[dr]) - min(mini,prefmini[dr]) > Z){
            dr--;
        }
        if(dr <= mid){
            return ;
        }
        if(dr - i + 1 >= X){
            update(i,min(dr,i + Y - 1));
        }
    }
}
int main()
{
    fscanf(f,"%d %d %d %d\n",&N,&X,&Y,&Z);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
    }
    solve(1,N);
    if(st == dr && st == 0){
        fprintf(g,"-1");
        return 0;
    }
    fprintf(g,"%d %d %d\n",dr - st + 1,st,dr);
    fclose(f);
    fclose(g);
    return 0;
}
