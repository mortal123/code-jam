#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#define inf 0x1f1f1f1f
using namespace std;
struct N
{
int rm,lm,mx,dl,dr;
};
struct seg
{
int l,r;
N d;
};
seg *r[100020],t[400020];
int ts,n;
int h[100020];
int a[200020][3],tot;
int g[100020];
int d[100020];
int f[100020];
int u[100020];
int z[100020];
int w[100020];
int b[100020];
int ps[400020];
int num[100020];
int pa[400020];
int l[100020];
int cc[100020];
int lnc;
int cnt,ac;
N operator+(const N &x,const N &y)
{
N re;
re.lm=max(x.lm,x.dr-x.dl+y.dl+y.lm);
re.rm=max(y.rm,x.rm+y.dr);
re.mx=max(max(x.mx,y.mx),x.rm+y.dl+y.lm);
re.dr=x.dr+y.dr;
re.dl=x.dl;
return re;
}
bool operator<(const seg &x,const seg &y)
{
return x.d.lm+x.d.dl<y.d.lm+y.d.dl;
}
struct H
{
int *a;
int n;
void init(int _n)
{
n=_n;
a=new int[n+1];
memset(a,0,4*n+4);
}
void up(int x)
{
while(x>1)
if(t[a[x>>1]]<t[a[x]])
{
swap(a[x],a[x>>1]);
swap(ps[a[x]],ps[a[x>>1]]);
x>>=1; 
} 
else
break; 
} 
void dn(int x) 
{
for(int y=x*2;y<=n;x=y,y=2*x)
{ 
if(y<n&&t[a[y]]<t[a[y+1]])
y++;
if(t[a[x]]<t[a[y]])
{
swap(a[x],a[y]);
swap(ps[a[x]],ps[a[y]]); 
}
else
break;
}
}
void st()
{
for(int i=n/2;i>0;i--)
dn(i);	
return;
}
#define Z(x) (t[x].d.lm+t[x].d.dl)
int Q1()
{
//	if(n>0)
//	 printf("%d %d %d\n",a[1],Z(a[1]));
//	printf("Q1 re :%d\n",n>0?Z(a[1]):-inf);
return n>0?Z(a[1]):-inf;
}
int Q2()
{
if(n<2)
return -inf;
int i=2;
if(n>2&&Z(a[2])<Z(a[3]))
i++;
//	printf("Q2 re :%d\n",Z(a[i]));
return Z(a[i]);
}
}hp[100020];
struct ALL
{
int a[100020];
void up(int x)
{
while(x>1)
if(t[a[x>>1]].d.mx<t[a[x]].d.mx)
{
swap(a[x],a[x>>1]);
swap(pa[a[x]],pa[a[x>>1]]);
x>>=1; 
} 
else
break; 
} 
void dn(int x) 
{
for(int y=x*2;y<=lnc;x=y,y=2*x)
{ 
if(y<lnc&&t[a[y]].d.mx<t[a[y+1]].d.mx)
y++;
if(t[a[x]].d.mx<t[a[y]].d.mx)
{
swap(a[x],a[y]);
swap(pa[a[x]],pa[a[y]]);
}
else
break;
}
}
void st()
{
for(int i=lnc/2;i>0;i--)
dn(i);
return;
}
}all;
void add(int x,int y,int z)
{
//printf("add:%d %d %d\n",x,y,z);
tot++;
a[tot][0]=h[x];
a[tot][1]=y;
a[tot][2]=z;
h[x]=tot;
}
int lg(int x)
{
if(x==1)
return 0;
return lg((x+1)/2)+1;
}
void bd(seg *rt,int l,int r,int x)
{
rt[x].l=l;
rt[x].r=r;
if(l==r)
{
rt[x].d.lm=rt[x].d.rm=max(0,hp[b[l]].Q1());
rt[x].d.mx=max(0,hp[b[l]].Q1())+max(0,hp[b[l]].Q2());
rt[x].d.dl=rt[x].d.dr=g[b[l]]-g[f[b[l]]];
}
else
{
int m=(l+r)/2;
bd(rt,l,m,x*2);
bd(rt,m+1,r,x*2+1);
rt[x].d=rt[x*2].d+rt[x*2+1].d;
}
if(x==1)
all.a[++ac]=rt-t+1,pa[rt-t+1]=ac;
return;
}
void cg(seg *rt,int p,int x)
{
if(rt[x].l==rt[x].r)
{
if(w[p]==0)
{
rt[x].d.lm=rt[x].d.rm=max(0,hp[p].Q1());
rt[x].d.mx=max(0,hp[p].Q1())+max(0,hp[p].Q2());
rt[x].d.dl=rt[x].d.dr=g[p]-g[f[p]];
}
else
{
rt[x].d.lm=rt[x].d.rm=hp[p].Q1();
rt[x].d.mx=hp[p].Q1()+hp[p].Q2();
rt[x].d.dl=rt[x].d.dr=g[p]-g[f[p]];
}
}
else
{
int m=(rt[x].l+rt[x].r)/2;
if(num[p]<=m)
cg(rt,p,x*2);
else
cg(rt,p,x*2+1);
rt[x].d=rt[x*2].d+rt[x*2+1].d;
}
if(x==1)
{
all.up(pa[rt-t+1]);
all.dn(pa[rt-t+1]);
if(f[l[p]])
{
hp[f[l[p]]].up(ps[rt-t+1]);
hp[f[l[p]]].dn(ps[rt-t+1]);
}
}
return;
}
void dfs(int x)
{
int i,e;
u[x]=0;
for(i=h[x];i;i=a[i][0])
if((e=a[i][1])!=f[x])
{
f[e]=x;
d[e]=d[x]+1;
g[e]=g[x]+a[i][2];
dfs(e);
u[x]+=u[e];
if(u[e]>u[z[x]])
z[x]=e;
}
u[x]++;
for(i=h[x];i;i=a[i][0])
if((e=a[i][1])!=f[x]&&e!=z[x])
{
cc[x]++;
cnt=0;
for(int j=e;j;j=z[j])
{
cnt++;
b[cnt]=j;
l[j]=e;
num[j]=cnt;
}
lnc++;
r[e]=&t[ts];
bd(&t[ts],1,cnt,1);
ts+=(1<<(lg(cnt)+1));
}
hp[x].init(cc[x]);
cc[x]=0;
for(i=h[x];i;i=a[i][0])
if((e=a[i][1])!=f[x]&&e!=z[x])
hp[x].a[++cc[x]]=(r[l[e]]-t+1),ps[r[l[e]]-t+1]=cc[x];
hp[x].st();
return;
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
scanf("%d",&n);
add(0,1,0);
int i;
for(i=1;i<n;i++)
{
int x,y,z;
scanf("%d %d %d",&x,&y,&z);
add(x,y,z);
add(y,x,z);
}
dfs(0);
int q;
all.st();
cnt=n;
for(scanf("%d",&q);q--;)
{
char o[5];
int x;
scanf("%s",o);
if(*o=='C')
{
scanf("%d",&x);
if(w[x])
cnt++;
else
cnt--;
w[x]^=1;
while(x)
{
cg(r[l[x]],x,1);
x=f[l[x]];
}
}
else
{
if(!cnt)
puts("They have disappeared.");
else
printf("%d\n",t[all.a[1]].d.mx);
}
}
return 0;
}
