#include <stdio.h>

double x[31]={0},y[31]={0},f[31]={0};
char stop[31]={'\0'};

int main()
{
   long i,j,k,l,n;
   double s,ans;
   scanf("%ld",&n);
   for (i=17;i<=21;i++)
   {
      memset(f,0,sizeof(f));
      x[i]=f[0]=1;
      for (j=0;j<i;j++)
         for (k=1;k<=6;k++)
            f[j+k]+=f[j]/6;
      for (j=i;j<=21;j++)
         x[i]-=f[j];
   }
   for (i=21;i>=0;i--)
   {
      s=0;
      for (j=1;j<=6;j++)
         s+=x[i+j]/6;
      if (s>x[i])
         x[i]=s;
   }
   memset(f,0,sizeof(f));
   y[0]=1;
   for (i=0;i<=18;i++)
      for (j=1;j<=6;j++)
         y[i+j]+=y[i]/6;
   ans=x[0]*(1-y[21]-y[20]-y[19]);
   for (i=19;i<=21;i++)
   {
      for (j=0;j<=21;j++)
      {
         memset(stop,'\0',sizeof(stop));
         memset(f,0,sizeof(f));
         f[22]=f[23]=f[24]=f[25]=f[26]=f[27]=-n-1;
         for (k=21;k>=0;k--)
         {
            s=0;
            for (l=1;l<=6;l++)
               s+=f[k+l]/6;
            f[k]=(2*(k>=i)-1)*n+2*(k>=j)-1;
            if (s+1e-10<f[k])
               stop[k]=1;
            else
               f[k]=s;
         }
         memset(f,0,sizeof(f));
         f[0]=x[j]=1;
         for (k=0;k<=21;k++)
            if (stop[k])
               x[j]-=(k>=j)*f[k];
            else
               for (l=1;l<=6;l++)
                  f[k+l]+=f[k]/6;
      }
      memset(stop,'\0',sizeof(stop));
      memset(f,0,sizeof(f));
      for (j=21;j>=0;j--)
      {
         s=0;
         for (k=1;k<=6;k++)
            s+=x[j+k]/6;
         if (s+1e-10<x[j])
            stop[j]=1;
         else
            x[j]=s;
      }
      s=0;
      f[0]=1;
      for (j=0;j<=21;j++)
         if (stop[j])
            s+=f[j]*x[j];
         else
            for (k=1;k<=6;k++)
               f[j+k]+=f[j]/6;
      ans+=s*y[i];
   }
   printf("%.6lf\n",ans);
   return 0;
}
