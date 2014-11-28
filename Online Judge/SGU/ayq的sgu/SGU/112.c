#include<stdio.h>

long x[210]={0},y[210]={0};

long cmp()
{
   long i;
   for (i=205;i>=1;i--)
   {
      if (x[i]>y[i])
         return 1;
      else if (x[i]<y[i])
         return -1;
   }
   return 0;
}

int main()
{
   long i,j,a,b;
   x[1]=y[1]=1;
   scanf("%ld%ld",&a,&b);
   for (i=1;i<=b;i++)
      for (j=1;j<=205;j++)
      {
         x[j]=x[j]*a+x[j-1]/10;
         x[j-1]%=10;
      }
   for (i=1;i<=a;i++)
      for (j=1;j<=205;j++)
      {
         y[j]=y[j]*b+y[j-1]/10;
         y[j-1]%=10;
      }
   if (cmp()>=0)
   {
      for (i=1;i<=205;i++)
      {
         x[i]=x[i]-y[i]+(x[i-1]+20)/10-2;
         x[i-1]=(x[i-1]+20)%10;
      }
      j=0;
      for (i=205;i>=1;i--)
      {
         if (x[i])
            j=1;
         if (j)
            printf("%ld",x[i]);
      }
      if (!j)
         printf("0");
      printf("\n");
   }
   else
   {
      printf("-");
      for (i=1;i<=205;i++)
      {
         y[i]=y[i]-x[i]+(y[i-1]+20)/10-2;
         y[i-1]=(y[i-1]+20)%10;
      }
      j=0;
      for (i=205;i>=1;i--)
      {
         if (y[i])
            j=1;
         if (j)
            printf("%ld",y[i]);
      }
      printf("\n");
   }
   return 0;
}
