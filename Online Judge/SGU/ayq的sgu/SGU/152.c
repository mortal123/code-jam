#include<stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=0.0000001)

double a[10001]={0};
long b[10001]={0};

int main()
{
   long i,n,tot=0,s=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&b[i]);
      s+=b[i];
   }
   for (i=1;i<=n;i++)
   {
      a[i]=b[i]*100.0/s;
      b[i]=a[i];
   }
   s=0;
   for (i=1;i<=n;i++)
   {
      if (!zero(a[i]-b[i]))
         tot++;
      s+=b[i];
   }
   if (s>100||s+tot<100)
      printf("No solution\n");
   else
   {
      tot=1;
      for (i=1;i<=100-s;i++)
      {
         while (zero(a[tot]-b[tot]))
            tot++;
         b[tot]++;
         tot++;
      }
      printf("%ld",b[1]);
      for (i=2;i<=n;i++)
         printf(" %ld",b[i]);
      printf("\n");
   }
   return 0;
}
