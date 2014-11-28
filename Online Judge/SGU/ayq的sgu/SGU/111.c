#include <stdio.h>
#include <string.h>

char str[1005]={'\0'};
long a[1005]={0},b[1005]={0},ans[505]={0};
long l;

void dec()
{
   long i;
   for (i=1;i<=l;i++)
   {
      a[i]=a[i]-b[i]+(a[i-1]+20)/10-2;
      a[i-1]=(a[i-1]+20)%10;
   }
}

long cmp()
{
   long i;
   for (i=l;i>=1;i--)
   {
      if (a[i]>b[i])
         return 1;
      else if (a[i]<b[i])
         return -1;
   }
   return 0;
}

void work(long now)
{
   long i,j;
   if (now==0)
      return;
   for (i=1;i<=9;i++)
   {
      memset(b,0,sizeof(b));
      b[now*2-1]=2*i-1;
      for (j=now+1;j<=((l+1)>>1)+1;j++)
      {
         b[j+now-1]=ans[j]*2+b[j+now-2]/10;
         b[j+now-2]%=10;
      }
      if (cmp()>=0)
         dec();
      else
         break;
   }
   printf("%ld",ans[now]=i-1);
   work(now-1);
}

int main()
{
   long i;
   gets(str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      a[i]=str[l-i+1]-'0';
   work((l+1)>>1);
   printf("\n");
   return 0;
}
