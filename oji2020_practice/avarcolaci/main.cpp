#include <cstdio>

using namespace std;

FILE *f;
FILE *g = fopen("avarcolaci.out","w");

int t;

int ans[20];

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

void init(){
    f = fopen("avarcolaci.in","r");
    ind = LEN - 1;
    buff[ind] = 0;
}

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

int main(){

    init();

    t = i32();

    for(int i = 1;i <= t;i++){
        int val = 0,cnt = 0;
        int n = i32();

        for(int j = 1;j <= 2 * n;j++){
            int a = i32();
            if(val == a){
                cnt++;
            }
            else if(cnt == 0){
                cnt = 1;
                val = a;
            }
            else{
                cnt--;
            }
        }
        ans[i] = val;
    }

    fclose(f);

    init();

    t = i32();

    for(int i = 1;i <= t;i++){
        int cnt = 0;
        int n = i32();

        for(int j = 1;j <= 2 * n;j++){
            int a = i32();
            if(ans[i] == a){
                cnt++;
            }
        }
        if(cnt > n){
            fprintf(g,"%d\n",ans[i]);
        }
        else{
            fprintf(g,"Mozart\n");
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
