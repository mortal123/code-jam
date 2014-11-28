#include <stdio.h>
#include <string.h>
#define oo 1000000000
#define lex(a) ((str[a]=='?')?'a':str[a])
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long a,b;
   char c;
}rec[770][770]={{0,0},{'\0'}};
char str[770]={'\0'},t1[1540]={'\0'},t2[1540]={'\0'},ans[1540]={'\0'};
long f[770][770]={0};

void turn(long a,long b,char c[])
{
   long x,y,l=1,r=f[a][b];
   c[f[a][b]+1]='\0';
   while (a<=b)
   {
      if (rec[a][b].c)
         c[l++]=c[r--]=rec[a][b].c;
      x=a;
      y=b;
      a=rec[x][y].a;
      b=rec[x][y].b;
   }
}

long cmp(long a,long b,long c,long d)
{
   turn(a,b,t1);
   turn(c,d,t2);
   return strcmp(t1+1,t2+1);
}

void fit(long l,long r)
{
   if (l>r||rec[l][r].a)
      return;
   if (l==r)
   {
      rec[l][r]=(struct case1){l+1,r-1,(str[l]=='?')?'a':(str[l]*(str[l]!='*'))};
      return;
   }
   if (str[l]=='*'&&str[r]=='*')
   {
      if (f[l+1][r]<f[l][r-1])
         rec[l][r]=(struct case1){l+1,r,'\0'};
      else if (f[l+1][r]>f[l][r-1])
         rec[l][r]=(struct case1){l,r-1,'\0'};
      else
      {
         fit(l+1,r);
         fit(l,r-1);
         if (cmp(l+1,r,l,r-1)<0)
            rec[l][r]=(struct case1){l+1,r,'\0'};
         else
            rec[l][r]=(struct case1){l,r-1,'\0'};
      }
   }
   else if (str[l]=='*')
   {
      if (f[l+1][r]<f[l][r-1]+2)
         rec[l][r]=(struct case1){l+1,r,'\0'};
      else if (f[l+1][r]>f[l][r-1]+2)
         rec[l][r]=(struct case1){l,r-1,(str[r]=='?')?'a':str[r]};
      else
      {
         fit(l,r-1);
         fit(l+1,r);
         rec[l][r]=(struct case1){l,r-1,(str[r]=='?')?'a':str[r]};
         if (cmp(l,r,l+1,r)>0)
            rec[l][r]=(struct case1){l+1,r,'\0'};
      }
   }
   else if (str[r]=='*')
   {
      if (f[l][r-1]<f[l+1][r]+2)
         rec[l][r]=(struct case1){l,r-1,'\0'};
      else if (f[l][r-1]>f[l+1][r]+2)
         rec[l][r]=(struct case1){l+1,r,(str[l]=='?')?'a':str[l]};
      else
      {
         fit(l,r-1);
         fit(l+1,r);
         rec[l][r]=(struct case1){l+1,r,(str[l]=='?')?'a':str[l]};
         if (cmp(l,r,l,r-1)>0)
            rec[l][r]=(struct case1){l,r-1,'\0'};
      }
   }
   else if (str[l]!='?')
      rec[l][r]=(struct case1){l+1,r-1,str[l]};
   else if (str[r]!='?')
      rec[l][r]=(struct case1){l+1,r-1,str[r]};
   else
      rec[l][r]=(struct case1){l+1,r-1,'a'};
   fit(rec[l][r].a,rec[l][r].b);
}

int main()
{
   long i,j,l,n=0;
   gets(str+1);
   for (i=1;str[i];i++)
      if (str[i]=='!')
      {
         t1[++n]='?';
         t1[++n]='?';
         t1[++n]='?';
      }
      else if (str[i]!='*'||str[i-1]!='*')
         t1[++n]=str[i];
   strcpy(str+1,t1+1);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         f[i][j]=oo;
   for (i=1;i<=n;i++)
      f[i][i]=(str[i]!='*');
   for (l=2;l<=n;l++)
      for (i=1;i<=n-l+1;i++)
      {
         j=i+l-1;
         if (str[i]=='*'||str[j]=='*')
            f[i][j]=min(f[i+1][j]+2*(str[i]!='*'),f[i][j-1]+2*(str[j]!='*'));
         else if (str[i]=='?'||str[j]=='?'||str[i]==str[j])
            f[i][j]=f[i+1][j-1]+2;
      }
   if (f[1][n]<oo)
   {
      printf("YES\n");
      fit(1,n);
      turn(1,n,ans);
      puts(ans+1);
   }
   else
      printf("NO\n");
   return 0;
}
