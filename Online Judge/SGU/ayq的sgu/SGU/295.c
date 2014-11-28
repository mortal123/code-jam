#include <stdio.h>
#include <string.h>

char str[71]={'\0'},list[21]="ABCEHKMOPTXaceopxy";
unsigned long long f[71][71]={0};

int main()
{
   long i,j,k,l,r,st,en,len,n=2,t=0;
   unsigned long long ans=0;
   scanf("%ld%ld\n",&l,&r);
   gets(str+1);
   len=strlen(str+1);
   for (st=1;st<=len&&str[st]==' ';st++);
   if (st>len)
   {
      printf("%ld\n",r-l);
      goto end;
   }
   for (en=len;str[en]==' ';en--);
   for (i=st;i<=en;i++)
   {
      if (strchr(list,str[i])!=NULL)
         t++;
      if (str[i]!=' ')
      {
         l--;
         r--;
         if (i>st&&str[i-1]==' ')
         {
            n++;
            l--;
            r--;
         }
      }
   }
   f[0][0]=1;
   l=((l>0)?l:0);
   for (i=1;i<=n;i++)
      for (j=0;j<=r;j++)
         for (k=0;k<=j;k++)
            f[i][j]+=f[i-1][k];
   for (i=l;i<=r;i++)
      ans+=f[n][i];
   printf("%I64u\n",ans*(1LL<<t)-1);
   end:
   return 0;
}
