#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
FILE *f = fopen("dsip.in","r");
FILE *g = fopen("dsip.out","w");
struct event{
    double angle;
    int ind;
    int x,y;
    int a,b,c;
    bool operator <(const event &other)const{
        return angle < other.angle;
    }
};
int N,M;
int ord[2005];
int pos[2005];
int A[200005];
int B[200005];
event V[200000 + 2000 * 1000 + 5];
int len;
pair<int,int> P[2005];
bool cmp(int i,int j){
    if(P[i].second != P[j].second){
        return P[i].second > P[j].second;
    }
    return P[i].first < P[j].first;
}
int main(){
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d %d",&P[i].first,&P[i].second);
        ord[i] = i;
    }
    for(int i = 1;i <= M;i++){
        int x,y,xx,yy;
        fscanf(f,"%d %d %d %d",&x,&y,&xx,&yy);
        if(y > yy){
            swap(x,xx);
            swap(y,yy);
        }
        else if(y == yy && x > xx){
            swap(x,xx);
            swap(y,yy);
        }
        event tmp;
        tmp.angle = atan2(yy - y,xx - x);
        tmp.ind = i;
        tmp.x = 0;
        tmp.y = 0;
        tmp.a = yy - y;
        tmp.b = x - xx;
        tmp.c = xx * y - x * yy;
        V[++len] = tmp;
    }
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            if(P[i].second < P[j].second){
                event tmp;
                tmp.angle = atan2(P[j].second - P[i].second,P[j].first - P[i].first);
                tmp.ind = 0;
                tmp.x = i;
                tmp.y = j;
                tmp.a = 0;
                tmp.b = 0;
                tmp.c = 0;
                V[++len] = tmp;
            }
        }
    }
    sort(ord + 1,ord + 1 + N,cmp);
    sort(V + 1,V + 1 + len);
    for(int i = 1;i <= N;i++){
        pos[ord[i]] = i;
    }
    for(int i = 1;i <= len;i++){
        event it = V[i];
        if(it.ind){
            long long tmp = 1LL * it.a * P[ord[1]].first + 1LL * it.b * P[ord[1]].second + it.c;
            if(tmp < 0){
                int st = 0,dr = N + 1;
                while(dr - st > 1){
                    int mid = (st + dr) / 2;
                    if(1LL * it.a * P[ord[mid]].first + 1LL * it.b * P[ord[mid]].second + it.c < 0){
                        st = mid;
                    }
                    else{
                        dr = mid;
                    }
                }
                int a = st;
                st = 0;
                dr = N + 1;
                while(dr - st > 1){
                    int mid = (st + dr) / 2;
                    if(1LL * it.a * P[ord[mid]].first + 1LL * it.b * P[ord[mid]].second + it.c > 0){
                        dr = mid;
                    }
                    else{
                        st = mid;
                    }
                }
                int b = N - dr + 1;
                if(a > b){
                    swap(a,b);
                }
                A[it.ind] = a;
                B[it.ind] = b;
            }
            else if(tmp > 0){
                int st = 0,dr = N + 1;
                while(dr - st > 1){
                    int mid = (st + dr) / 2;
                    if(1LL * it.a * P[ord[mid]].first + 1LL * it.b * P[ord[mid]].second + it.c > 0){
                        st = mid;
                    }
                    else{
                        dr = mid;
                    }
                }
                int a = st;
                st = 0;
                dr = N + 1;
                while(dr - st > 1){
                    int mid = (st + dr) / 2;
                    if(1LL * it.a * P[ord[mid]].first + 1LL * it.b * P[ord[mid]].second + it.c < 0){
                        dr = mid;
                    }
                    else{
                        st = mid;
                    }
                }
                int b = N - dr + 1;
                if(a > b){
                    swap(a,b);
                }
                A[it.ind] = a;
                B[it.ind] = b;
            }
            else{
                int st = 0,dr = N + 1;
                while(dr - st > 1){
                    int mid = (st + dr) / 2;
                    if(1LL * it.a * P[ord[mid]].first + 1LL * it.b * P[ord[mid]].second + it.c == 0){
                        st = mid;
                    }
                    else{
                        dr = mid;
                    }
                }
                A[it.ind] = 0;
                B[it.ind] = N - st;
            }
        }
        else{
            int a = pos[it.x];
            int b = pos[it.y];
            swap(ord[a],ord[b]);
            swap(pos[it.x],pos[it.y]);
        }
    }
    for(int i = 1;i <= M;i++){
        fprintf(g,"%d %d\n",A[i],B[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
