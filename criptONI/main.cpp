#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("cript.in","r");
FILE *g=fopen("cript.out","w");
char c,V[128][13],cer[10];
int vec[9],i,tip;
int main()
{
    for(c=32;c<127;c++)
    {
        vec[1]=(int)c;
        for(i=2;i<=8;i++)
            {vec[i]=(vec[i-1]>>7)+(vec[i-1]-(vec[i-1]&(1<<7)))*2;}
        sort(vec+1,vec+9);
        for(i=1;i<=8;i++)
        {
            if(vec[i]==(int)c&&V[int(c)][8]=='\0')
                V[int(c)][8]=i-1+'0';
            V[int(c)][i-1]=vec[i]%2+'0';
        }
    }
    vec[1]=(int)c;
        for(i=2;i<=8;i++)
            {vec[i]=(vec[i-1]>>7)+(vec[i-1]-(vec[i-1]&(1<<7)))*2;}
        sort(vec+1,vec+8);
        for(i=1;i<=8;i++)
        {
            if(vec[i]==(int)c&&V[int(c)][8]=='\0')
                V[int(c)][8]=i-1+'0';
            V[int(c)][i-1]=vec[i]%2+'0';
        }
    fscanf(f,"%d\n",&tip);
    if(tip==1)
    {
        while(fscanf(f,"%c",&c)&&c!='\n')
        {
            fprintf(g,"%s",V[int(c)]);
        }
    }
    else
   {
        while(fgets(cer,10,f)&&cer[0]!='\n')
        {
            for(i=32;i<=127;i++)
            if(strcmp(cer,V[i])==0){fputc((char)i,g);break;}
        }
   }
    fclose(f);
    fclose(g);
    return 0;
}
