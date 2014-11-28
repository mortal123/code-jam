#include <stdio.h>
#define oo 1000000000
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   unsigned char a,b,c,d,e,f;
}last[16][16][16][226][2][2]={{0,0,0,0,0,0}};
long f[16][16][16][226][2][2]={0},s[16]={0};
char hash[16][16]={'\0'};

int main()
{
   long i,j,k,l,a,b,n,m,x,ans=-oo;
   struct case1 t;
   scanf("%ld%ld%ld",&n,&m,&x);
   for (i=1;i<=m;i++)
      for (j=1;j<=m;j++)
         for (k=0;k<=x;k++)
            f[0][i][j][k][0][0]=f[0][i][j][k][0][1]=f[0][i][j][k][1][0]=f[0][i][j][k][1][1]=-oo;
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=m;j++)
      {
         scanf("%ld",&s[j]);
         s[j]+=s[j-1];
      }
      for (j=1;j<=m;j++)
         for (k=j;k<=m;k++)
         {
            f[i][j][k][k-j+1][0][1]=f[i][j][k][k-j+1][1][0]=f[i][j][k][k-j+1][1][1]=-oo;
            f[i][j][k][k-j+1][0][0]=s[k]-s[j-1];
            for (l=k-j+2;l<=x;l++)
            {
               f[i][j][k][l][0][0]=f[i][j][k][l][0][1]=f[i][j][k][l][1][0]=f[i][j][k][l][1][1]=-oo;
               for (a=1;a<=k;a++)
                  for (b=max(a,j);b<=m&&b-a+1+k-j+1<=l;b++)
                  {
                     if (a>=j&&b<=k)
                     {
                        if (f[i][j][k][l][0][0]<f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][0][0]=f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1];
                           last[i][j][k][l][0][0]=(struct case1){i-1,a,b,l-k+j-1,0,0};
                        }
                     }
                     if (a<=j&&b<=k)
                     {
                        if (f[i][j][k][l][1][0]<f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][1][0]=f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1];
                           last[i][j][k][l][1][0]=(struct case1){i-1,a,b,l-k+j-1,0,0};
                        }
                        if (f[i][j][k][l][1][0]<f[i-1][a][b][l-k+j-1][1][0]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][1][0]=f[i-1][a][b][l-k+j-1][1][0]+s[k]-s[j-1];
                           last[i][j][k][l][1][0]=(struct case1){i-1,a,b,l-k+j-1,1,0};
                        }
                     }
                     if (a>=j&&b>=k)
                     {
                        if (f[i][j][k][l][0][1]<f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][0][1]=f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1];
                           last[i][j][k][l][0][1]=(struct case1){i-1,a,b,l-k+j-1,0,0};
                        }
                        if (f[i][j][k][l][0][1]<f[i-1][a][b][l-k+j-1][0][1]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][0][1]=f[i-1][a][b][l-k+j-1][0][1]+s[k]-s[j-1];
                           last[i][j][k][l][0][1]=(struct case1){i-1,a,b,l-k+j-1,0,1};
                        }
                     }
                     if (a<=j&&b>=k)
                     {
                        if (f[i][j][k][l][1][1]<f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][1][1]=f[i-1][a][b][l-k+j-1][0][0]+s[k]-s[j-1];
                           last[i][j][k][l][1][1]=(struct case1){i-1,a,b,l-k+j-1,0,0};
                        }
                        if (f[i][j][k][l][1][1]<f[i-1][a][b][l-k+j-1][1][0]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][1][1]=f[i-1][a][b][l-k+j-1][1][0]+s[k]-s[j-1];
                           last[i][j][k][l][1][1]=(struct case1){i-1,a,b,l-k+j-1,1,0};
                        }
                        if (f[i][j][k][l][1][1]<f[i-1][a][b][l-k+j-1][0][1]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][1][1]=f[i-1][a][b][l-k+j-1][0][1]+s[k]-s[j-1];
                           last[i][j][k][l][1][1]=(struct case1){i-1,a,b,l-k+j-1,0,1};
                        }
                        if (f[i][j][k][l][1][1]<f[i-1][a][b][l-k+j-1][1][1]+s[k]-s[j-1])
                        {
                           f[i][j][k][l][1][1]=f[i-1][a][b][l-k+j-1][1][1]+s[k]-s[j-1];
                           last[i][j][k][l][1][1]=(struct case1){i-1,a,b,l-k+j-1,1,1};
                        }
                     }
                  }
            }
         }
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         for (k=j;k<=m;k++)
            for (a=0;a<=1;a++)
               for (b=0;b<=1;b++)
                  if (f[i][j][k][x][a][b]>ans)
                  {
                     ans=f[i][j][k][x][a][b];
                     t=(struct case1){i,j,k,x,a,b};
                  }
   printf("Oil : %ld\n",ans);
   while (t.d)
   {
      for (i=t.b;i<=t.c;i++)
         hash[t.a][i]=1;
      i=t.a;
      j=t.b;
      k=t.c;
      l=t.d;
      a=t.e;
      b=t.f;
      t.a=last[i][j][k][l][a][b].a;
      t.b=last[i][j][k][l][a][b].b;
      t.c=last[i][j][k][l][a][b].c;
      t.d=last[i][j][k][l][a][b].d;
      t.e=last[i][j][k][l][a][b].e;
      t.f=last[i][j][k][l][a][b].f;
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (hash[i][j])
            printf("%ld %ld\n",i,j);
   return 0;
}
