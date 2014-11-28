#include<stdio.h>
#define oo 10000

long a[10]={0},need[100]={0},d[10001]={0};
char hash[100]={'\0'};

int main()
{
   long i,up,down,dou,now,x,y,st=1,en=0;
   scanf("%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld",&a[1],&a[2],&a[3],&up,&a[4],&a[5],&a[6],&down,&a[7],&a[8],&a[9],&dou,&a[0],&x,&y);
   for (i=0;i<=99;i++)
   {
      if (i<=9)
      {
         if (a[i])
            need[i]=1;
         else
            need[i]=oo;
      }
      else
      {
         if (a[i%10]&&a[i/10]&&dou)
            need[i]=3;
         else
            need[i]=oo;
      }
   }
   need[x]=0;
   for (i=0;i<=99;i++)
      if (need[i]<oo)
      {
         d[++en]=i;
         hash[i]=1;
      }
   while (st<=en)
   {
      now=d[st++];
      hash[now]=0;
      if (up&&need[(now+1)%100]>need[now]+1)
      {
         need[(now+1)%100]=need[now]+1;
         if (!hash[(now+1)%100])
         {
            hash[(now+1)%100]=1;
            d[++en]=(now+1)%100;
         }
      }
      if (down&&need[(now+99)%100]>need[now]+1)
      {
         need[(now+99)%100]=need[now]+1;
         if (!hash[(now+99)%100])
         {
            hash[(now+99)%100]=1;
            d[++en]=(now+99)%100;
         }
      }
   }
   if (need[y]<oo)
      printf("%ld\n",need[y]);
   else
      printf("-1\n");
   return 0;
}
