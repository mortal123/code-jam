#include <stdio.h>
#define oo 1000000000
#define cj(x1,y1,x2,y2) ((long long)(x1)*(y2)-(long long)(x2)*(y1))

struct case1
{
   long x,y;
}p[301]={0,0};
long du[601]={0},d[301]={0},rec[305]={0},l[305]={0},con[601][601]={0},mat[601][601]={0},pos[601][601]={0},dis[601]={0},gap[601]={0},last[601]={0},laste[601]={0},head[601]={0},e[602]={0},next[602]={0},r[602]={0},num[602]={0};
char hash[601][601]={0},h2[601]={0};
long X1,Y1,X2,Y2,n,now,tot=0,s=1,totm=1,S=1,T=1;

void add(long a,long b,long c,long d)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   r[totm]=c;
   num[totm]=d;
}

long find(long x,long y)
{
   long i;
   for (i=1;i<=tot;i++)
      if (p[i].x==x&&p[i].y==y)
         return i;
   p[++tot]=(struct case1){x,y};
   return tot;
}

void check(long x,long y,long m,long rec,long *t)
{
   long i,flag=0,x2=20731,y2=-18727;
   for (i=1;i<m;i++)
      flag^=(cj(x2-x,y2-y,p[l[i]].x-x,p[l[i]].y-y)*cj(x2-x,y2-y,p[l[i+1]].x-x,p[l[i+1]].y-y)<0&&cj(p[l[i+1]].x-p[l[i]].x,p[l[i+1]].y-p[l[i]].y,x-p[l[i]].x,y-p[l[i]].y)*cj(p[l[i+1]].x-p[l[i]].x,p[l[i+1]].y-p[l[i]].y,x2-p[l[i]].x,y2-p[l[i]].y)<0);
   if (flag)
      *t=rec;
}

void dfs(long x,long y,long last,long num,long long sum)
{
   long i,c1,c2,c3,t=0;
   l[num]=y;
   if (x==y)
   {
      if (sum>0)
      {
         now=++s;
         if (S==1)
            check(X1,Y1,num,now,&S);
         if (T==1)
            check(X2,Y2,num,now,&T);
      }
      else
         now=1;
   }
   else
   {
      for (i=1;i<=tot;i++)
         if (i!=last&&mat[y][i])
            if (!t)
               t=i;
            else
            {
               c1=cj(p[last].x-p[y].x,p[last].y-p[y].y,p[t].x-p[y].x,p[t].y-p[y].y);
               c2=cj(p[last].x-p[y].x,p[last].y-p[y].y,p[i].x-p[y].x,p[i].y-p[y].y);
               c3=cj(p[i].x-p[y].x,p[i].y-p[y].y,p[t].x-p[y].x,p[t].y-p[y].y);
               if (c1<=0&&c2>0||(c1>=0&&c2>=0||c1<=0&&c2<=0)&&c3>0)
                  t=i;
            }
      hash[y][t]=1;
      dfs(x,t,y,num+1,sum+cj(p[t].x-p[x].x,p[t].y-p[x].y,p[y].x-p[x].x,p[y].y-p[x].y));
      con[y][t]=now;
   }
}

void fill(long x)
{
   long i;
   h2[x]=1;
   for (i=head[x];i;i=next[i])
      if (r[i]&&!h2[e[i]])
         fill(e[i]);
}

int main()
{
   long i,j,a,b,v,min,ss=0,ans=0,st=1,en=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld%ld%ld%ld",&X1,&Y1,&X2,&Y2,&v);
      a=find(X1,Y1);
      b=find(X2,Y2);
      mat[a][b]=mat[b][a]=v;
      pos[a][b]=pos[b][a]=i;
      du[a]++;
      du[b]++;
   }
   for (i=1;i<=tot;i++)
      if (du[i]==1)
         d[++en]=i;
   while (st<=en)
   {
      for (i=1;i<=tot;i++)
         if (mat[d[st]][i])
         {
            du[i]--;
            mat[d[st]][i]=mat[i][d[st]]=0;
            if (du[i]==1)
               d[++en]=i;
         }
      st++;
   }
   scanf("%ld%ld%ld%ld",&X1,&Y1,&X2,&Y2);
   for (i=1;i<=tot;i++)
      for (j=1;j<=tot;j++)
         if (mat[i][j]&&!hash[i][j])
         {
            hash[i][j]=1;
            l[1]=i;
            dfs(i,j,i,2,0);
            con[i][j]=now;
         }
   for (i=1;i<tot;i++)
      for (j=i+1;j<=tot;j++)
         if (con[i][j])
         {
            add(con[i][j],con[j][i],mat[i][j],pos[i][j]);
            add(con[j][i],con[i][j],mat[i][j],pos[i][j]);
         }
   gap[0]=s;
   for (i=S;dis[S]<s;)
   {
      for (j=head[i];j;j=next[j])
         if (r[j]&&dis[e[j]]==dis[i]-1)
         {
            last[e[j]]=i;
            laste[e[j]]=j;
            i=e[j];
            break;
         }
      if (i==T)
      {
         for (min=oo;last[i];i=last[i])
            if (r[laste[i]]<min)
               min=r[laste[i]];
         ans+=min;
         for (i=T;last[i];i=last[i])
         {
            r[laste[i]]-=min;
            r[laste[i]^1]+=min;
         }
      }
      else if (!j)
      {
         if (gap[dis[i]]==1)
            break;
         min=oo;
         for (j=head[i];j;j=next[j])
            if (r[j]&&dis[e[j]]<min)
               min=dis[e[j]];
         min++;
         if (min>s)
            min=s;
         gap[dis[i]]--;
         dis[i]=min;
         gap[dis[i]]++;
         if (last[i])
            i=last[i];
      }
   }
   fill(S);
   for (i=1;i<=s;i++)
      if (h2[i])
         for (j=head[i];j;j=next[j])
            if (!h2[e[j]])
               rec[++ss]=num[j];
   printf("%ld\n%ld\n",ans,ss);
   for (i=1;i<=ss;i++)
      printf("%ld%c",rec[i],(i==ss)?'\n':' ');
   return 0;
}
