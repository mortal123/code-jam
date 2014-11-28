#include <stdio.h>
#include <string.h>

char tmp[1030]={0},str[1030]={0},std1[4][10]={"can","may","must","should"},std2[2][10]={"is","are"},std3[2][10]={"a","the"};
long count[1025]={0};

long cmp1(long x)
{
   long i,j;
   for (i=0;i<=3;i++)
   {
      for (j=0;std1[i][j]&&(std1[i][j]==str[x+j]||std1[i][j]==str[x+j]+32);j++);
      if (!std1[i][j]&&(str[x+j]==' '||str[x+j]=='.'))
         return 1;
   }
   return 0;
}

long cmp2(long x)
{
   long i,j;
   for (i=0;i<=1;i++)
   {
      for (j=0;std2[i][j]&&(std2[i][j]==str[x+j]||std2[i][j]==str[x+j]+32);j++);
      if (!std2[i][j]&&(str[x+j]==' '||str[x+j]=='.'))
         return 1;
   }
   return 0;
}

long cmp3(long x)
{
   long i,j;
   for (i=0;i<=1;i++)
   {
      for (j=0;std3[i][j]&&(std3[i][j]==str[x+j]||std3[i][j]==str[x+j]+32);j++);
      if (!std3[i][j]&&(str[x+j]==' '||str[x+j]=='.'))
         return 1;
   }
   return 0;
}

int main()
{
   long i,j,k,a,b,x,n,t,flag,first,s=0,l=0,ans=0;
   while (gets(tmp+1)!=NULL)
   {
      if (l&&str[l]!=' ')
         str[++l]=' ';
      l+=strlen(tmp+1);
      strcat(str+1,tmp+1);
   }
   for (i=1;i<=l;i=j+3)
   {
      s++;
      j=i;
      while (str[j+1]!='.')
         j++;
      for (a=i;a<j;a=b+2)
      {
         b=a;
         while (str[b+1]>='a'&&str[b+1]<='z'||str[b+1]>='A'&&str[b+1]<='Z')
            b++;
         if (cmp1(a)||cmp2(a))
            count[s]++;
      }
      ans+=count[s];
   }
   printf("%ld\n",ans);
   s=0;
   for (i=1;i<=l;i=j+3)
   {
      s++;
      j=i;
      while (str[j+1]!='.')
         j++;
      for (k=1;k<=count[s];k++)
      {
         t=flag=0;
         first=1;
         for (a=i;a<j;a=b+2)
         {
            b=a;
            while (str[b+1]>='a'&&str[b+1]<='z'||str[b+1]>='A'&&str[b+1]<='Z')
               b++;
            if (cmp1(a)&&(++t==k))
               flag=1;
            else if (cmp2(a)&&(++t==k))
               flag=2;
            else if (flag==2&&cmp3(a))
               flag=3;
            else
               flag=0;
            if (flag!=3)
            {
               if (first)
                  first=0;
               else
                  putchar(' ');
               for (x=a;x<=b;x++)
                  putchar(str[x]);
            }
            if (flag==1)
               printf(" not");
            else if (flag==2)
               printf(" no");
         }
         puts(".");
      }
   }
   return 0;
}
