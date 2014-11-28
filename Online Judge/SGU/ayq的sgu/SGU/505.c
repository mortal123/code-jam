#include <stdio.h>
#include <string.h>
#define lowbit(a) ((a)&(-(a)))

struct case1
{
   char *str;
   long l,pos;
}p[100001]={0,0,0};
struct case2
{
   long pos,s,l,r,num;
}q[200001]={0,0,0,0,0};
long l[100001]={0},r[100001]={0},ans[100001]={0},tree[100001]={0};
char *rec[100001]={0},str[200005]={0},tmp[200005]={0};
long n;

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&strcmp(p[j].str,t.str)>0)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&strcmp(p[i].str,t.str)<0)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y;
   struct case2 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&q[j].pos>t.pos)
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&q[i].pos<t.pos)
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

void ins(long i)
{
   for (;i<=n;i+=lowbit(i))
      tree[i]++;
}

long sum(long i)
{
   long s=0;
   for (;i;i-=lowbit(i))
      s+=tree[i];
   return s;
}

long cmp(char x[],char y[])
{
   long i;
   for (i=0;x[i];i++)
      if (x[i]>y[i])
         return 1;
      else if (x[i]<y[i])
         return -1;
   return 0;
}

long getl(char x[])
{
   long l=0,r=n,mid;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (cmp(x,p[mid].str)<=0)
         r=mid;
      else
         l=mid;
   }
   return cmp(x,p[r].str)?0:r;
}

long getr(char x[])
{
   long l=1,r=n+1,mid;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (cmp(x,p[mid].str)>=0)
         l=mid;
      else
         r=mid;
   }
   return l;
}

int main()
{
   long i,j,len,x,last=0,s=0;
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
   {
      gets(str);
      p[i].l=strlen(str);
      p[i].str=(char*)malloc((p[i].l+1)*sizeof(char));
      strcpy(p[i].str,str);
   }
   qs(1,n);
   scanf("%ld",&x);
   for (i=1;i<=x;i++)
   {
      scanf("%s%s",str,tmp);
      len=strlen(tmp);
      rec[i]=(char*)malloc((len+1)*sizeof(char));
      rec[i][len]=0;
      for (j=0;j<len;j++)
         rec[i][j]=tmp[len-j-1];
      if (l[i]=getl(str))
         r[i]=getr(str);
   }
   for (i=1;i<=n;i++)
   {
      for (j=0;j<p[i].l/2;j++)
      {
         p[i].str[j]^=p[i].str[p[i].l-j-1];
         p[i].str[p[i].l-j-1]^=p[i].str[j];
         p[i].str[j]^=p[i].str[p[i].l-j-1];
      }
      p[i].pos=i;
   }
   qs(1,n);
   for (i=1;i<=x;i++)
      if (l[i]&&(j=getl(rec[i])))
      {
         q[++s]=(struct case2){j-1,-1,l[i],r[i],i};
         q[++s]=(struct case2){getr(rec[i]),1,l[i],r[i],i};
      }
   qs2(1,s);
   for (i=1;i<=s;i++)
   {
      for (j=last+1;j<=q[i].pos;j++)
         ins(p[j].pos);
      last=q[i].pos;
      ans[q[i].num]+=q[i].s*(sum(q[i].r)-sum(q[i].l-1));
   }
   for (i=1;i<=x;i++)
      printf("%ld\n",ans[i]);
   return 0;
}
