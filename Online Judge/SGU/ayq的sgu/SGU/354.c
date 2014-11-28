#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long st,en,mid,min,flag;
}p[2401]={0,0,0,0,0};
long head[360001]={0},du[360001]={0},d[360001]={0},e[720001]={0},next[720001]={0},mat[601][601]={0},a[601]={0};
char str[2501]={0};
long totm=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   du[b]++;
}

void build(long now,long st,long en)
{
   long mid=(st+en)>>1;
   p[now].st=st;
   p[now].en=en;
   p[now].mid=mid;
   if (st<en-1)
   {
      build(now<<1,st,mid);
      build((now<<1)+1,mid,en);
   }
}

void rebuild(long now)
{
   p[now].flag=0;
   if (p[now].st<p[now].en-1)
   {
      rebuild(now<<1);
      rebuild((now<<1)+1);
      p[now].min=min(p[now<<1].min,p[(now<<1)+1].min);
   }
   else
      p[now].min=a[p[now].st];
}

void ins(long now,long st,long en,long flag)
{
   if (!flag&&p[now].st==st&&p[now].en==en)
   {
      p[now].min--;
      p[now].flag--;
   }
   else if (flag&&p[now].st==p[now].en-1)
      p[now].min=oo;
   else
   {
      if (en<=p[now].mid)
         ins(now<<1,st,en,flag);
      else if (st>=p[now].mid)
         ins((now<<1)+1,st,en,flag);
      else
      {
         ins(now<<1,st,p[now].mid,flag);
         ins((now<<1)+1,p[now].mid,en,0);
      }
      p[now].min=min(p[now<<1].min,p[(now<<1)+1].min);
   }
}

long ask(long now)
{
   if (p[now].st==p[now].en-1)
      return p[now].st;
   if (p[now].flag)
   {
      p[now<<1].flag+=p[now].flag;
      p[(now<<1)+1].flag+=p[now].flag;
      p[now<<1].min+=p[now].flag;
      p[(now<<1)+1].min+=p[now].flag;
      p[now].flag=0;
   }
   if (p[(now<<1)+1].min==0)
      return ask((now<<1)+1);
   return ask(now<<1);
}

int main()
{
   long i,j,k,n,pos,last,now,st=1,en=0;
   scanf("%ld\n",&n);
   build(1,1,n+1);
   for (i=1;i<=n;i++)
   {
      k=0;
      gets(str+1);
      for (j=1;j<=n;j++)
         for (k++;str[k]>='0'&&str[k]<='9';k++)
            mat[i][j]=mat[i][j]*10+str[k]-'0';
   }
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=n;j++)
         a[j]=mat[j][i];
      rebuild(1);
      last=0;
      for (j=1;j<=n&&p[1].min==0;j++)
      {
         pos=ask(1);
         if (last)
            add((last-1)*n+i,(pos-1)*n+i);
         last=pos;
         ins(1,pos,n+1,1);
      }
      if (j<=n)
      {
         printf("0\n");
         goto end;
      }
   }
   gets(str+1);
   for (i=1;i<=n;i++)
   {
      k=0;
      gets(str+1);
      for (j=1;j<=n;j++)
      {
         a[j]=0;
         for (k++;str[k]>='0'&&str[k]<='9';k++)
            a[j]=a[j]*10+str[k]-'0';
      }
      rebuild(1);
      last=0;
      for (j=1;j<=n&&p[1].min==0;j++)
      {
         pos=ask(1);
         if (last)
            add((i-1)*n+last,(i-1)*n+pos);
         last=pos;
         ins(1,pos,n+1,1);
      }
      if (j<=n)
      {
         printf("0\n");
         goto end;
      }
   }
   for (i=1;i<=n*n;i++)
      if (!du[i])
         d[++en]=i;
   while (st<=en)
   {
      now=d[st];
      mat[(now-1)/n+1][(now-1)%n+1]=n*n-(st++)+1;
      for (i=head[now];i;i=next[i])
      {
         du[e[i]]--;
         if (!du[e[i]])
            d[++en]=e[i];
      }
   }
   if (en==n*n)
      for (i=1;i<=n;i++)
      {
         str[k=2500]=0;
         for (j=n;j>=1;j--)
         {
            while (mat[i][j])
            {
               str[--k]=mat[i][j]%10+'0';
               mat[i][j]/=10;
            }
            if (j>1)
               str[--k]=' ';
         }
         puts(str+k);
      }
   else
      printf("0\n");
   end:
   return 0;
}
