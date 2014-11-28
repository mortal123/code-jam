#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b)?(a):(b))

int mod[201],di[201],rec[2][20],a[10005],p[10005],tmp[10005],ans[10005];
char str[10005];
int lans;

void count(int len)
{
   int i,j=0,ltmp=1;
   for (i=1;i<=len+1;i++)
   {
      if ((p[i]+j)%10!=a[i])
         return;
      j=(p[i]+j>=10);
   }
   if ((len&1)&&(p[len/2+1]&1)||j)
      return;
   memset(tmp,0,sizeof(tmp));
   tmp[1]=1;
   if (len/2)
   {
      for (i=1;i<=lans+1;i++)
      {
         tmp[i]=tmp[i]*rec[1][p[1]]+tmp[i-1]/10;
         tmp[i-1]%=10;
      }
      if (tmp[lans+1])
         lans++;
   }
   for (i=2;i<=len/2;i++)
   {
      for (j=1;j<=lans+1;j++)
      {
         tmp[j]=tmp[j]*rec[0][p[i]]+di[tmp[j-1]];
         tmp[j-1]=mod[tmp[j-1]];
      }
      if (tmp[lans+1])
         lans++;
   }
   lans=max(lans,ltmp)+1;
   for (i=1;i<=lans;i++)
   {
      ans[i]+=tmp[i]+ans[i-1]/10;
      ans[i-1]%=10;
   }
   while (!ans[lans])
      lans--;
}

void work(int l,int r,int al,int ar,int len)
{
   int i;
   if (l>r)
      count(len);
   else if (ar%10==(a[l]-al+10)%10)
   {
      p[l]=p[r]=ar;
      work(l+1,r-1,ar+al>=10,a[r-1],len);
   }
   else if (ar&&(ar+9)%10==(a[l]-al+10)%10)
   {
      p[l]=p[r]=ar-1;
      work(l+1,r-1,ar+al>10,10+a[r-1],len);
   }
}

int main()
{
   int i,j,l;
   for (i=1;i<=200;i++)
   {
      mod[i]=i%10;
      di[i]=i/10;
   }
   for (i=0;i<=19;i++)
   {
      for (j=0;j<=9&&j<=i;j++)
         rec[0][i]+=(i-j<=9);
      for (j=1;j<=9&&j<=i;j++)
         rec[1][i]+=(i-j<=9);
   }
   while (1)
   {
      gets(str+1);
      if (str[1]=='0')
         break;
      lans=0;
      memset(ans,0,sizeof(ans));
      memset(p,0,sizeof(p));
      memset(a,0,sizeof(a));
      l=strlen(str+1);
      for (i=1;i<=l;i++)
         a[i]=str[l-i+1]-'0';
      if (l>1&&a[l]==1)
         work(1,l-1,0,10+a[l-1],l-1);
      work(1,l,0,a[l],l);
      for (i=lans;i>=2;i--)
         printf("%d",ans[i]);
      printf("%d\n",ans[1]);
   }
   return 0;
}
