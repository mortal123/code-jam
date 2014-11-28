#include <stdio.h>
#define NOW f[a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]][a[8]][a[9]]

long a[10]={0},f[3][3][3][3][3][3][3][3][3]={0},l[8][3]={{1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9},{3,5,7}};
char str[9]={'\0'};

long win(long x)
{
   long i;
   for (i=0;i<8;i++)
      if (a[l[i][0]]==x&&a[l[i][1]]==x&&a[l[i][2]]==x)
         return 1;
   return 0;
}

long dfs(long now)
{
   long i,t;
   if (win(1))
      NOW=1;
   if (win(2))
      NOW=2;
   if (!NOW&&now<0)
      NOW=3;
   if (NOW)
      return NOW;
   NOW=1+!(now&1);
   for (i=1;i<=9;i++)
      if (!a[i])
      {
         a[i]=1+(now&1);
         t=dfs(now-1);
         a[i]=0;
         if (t==1+(now&1))
            NOW=1+(now&1);
         else if (t==3&&NOW!=1+(now&1))
            NOW=3;
      }
   return NOW;
}

int main()
{
   long i;
   dfs(8);
   while (1)
   {
      gets(str+1);
      if (str[1]=='Q')
         break;
      memset(a,0,sizeof(a));
      for (i=1;i<=3;i++)
         if (str[i]!='.')
            a[i]=1+(str[i]=='0');
      gets(str+1);
      for (i=1;i<=3;i++)
         if (str[i]!='.')
            a[i+3]=1+(str[i]=='0');
      gets(str+1);
      for (i=1;i<=3;i++)
         if (str[i]!='.')
            a[i+6]=1+(str[i]=='0');
      if (!NOW)
         printf("Illegal position.\n");
      else if (NOW==1)
         printf("X wins.\n");
      else if (NOW==2)
         printf("0 wins.\n");
      else
         printf("Game is a draw.\n");
      scanf("\n");
   }
   return 0;
}
