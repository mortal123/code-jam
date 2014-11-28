#include<stdio.h>
#include<string.h>

long f[201][201][4]={0},p[4]={0},c[4][17][2]={0};
char str[205]={'\0'},trans[201]={'\0'};

int main()
{
   long i,j,k,a,b,l;
   trans['r']=1;
   trans['y']=2;
   trans['w']=3;
   for (i=0;i<=3;i++)
      scanf("%ld",&p[i]);
   for (i=0;i<=3;i++)
      for (j=1;j<=p[i];j++)
      {
         scanf("%s",str+1);
         c[i][j][0]=trans[str[1]];
         c[i][j][1]=trans[str[2]];
      }
   scanf("%s",str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      f[i][i][trans[str[i]]]=1;
   for (i=2;i<=l;i++)
      for (j=1;i+j-1<=l;j++)
         for (k=0;k<=3;k++)
         {
            for (a=j+1;a<=i+j-1;a++)
               for (b=1;b<=p[k];b++)
                  if (f[j][a-1][c[k][b][0]]&f[a][i+j-1][c[k][b][1]])
                  {
                     f[j][i+j-1][k]=1;
                     goto out;
                  }
            out:;
         }
   if (!(f[1][l][0]|f[1][l][1]|f[1][l][2]|f[1][l][3]))
      printf("Nobody");
   else
   {
      if (f[1][l][0])
         putchar('b');
      if (f[1][l][1])
         putchar('r');
      if (f[1][l][2])
         putchar('y');
      if (f[1][l][3])
         putchar('w');
   }
   putchar('\n');
   return 0;
}
