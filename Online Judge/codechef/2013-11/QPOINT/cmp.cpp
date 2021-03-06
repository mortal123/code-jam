#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<iostream>
#include<ctype.h>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<cmath>
#include<bitset>
#include<iomanip>
#include<complex>
#include<utility>
 
#define X first
#define Y second
#define REP_0(i,n) for(int i=0;i<(n);++i)
#define REP_1(i,n) for(int i=1;i<=(n);++i)
#define REP_2(i,a,b) for(int i=(a);i<(b);++i)
#define REP_3(i,a,b) for(int i=(a);i<=(b);++i)
#define REP_4(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define DOW_0(i,n) for(int i=(n)-1;-1<i;--i)
#define DOW_1(i,n) for(int i=(n);0<i;--i)
#define DOW_2(i,a,b) for(int i=(b);(a)<i;--i)
#define DOW_3(i,a,b) for(int i=(b);(a)<=i;--i)
#define FOREACH(a,b) for(typeof((b).begin()) a=(b).begin();a!=(b).end();++a)
#define RFOREACH(a,b) for(typeof((b).rbegin()) a=(b).rbegin();a!=(b).rend();++a)
#define PB push_back
#define PF push_front
#define MP make_pair
#define IS insert
#define ES erase
#define IT iterator
#define RI reserve_iterator
#define PQ priority_queue
#define LB lower_bound
#define UB upper_bound
#define ALL(x) x.begin(),x.end()
 
#define PI 3.1415926535897932384626433832795
#define EXP 2.7182818284590452353602874713527
 
using namespace std;
 
typedef long long LL;
typedef long double LD;
typedef double DB;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef pair<int,PII> PIII;
typedef pair<LD,int> PLDI;
typedef vector<PII> VII;
 
template<class T>
T Mul(T x,T y,T P){
	T F1=0;
	while(y)
	{
		if(y&1)
		{
			F1+=x;
			if(F1<0||F1>=P)F1-=P;
		}
		x<<=1;
		if(x<0||x>=P)x-=P;
		y>>=1;
	}
	return F1;
}
 
template<class T>
T Pow(T x,T y,T P){
	T F1=1;x%=P;
	while(y)
	{
		if(y&1)
		{
			F1=Mul(F1,x,P);
		}
		x=Mul(x,x,P);
		y>>=1;
	}
	return F1;
}
 
template<class T>
T Gcd(T x,T y){
	if(y==0)return x;
	T z;
	while(z=x%y){
		x=y,y=z;
	}
	return y;
}
 
template<class T>
void UpdateMin(T &x,T y){
	if(y<x)
	{
		x=y;
	}
}
 
template<class T>
void UpdateMax(T &x,T y){
	if(x<y)
	{
		x=y;
	}
}
 
template<class T>
T Sqr(const T x){
	return x*x;
}
 
template<class T>
T Abs(const T x){
	return x<0?-x:x;
}
 
#define MaxBuffer 20000000
class ReadBuffer{
	private:
	char buff[MaxBuffer];
	char *buf;
	public:
	void init(int size=MaxBuffer)
	{
		fread(buff,1,size,stdin);
		buf=buff;
	}
	template<class T>
	bool readInteger(T &x)
	{
		x=0;
		while(*buf&&isspace(*buf)) ++buf;
		if(*buf==0) return false;
		static bool flag;
		flag=0;
		if(*buf=='-') flag=true;
		else x=*buf-'0';
		while(isdigit(*++buf)) x=x*10+*buf-'0';
		if(flag) x=-x;
		return true;
	}
	template<class T>
	bool readFloat(T &x)
	{
		long double nowpos=0.1;
		x=0;
		while(*buf&&isspace(*buf)) ++buf;
		if(*buf==0) return false;
		static bool flag,decimal;
		decimal=flag=0;
		if(*buf=='-') flag=true,++buf;
		else if(*buf=='.') decimal=true;
		while(isdigit(*buf)||*buf=='.')
		{
			if(*buf=='.') decimal=true;
			else
			{
				if(decimal)
				{
					x+=nowpos*(*buf-'0');
					nowpos*=0.1;
				}
				else
				{
					x=x*10+*buf-'0';
				}
			}
			++buf;
		}
		return true;
	}
	bool readChar(char c)
	{
		if(*buf==0) return 0;
		return c=*buf++,1;
	}
	bool readString(char *s)
	{
		while(*buf&&isspace(*buf)) ++buf;
		if(!*buf) return false;
		while(!isspace(*buf)) *s++=*buf++;
		*s++=0;
		return true;
	}
	int countSpacetonext(){
		int total=0;
		while(*buf&&*buf==' ') ++total,++buf;
		return total;
	}
	bool splitBycharactor(char *s,char Split='\n'){
		while(*buf&&*buf!=Split) *s++=*buf++;
		*s++=0;
		return *buf!=0;
	}
};
 
