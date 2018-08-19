#include <cstdio>
using namespace std;
void sch(int *ptr)
{

}
int main()
{
    int a=1;
    char b='1';
    void * ptr;
    ptr=&a;
    *ptr=0;
    printf("%d",a);
    ptr=&b;
    *ptr='0';
    printf("%c",b);
    return 0;
}
