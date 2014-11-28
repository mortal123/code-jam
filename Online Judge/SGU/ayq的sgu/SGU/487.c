#include <stdio.h>

long e[10002]={0},next[10002]={0},last[10002]={0},stack[20002]={0},st[10002]={0},en[10002]={0};
long totm,top=0;

void add(long a,long b)
{
   e[++totm]=(b+3)/4;
   next[totm]=next[(a+3)/4];
   last[totm]=(a+3)/4;
   st[totm]=a;
   en[totm]=b;
   next[last[totm]]=last[next[totm]]=totm;
}

void del(long a)
{
   last[next[a]]=last[a];
   next[last[a]]=next[a];
}

void dfs(long now,long a,long b)
{
   long i;
   for (i=next[now];i;i=next[now])
   {
      del(i);
      del(i^1);
      dfs(e[i],st[i],en[i]);
   }
   stack[++top]=b;
   stack[++top]=a;
}

int main()
{
   long i,n,a,b;
   scanf("%ld",&n);
   totm=n+!(n&1);
   for (i=1;i<=2*n;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b);
      add(b,a);
   }
   dfs(1,0,0);
   if (top-2==4*n)
   {
      puts("Yes");
      for (i=top-2;i;i--)
         printf("%ld%c",stack[i],(i==1)?'\n':' ');
   }
   else
      puts("No");
   return 0;
}
