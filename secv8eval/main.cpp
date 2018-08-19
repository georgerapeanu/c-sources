#include <cstdio>
#include <iostream>
using namespace std;
FILE *f=fopen("secv8.out","r");
FILE *g=fopen("secv8.ok","r");
int val1,val2;
int main()
{
    while(fscanf(f,"%d",&val1)!=EOF&&fscanf(g,"%d",&val2)!=EOF)
    {
        if(val1!=val2)
        {
            cout<<"Valoare incorecta";
            cin>>val1;
        }
    }
    if(fscanf(g,"%d",&val2)!=EOF)
    {
        cout<<"lipsesc niste numere";
        cin>>val1;
    }
    else if(fscanf(f,"%d",&val1)!=EOF)
    {
        cout<<"prea multe numere";
        cin>>val1;
    }
    else
    {
        cout<<"OK\n";
    }
    return 0;
}
