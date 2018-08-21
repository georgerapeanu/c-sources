#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int n,q;
bool isQ;
int last0;
int a[(int)2e5 + 5];
int b[(int)2e5 + 5];
int left[(int)2e5 + 5];
int right[(int)2e5 + 5];
set<int> active;
vector< pair<int,int> > events;

int main(){
	
	fscanf(stdin,"%d %d",&n,&q);
	
	for(int i = 1;i <= n;i++){
		fscanf(stdin,"%d",&a[i]);
		last0 = (a[i] == 0 ? i : last0);
		isQ |= (a[i] == q);
		b[i] = a[i];
	}
	
	if(!isQ){
		if(last0){
			b[last0] = q;
		}
		else{
			fputs("NO",stdout);
			return 0;
		}
	}
	
	for(int i = 2;i <= n;i++){
		b[i] = (b[i] == 0 ? b[i - 1]:b[i]);
	}
	
	for(int i = n - 1;i;i--){
		b[i] = (b[i] == 0 ? b[i + 1]:b[i]);
	}
	
	for(int i = 1;i <= n;i++){
		if(!left[b[i]]){
			left[b[i]] = i;
		}
		right[b[i]] = i;
	}
	
	
	for(int val = 1;val <= q;val++){
		if(left[val]){
			events.push_back({left[val],val});
			events.push_back({right[val] + 1,-val});
		}
	}
	
	sort(events.begin(),events.end());
	
	int latest = 0;
	
	for(auto it:events){
		while(latest + 1 < it.first){
			b[++latest] = *active.rbegin();
		}
		
		if(it.second < 0){
			active.erase(-it.second);
		}
		
		else{
			active.insert(it.second);
		}
	}
	
	for(int i = 1;i <= n;i++){
		if(a[i] && a[i] != b[i]){
			fputs("NO",stdout);
			return 0;
		}
	}
	
	fputs("YES\n",stdout);
	for(int i = 1;i <= n;i++){
		fprintf(stdout,"%d ",b[i]);
	}
	
	return 0;
}