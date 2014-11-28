#include <stdio.h>
#define oo 9999999999999999LL
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   short a,b;
   char c,d;
}last[1001][1001][2][2]={{0,0},{'\0','\0'}};
struct case2
{
   long v,pos;
}a[1001]={{0,0}},b[1001]={{0,0}};
long long f[1001][1001][2][2]={0};
long ans[1001]={0};

int main()
{
   long i,j,l,k,n,a1,b1,c1,d1,x,y,la=0,lb=0;
   long long rec=oo;
   struct case1 tmp;
   struct case2 t;
   scanf("%ld%ld",&k,&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&x,&y);
      if (!y)
         a[++la]=(struct case2){x,i};
      else
         b[++lb]=(struct case2){x,i};
   }
   if (k>n||3*la+2<k||3*lb+2<k)
   {
      printf("Impossible\n");
      goto end;
   }
   for (i=1;i<la;i++)
      for (j=i+1;j<=la;j++)
         if (a[i].v>a[j].v)
         {
            t=a[i];
            a[i]=a[j];
            a[j]=t;
         }
   for (i=1;i<lb;i++)
      for (j=i+1;j<=lb;j++)
         if (b[i].v>b[j].v)
         {
            t=b[i];
            b[i]=b[j];
            b[j]=t;
         }
   if (k==1)
   {
      if (a[1].v<b[1].v)
         printf("%ld\n",a[1].pos);
      else
         printf("%ld\n",b[1].pos);
      goto end;
   }
   for (i=0;i<=1;i++)
      for (j=0;j<=1;j++)
         f[1][1][i][j]=f[2][0][i][j]=f[0][2][i][j]=oo;
   if (la&&lb)
   {
      f[1][1][1][0]=k*a[1].v+(k-1)*b[1].v;
      f[1][1][0][1]=k*b[1].v+(k-1)*a[1].v;
   }
   if (la)
      f[2][0][0][0]=k*a[1].v+(k-1)*a[2].v;
   if (lb)
      f[0][2][1][1]=k*b[1].v+(k-1)*b[2].v;
   for (i=3;i<=k;i++)
      for (j=max(0,i-lb);j<=min(la,i);j++)
      {
         if (j>0)
         {
            f[j][i-j][0][0]=f[j-1][i-j][0][1]+a[j].v*(k-i+1);
            last[j][i-j][0][0]=(struct case1){j-1,i-j,0,1};
            if (f[j-1][i-j][1][0]<f[j-1][i-j][1][1])
            {
               f[j][i-j][0][1]=f[j-1][i-j][1][0]+a[j].v*(k-i+1);
               last[j][i-j][0][1]=(struct case1){j-1,i-j,1,0};
            }
            else
            {
               f[j][i-j][0][1]=f[j-1][i-j][1][1]+a[j].v*(k-i+1);
               last[j][i-j][0][1]=(struct case1){j-1,i-j,1,1};
            }
         }
         else
            f[j][i-j][0][0]=f[j][i-j][0][1]=oo;
         if (i-j>0)
         {
            f[j][i-j][1][1]=f[j][i-j-1][1][0]+b[i-j].v*(k-i+1);
            last[j][i-j][1][1]=(struct case1){j,i-j-1,1,0};
            if (f[j][i-j-1][0][0]<f[j][i-j-1][0][1])
            {
               f[j][i-j][1][0]=f[j][i-j-1][0][0]+b[i-j].v*(k-i+1);
               last[j][i-j][1][0]=(struct case1){j,i-j-1,0,0};
            }
            else
            {
               f[j][i-j][1][0]=f[j][i-j-1][0][1]+b[i-j].v*(k-i+1);
               last[j][i-j][1][0]=(struct case1){j,i-j-1,0,1};
            }
         }
         else
            f[j][i-j][1][0]=f[j][i-j][1][1]=oo;
      }
   for (i=max(0,k-lb);i<=min(la,k);i++)
      for (j=0;j<=1;j++)
         for (l=0;l<=1;l++)
            if (f[i][k-i][j][l]<rec)
            {
               rec=f[i][k-i][j][l];
               a1=i;
               b1=k-i;
               c1=j;
               d1=l;
            }
   for (i=k;i>=3;i--)
   {
      tmp=last[a1][b1][c1][d1];
      if (a1==tmp.a)
         ans[i]=1;
      a1=tmp.a;
      b1=tmp.b;
      c1=tmp.c;
      d1=tmp.d;
   }
   ans[2]=c1;
   ans[1]=d1;
   la=lb=0;
   for (i=1;i<=k;i++)
   {
      if (!ans[i])
         printf("%ld",a[++la].pos);
      else
         printf("%ld",b[++lb].pos);
      printf("%c",(i==k)?'\n':' ');
   }
   end:
   return 0;
}
