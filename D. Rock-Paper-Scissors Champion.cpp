#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

set<int> s[3];
int aib[3][200005];
char c[200005];
int n,q;

int c_to_i(char c){
	return (c == 'R' ? 0:(c == 'P' ? 1:2));
}

void update(int wh,int pos,int val){
	for(;pos <= n;pos += (-pos) & pos){
		aib[wh][pos] += val;
	}
}

bool convine(int tip,int mask){
	mask >>= 1;
	if(tip == 0){
		return mask == 0 || mask == 4 || mask == 1 || mask == 5 || mask == 6 || mask == 7;
	}
	if(tip == 1){
		return mask == 0 || mask == 2 || mask == 1 || mask == 3 || mask == 5 || mask == 7;
	}
	return mask == 0 || mask == 4 || mask == 2 || mask == 6 || mask == 3 || mask == 7;
}

int query(int wh,int pos){
	int ans = 0;
	for(;pos;pos -= (-pos) & pos){
		ans += aib[wh][pos];
	}
	return ans;
}

void set_char(int pos,int val,bool ini = false){
	if(!ini){
		s[c[pos]].erase(pos);
		update(c[pos],pos,-1);
	}
	// if(!ini)fprintf(stderr,"yummi");
	s[val].insert(pos);
	update(val,pos,1);
	c[pos] = val;
}

int answer(){
	int ans = 0;
	vector<pair<int,int> > events;
	int mask1 = 0,mask2 = 0;
	for(int i = 0;i < 3;i++){
		if(s[i].size()){
			events.push_back({*s[i].begin(),i + 1});
			events.push_back({*s[i].rbegin(),-i - 1});
			mask2 |= (1 << (i + 1));
		}
	}
	sort(events.begin(),events.end());
	
	///check segments
	for(int i = 0;i < (int)events.size() - 1;i++){
		// fprintf(stderr,"%d %d\n",events[i].first,events[i].second);
		mask1 |= (1 << abs(events[i].second));
		if(events[i].second < 0){
			mask2 -= (1 << (-events[i].second));
		}
		int left = events[i].first + 1;
		int right = events[i + 1].first - 1;
		if(left > right){
			continue;
		}
		
		for(int i = 0;i < 3;i++){
			if(convine(i,mask1) && convine(i,mask2)){
				ans += query(i,right) - query(i,left - 1);
			}
		}
	}
	
	
	///check individual
	for(int i = 0;i < (int)events.size();i++){
		if(i && events[i - 1].first == events[i].first){
			continue;
		}
		int mask1 = 0,mask2 = 0;
		for(int j = 0;j < i;j++){
			mask1 |= 1 << abs(events[j].second);
		}
		for(int j = (int)events.size() - 1;j > i;j--){
			mask2 |= 1 << abs(events[j].second);
		}
		if(convine(c[events[i].first],mask1) && convine(c[events[i].first],mask2)){
			ans ++;
		}
		// fprintf(stderr,"%d %d %d\n",c[events[i].first],mask1 / 2,mask2 / 2);
	}
	// fprintf(stderr,"%d\n",ans);
	return ans;
}

int main(){
	
	// freopen("tmp.in","r",stdin);
	// freopen("tmp.out","w",stdout);

	fscanf(stdin,"%d %d\n",&n,&q);

	fgets(c + 1,200005,stdin);
	for(int i = 1;i <= n;i++){
		set_char(i,c_to_i(c[i]),true);
	}
	
	fprintf(stdout,"%d\n",answer());
	// fprintf(stderr,"lebene\n");
	while(q--){
		int pos;
		char c;
		fscanf(stdin,"%d %c\n",&pos,&c);
		set_char(pos,c_to_i(c));
		// fprintf(stderr,"bene\n");
		fprintf(stdout,"%d\n",answer());
	}
	
	return 0;
}