#include <cstdio>
using namespace std;
FILE *f=fopen("random.in","r");
FILE *g=fopen("random.out","w");
int val;
int main()
{
    fscanf(f,"%d",&val);
    if(val==1982)fputs("Robert Tarjan",g);
    else if(val==1986)fputs("Leslie Valiant",g);
    else if(val==1990)fputs("Alexander Razborov",g);
    else if(val==1994)fputs("Avi Wigderson",g);
    else if(val==1998)fputs("Peter Shor",g);
    else if(val==2002)fputs("Madhu Sudan",g);
    else if(val==2006)fputs("Jon Kleinberg",g);
    else if(val==2010)fputs("Daniel Spielman",g);
    else if(val==2014)fputs("Subhash Khot",g);
    fclose(f);
    fclose(g);
    return 0;
}
