#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char hash[100001]={'\0'};
long big[20001]={0},mi[20001]={0},tt[20001]={0},prime[21]={0},s[21]={0},rec[21]={0},ans[21]={0},P[21]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,51,53};
long ptot,lmi,tot=0,flag=0;
double tmp;

void quick(long a,long b)
{
   long i,j;
   if (b==0)
   {
      memset(mi,0,sizeof(mi));
      lmi=mi[1]=1;
   }
   else
   {
      quick(a,b>>1);
      for (i=1;i<=2*lmi;i++)
         tt[i]=0;
      for (i=1;i<=lmi;i++)
         for (j=1;j<=lmi;j++)
            tt[i+j-1]+=mi[i]*mi[j];
      for (i=1;i<=2*lmi;i++)
      {
         mi[i]=tt[i]+mi[i-1]/100;
         mi[i-1]%=100;
      }
      lmi<<=1;
      while (!mi[lmi])
         lmi--;
      if (b&1)
      {
         lmi++;
         for (i=1;i<=lmi;i++)
         {
            mi[i]=mi[i]*a+mi[i-1]/100;
            mi[i-1]%=100;
         }
         while (!mi[lmi])
            lmi--;
      }
   }
}

void dfs(long now,long max,long last)
{
   long i,j,t;
   double sum;
   if (now>tot)
   {
      for (i=1;i<=max;i++)
         rec[i]=s[i];
      for (i=1;i<max;i++)
         for (j=i+1;j<=max;j++)
            if (rec[i]<rec[j])
            {
               t=rec[i];
               rec[i]=rec[j];
               rec[j]=t;
            }
      sum=0;
      for (i=1;i<=max;i++)
         sum+=(rec[i]-1)*log(P[i]);
      if (!flag||sum<tmp)
      {
         tmp=sum;
         ptot=max;
         for (i=1;i<=max;i++)
            ans[i]=rec[i]-1;
      }
      flag=1;
   }
   else
      for (i=((prime[now]==prime[now-1])?last:1);i<=max+1;i++)
      {
         s[i]*=prime[now];
         dfs(now+1,max+(i>max),i);
         s[i]/=prime[now];
      }
}

int main()
{
   long i,j,k,n,t,l;
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
      if (!hash[i])
         for (j=2;i*j<=n;j++)
            hash[i*j]=1;
   t=n;
   for (i=2;i<=n;i++)
      if (!hash[i])
         while (t%i==0)
         {
            prime[++tot]=i;
            t/=i;
         }
   for (i=1;i<=20;i++)
      s[i]=1;
   dfs(1,0,0);
   big[1]=l=1;
   for (i=1;i<=ptot;i++)
   {
      quick(P[i],ans[i]);
      for (j=1;j<=l+lmi;j++)
         tt[j]=0;
      for (j=1;j<=l;j++)
         for (k=1;k<=lmi;k++)
            tt[j+k-1]+=big[j]*mi[k];
      for (j=1;j<=l+lmi;j++)
      {
         big[j]=tt[j]+big[j-1]/100;
         big[j-1]%=100;
      }
      l+=lmi;
      while (!big[l])
         l--;
   }
   printf("%ld",big[l]);
   for (i=l-1;i>=1;i--)
      printf("%.2ld",big[i]);
   printf("\n");
   return 0;
}
