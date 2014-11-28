#include<stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

long a[1000001]={0},upl[1000001]={0},downl[1000001]={0},upr[1000001]={0},downr[1000001]={0};
char str[8000005]={'\0'};

int main()
{
   long i,j,n,q,hill,dale;
   scanf("%ld",&q);
   while (q--)
   {
      scanf("%ld",&n);
      getchar();
      gets(str+1);
      j=0;
      for (i=1;i<=n;i++)
      {
         a[i]=0;
         if (str[++j]=='-')
         {
            for (j++;str[j]>='0'&&str[j]<='9';j++)
               a[i]=a[i]*10+str[j]-'0';
            a[i]=-a[i];
         }
         else
            for (;str[j]>='0'&&str[j]<='9';j++)
               a[i]=a[i]*10+str[j]-'0';
         if (a[i]>a[i-1]&&i>1)
            upl[i]=upl[i-1]+1;
         else
            upl[i]=0;
         if (a[i]<a[i-1]&&i>1)
            downl[i]=downl[i-1]+1;
         else
            downl[i]=0;
      }
      for (i=n;i>=1;i--)
      {
         if (a[i]>a[i+1]&&i<n)
            downr[i]=downr[i+1]+1;
         else
            downr[i]=0;
         if (a[i]<a[i+1]&&i<n)
            upr[i]=upr[i+1]+1;
         else
            upr[i]=0;
      }
      hill=dale=0;
      for (i=1;i<=n;i++)
      {
         if (min(upl[i],downr[i])>hill)
            hill=min(upl[i],downr[i]);
         if (min(downl[i],upr[i])>dale)
            dale=min(downl[i],upr[i]);
      }
      printf("%ld %ld\n",hill,dale);
   }
   return 0;
}
