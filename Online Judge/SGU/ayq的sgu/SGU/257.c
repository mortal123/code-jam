#include <stdio.h>

long num[8]={0},st[8]={0},use[100001]={0},r[3]={0},list[8][100001]={0},con[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
char str[5]={'\0'};
long a,b,c;

long check(long v1,long v2,long v3)
{
   long t;
   r[0]=a;
   r[1]=b;
   r[2]=c;
   for (st[1]=1;st[1]<=num[1]&&r[0]>1;st[1]++)
   {
      use[list[1][st[1]]]=0;
      r[0]-=2;
   }
   for (st[2]=1;st[2]<=num[2]&&r[1]>1;st[2]++)
   {
      use[list[2][st[2]]]=1;
      r[1]-=2;
   }
   for (st[4]=1;st[4]<=num[4]&&r[2]>1;st[4]++)
   {
      use[list[4][st[4]]]=2;
      r[2]-=2;
   }
   t=(1<<v1)+(1<<v2);
   for (st[t]=1;st[t]<=num[t]&&(r[v1]>1||r[v2]>1);st[t]++)
      if (r[v1]>1)
      {
         use[list[t][st[t]]]=v1;
         r[v1]-=2;
      }
      else
      {
         use[list[t][st[t]]]=v2;
         r[v2]-=2;
      }
   t=(1<<v2)+(1<<v3);
   for (st[t]=1;st[t]<=num[t]&&(r[v2]>1||r[v3]>1);st[t]++)
      if (r[v2]>1)
      {
         use[list[t][st[t]]]=v2;
         r[v2]-=2;
      }
      else
      {
         use[list[t][st[t]]]=v3;
         r[v3]-=2;
      }
   t=(1<<v3)+(1<<v1);
   for (st[t]=1;st[t]<=num[t]&&(r[v3]>1||r[v1]>1);st[t]++)
      if (r[v3]>1)
      {
         use[list[t][st[t]]]=v3;
         r[v3]-=2;
      }
      else
      {
         use[list[t][st[t]]]=v1;
         r[v1]-=2;
      }
   for (st[7]=1;st[7]<=num[7];st[7]++)
      if (r[0]>1||r[0]==1&&r[1]<2&&r[2]<2)
      {
         use[list[7][st[7]]]=0;
         r[0]-=2;
      }
      else if (r[1]>1||r[1]==1&&r[0]<2&&r[2]<2)
      {
         use[list[7][st[7]]]=1;
         r[1]-=2;
      }
      else
      {
         use[list[7][st[7]]]=2;
         r[2]-=2;
      }
   st[0]=1;
   for (t=0;t<7;t++)
      for (;st[t]<=num[t];st[t]++)
         if (r[0]>0)
         {
            use[list[t][st[t]]]=0;
            r[0]--;
         }
         else if (r[1]>0)
         {
            use[list[t][st[t]]]=1;
            r[1]--;
         }
         else
         {
            use[list[t][st[t]]]=2;
            r[2]--;
         }
   return r[0]<1&&r[1]<1&&r[2]<1;
}

int main()
{
   long i,j,n;
   scanf("%ld%ld%ld%ld\n",&a,&b,&c,&n);
   for (i=1;i<=n;i++)
   {
      gets(str);
      list[(str[0]=='B')+(str[1]=='B')*2+(str[2]=='B')*4][++num[(str[0]=='B')+(str[1]=='B')*2+(str[2]=='B')*4]]=i;
   }
   for (i=0;i<6;i++)
      if (check(con[i][0],con[i][1],con[i][2]))
      {
         for (j=1;j<=n;j++)
            if (!use[j])
               putchar('P');
            else if (use[j]==1)
               putchar('O');
            else
               putchar('S');
         putchar('\n');
         break;
      }
   if (i==6)
      printf("no solution\n");
   return 0;
}
