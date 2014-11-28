#include <stdio.h>

void work(int st,int en,int k,int flag)
{
   int i;
   if (!flag)
   {
      if (st<=en)
      {
         if (k==1||st==en)
         {
            for (i=st;i<en;i++)
               printf("++%d",i);
            printf("-%d",en);
         }
         else
         {
            work(en,st+1,k-1,1);
            printf("-%d",st);
            work(en,st+1,k,0);
         }
      }
      else
      {
         if (k==1)
         {
            for (i=st;i>en;i--)
               printf("--%d",i);
            printf("-%d",en);
         }
         else
         {
            work(en,st-1,k-1,1);
            printf("-%d",st);
            work(en,st-1,k,0);
         }
      }
   }
   else if (st<=en)
   {
      if (k==1||st==en)
      {
         printf("+%d",en);
         for (i=en;i>st;i--)
            printf("--%d",i);
      }
      else
      {
         work(en,st+1,k,1);
         printf("+%d",st);
         work(en,st+1,k-1,0);
      }
   }
   else
   {
      if (k==1)
      {
         printf("+%d",en);
         for (i=en;i<st;i++)
            printf("++%d",i);
      }
      else
      {
         work(en,st-1,k,1);
         printf("+%d",st);
         work(en,st-1,k-1,0);
      }
   }
}

int main()
{
   int n,k;
   scanf("%d%d",&n,&k);
   printf("+1");
   work(1,n,k,0);
   puts("");
   return 0;
}
