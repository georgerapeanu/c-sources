#ifndef set_type
#define set_type
#include <cstdlib>
#include <cstring>
int type;
void settype(char *ptr)
{
    if(strcmp(ptr,"short")==0||strcmp(ptr,"unsigned short")==0)
    {
         type=2;
    }
    else if(strcmp(ptr,"int")==0||strcmp(ptr,"unsigned int")==0)
    {
         type=4;
    }
    else if(strcmp(ptr,"long")==0||strcmp(ptr,"long int")==0||strcmp(ptr,"unsigned long")==0||strcmp(ptr,"unsigned long int")==0)
    {
         type=4;
    }
    else if(strcmp(ptr,"long long")==0||strcmp(ptr,"long long int")==0||(strcmp (ptr,"unsigned long long")==0||strcmp(ptr,"unsigned long long int")==0))
    {
         type=8;
    }
    else if(strcmp(ptr,"float")==0)
    {
         type=4;
    }
    else if(strcmp(ptr,"double")==0)
    {
         type=8;
    }
    else if(strcmp(ptr,"char")==0)
    {
         type=1;
    }
}
#endif // set_type
