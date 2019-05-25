#include <cstdio>

using namespace std;

int a,b;

int main(){
    scanf("%d %d",&a,&b);

    if(a <= 5)printf("0\n");
    else if(a <= 12)printf("%d\n",b / 2);
    else printf("%d\n",b);

    return 0;
}
