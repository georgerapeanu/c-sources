#include <cstdio>

using namespace std;

FILE *f = fopen("test_charactere.in","r");
FILE *g = fopen("test_charactere.out","w");

int a,b;
char c1[10];
char c2[10];
int c;

int main(){

    fscanf(f,"%d\n%d\n",&a,&b);
    fgets(c1,10,f);
    fscanf(f,"%s\n",c2);
    fscanf(f,"%d\n",&c);

    fputs(c1,g);
    fprintf(g,"%d\n",a + b);
    fputs(c2,g);fputc('\n',g);
    fprintf(g,"%d\n",c);

    fclose(f);
    fclose(g);
    return 0;
}
