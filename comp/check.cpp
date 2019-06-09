#include <cstdio>
#include <vector>

using namespace std;

FILE *f1 = fopen("comp.in","r");
FILE *f2 = fopen("comp.out","r");

const int NMAX = 16000;

int n;
int colors[NMAX + 5];
vector<int> sons[NMAX + 5];
int fr[4];

int main(){

    
    fscanf(f1,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f2,"%d",&colors[i]);
    }

    for(int i = 1;i < n;i++){
        int a,b;
        fscanf(f1,"%d %d",&a,&b);
        if(colors[a] == colors[b]){
            printf("WA son-father structure\n");
            while(1);
        }
        sons[b].push_back(a);
    }

    for(int i = 1;i <= n;i++){
        fr[colors[i]]++;
        if((int)sons[i].size() == 2){
            if(colors[sons[i][0]] == colors[sons[i][1]]){
                printf("WA 2sons structure\n");
                while(1);
            }
        }
    }

    fr[1] -= fr[3];
    fr[2] -= fr[3];

    if(fr[1] < 0 || fr[2] < 0){
        printf("WA nonincreasing custom structure");
        while(1);
    }

    if(fr[1] != (n % 3 >= 1) || fr[2] != (n % 3 >= 2)){
        printf("WA freq structure\n");
        while(1);
    }

    printf("OK\n");

    return 0;
}
