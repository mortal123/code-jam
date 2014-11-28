#include <stdio.h>
#include <math.h>
#define mod 20000007
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   int sign;
   int a[13];
   double v;
}d[1300001];
int head[20000007],e[1300001][13],next[1300001],c[10001][14],tt[10001],a[10001],ans[101];
double dc[10001][14];
int n,m,tot=1,totm=0;

void qs(long x,long y)
{
   long i=x,j=y,t=a[(x+y)>>1];
   if (x>=y)
      return;
   a[(x+y)>>1]=a[x];
   while (i<j)
   {
      while (i<j&&abb(a[j])>abb(t))
         j--;
      if (i<j)
         a[i++]=a[j];
      while (i<j&&abb(a[i])<abb(t))
         i++;
      if (i<j)
         a[j--]=a[i];
   }
   a[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void print(int tmp[])
{
   int i,j,l=1;
   ans[1]=1;
   for (i=0;i<m;i++)
   {
      l+=6;
      for (j=1;j<=l;j++)
      {
         ans[j]=ans[j]*abb(a[tmp[i]])+ans[j-1]/10;
         ans[j-1]%=10;
      }
      while (!ans[l])
         l--;
   }
   for (i=l;i>=2;i--)
      printf("%d",ans[i]);
   printf("%d\n",ans[1]);
}

void up(int x,int flag)
{
   struct case1 t;
   while (x>1)
      if ((d[x>>1].v<d[x].v)^flag)
      {
         t=d[x>>1];
         d[x>>1]=d[x];
         d[x]=t;
         x>>=1;
      }
      else
         break;
}

void down(int x,int flag)
{
   struct case1 t;
   int y;
   while (x<<1<=tot)
   {
      y=x<<1;
      if (y<tot&&((d[y+1].v>d[y].v)^flag))
         y++;
      if ((d[y].v>d[x].v)^flag)
      {
         t=d[x];
         d[x]=d[y];
         d[y]=t;
         x=y;
      }
      else
         break;
   }
}

int key(int tmp[])
{
   int i,s=0;
   for (i=0;i<m;i++)
      s=((long long)s*n+tmp[i]-1)%mod;
   return s;
}

void add(int a,int b[])
{
   int i;
   totm++;
   for (i=0;i<m;i++)
      e[totm][i]=b[i];
   next[totm]=head[a];
   head[a]=totm;
}

int cmp(int a[],int b[])
{
   int i;
   for (i=0;i<m;i++)
      if (a[i]!=b[i])
         return 0;
   return 1;
}

int check(int tmp[])
{
   int i,y=key(tmp);
   for (i=head[y];i&&!cmp(e[i],tmp);i=next[i]);
   if (i)
      return 0;
   add(y,tmp);
   return 1;
}

int main()
{
   int i,j,k,t,z=0;
   struct case1 tmp,tmp2;
   scanf("%d%d%d",&n,&m,&k);
   for (i=0;i<=n;i++)
   {
      dc[i][0]=c[i][0]=1;
      for (j=1;j<=min(i,m);j++)
      {
         c[i][j]=c[i-1][j]+c[i-1][j-1];
         dc[i][j]=dc[i-1][j]+dc[i-1][j-1];
      }
   }
   for (i=1;i<=n;i++)
      scanf("%d",&a[i]);
   qs(1,n);
   for (i=1;i<=n;i++)
      z+=!a[i];
   if (n-z<m)
   {
      puts("0");
      goto end;
   }
   tt[z]=z;
   for (i=z+1;i<=n;i++)
      if (a[i]>0)
         tt[i]=i;
      else
         tt[i]=tt[i-1];
   for (i=0;i<m;i++)
   {
      d[1].a[i]=n-m+i+1;
      d[1].v+=log(abb(a[n-m+i+1]));
      d[1].sign+=(a[n-m+i+1]<0);
   }
   while (tot)
   {
      if (!(d[1].sign&1))
      {
         k--;
         if (!k)
         {
            print(d[1].a);
            goto end;
         }
      }
      tmp=d[1];
      d[1]=d[tot--];
      down(1,0);
      for (i=0;i<m;i++)
      {
         t=tmp.a[i]-1;
         if ((m&1)&&tmp.sign==m)
            t=tt[t];
         if ((!i||t>tmp.a[i-1])&&t>z)
         {
            tmp2.sign=tmp2.v=0;
            for (j=0;j<m;j++)
            {
               tmp2.a[j]=((j==i)?t:tmp.a[j]);
               tmp2.v+=log(abb(a[tmp2.a[j]]));
               tmp2.sign+=(a[tmp2.a[j]]<0);
            }
            if (check(tmp2.a))
            {
               d[++tot]=tmp2;
               up(tot,0);
            }
         }
      }
   }
   if (dc[n][m]-dc[n-z][m]<2*k)
   {
      if (c[n][m]-c[n-z][m]>=k)
         puts("0");
      else
      {
         memset(head,0,sizeof(head));
         k-=c[n][m]-c[n-z][m];
         tot=1;
         d[1].sign=d[1].v=totm=0;
         for (i=0;i<m;i++)
         {
            d[1].a[i]=z+i+1;
            d[1].v+=log(abb(a[z+i+1]));
            d[1].sign+=(a[z+i+1]<0);
         }
         while (k)
         {
            if (d[1].sign&1)
            {
               k--;
               if (!k)
               {
                  putchar('-');
                  print(d[1].a);
               }
            }
            tmp=d[1];
            d[1]=d[tot--];
            down(1,1);
            for (i=0;i<m;i++)
               if ((i==m||tmp.a[i+1]!=tmp.a[i]+1)&&tmp.a[i]<n)
               {
                  tmp2.sign=tmp2.v=0;
                  for (j=0;j<m;j++)
                  {
                     tmp2.a[j]=tmp.a[j]+(j==i);
                     tmp2.v+=log(abb(a[tmp2.a[j]]));
                     tmp2.sign+=(a[tmp2.a[j]]<0);
                  }
                  if (check(tmp2.a))
                  {
                     d[++tot]=tmp2;
                     up(tot,1);
                  }
               }
         }
      }
   }
   else
      puts("0");
   end:
   return 0;
}
