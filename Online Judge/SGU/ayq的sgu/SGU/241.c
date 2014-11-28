#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long f1[21][21][51]={0},l1[21][21]={0},f2[41][51]={0},l2[41]={0};
long ans[51]={0};

void add(long a[],long b[],long c,long *la,long lb)
{
   long i;
   *la=max(*la,lb)+2;
   for (i=1;i<=*la;i++)
   {
      a[i]+=a[i-1]/10+b[i]*c;
      a[i-1]%=10;
   }
   while (*la&&!a[*la])
      (*la)--;
}

int main()
{
   long i,j,k,l,n,m,w,h,x,x2,h1,h2,w1,w2,lans=0;
   scanf("%ld%ld%ld%ld%ld",&n,&m,&w,&h,&x);
   w=min(w,n);
   h=min(h,n);
   if (w+m<n)
      w=n-m;
   if (h+m<n)
      h=n-m;
   if (x>min(w,h)+m)
      printf("0\n");
   else
   {
      f1[0][0][1]=l1[0][0]=1;
      for (i=1;i<=h;i++)
         for (j=min(x,w);j>=0;j--)
            for (k=min(x,n-w);k>=0;k--)
            {
               if (j)
                  add(f1[j][k],f1[j-1][k],w-j+1,&l1[j][k],l1[j-1][k]);
               if (k)
                  add(f1[j][k],f1[j][k-1],n-w-k+1,&l1[j][k],l1[j][k-1]);
            }
      h1=n-h;
      h2=max(m+h-n,0);
      for (i=0;i<=min(x,w);i++)
         for (j=0;i+j<=x&&j<=n-w;j++)
         {
            w1=w-i;
            w2=max(n-w,m)-j;
            x2=x-i-j;
            memset(l2,0,sizeof(l2));
            memset(f2,0,sizeof(f2));
            f2[0][1]=l2[0]=1;
            for (k=1;k<=h2;k++)
               for (l=x2;l>=1;l--)
                  add(f2[l],f2[l-1],w2-l+1,&l2[l],l2[l-1]);
            for (k=h2+1;k<=h1+h2;k++)
               for (l=x2;l>=1;l--)
                  add(f2[l],f2[l-1],w1+w2-l+1,&l2[l],l2[l-1]);
            for (k=1;k<=l1[i][j];k++)
               for (l=1;l<=l2[x2];l++)
                  ans[k+l-1]+=f1[i][j][k]*f2[x2][l];
            lans=max(lans,l1[i][j]+l2[x2])+1;
            for (k=2;k<=lans;k++)
            {
               ans[k]+=ans[k-1]/10;
               ans[k-1]%=10;
            }
            while (!ans[lans])
               lans--;
         }
      for (i=lans;i>=2;i--)
         printf("%ld",ans[i]);
      printf("%ld\n",ans[1]);
   }
   return 0;
}
