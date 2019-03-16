#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f0 = fopen("in","r");
FILE *f1 = fopen("out","r");
FILE *f2 = fopen("ok","r");

int main(){
    int a,b;
    fscanf(f1,"%d",&a);
    fscanf(f2,"%d",&b);

    if(a == -1 || b == -1){
        if(a == b){
            printf("Ok\n");
            return 0;
        }
        if(a == -1){
            printf("Solution not found when judge found one");
        }
        printf("Solution found when none");
        fflush(stdout);
        while(true);
    }

    int n,m,k;
    fscanf(f0,"%d %d %d",&n,&m,&k);

    vector<int> ans = {a};
    vector<int> l;

    while(fscanf(f1,"%d",&a) == 1){
        ans.push_back(a);
    }

    for(int i = 0;i < (int)ans.size();i++){
        int st = -1;
        int dr = l.size();
        while(dr - st > 1){
            int mid = (st + dr) / 2;
            if(l[mid] <= ans[i]){
                st = mid;
            }
            else{
                dr = mid;
            }
        }

        if(dr >= (int)l.size()){
            l.push_back(ans[i]);
        }
        else{
            l[dr] = min(l[dr],ans[i]);
        }
    }

    if(l.size() != n){
        printf("WA sketch length differs");
        fflush(stdout);
        while(1);
    }


    for(int i = 0;i < n;i++){
        fscanf(f0,"%d",&a);
        b = l[i];

        if(a != -1 && a != b){
            printf("WA sketch differs\n");
            fflush(stdout);
            while(1);
        }
    }

    printf("OK\n");

    return 0;
}
