#include<stdio.h>

long a[301][301]={0},b[301][301]={0},c[301][301]={0},e[720001]={0},next[720001]={0},head[1201]={0},dfn[1201]={0},low[1201]={0},stack[1201]={0},p[1201]={0},last[1201]={0},co[1201]={0},e2[720001]={0},next2[720001]={0},head2[1201]={0},du[1201]={0},d[1201]={0},oppo[1201]={0};
char in[1201]={'\0'},paint[1201]={'\0'};
long n,m,totm,tot,color,top=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void add2(long a,long b)
{
   e2[++totm]=b;
   next2[totm]=head2[a];
   head2[a]=totm;
}

void targan(long now)
{
   long i,flag;
   for (i=now;i;)
   {
      if (!p[i])
      {
         stack[++top]=i;
         in[i]=1;
         dfn[i]=low[i]=++tot;
         p[i]=head[i];
      }
      else
      {
         if (low[e[p[i]]]<low[i])
            low[i]=low[e[p[i]]];
         p[i]=next[p[i]];
      }
      for (flag=1;p[i];p[i]=next[p[i]])
      {
         if (!dfn[e[p[i]]])
         {
            last[e[p[i]]]=i;
            i=e[p[i]];
            flag=0;
            break;
         }
         else if (in[e[p[i]]]&&dfn[e[p[i]]]<low[i])
            low[i]=dfn[e[p[i]]];
      }
      if (flag)
      {
         if (low[i]==dfn[i])
         {
            color++;
            do
            {
               co[stack[top]]=color;
               in[stack[top--]]=0;
            }while(stack[top+1]!=i);
         }
         i=last[i];
      }
   }
}

long work()
{
   long i,j,k,l,now,st=1,en=0;
   memset(p,0,sizeof(p));
   memset(du,0,sizeof(du));
   memset(dfn,0,sizeof(dfn));
   memset(last,0,sizeof(last));
   memset(head,0,sizeof(head));
   memset(head2,0,sizeof(head2));
   memset(paint,0,sizeof(paint));
   totm=tot=color=0;
   for (i=2;i<=m;i++)
      for (j=2;j<=n;j++)
         for (k=0;k<=1;k++)
            for (l=0;l<=1;l++)
               if (c[j][i]+(2*(i&1)-1)*l+(2*(j&1)-1)*k+(2*((i+j)&1)-1)*a[1][1]!=0&&c[j][i]+(2*(i&1)-1)*l+(2*(j&1)-1)*k+(2*((i+j)&1)-1)*a[1][1]!=1)
               {
                  add(k*(m+n-2)+i-1,(!l)*(m+n-2)+j+m-2);
                  add(l*(m+n-2)+j+m-2,(!k)*(m+n-2)+i-1);
               }
   for (i=1;i<=2*(m+n-2);i++)
      if (!dfn[i])
         targan(i);
   for (i=1;i<=n+m-2;i++)
   {
      if (co[i]==co[i+n+m-2])
         return 0;
      oppo[co[i]]=co[i+n+m-2];
      oppo[co[i+n+m-2]]=co[i];
   }
   totm=0;
   for (i=1;i<=2*(n+m-2);i++)
      for (j=head[i];j;j=next[j])
         if (co[i]!=co[e[j]])
         {
            add2(co[e[j]],co[i]);
            du[co[i]]++;
         }
   for (i=1;i<=color;i++)
      if (!du[i])
         d[++en]=i;
   while (st<=en)
   {
      now=d[st++];
      if (!paint[oppo[now]])
         paint[now]=1;
      else
         paint[now]=2;
      for (i=head2[now];i;i=next2[i])
      {
         du[e2[i]]--;
         if (!du[e2[i]])
            d[++en]=e2[i];
      }
   }
   for (i=2;i<=m;i++)
   {
      if (paint[co[i-1]]==1)
         a[1][i]=0;
      else
         a[1][i]=1;
   }
   for (i=2;i<=n;i++)
   {
      if (paint[co[i+m-2]]==1)
         a[i][1]=0;
      else
         a[i][1]=1;
   }
   for (i=2;i<=n;i++)
      for (j=2;j<=m;j++)
         a[i][j]=b[i-1][j-1]-a[i-1][j-1]-a[i][j-1]-a[i-1][j];
   return 1;
}

void print()
{
   long i,j;
   for (i=1;i<=n;i++)
   {
      for (j=1;j<m;j++)
         printf("%ld",a[i][j]);
      printf("%ld\n",a[i][m]);
   }
}

int main()
{
   long i,j;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<n;i++)
      for (j=1;j<m;j++)
      {
         scanf("%1ld",&b[i][j]);
         c[i+1][j+1]=b[i][j]-c[i][j]-c[i+1][j]-c[i][j+1];
      }
   if (work())
      print();
   else
   {
      a[1][1]=1;
      if (work())
         print();
      else
         printf("CORRUPT\n");
   }
   return 0;
}
