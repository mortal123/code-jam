#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long l;
   long a[505];
}p[1001]={{0},{0}};
char str[505]={'\0'};

long cmp(struct case1 a,struct case1 b)
{
   long i;
   if (a.l>b.l)
      return 1;
   if (a.l<b.l)
      return -1;
   for (i=a.l;i>=1;i--)
   {
      if (a.a[i]>b.a[i])
         return 1;
      if (a.a[i]<b.a[i])
         return -1;
   }
   return 0;
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
      while (i<j&&cmp(p[j],t)>0)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&cmp(p[i],t)<0)
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
   long i,j,n;
   struct case1 a;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%s",str+1);
      p[i].l=strlen(str+1);
      for (j=1;j<=p[i].l;j++)
         p[i].a[j]=str[p[i].l-j+1]-'0';
      while (p[i].l>=2&&p[i].a[p[i].l]==0)
         p[i].l--;
   }
   qs(1,n);
   for (i=1;i<=n-2;i++)
   {
      memset(a.a,0,sizeof(a.a));
      a.l=max(p[i].l,p[i+1].l)+1;
      for (j=1;j<=a.l;j++)
      {
         a.a[j]=p[i].a[j]+p[i+1].a[j]+a.a[j-1]/10;
         a.a[j-1]%=10;
      }
      while (a.l>=2&&a.a[a.l]==0)
         a.l--;
      if (cmp(a,p[i+2])>0)
         break;
   }
   if (i<=n-2)
   {
      for (j=p[i].l;j>=1;j--)
         printf("%ld",p[i].a[j]);
      printf(" ");
      for (j=p[i+1].l;j>=1;j--)
         printf("%ld",p[i+1].a[j]);
      printf(" ");
      for (j=p[i+2].l;j>=1;j--)
         printf("%ld",p[i+2].a[j]);
      printf("\n");
   }
   else
      printf("0 0 0\n");
   return 0;
}
