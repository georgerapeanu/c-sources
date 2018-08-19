#include <iostream>
#include <cstdlib>
using namespace std;
int v1,v2,v3,v4,v5,v6;
int main()
{
    v1 = rand() % 52 + 1;
    v2 = rand() % 52 + 1;
    v3 = rand() % 52 + 1;
    v4 = rand() % 52 + 1;
    v5 = rand() % 52 + 1;
    v6 = rand() % 52 + 1;
    cout<<v1<<" "<<v2<<" "<<v3<<" "<<v4<<" "<<v5<<" "<<v6;
    return 0;
}
