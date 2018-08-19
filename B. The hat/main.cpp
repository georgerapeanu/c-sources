#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

int N;
int real_id[100005];

int query(int a){
    fprintf(stdout,"? %d\n",a);
    fflush(stdout);
    int ans;
    fscanf(stdin,"%d",&ans);
    return ans;
}

void answear(int a){
    fprintf(stdout,"! %d\n",a);
    fflush(stdout);
    exit(0);
}

bool sect(int x,int y,int X,int Y){
    if(x > y){
        swap(x,y);
    }

    if(X > Y){
        swap(X,Y);
    }

    if((X <= x && x <= Y) || (X <= y && y <= Y) || (x <= X && X <= y) || (x <= Y && Y <= y)){
        return 1;
    }
    return 0;
}

int sign(int a,int b){
    if(a == b){
        return 0;
    }
    return (a < b ? -1 : 1);
}

void solve(int st,int dr,int sta,int stb,int dra,int drb){

    if(dr - st == 1){
        if(sta == stb){
            answear(st);
        }

        if(dra == drb){
            answear(dr);
        }

        answear(-1);
    }

    int mid = (st + dr) / 2;
    int mida = query(mid);
    int midb = query(mid + N / 2);
    if(mida == midb){
        answear(mid);
    }
    if(sign(sta,stb) * sign(mida,midb) == -1){
        solve(st,mid,sta,stb,mida,midb);
    }
    else{
        solve(mid,dr,mida,midb,dra,drb);
    }
}

int main(){

    fscanf(stdin,"%d",&N);

    if(N % 4 != 0){
        answear(-1);
    }

    int a = query(1);
    int b = query(1 + N / 2);

    if(a == b){
        answear(1);
    }

    solve(1,1 + N / 2,a,b,b,a);


    return 0;
}
