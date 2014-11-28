#include <stdio.h>

long a[300002]={0},c[150001]={0},rec[150001]={0};
char b[150005]={'\0'};
long tot;

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

void renew()
{
   long i;
   for (i=1;i<=tot;i++)
   {
      if (rec[i]>c[i])
         return;
      if (rec[i]<c[i])
         break;
   }
   for (i=1;i<=tot;i++)
      rec[i]=c[i];
}

int main()
{
   long i,j,k,t,x,q,n;
   scanf("%ld%ld%s",&n,&x,b+1);
   q=gcd(x,n);
   tot=n/q;
   for (t=1;t<=q;t++)
   {
      for (i=1;i<=tot;i++)
         a[i]=a[i+tot]=b[(long long)(i-1)*x%n+t]-'0';
      a[2*tot+1]=-1;
      i=j=1;
      while (i<=tot&&j<=tot)
      {
         if (i==j)
            j++;
         k=0;
         while (a[i+k]==a[j+k])
            k++;
         if (a[i+k]<a[j+k])
            i+=k+1;
         else
            j+=k+1;
      }
      if (i<=tot)
         k=i;
      else
         k=j;
      for (i=1;i<=tot;i++)
         c[i]=a[k+i-1];
      renew();
   }
   for (i=1;i<=q;i++)
      for (j=1;j<=tot;j++)
         printf("%ld",rec[j]);
   printf("\n");
   return 0;
}
