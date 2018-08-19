#include <cstdio>
using namespace std;
int fr[100005];
int N;
int main()
{
    scanf("%d",&N);
    for(int i = 1;i <= N;i++){
        int a;
        scanf("%d",&a);
        fr[a]++;
    }
    bool ok = 0;
    for(int i = 1;i <= 100000;i++){
        ok |= (fr[i] & 1);
    }
    if(ok){
        printf("Conan");
    }
    else{
        printf("Agasa");
    }
    return 0;
}
