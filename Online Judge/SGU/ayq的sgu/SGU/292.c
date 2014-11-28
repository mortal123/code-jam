#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))

long a[2005]={0},b[2005]={0},n[2005]={0},t1[2005]={0},t2[2005]={0},p1[2005]={0},q1[2005]={0},p2[2005]={0},q2[2005]={0},ans[2005]={0};
char str[2005]={'\0'};

long cmp(long x[],long y[],long lx,long ly)
{
   long i;
   if (lx>ly)
      return 1;
   if (lx<ly)
      return -1;
   for (i=lx;i>=1;i--)
   {
      if (x[i]>y[i])
         return 1;
      if (x[i]<y[i])
         return -1;
   }
   return 0;
}

void jia(long x[],long y[],long *lx,long ly)
{
   long i;
   *lx=max(*lx,ly)+1;
   for (i=1;i<=*lx;i++)
   {
      x[i]+=x[i-1]/10+y[i];
      x[i-1]%=10;
   }
   while (!x[*lx]&&*lx)
      (*lx)--;
}

void jian(long x[],long y[],long *lx,long ly)
{
   long i;
   *lx=max(*lx,ly);
   for (i=1;i<=*lx;i++)
   {
      x[i]+=(x[i-1]+20)/10-2-y[i];
      x[i-1]=(x[i-1]+20)%10;
   }
   while (!x[*lx]&&*lx)
      (*lx)--;
}

void cheng(long x[],long y[],long *lx,long ly)
{
   long i,j;
   memset(t1,0,sizeof(t1));
   for (i=1;i<=*lx;i++)
      for (j=1;j<=ly;j++)
         t1[i+j-1]+=x[i]*y[j];
   (*lx)+=ly;
   for (i=1;i<=*lx+1;i++)
   {
      x[i]=t1[i]+x[i-1]/10;
      x[i-1]%=10;
   }
   while (!x[*lx]&&*lx)
      (*lx)--;
}

void chu(long x[],long y[],long *lx,long ly)
{
   long i,lt1=0;
   memset(t1,0,sizeof(t1));
   memset(t2,0,sizeof(t2));
   for (i=*lx-ly+1;i>=1;i--)
   {
      for (t2[i]=1;t2[i]<=10;t2[i]++)
      {
         jia(t1+i-1,y,&lt1,ly);
         if (cmp(t1,x,lt1+i-1,*lx)>0)
            break;
      }
      jian(t1+i-1,y,&lt1,ly);
      lt1++;
      t2[i]--;
   }
   memset(x,0,sizeof(x));
   for (i=1;i<=lt1;i++)
      x[i]=t2[i];
   (*lx)-=ly-1;
   while (!x[*lx]&&*lx)
      (*lx)--;
}

void mod(long x[],long y[],long *lx,long ly)
{
   long i,j,lt1=0;
   memset(t1,0,sizeof(t1));
   for (i=*lx-ly+1;i>=1;i--)
   {
      while (1)
      {
         jia(t1+i-1,y,&lt1,ly);
         if (cmp(t1,x,lt1+i-1,*lx)>0)
            break;
      }
      jian(t1+i-1,y,&lt1,ly);
      lt1++;
   }
   jian(x,t1,lx,lt1);
}

void print(long x[],long lx)
{
   long i,flag=0;
   for (i=lx;i>=2;i--)
   {
      if (x[i])
         flag=1;
      if (flag)
         printf("%ld",x[i]);
   }
   printf("%ld\n",x[1]);
}

int main()
{
   long i,la,lb,ln,lp1,lq1,lp2,lq2,lans;
   gets(str+1);
   lans=la=strlen(str+1);
   for (i=1;i<=la;i++)
      ans[i]=a[i]=str[la-i+1]-'0';
   gets(str+1);
   lb=strlen(str+1);
   for (i=1;i<=lb;i++)
      b[i]=str[lb-i+1]-'0';
   gets(str+1);
   ln=strlen(str+1);
   for (i=1;i<=ln;i++)
      n[i]=str[ln-i+1]-'0';
   lp1=la;
   for (i=1;i<=la;i++)
      p1[i]=a[i];
   mod(p1,n,&lp1,ln);
   lq1=lb;
   for (i=1;i<=lb;i++)
      q1[i]=b[i];
   mod(q1,n,&lq1,ln);
   if (cmp(a,n,la,ln)>=0&&cmp(b,n,lb,ln)>=0)
   {
      lp2=lq2=ln;
      for (i=1;i<=ln;i++)
         p2[i]=q2[i]=n[i];
      jian(p2,p1,&lp2,lp1);
      jian(q2,q1,&lq2,lq1);
      cheng(p1,q1,&lp1,lq1);
      cheng(p2,q2,&lp2,lq2);
      if (cmp(p1,p2,lp1,lp2)>0)
      {
         memset(p1,0,sizeof(p1));
         for (i=1;i<=lp2;i++)
            p1[i]=p2[i];
         lp1=lp2;
      }
   }
   else
      cheng(p1,q1,&lp1,lq1);
   cheng(ans,b,&lans,lb);
   jian(ans,p1,&lans,lp1);
   chu(ans,n,&lans,ln);
   print(ans,lans);
   return 0;
}
