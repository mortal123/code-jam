#include <stdio.h>
#define oo 1000000000

int e[8000005],d[16777217],tmp[20001],dis[4000005],last[4000001],*ro[10005],len[10005],sum[10005],r1[10005][11],r2[10005][11],tot[10005],pos[10005][1025],head[4000005],next[8000005],head2[1005],e2[10005],next2[10005],v2[10005];
short v[8000005],num[8000005];
char hash[4000005];
int totm=0,o=2;

void add(int a,int b,int c,int d)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
   num[totm]=d;
}

void add2(int a,int b)
{
   e2[++totm]=b;
   next2[totm]=head2[a];
   head2[a]=totm;
}

int check(int a,int b,int c)
{
   int i;
   for (i=1;r1[a][i]!=c;i++);
   return b&(1<<i-1);
}

int main()
{
   int i,j,k,l,n,m,r,s,t,a,b,c,va,vb,now,st=100000000,en=100000000;
   scanf("%d%d%d%d%d",&n,&m,&r,&s,&t);
   for (i=1;i<=m;i++)
   {
      scanf("%d%d%d",&a,&b,&v2[i]);
      add2(a,b);
   }
   add2(++n,s);
   pos[++m][0]=1;
   totm=0;
   dis[2]=oo;
   for (i=1;i<=r;i++)
   {
      scanf("%d",&len[i]);
      ro[i]=(int*)malloc((len[i]+2)*sizeof(int));
      for (j=1;j<=len[i];j++)
      {
         scanf("%d",&ro[i][j]);
         sum[i]+=v2[ro[i][j]];
         r1[ro[i][j]][++tot[ro[i][j]]]=i;
         r2[ro[i][j]][tot[ro[i][j]]]=j;
      }
   }
   for (i=1;i<m;i++)
      for (j=0;j<1<<tot[i];j++)
      {
         pos[i][j]=++o;
         dis[o]=oo;
      }
   for (i=1;i<=n;i++)
      for (j=head2[i];j;j=next2[j])
         for (k=0;k<1<<tot[j];k++)
         {
            for (l=head2[e2[j]];l;l=next2[l])
            {
               va=v2[l];
               vb=0;
               for (a=1;a<=tot[l];a++)
                  if (r2[l][a]==1||ro[r1[l][a]][r2[l][a]-1]==j&&check(j,k,r1[l][a]))
                     if (r2[l][a]==len[r1[l][a]])
                        va+=sum[r1[l][a]];
                     else
                        vb+=(1<<a-1);
               add(pos[j][k],pos[l][vb],va,l);
            }
            if (e2[j]==t)
               add(pos[j][k],2,0,0);
         }
   d[st&16777215]=1;
   while (st<=en)
   {
      now=d[(st++)&16777215];
      hash[now]=0;
      for (i=head[now];i;i=next[i])
         if (dis[e[i]]>dis[now]+v[i])
         {
            dis[e[i]]=dis[now]+v[i];
            last[e[i]]=now;
            if (!hash[e[i]]&&dis[e[i]]<dis[2])
            {
               hash[e[i]]=1;
               if (dis[e[i]]<dis[d[st&16777215]])
                  d[(--st)&16777215]=e[i];
               else
                  d[(++en)&16777215]=e[i];
            }
         }
   }
   if (dis[2]>=oo)
      puts("-1");
   else
   {
      o=0;
      for (i=last[2];i;i=last[i])
         tmp[++o]=i;
      printf("%d\n%d\n",dis[2],o-1);
      for (i=o;i>1;i--)
      {
         for (j=head[tmp[i]];e[j]!=tmp[i-1];j=next[j]);
         printf("%d%c",num[j],(i==2)?'\n':' ');
      }
   }
   return 0;
}
