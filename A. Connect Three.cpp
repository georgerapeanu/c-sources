#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
	int xa,ya;
	int xb,yb;
	int xc,yc;
	
	
	scanf("%d %d",&xa,&ya);
	scanf("%d %d",&xb,&yb);
	scanf("%d %d",&xc,&yc);
	
	int xmax = max(max(xa,xb),xc);
	int xmin = min(min(xa,xb),xc);
	int ymax = max(max(ya,yb),yc);
	int ymin = min(min(ya,yb),yc);
	int xmid = xa ^ xb ^ xc ^ xmin ^ xmax;
	int ymid = ya ^ yb ^ yc ^ ymin ^ ymax;
	
	printf("%d\n",(xmax - xmin) + (ymax - ymin) + 1);
	
	for(int i = xmin;i <= xmax;i++){
		printf("%d %d\n",i,ymid);
	}
	
	///a
	
	for(int i = ya;i != ymid;i += (ya > ymid ? -1:1)){
		printf("%d %d\n",xa,i);
	}
	
	///b
		
	for(int i = yb;i != ymid;i += (yb > ymid ? -1:1)){
		printf("%d %d\n",xb,i);
	}
		
	///c
	
	for(int i = yc;i != ymid;i += (yc > ymid ? -1:1)){
		printf("%d %d\n",xc,i);
	}
	
	return 0;
}