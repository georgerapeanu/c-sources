#include <cstdio>
#include <cstring>
using namespace std;
char s[128][10],ch,ss[10];
int i,cer;
void cript(char c, char cod[10])
{
    int n,ord[10],ax,i,j;
    char s[10][10],aux[10];
    n=c;
    for(i=7; i>=0; i--)
    {
        s[0][i]='0'+n%2;
        n=n/2;
    }
    s[0][8]='\0';
    for(i=1;i<=7;i++)
    {
        for(j=0;j<7;j++)
            s[i][j]=s[i-1][j+1];
        s[i][7]=s[i-1][0];
        s[i][8]='\0';
    }
    //ordonez lexicografic sirul s[]
    for(i=0; i<=7; i++)
        ord[i]=i;
    for(i=0; i<7; i++)
        for(j=i+1; j<=7; j++)
            if(strcmp(s[i],s[j])>0)
            {
                strcpy(aux,s[i]);
                strcpy(s[i],s[j]);
                strcpy(s[j],aux);
                ax=ord[i];
                ord[i]=ord[j];
                ord[j]=ax;
            }
     for(i=0; i<7; i++)
        for(j=i+1; j<=7; j++)
                if(strcmp(s[i],s[j])==0&&ord[i]>ord[j])
                {
                strcpy(aux,s[i]);
                strcpy(s[i],s[j]);
                strcpy(s[j],aux);
                ax=ord[i];
                ord[i]=ord[j];
                ord[j]=ax;
            }


    for(i=0; i<=7; i++)
        cod[i]=s[i][7];
    for(i=0; i<=7; i++)
        if(ord[i]==0)break;
    cod[8]='0'+i;
    cod[9]='\0';
}
int main()
{
    for(int l=32;l<=127;l++)
//    FILE *f,*g;
//    g=fopen("criptat.out","w");
//    f=fopen("criptat.in","r");
//    fscanf(f,"%d",&cer);
//    if(cer==1)
//    {
//        fscanf(f,"%c",&ch);
//        fscanf(f,"%c",&ch);
//        while(ch!='\n')
//        {
//            fprintf(g,"%s",c[ch]);
//            fscanf(f,"%c",&ch);
//        }
//        fprintf(g,"\n");
//    }
//    else
//    {
//        fscanf(f,"%c",&ch);
//        while(s[0]!='\n')
//        {
//            for(i=0;i<=8;i++)
//            {
//                fscanf(f,"%c",&s[i]);
//            }
//            s[9]='\0';
//            if(s[0]!='\n')
//            for(i=32;i<=80;i++)
//            {
//                if(strcmp(c[i],s)==0)
//                {
//                    fprintf(g,"%c",i);
//                    break;
//                }
//                if(strcmp(c[127-i+32],s)==0)
//                {
//                    fprintf(g,"%c",127-i+32);
//                    break;
//                }
//            }
//        }
//        fprintf(g,"\n");
//    }
//    fclose(f);fclose(g);
}