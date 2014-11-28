#include<stdio.h>
#include<string.h>
#define abs(a) ((a)>0?(a):(-(a)))

char str1[5005]={'\0'},str2[5005]={'\0'};

int main()
{
   long i,j,k,n,ans=0,num1=0,num2=0;
   gets(str1+1);
   n=strlen(str1+1);
   gets(str2+1);
   for (i=1;i<=n;i++)
      if (str1[i]=='-')
         num1++;
   for (i=1;i<=n;i++)
      if (str2[i]=='-')
         num2++;
   if (num1!=num2)
      printf("-1\n");
   else
   {
      j=k=0;
      for (i=1;i<=num1;i++)
      {
         for (j++;str1[j]=='+';j++);
         for (k++;str2[k]=='+';k++);
         ans+=abs(j-k);
      }
      printf("%ld\n",ans);
   }
   return 0;
}
