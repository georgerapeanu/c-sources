#include <iostream>
#include <vector>
#define x first
#define y second
using namespace std;
typedef pair<int,int> point;
vector <point> st,dr,med;
int val,i,j,ctr=1;
int main()
{
    st.push_back(point(0,0));
    st.push_back(point(0,0));
    dr.push_back(point(0,0));
    dr.push_back(point(199,199));
    med.push_back(point(0,0));
    med.push_back(point(0,0));
    val=-1;
    while(val!=0)
    {
        for(i=1;i<=ctr;i++)
        {
            med[ctr]=point((st[i].x+dr[i].x)/2,(st[i].y+dr[i].y)/2);
            cout<<med[ctr].x<<" "<<med[ctr].y<<"\n";cout.flush();cin>>val;
            if(val>0)
                dr[ctr]=med[ctr];
            else if(val<0)
            {
                cout<<st[ctr].x<<" "<<med[ctr].y+1<<"\n";cout.flush();cin>>val;
                if(val>0)
                    {st[ctr].y=med[ctr].y;}
                else if(val<0)
                {
                    cout<<med[ctr].x+1<<" "<<st[ctr].y<<"\n";cout.flush();cin>>val;
                    if(val>0)
                        st[ctr].x=med[ctr].x+1;
                    else if(val<0)
                    {
                        st[ctr].y=med[ctr].y+1;
                        ctr++;
                        st.push_back(point(med[ctr-1].x+1,st[ctr-1].y));
                        dr.push_back(dr[ctr-1]);
                    }

                }
            }
        }
    }
    return 0;
}