struct EDGE{
	int T;EDGE *Nxt;
};
 
namespace TwoDimension{
	inline int Sign(LL x){
		return x<0?-1:x>0;
	}
	struct point{
		int x,y;
		point(){}
		point(int x,int y):x(x),y(y){}
		void read(){int tx,ty;scanf("%d%d",&tx,&ty);x=tx,y=ty;}
		bool operator <(const point &a)const{
			return x<a.x||(x==a.x&&y<a.y);
		}
		bool operator ==(const point &a)const{
			return x==a.x&&y==a.y;
		}
		point operator -(const point &a)const{
			return point(x-a.x,y-a.y);
		}
		point operator +(const point &a)const{
			return point(x+a.x,y+a.y);
		}
		point operator *(const LL &a)const{
			return point(x*a,y*a);
		}
	};
	inline LL det(const point &a,const point &b){
		return (LL)a.x*b.y-(LL)a.y*b.x;
	}
	struct segment{
		point s,t;
		int belong;
		segment(){}
		segment(point _s,point _t,int _belong):s(_s),t(_t),belong(_belong){
			if(t<s) swap(s,t),belong=-belong;
		}
		bool operator <(const segment &a){return s<a.s;}
		bool operator ==(const segment &a){return s==a.s&&t==a.t;}
		LL relation(const point &b)const{
			return Sign(det(s-b,t-b));
		}
		bool under(const segment &b)const{
			register int f;
			if(b.s.x<s.x){
				f=b.relation(s);
				if(f) return f>0;
			}
			else{
				f=relation(b.s);
				if(f) return f<0;
			}
			if(b.t.x>t.x){
				f=b.relation(t);
				if(f) return f>0;
			}
			else{
				f=relation(b.t);
				if(f) return f<0;
			}
			return false;
		}
	};
}
 
namespace Treap{
	const int maxTreepNode = 8000000;
	struct TreapNode{
		TwoDimension::segment x;
		int y;
		TreapNode *c[2];
		void init(const TwoDimension::segment &_x){
			c[0]=c[1]=0;
			x=_x,y=((rand()&32768)<<16)|(rand()&32768);
		}
	}*root,totalnode[maxTreepNode],*pn;
	
