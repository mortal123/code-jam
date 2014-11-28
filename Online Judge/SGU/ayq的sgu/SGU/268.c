#include <stdio.h>
#define oo 1000000000

char a[30]={'\0'},b[30]={'\0'},st[30]={'\0'},hash[30]={'\0'},pos[130]={'\0'},ans[2001]={'\0'},rec[2001]={0};
long n,min=oo;

void renew()
{
   long i,j,at,now,cost=n;
   char tmp;
   strcpy(rec+1,st+1);
   while (1)
   {
      memset(hash,'\0',sizeof(hash));
      for (i=1;st[i]!='@';i++);
      at=i;
      while (!hash[i])
      {
         hash[i]=1;
         i=pos[st[i]];
      }
      for (i=1;i<=n;i++)
      {
         now=(at+i-1)%(n+1)+1;
         if (!hash[now]&&pos[st[now]]!=now||pos[st[now]]==at)
         {
            if (i<n)
               rec[++cost]=st[now];
            for (j=1;j<i;j++)
               rec[++cost]=st[(at+j-1)%(n+1)+1];
            tmp=st[now];
            st[now]=st[at];
            st[at]=tmp;
            break;
         }
      }
      if (i>n)
         break;
   }
   if (cost<min)
   {
      min=cost;
      strncpy(ans+1,rec+1,cost);
      ans[cost+1]='\0';
   }
}

int main()
{
   long i,j;
   scanf("%ld%s%s",&n,a+1,b+1);
   for (i=1;i<=n+1;i++)
   {
      strcpy(st+1,a+1);
      st[n+1]='@';
      for (j=1;j<=n-i+1;j++)
         pos[b[j]]=i+j;
      pos['@']=i;
      for (j=n-i+2;j<=n;j++)
         pos[b[j]]=j-n+i-1;
      renew();
   }
   for (i=1;i<=n+1;i++)
   {
      strcpy(st+1,b+1);
      st[n+1]='@';
      for (j=1;j<=n-i+1;j++)
         pos[a[j]]=i+j;
      pos['@']=i;
      for (j=n-i+2;j<=n;j++)
         pos[a[j]]=j-n+i-1;
      renew();
   }
   puts(ans+1);
   return 0;
}
