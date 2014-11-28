#include <stdio.h>

struct case1
{
   long s,d;
}q[11]={{0,0}};
long mat[201][51]={0},pos[51]={0},a[51]={0},v[51]={0},w[51]={0},one[51][51]={0},p[51][51]={0},tmp[51][51]={0};
char str1[55]={'\0'},str2[55]={'\0'};
long k;

void mi(long now)
{
   long i,j,x;
   if (now==1)
      for (i=1;i<=k;i++)
         for (j=1;j<=k;j++)
            p[i][j]=one[i][j];
   else
   {
      mi(now>>1);
      memset(tmp,0,sizeof(tmp));
      for (i=1;i<=k;i++)
         for (j=1;j<=k;j++)
            for (x=1;x<=k;x++)
               tmp[i][j]^=p[i][x]*p[x][j];
      for (i=1;i<=k;i++)
         for (j=1;j<=k;j++)
            p[i][j]=tmp[i][j];
      if (now&1)
      {
         memset(tmp,0,sizeof(tmp));
         for (i=1;i<=k;i++)
            for (j=1;j<=k;j++)
               for (x=1;x<=k;x++)
                  tmp[i][j]^=p[i][x]*one[x][j];
        for (i=1;i<=k;i++)
           for (j=1;j<=k;j++)
              p[i][j]=tmp[i][j];
      }
   }
}

int main()
{
   long i,j,x,y,n,m,l,t;
   scanf("%ld%ld%ld%ld",&n,&m,&k,&l);
   for (i=1;i<=m;i++)
      scanf("%ld%ld",&q[i].s,&q[i].d);
   for (i=1;i<=l;i++)
   {
      scanf("%s%s",str1+1,str2+1);
      for (j=1;j<k;j++)
         mat[i][j]=str2[j]-'0';
      mat[i][k]=(str1[1]!=str2[k]);
   }
   for (i=1;i<=n;i++)
      pos[i]=i;
   for (i=1;i<k;i++)
   {
      for (x=i;x<=l;x++)
         for (y=i;y<k;y++)
            if (mat[x][y])
               goto out;
      out:
      t=pos[i];
      pos[i]=pos[y];
      pos[y]=t;
      for (j=1;j<=k;j++)
      {
         t=mat[i][j];
         mat[i][j]=mat[x][j];
         mat[x][j]=t;
      }
      for (j=1;j<=l;j++)
      {
         t=mat[j][i];
         mat[j][i]=mat[j][y];
         mat[j][y]=t;
      }
      for (x=i+1;x<=l;x++)
         if (mat[x][i])
            for (y=1;y<=k;y++)
               mat[x][y]^=mat[i][y];
   }
   for (i=k-1;i>=1;i--)
   {
      for (j=i+1;j<k;j++)
         a[pos[i]]^=mat[i][j]*a[pos[j]];
      a[pos[i]]^=mat[i][k];
   }
   scanf("%s",str1+1);
   for (i=1;i<=n;i++)
      v[i]=str1[i]-'0';
   for (i=1;i<k;i++)
   {
      one[i+1][i]=1;
      one[i+1][k]=a[k-i];
   }
   one[1][k]=1;
   for (i=m;i>=1;i--)
   {
      mi(q[i].d);
      memset(w,0,sizeof(w));
      for (j=1;j<=k;j++)
         for (x=1;x<=k;x++)
            w[j]^=p[k-x+1][k-j+1]*v[q[i].s+x-1];
      for (j=1;j<=k;j++)
         v[q[i].s+j-1]=w[j];
   }
   for (i=1;i<=n;i++)
      printf("%ld",v[i]);
   printf("\n");
   return 0;
}
