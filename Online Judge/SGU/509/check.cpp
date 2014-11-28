#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#define min(a,b)	((a)<(b)?(a):(b))
#define max(a,b)	((a)>(b)?(a):(b))
#define inf 214748364
#define pi 3.141592653589793
#define maxn 500001
using namespace std;
typedef long long ll;
struct tinfo
{
	ll p,c,d,num,cross,no;
}	g[maxn];
ll q[maxn],qp[maxn];
ll n,l,t;
ll rest,p,c,cc;
int no[maxn];
inline ll dist(ll a,ll b)
{
	a-=b;
	while(a<0)	a+=l;
	return a%l;
}
inline int cmp(const void *inpa,const void *inpb)
{
	tinfo a=*(tinfo*)inpa,b=*(tinfo*)inpb;
	return a.p-b.p;
}
inline int cmp2(const void *inpa,const void *inpb)
{
	tinfo a=*(tinfo*)inpa,b=*(tinfo*)inpb;
	return a.no-b.no;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output2.txt","w",stdout);
	#endif
	scanf("%I64d",&n);
	scanf("%I64d",&l);
	for(int i=0;i<n;i++)
	{
		scanf("%I64d%I64d%I64d",&g[i].p,&g[i].c,&g[i].d);
		g[i].no=i;
		if(g[i].d==-1)
			cc++;else
			c++;
	}
	cin>>t;
	//work 1
	for(int i=0;i<n;i++)
		g[i].p=l-g[i].p-1;
	qsort(g,n,sizeof(g[0]),cmp);
	rest=t%l;	//Ê£ÓàµÄÊ±¼ä
	int head=0,tail=-1;
	int now=-1;
	for(int i=0;i<n*3;i++)
	{
		p=i%n;
		if(p==0)	now++;
		while(head<=tail&&g[p].p+now*l-q[head]>rest*2)
			head++;
		if(g[p].d==1)
			g[p].num=max(g[p].num,tail-head+1);else
			q[++tail]=g[p].p+now*l;
	}
	//work -1
	for(int i=0;i<n;i++)
		g[i].p=l-g[i].p-1;
	qsort(g,n,sizeof(g[0]),cmp);
	for(int i=0;i<n;i++)
		g[i].cross=i;
	head=0,tail=-1;
	now=-1;
	for(int i=0;i<n*3;i++)
	{
		p=i%n;
		if(p==0)	now++;
		while(head<=tail&&g[p].p+now*l-q[head]>rest*2)
			head++;
		if(g[p].d==-1)
		{
			g[p].num=max(g[p].num,tail-head+1);
			if(head<=tail)
				g[p].cross=qp[head];
		}else
			q[++tail]=g[p].p+now*l,qp[tail]=p;
	}
	
	if(t>=l)
	{
		q[0]=-1;
		for(int i=n*2-1;i>=0;i--)
		{
			p=i%n;
			if(g[p].d==1)
				q[0]=p;else
			if(g[p].cross==p&&q[0]!=-1)
				g[p].cross=q[0];
		}
	}
	for(int i=0;i<n;i++)
		g[i].c=g[g[i].cross].c;
	
	ll da=t/l*c*2%n,db=t/l*cc*2%n;
	for(int i=0;i<n;i++)
	{
		if(g[i].d==1)
			g[i].num+=db;else
			g[i].num+=da;
		g[i].num%=n;
		if(g[i].d==1)
			no[i]=g[(i+g[i].num)%n].no;else
			no[i]=g[(i-g[i].num+n)%n].no;
		if(g[i].d==1)
			g[i].p=(g[i].p+rest)%l;else
			g[i].p=(g[i].p-rest+l)%l;
	}
	for(int i=0;i<n;i++)
		g[i].no=no[i];
	qsort(g,n,sizeof(g[0]),cmp2);
	for(int i=0;i<n;i++)
	{
		//printf("%I64d.000 %I64d %I64d %d\n",g[i].p,g[i].c,g[i].d,g[i].num);
		printf("%I64d %I64d %I64d\n",g[i].p,g[i].c,g[i].d);
	}
	return 0;
}
