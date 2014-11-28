#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long num;
   char a[22];
}p[50001]={{0},{'\0'}};
char name[50001][22]={'\0'};

void qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&strcmp(p[j].a,t.a)>0)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&strcmp(p[i].a,t.a)<0)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y;
   char t[22];
   strcpy(t,name[(x+y)>>1]);
   if (x>=y)
      return;
   strcpy(name[(x+y)>>1],name[x]);
   while (i<j)
   {
      while (i<j&&strcmp(name[j],t)>0)
         j--;
      if (i<j)
         strcpy(name[i++],name[j]);
      while (i<j&&strcmp(name[i],t)<0)
         i++;
      if (i<j)
         strcpy(name[j--],name[i]);
   }
   strcpy(name[i],t);
   qs2(x,i-1);
   qs2(i+1,y);
}

int main()
{
   long i,n,l,r,mid,m=0,last=1;
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
   {
      p[i].num=i;
      gets(p[i].a);
   }
   qs1(1,n);
   for (i=1;i<=n;i++)
   {
      gets(name[i]);
      l=0;
      r=n;
      while (l<r-1)
      {
         mid=(l+r)>>1;
         if (strcmp(p[mid].a,name[i])>=0)
            r=mid;
         else
            l=mid;
      }
      m=max(m,p[r].num);
      if (m==i)
      {
         qs2(last,i);
         last=i+1;
         m=0;
      }
   }
   for (i=1;i<=n;i++)
      puts(name[i]);
   return 0;
}
