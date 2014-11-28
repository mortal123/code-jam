#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long head[200001]={0},e[400001]={0},next[400001]={0},num[400001]={0},ans[200001]={0};
char choose[400001]={'\0'},str[51]={'\0'};
long totm=0,tot=0;

void add(long a,long b,long c,char d)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   num[totm]=c;
   choose[totm]=d;
}

long dfs(long now,long layer,long last)
{
   long i,t,s=layer>>1;
   for (i=head[now];i;i=next[i])
      if (e[i]!=last)
      {
         t=dfs(e[i],layer+1,now);
         if (t==layer||choose[i])
         {
            if (!choose[i])
               ans[++tot]=num[i];
            t--;
         }
         s=max(s,t);
      }
   return s;
}

int main()
{
   long i,j,n,a,b;
   scanf("%ld\n",&n);
   for (i=1;i<n;i++)
   {
      gets(str);
      a=b=0;
      for (j=0;str[j]>='0'&&str[j]<='9';j++)
         a=a*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         b=b*10+str[j]-'0';
      add(a,b,i,str[j+1]=='p');
      add(b,a,i,str[j+1]=='p');
   }
   dfs(1,1,0);
   printf("%ld\n",tot);
   for (i=1;i<=tot;i++)
      printf("%ld%c",ans[i],(i==tot)?'\n':' ');
   return 0;
}
