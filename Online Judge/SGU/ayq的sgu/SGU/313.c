#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long v,s,pos;
}p[100001]={0,0,0};
long long sum[50001]={0};
long rec[50001]={0},d[50001]={0},ans[50001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].v>t.v)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].v<t.v)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,j,n,l,last=0,s=0,min=0,max=0;
   long long x=0;
   scanf("%ld%ld",&n,&l);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&p[i].v);
      p[i].pos=i;
      p[i].s=1;
   }
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&p[i+n].v);
      p[i+n].pos=i;
      p[i+n].s=-1;
   }
   qs(1,n<<1);
   for (i=1;i<=(n<<1);i++)
   {
      s+=p[i].s;
      min=min(min,s);
      max=max(max,s);
   }
   s=0;
   for (i=1;i<=(n<<1);i++)
   {
      rec[s-min]+=p[i].v-last;
      last=p[i].v;
      s+=p[i].s;
   }
   rec[s-min]+=l-last;
   sum[0]=rec[0];
   for (i=1;i<=max-min;i++)
      sum[i]=rec[i]+sum[i-1];
   for (i=0;(sum[i]<<1)<sum[max-min];i++);
   if (i<max-min&&sum[i+1]+sum[i]<sum[max-min])
      i++;
   for (j=0;j<=max-min;j++)
      x+=(long long)abb(i-j)*rec[j];
   printf("%I64d\n",x);
   s=j=0;
   while (s-min!=i)
      s+=p[++j].s;
   s=0;
   for (i=j+1;i<=2*n;i++)
      if (p[i].s==-1)
      {
         if (s<=0)
            d[-(--s)]=p[i].pos;
         else
            ans[d[s--]]=p[i].pos;
      }
      else if (s>=0)
         d[++s]=p[i].pos;
      else
         ans[p[i].pos]=d[-(s++)];
   for (i=1;i<=j;i++)
      if (p[i].s==-1)
      {
         if (s<=0)
            d[-(--s)]=p[i].pos;
         else
            ans[d[s--]]=p[i].pos;
      }
      else if (s>=0)
         d[++s]=p[i].pos;
      else
         ans[p[i].pos]=d[-(s++)];
   for (i=1;i<=n;i++)
      printf("%ld%c",ans[i],(i==n)?'\n':' ');
   return 0;
}
