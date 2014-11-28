#include <stdio.h>
#include <string.h>
#define oo 1000000000

char hash[3200011]={0},str[100005]={0},tmp[9]={0},list[28][9]={"R1......","R1.....","R1....","R1...","R1..","R1.","R16..","R16.","R16","R1","R2.....","R2....","R2...","R2..","R2.","R2","R32.","R32","R4....","R4...","R4..","R4.","R4","R64","R8...","R8..","R8.","R8"};
long f[3200011]={0},len[28]={0},v[28]={0};

int main()
{
   long i,j,l,t,pos,sum=0;
   for (i=0;i<28;i++)
   {
      len[i]=strlen(list[i]);
      pos=2+(list[i][2]>='0'&&list[i][2]<='9');
      if (list[i][1]=='6')
         t=1;
      else if (list[i][1]=='3')
         t=2;
      else if (list[i][1]=='1'&&list[i][2]=='6')
         t=4;
      else if (list[i][1]=='8')
         t=8;
      else if (list[i][1]=='4')
         t=16;
      else if (list[i][1]=='2')
         t=32;
      else
         t=64;
      do
      {
         v[i]+=t;
         t>>=1;
      }while (list[i][pos++]=='.');
   }
   gets(str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i=j+1)
   {
      j=i+1;
      while (j<l&&str[j+1]!='R')
         j++;
      for (t=0;t<=j-i;t++)
         tmp[t]=str[i+t];
      tmp[t]=0;
      for (t=0;t<28&&strcmp(tmp,list[t]);t++);
      sum+=v[t];
   }
   for (i=1;i<=sum;i++)
   {
      f[i]=oo;
      for (j=0;j<28;j++)
         if (i>=v[j]&&f[i-v[j]]+len[j]<f[i])
            f[i]=f[i-v[j]]+len[j];
   }
   hash[sum]=1;
   for (i=sum;i;i--)
      if (hash[i])
         for (j=0;j<28;j++)
            if (i>=v[j]&&f[i-v[j]]+len[j]==f[i])
               hash[i-v[j]]=1;
   for (i=0;i<sum;i+=v[j])
   {
      for (j=0;j<28&&!hash[i+v[j]]||f[i+v[j]]!=f[i]+len[j];j++);
      printf("%s",list[j]);
   }
   puts("");
   return 0;
}
