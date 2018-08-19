#include<iostream>
using namespace std;
int x[3000],z;

int main()
{int a,b;
 int y,i,k,c,d;
 cin>>a>>b>>c>>d;
 for(i=a;i<=b;i++)
 { k=i; y=1;
   while(k)
    {y=y*10+k%10; k=k/10;}
   while(y>1)
    {x[++z]=y%10; y=y/10;}
 }


cout<<"a) "<<x[c];
i=1;
while(c&&z>1)
 {
  if(x[i]==9)i++;
  else
  if(x[i]<x[i+1]){
		  for(int p=i;p<z;p++)
		      x[p]=x[p+1];
		   z--;
		  if(i>1)i--;c--;}
       else
	if(x[i]==x[i+1])i++;
	  else {if (x[i+1]<=x[i+2])
			 {
			   for(int p=i+1;p<z;p++)
			       x[p]=x[p+1];
			   z--;
			 }
		 else { for(int p=i+2;p<z;p++)
			   x[p]=x[p+1];
			 z--;}
			 c--;
		       }
 }
if(c)
   if(x[1]<=x[2]){x[1]=x[2];z=1;}
     else z--;

cout<<"\nb) ";
for(i=1;(i<=76)&&(i<=z);i++)
    cout<<x[i];

cout<<endl;
y=0;
 for(i=1;i<=z;i++)
    if(x[i]==d)y++;
cout<<"c) "<<y;


return 0;
}
