#include <stdio.h>
#include <string.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=1e-7)
#define line(i,j,k) (zero((p[j].x-p[i].x)*(p[k].y-p[i].y)-(p[j].y-p[i].y)*(p[k].x-p[i].x))&&zero((p[j].x-p[i].x)*(p[k].z-p[i].z)-(p[j].z-p[i].z)*(p[k].x-p[i].x))&&zero((p[j].y-p[i].y)*(p[k].z-p[i].z)-(p[j].z-p[i].z)*(p[k].y-p[i].y)))

struct case1
{
   double x,y,z;
}p[101]={{0,0,0}};
char str[305]={'\0'},name[101][205]={'\0'},hash[101]={'\0'};
long rec[101]={0};

long read(long *l)
{
   long s=1,a=0;
   while (str[*l]==' ')
      (*l)--;
   while (str[*l]>='0'&&str[*l]<='9')
   {
      a+=s*(str[*l]-'0');
      s*=10;
      (*l)--;
   }
   if (str[*l]=='-')
   {
      a=-a;
      (*l)--;
   }
   return a;
}

int main()
{
   long i,j,k,l,n,f1,f2,ans=0;
   double a,b,c,x,y,z,x1,x2,y1,y2,z1,z2;
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
   {
      gets(str+1);
      l=strlen(str+1);
      p[i].z=read(&l);
      p[i].y=read(&l);
      p[i].x=read(&l);
      for (l--;l>=1;l--)
         name[i][l]=str[l];
   }
   for (i=3;i<=n&&line(1,2,i);i++);
   if (i>n)
   {
      for (i=1;i<=n;i++)
         hash[i]=1;
      goto end;
   }
   for (i=1;i<=n-2;i++)
      for (j=i+1;j<=n-1;j++)
         for (k=j+1;k<=n;k++)
            if ((!hash[i]||!hash[j]||!hash[k])&&!line(i,j,k))
            {
               x1=p[j].x-p[i].x;
               y1=p[j].y-p[i].y;
               z1=p[j].z-p[i].z;
               x2=p[k].x-p[i].x;
               y2=p[k].y-p[i].y;
               z2=p[k].z-p[i].z;
               if (!zero(z1*y2-z2*y1))
               {
                  a=1;
                  c=(x2*y1-x1*y2)/(z1*y2-z2*y1);
                  if (!zero(y1))
                     b=(-z1*c-x1)/y1;
                  else
                     b=(-z2*c-x2)/y2;
               }
               else if (!zero(y1*x2-y2*x1))
               {
                  c=1;
                  b=(z2*x1-z1*x2)/(y1*x2-y2*x1);
                  if (!zero(x1))
                     a=(-y1*b-z1)/x1;
                  else
                     a=(-y2*b-z2)/x2;
               }
               else
               {
                  b=1;
                  a=(y2*z1-y1*z2)/(x1*z2-x2*z1);
                  if (!zero(z1))
                     c=(-x1*a-y1)/z1;
                  else
                     c=(-x2*a-y2)/z2;
               }
               f1=f2=0;
               for (l=1;l<=n;l++)
                  if (l!=i&&l!=j&&l!=k)
                  {
                     x=p[l].x-p[i].x;
                     y=p[l].y-p[i].y;
                     z=p[l].z-p[i].z;
                     if (a*x+b*y+c*z<-1e-7)
                        f1=1;
                     else if (a*x+b*y+c*z>1e-7)
                        f2=1;
                     if (f1&f2)
                        break;
                  }
               if (l>n)
                  hash[i]=hash[j]=hash[k]=1;
            }
   end:
   for (i=1;i<=n;i++)
      if (hash[i])
         rec[++ans]=i;
   for (i=1;i<ans;i++)
      for (j=i+1;j<=ans;j++)
         if (strcmp(name[rec[i]]+1,name[rec[j]]+1)>0)
         {
            k=rec[i];
            rec[i]=rec[j];
            rec[j]=k;
         }
   printf("%ld\n",ans);
   for (i=1;i<=ans;i++)
      printf("%s\n",name[rec[i]]+1);
   return 0;
}
