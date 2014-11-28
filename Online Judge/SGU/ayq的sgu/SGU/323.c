#include <stdio.h>
#define oo 2000000000

struct case1
{
   long a,b,v,num;
}p[200001]={0,0,0,0};
long f[2001][2001]={0},count[2001]={0},cost[2001]={0},rec[2001][2001]={0};
char str[100]={0};

long getf(long x,long y)
{
   if (f[x][y]==y)
      return y;
   return f[x][y]=getf(x,f[x][y]);
}

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
   long i,j,c,n,m,k,s,fa,fb;
   scanf("%ld%ld%ld\n",&n,&m,&k);
   for (i=1;i<=m;i++)
      for (j=1;j<=n;j++)
         f[i][j]=j;
   for (i=1;i<=k;i++)
   {
      c=0;
      gets(str+1);
      for (j=1;str[j]>='0'&&str[j]<='9';j++)
         p[i].a=p[i].a*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         p[i].b=p[i].b*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         c=c*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         p[i].v=p[i].v*10+str[j]-'0';
      p[i].num=i;
      fa=getf(c,p[i].a);
      fb=getf(c,p[i].b);
      if (fa!=fb)
      {
         f[c][fa]=fb;
         rec[c][++count[c]]=i;
      }
   }
   qs(1,k);
   cost[c=0]=oo;
   for (i=1;i<=m;i++)
   {
      s=count[i];
      count[i]=0;
      for (j=1;count[i]+s<n-1&&cost[i]<cost[c];j++)
      {
         fa=getf(i,p[j].a);
         fb=getf(i,p[j].b);
         if (fa!=fb)
         {
            f[i][fa]=fb;
            rec[i][++count[i]]=p[j].num;
            cost[i]+=p[j].v;
         }
      }
      if (count[i]+s==n-1&&cost[i]<cost[c])
         c=i;
   }
   printf("%ld %ld %ld\n",cost[c],c,count[c]);
   for (i=1;i<=count[c];i++)
      printf("%ld\n",rec[c][i]);
   return 0;
}
