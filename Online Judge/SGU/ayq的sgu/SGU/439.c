#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

int st[21][1000005],mi[1000005],hl[1000005],hr[1000005];
char a[1000005],b[2000005];

int main()
{
   int i,j,k,la,lb,pos,len,hash,dis=oo,t=1,tot=0;
   scanf("%d%d\n",&la,&lb);
   gets(a+1);
   gets(b+1);
   for (i=1;i<=lb;i++)
      b[i+lb]=b[i];
   i=j=1;
   while (i<=lb&&j<=lb)
      if (i==j)
         j++;
      else
      {
         for (k=0;k<lb&&b[i+k]==b[j+k];k++);
         if (b[i+k]<b[j+k])
            j+=k+1;
         else
            i+=k+1;
      }
   pos=min(i,j);
   for (i=1;i<=lb;i++)
      b[i]=b[pos+i-1];
   b[lb+1]=0;
   puts(b+1);
   mi[0]=1;
   for (i=1;i<=la;i++)
   {
      st[0][i]=a[i]-'A';
      mi[i]=mi[i-1]*29;
   }
   for (i=1;i<=lb;i++)
      hl[i]=hl[i-1]*29+b[i]-'A';
   for (i=lb;i>=1;i--)
      hr[i]=(b[i]-'A')*mi[lb-i]+hr[i+1];
   while ((t<<1)<=la)
   {
      t<<=1;
      tot++;
   }
   for (i=1;i<=tot;i++)
      for (j=1;j<=la;j++)
         st[i][j]=st[i-1][j]*mi[1<<i-1]+st[i-1][(j+(1<<i-1)-1)%la+1];
   for (i=la-1;i>=0;i--)
      if (min(i,la-i)<dis||min(i,la-i)==dis&&!i)
      {
         len=hash=0;
         for (j=tot;j>=0;j--)
            if (len+(1<<j)<=lb&&hash*mi[1<<j]+st[j][(i+len)%la+1]==hl[len+(1<<j)])
            {
               hash=hash*mi[1<<j]+st[j][(i+len)%la+1];
               len+=1<<j;
            }
         k=len;
         len=hash=0;
         for (j=tot;j>=0;j--)
            if (len+(1<<j)<=lb&&hash+st[j][(i+lb-len-(1<<j)+2*la)%la+1]*mi[len]==hr[lb-len-(1<<j)+1])
            {
               hash+=st[j][(i+lb-len-(1<<j)+2*la)%la+1]*mi[len];
               len+=1<<j;
            }
         if (k+len>=lb-1)
         {
            dis=min(i,la-i);
            pos=i+1;
         }
      }
   for (i=0;i<la;i++)
      putchar(a[(pos+i-1)%la+1]);
   puts("");
   return 0;
}
