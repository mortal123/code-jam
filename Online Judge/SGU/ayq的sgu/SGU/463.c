#include<stdio.h>
#include<string.h>

long v[103][103]={0};
char hash[103][103]={'\0'},str[505]={'\0'};

int main()
{
   long i,j,n,m,l,x=1,y=1,sign=0,ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         scanf("%1ld",&v[i][j]);
   getchar();
   gets(str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
   {
      if (str[i]=='R')
         sign=(sign+1)%4;
      else if (str[i]=='L')
         sign=(sign+3)%4;
      else
      {
         if (sign==0)
         {
            if (hash[x][y])
               ans+=v[x][y]/2;
            else
               ans+=v[x][y];
            if (hash[x-1][y])
               ans+=v[x-1][y]/2;
            else
               ans+=v[x-1][y];
            hash[x][y]=hash[x-1][y]=1;
            y++;
         }
         else if (sign==1)
         {
            if (hash[x][y])
               ans+=v[x][y]/2;
            else
               ans+=v[x][y];
            if (hash[x][y-1])
               ans+=v[x][y-1]/2;
            else
               ans+=v[x][y-1];
            hash[x][y]=hash[x][y-1]=1;
            x++;
         }
         else if (sign==2)
         {
            if (hash[x][y-1])
               ans+=v[x][y-1]/2;
            else
               ans+=v[x][y-1];
            if (hash[x-1][y-1])
               ans+=v[x-1][y-1]/2;
            else
               ans+=v[x-1][y-1];
            hash[x][y-1]=hash[x-1][y-1]=1;
            y--;
         }
         else
         {
            if (hash[x-1][y])
               ans+=v[x-1][y]/2;
            else
               ans+=v[x-1][y];
            if (hash[x-1][y-1])
               ans+=v[x-1][y-1]/2;
            else
               ans+=v[x-1][y-1];
            hash[x-1][y]=hash[x-1][y-1]=1;
            x--;
         }
      }
   }
   printf("%ld\n",ans);
   return 0;
}
