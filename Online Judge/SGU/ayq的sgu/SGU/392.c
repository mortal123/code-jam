#include <stdio.h>

struct case1
{
   long x,y,hash;
}f[31][31][31]={0,0,0};
char turn[33][33]={0},map[33][33]={0},str[2005]={0};
long l[129][2]={0},ll[33][33]={0};

long mi(long a,long b)
{
   long t;
   if (!b)
      return 1;
   t=mi(a,b>>1);
   t*=t;
   if (b&1)
      t=t*a;
   return t;
}

long check(long x,long y,long len)
{
   long i,px,py,s=1,hash=map[x][y]-'a';
   for (i=0;i<=30;i++)
      if ((len-1)&(1<<i))
      {
         hash+=mi(29,s)*f[x][y][i].hash;
         s+=(1<<i);
         px=x;
         py=y;
         x=f[px][py][i].x;
         y=f[px][py][i].y;
      }
   return hash;
}

long work(long s,long len)
{
   long t;
   if (!len)
      return 1;
   t=work(s,(len-1)>>1)*(1+mi(s,(len+1)>>1));
   if (!(len&1))
      t+=mi(s,len);
   return t;
}

int main()
{
   long i,j,k,q,x,y,px,py,n,m,t,len,hash,num,rec,s=29;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
      gets(turn[i]+1);
   l['^'][0]=l['<'][1]=-1;
   l['v'][0]=l['>'][1]=1;
   for (i=1;i<=n;i++)
      gets(map[i]+1);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         x=i+l[turn[i][j]][0];
         y=j+l[turn[i][j]][1];
         if (x>0&&y>0&&x<=n&&y<=m)
            f[i][j][0]=(struct case1){x,y,map[x][y]-'a'};
      }
   for (i=1;i<=30;i++)
   {
      for (j=1;j<=n;j++)
         for (k=1;k<=m;k++)
            if (f[j][k][i-1].x)
            {
               x=f[j][k][i-1].x;
               y=f[j][k][i-1].y;
               if (f[x][y][i-1].x)
                  f[j][k][i]=(struct case1){f[x][y][i-1].x,f[x][y][i-1].y,f[j][k][i-1].hash+f[x][y][i-1].hash*s};
            }
      s*=s;
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (f[i][j][30].x)
            ll[i][j]=(1<<30);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (!f[i][j][30].x)
         {
            x=i;
            y=j;
            while (f[x][y][0].x)
            {
               k=30;
               while (!f[x][y][--k].x);
               ll[i][j]+=(1<<k);
               px=x;
               py=y;
               x=f[px][py][k].x;
               y=f[px][py][k].y;
            }
      }
   scanf("%ld\n",&q);
   while (q--)
   {
      gets(str+1);
      len=hash=t=0;
      for (i=1;str[i];i++)
         if (str[i]>='0'&&str[i]<='9'&&!(str[i+1]>='0'&&str[i+1]<='9'))
         {
            x=i;
            while (str[--x]!='(');
            y=x;
            while (str[++y]!=')');
            num=rec=t=0;
            for (j=y+1;j<=i;j++)
               num=num*10+str[j]-'0';
            for (j=y-1;j>x;j--)
               rec=rec*29+str[j]-'a';
            hash+=mi(29,len)*(work(mi(29,y-x-1),num-1)*rec);
            len+=(y-x-1)*num;
         }
         else if (str[i]=='(')
            t=1;
         else if (!t&&str[i]>='a'&&str[i]<='z')
         {
            hash+=(str[i]-'a')*mi(29,len);
            len++;
         }
      for (i=1;i<=n;i++)
         for (j=1;j<=m;j++)
            if (ll[i][j]+1>=len&&check(i,j,len)==hash)
            {
               printf("YES (%ld,%ld)\n",i,j);
               goto out;
            }
      puts("NO");
      out:;
   }
   return 0;
}
