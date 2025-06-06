#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
class Stack{
    private:
     int v[100],_top;
    public:
    void push(int value)
    {
        v[_top++]=value;
    }
    Stack()
    {
        _top=0;
        memset(v,0,sizeof(v));
    }
    void pop()
    {
        if(_top==0)
        return ;
        --_top;
    }
    int top()
    {
        if(_top==0)
            return v[_top-1];
    }
    bool empty()
    {
        if(_top<0)
        return 1;
        return 0;
    }
};
int main()
{
    Stack st;
    for(int i=1;i<=10;i++)
    st.push(i);
    while(!st.empty())
    {
        cout<<st.top()<<" ";
        st.pop();
    }
    return 0;
}