	inline void Rotate(TreapNode *x,TreapNode *y,int p){
		y->c[p]=x->c[!p];
		x->c[!p]=y;
	}/*
	void Maintain(TreapNode *x){
		while(x->fa&&x->fa->y > x->y){
			Rotate(x,x->fa->c[1]==x);
			if(!x->fa) root=x;
		}
	}*/
	inline TreapNode* NewNode(const TreapNode &x){
		*pn=x;
		return pn++;
	}
	inline void Clear(){root=0;pn=totalnode;}
	TreapNode* Union(TreapNode *x,TreapNode *y){
		if(!x||!y) return x?x:y;
		if(x->y>y->y) swap(x,y);
		x=NewNode(*x);
		int f=!(x->x.under(y->x));
		x->c[f]=Union(x->c[f],y);
		return x;
	}
	TreapNode* Insert(TreapNode *now,const TwoDimension::segment &s){
		if(!now){
			TreapNode *x=pn;
			x->init(s);
			++pn;
			return x;
		}
		else{
			now=NewNode(*now);
			int f=!(now->x.under(s));
			now->c[f]=Insert(now->c[f],s);
			if(now->c[f]->y>now->y){
				TreapNode *g=now->c[f];
				Rotate(g,now,f);
				now=g;
			}
			return now;
		}
	}
	/*
	inline TreapNode *Find(const segment &s){
		TreapNode *now=root;
		while(1){
			if(now->x==s) return now;
			now=now->c[!now->x.under(s)];
		}
	}
	*/
	TreapNode *Delete(TreapNode *now,const TwoDimension::segment &s){
		if(now->x==s){
			return Union(now->c[0],now->c[1]);
		}
		else{
			now=NewNode(*now);
			int f=!(now->x.under(s));
			now->c[f]=Delete(now->c[f],s);
			return now;
		}
	}
	inline int Query(const TwoDimension::point &s,TreapNode* nowroot){
		int ans=1;
		while(nowroot){
			int f=nowroot->x.relation(s);
			if(!f){
				ans=-Abs(nowroot->x.belong);
				break;
			}
			if(f<0){
				ans=nowroot->x.belong;
				nowroot=nowroot->c[0];
			}
			else nowroot=nowroot->c[1];
		}
		return ans>0?-1:-ans;
	}
	inline void TLE(){
		if(pn-totalnode>8000000) while(1);
	}
}
 
struct Event{
	TwoDimension::segment s;
	int x,y;
	inline bool operator <(const Event &a)const{
		return x<a.x||x==a.x&&y<a.y;
	}
}E[601001];
 
int totalE;
 
Treap::TreapNode *recordroot[600101];
int recordx[600101];
int totalrecord;
TwoDimension::point polygon[601001];
int main(){
	freopen("input.txt","r",stdin);
	freopen("a.out","w",stdout);
	srand(361120154);
	int n;
	scanf("%d",&n);
//	n=1;
	totalE=0;
	REP_1(i,n){
		int m;
		scanf("%d",&m);
//		m=300000;
		REP_1(j,m){
			polygon[j].read();
			//polygon[j]=TwoDimension::point(j,2*j+1);
		}
		polygon[0]=polygon[m];
		LL s=0;
		REP_1(j,m) s+=TwoDimension::det(polygon[j-1],polygon[j]);
		if(s<0) reverse(polygon+0,polygon+m+1);
		REP_1(j,m){
			if(polygon[j].x!=polygon[j-1].x){
			//	verseg.push_back(TwoDimension::segment(polygon[j-1],polygon[j],i));
			//}
			//else{
				TwoDimension::segment s(polygon[j-1],polygon[j],i);
				E[totalE].s=s,E[totalE].x=s.s.x,E[totalE].y=1;
				++totalE;
				E[totalE].s=s,E[totalE].x=s.t.x,E[totalE].y=-1;
				++totalE;
			}
		}
	}
	sort(E,E+totalE);
	Treap::Clear();
	totalrecord=0;
	for(int i=0;i<totalE;){
		int j=i;
		while(j<totalE&&E[i].x==E[j].x){
			if(E[j].y==1) Treap::root=Treap::Insert(Treap::root,E[j].s);
			else Treap::root=Treap::Delete(Treap::root,E[j].s);
			++j;
		}
		recordx[++totalrecord]=E[i].x;
		recordroot[totalrecord]=Treap::root;
		i=j;
		Treap::TLE();
//		if(totalrecord==4024){
//			printf("!!!\n");
//		}
	}
	
	int q;
	scanf("%d",&q);
//	q=100000;
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
//		x=rand(),y=rand();
		int pos=lower_bound(recordx+1,recordx+totalrecord+1,x)-recordx-1;
		int ans=-1;
		
		if(ans==-1&&pos){
			ans=Treap::Query(TwoDimension::point(x,y),recordroot[pos]);
		}
		if(ans==-1&&pos!=totalrecord&&recordx[pos+1]==x){
			ans=Treap::Query(TwoDimension::point(x,y),recordroot[pos+1]);
		}
		printf("%d\n",ans);
		fflush(stdout);
	}
//	printf("!!!\n");
//	scanf("%d",&q);
	return 0;
}
