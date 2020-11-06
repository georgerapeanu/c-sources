#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

struct segm_t{
    int x,y,xx,yy;
};

int n;
segm_t segm[NMAX + 5];

bool cmp(segm_t &a,segm_t &b){
    if(a.x == a.xx){
        if(a.x != b.x){
            return a.x < b.x;
        }
        return a.y < b.y;
    }
    if(a.y == a.yy){
        if(a.y != b.y){
            return a.y < b.y;
        }
        return a.x < b.x;
    }
    
    long long aa = a.yy - a.y;
    long long ab = a.x - a.xx;
    long long ac = (1LL * a.yy * a.x - 1LL * a.y * a.xx);
    
    long long ba = b.yy - b.y;
    long long bb = b.x - b.xx;
    long long bc = (1LL * b.yy * b.x - 1LL * b.y * b.xx);

    if(1LL * ac * ba != 1LL * bc * aa){
        return 1LL * ac * ba < 1LL * bc * aa; 
    }

    if(a.x != b.x){
        return a.x < b.x;
    }
    return a.y < b.y;
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d %d %d %d",&segm[i].x,&segm[i].y,&segm[i].xx,&segm[i].yy);
        if(segm[i].x > segm[i].xx || (segm[i].x == segm[i].xx && segm[i].y > segm[i].yy)){
            swap(segm[i].x,segm[i].xx);
            swap(segm[i].y,segm[i].yy);
        }
    }

    sort(segm + 1,segm + 1 + n,cmp);

    for(int i = 1;i < n;i++){
        printf("%d %d %d %d\n",segm[i].xx,segm[i].yy,segm[i + 1].x,segm[i + 1].y);
    }

    return 0;
}
