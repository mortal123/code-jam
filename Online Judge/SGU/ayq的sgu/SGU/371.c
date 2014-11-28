#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

long cicle[100001][21]={0},line[100001][2]={0};

int main()
{
   long i,j,k,n,m,c,last,tmp,s=0,s2=0;
   scanf("%ld%ld",&n,&m);
   c=m-n+1;
   if (c>0&&2*c+1<=n&&17*c+3>=n)
   {
      for (i=1;i<=c;i++)
         if (i==1)
         {
            for (j=3;j<=19;j++)
               if (2*(c-1)<=n-j&&17*(c-1)+1>=n-j)
               {
                  n-=j;
                  cicle[i][0]=min(j,10);
                  tmp=s;
                  for (k=1;k<=cicle[i][0];k++)
                     cicle[i][k]=++s;
                  last=s;
                  for (k=1;k<=j-cicle[i][0];k++)
                  {
                     line[++s2][0]=++s;
                     line[s2][1]=tmp+k;
                  }
                  break;
               }
         }
         else
            for (j=2;j<=17;j++)
               if (2*(c-i)<=n-j&&17*(c-i)+1>=n-j)
               {
                  n-=j;
                  cicle[i][0]=min(j,9);
                  tmp=s;
                  for (k=1;k<=cicle[i][0];k++)
                     cicle[i][k]=++s;
                  cicle[i][cicle[i][0]+1]=last;
                  last=s;
                  for (k=1;k<=j-cicle[i][0];k++)
                  {
                     line[++s2][0]=++s;
                     line[s2][1]=tmp+k;
                  }
                  cicle[i][0]++;
                  break;
               }
      if (n)
      {
         line[++s2][0]=last;
         line[s2][1]=++s;
      }
      printf("%ld\n",c);
      for (i=1;i<=c;i++)
      {
        printf("%ld",cicle[i][0]);
        for (j=1;j<=cicle[i][0];j++)
           printf(" %ld",cicle[i][j]);
        puts("");
      }
      printf("%ld\n",s2);
      for (i=1;i<=s2;i++)
         printf("%ld %ld\n",line[i][0],line[i][1]);
   }
   else
      puts("No solution");
   return 0;
}
