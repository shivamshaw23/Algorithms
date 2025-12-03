#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define mod 1000000007
 
 
 

 
//-----------------MOS ALGO---------------------------------       

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) { 
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
struct query {
	int l, r, i;
	int64_t ord;
 
	inline void calcOrder() {
		ord = gilbertOrder(l, r, 21, 0);
	}
};

inline bool operator<(const query &a, const query &b) {
	return a.ord < b.ord;
}




int freq[1000001];
       
 
int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL); cout.tie(NULL);
ll ttt;cin>>ttt;while(ttt--){
ll n,q;cin>>n>>q;
vector<ll>arr(n);
 
for(int i=0;i<n;i++){cin>>arr[i];freq[arr[i]]=0;}
int block = sqrtl(n);
 
vector<query>queries;
queries.reserve(q);
for(int i=0;i<q;i++){
    ll a,b;cin>>a>>b;a--;b--;
    query qq;
    qq.i=i;
    qq.l=a;
    qq.r=b;
    qq.calcOrder();
    queries.push_back(qq);
}

sort(queries.begin(),queries.end());

ll odd=0,even=0;

ll curL=0,curR=-1;

 
auto add=[&](ll x){   
    if((freq[x]&1)==0)odd++;
    else odd--;
    freq[x]++;
};

auto rem=[&](ll x){
     if((freq[x]&1)==0)odd++;
     else odd--;
    freq[x]--;
};
vector<ll>fin(q);
 
for(auto u : queries){
    while(curL>u.l){
        curL--;
        add(arr[curL]);
    }
    while(curR<u.r){
        curR++;
        add(arr[curR]);
    }
    while(curL<u.l){
        rem(arr[curL]);
        curL++;
    }
    while(curR>u.r){
        rem(arr[curR]);
        curR--;
    }
    ll ans = (odd==0)?1:0;
    fin[u.i]=ans;
}
for(auto u : fin)fYES(u==1);
}

}
 
