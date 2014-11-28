#include <stdio.h>
#include <stdlib.h>

int pos[257],max[11]={2,3,5,7,11,13,17,19,23},con[11]={1,3,12,72,576,6912,96768,1741824,34836480,836075520},p[1050001],flag[1050001];
char rec[1050001],sign[11]="_.,-~='^\"";
int last=0,s=0,o=0,sum=0,cur=8,tot=0;

void qs(long x,long y)
{
   long i=x,j=y,t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j]>t)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i]<t)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void end()
{
   cur=8;
   flag[++s]=last;
   p[++o]=sum;
   sum=last=tot=0;
}

int main()
{
   int i,j,o2=0;
   char ch;
   for (i=0;i<=8;i++)
      pos[sign[i]]=i+1;
   while ((ch=getchar())!=EOF)
      if (!pos[ch]&&ch!='O'&&(ch<'0'||ch>'9'))
      {
         if (last)
            end();
         rec[++s]=ch;
      }
      else if (ch=='0'&&(last!=2||(long long)sum*10>=con[9])||ch=='O')
      {
         if (last)
            end();
         cur=8;
         flag[++s]=1+(ch=='0');
         p[++o]=tot=0;
      }
      else if (pos[ch])
      {
         if (last==2||last==1&&(pos[ch]-1>cur||pos[ch]-1==cur&&tot>=max[cur]))
            end();
         if (pos[ch]-1<cur)
         {
            cur=pos[ch]-1;
            tot=0;
         }
         tot++;
         sum+=con[pos[ch]-1];
         last=1;
      }
      else
      {
         if (last==1||last==2&&(long long)sum*10+ch-'0'>=con[9])
            end();
         sum=sum*10+ch-'0';
         last=2;
      }
   if (last)
      end();
   if (o&1)
      qs(1,o);
   for (i=1;i<=s;i++)
      if (!flag[i])
         putchar(rec[i]);
      else if (flag[i]==1)
         printf("%d",p[++o2]);
      else if (!p[++o2])
         putchar('O');
      else
         for (j=8;j>=0;j--)
            while (p[o2]>=con[j])
            {
               putchar(sign[j]);
               p[o2]-=con[j];
            }
   return 0;
}
