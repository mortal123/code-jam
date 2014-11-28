#include <stdio.h>

int a[1001][1002],b[1001][1001],s[1001][1001];
char hash[1001];
int k;

void cpy(int x[],int y[])
{
   int i;
   for (i=1;i<=k+1;i++)
      x[i]=y[i];
}

int cmp(int x[],int y[])
{
   int i;
   for (i=k;i>=1;i--)
      if (x[i]>y[i])
         return 1;
      else if (x[i]<y[i])
         return -1;
   return 0;
}

void qs(int x,int y)
{
   int i=x,j=y;
   int t[1002];
   if (x>=y)
      return;
   cpy(t,a[(x+y)>>1]);
   cpy(a[(x+y)>>1],a[x]);
   while (i<j)
   {
      while (i<j&&cmp(a[j],t)<0)
         j--;
      if (i<j)
         cpy(a[i++],a[j]);
      while (i<j&&cmp(a[i],t)>0)
         i++;
      if (i<j)
         cpy(a[j--],a[i]);
   }
   cpy(a[i],t);
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   int i,j,c,ans=0,need=8;
   scanf("%d%d",&c,&k);
   for (i=1;i<=c;i++)
   {
      a[i][k+1]=i;
      for (j=1;j<=k;j++)
      {
         scanf("%d",&a[i][j]);
         b[i][j]=a[i][j];
      }
   }
   for (i=1;i<=c;i++)
   {
      for (j=1;j<k;j++)
      {
         a[i][j+1]+=a[i][j]/8;
         a[i][j]%=8;
      }
      if (a[i][k]>=8)
         break;
   }
   if (i<=c)
      hash[i]=1;
   else
   {
      qs(1,c);
      for (i=1;i<=c;i++)
         for (j=1;j<=k;j++)
            s[i][j]=s[i-1][j]+a[i][j];
      for (i=1;i<=c;i++)
      {
         for (j=1;j<k;j++)
         {
            s[i][j+1]+=s[i][j]/8;
            s[i][j]%=8;
         }
         if (s[i][k]>=8)
            break;
      }
      if (i==c+1)
      {
         puts("NO SOLUTION");
         goto end;
      }
      else
         for (;i;i--)
            hash[a[i][k+1]]=1;
   }
   for (i=k;i>=1;i--)
   {
      for (j=1;j<=c;j++)
         if (hash[j]&&b[j][i])
            if (b[j][i]<need)
            {
               ans++;
               need-=b[j][i];
            }
            else
            {
               ans++;
               goto out;
            }
      need*=8;
   }
   out:
   printf("%d\n",ans);
   need=8;
   for (i=k;i>=1;i--)
   {
      for (j=1;j<=c;j++)
         if (hash[j]&&b[j][i])
            if (b[j][i]<need)
            {
               printf("%d %d %d\n",j,i-1,b[j][i]);
               need-=b[j][i];
            }
            else
            {
               printf("%d %d %d\n",j,i-1,need);
               goto end;
            }
      need*=8;
   }
   end:
   return 0;
}
