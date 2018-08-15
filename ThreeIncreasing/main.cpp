#include <iostream>

using namespace std;
class ThreeIncreasing
{
    public: minEaten(int a,int b,int c)
    {
         int rez=0;
        if(b<2||c<3)
            return -1;
        if(c<=b)
            {rez+=b-c+1;b=c-1;}
        if(b<=a)
            rez+=a-b+1;
        return rez;
    }
};
int main()
{
    ThreeIncreasing a;
    cout<<a.minEaten(1,3,4);
    return 0;
}
