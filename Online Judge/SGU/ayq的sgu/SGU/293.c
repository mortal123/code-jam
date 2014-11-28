#include<stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

char s1[4015]={'\0'},s2[4015]={'\0'};
long p[5]={0};

void swap(long a,long b)
{
   char ch=s1[a];
   s1[a]=s1[b];
   s1[b]=ch;
   printf("%ld %ld\n",a,b);
}

int main()
{
   long i,j,x,y,l,t,n,tx,ty;
   scanf("%ld %s",&n,s1+1);
   printf("Qc\n0 0\n");
   tx=(s1[1]=='C');
   ty=(s1[1]=='Q');
   for (i=1;i<n;i++)
   {
      x=(tx+=(s1[i*2]=='C')+(s1[i*2+1]=='C'));
      y=(ty+=(s1[i*2]=='Q')+(s1[i*2+1]=='Q'));
      s2[i+1]=(x&1)?'C':'Q';
      x-=(x&1);
      y-=(y&1);
      l=min(x/2,y/2);
      for (j=1;j<=l;j++)
      {
         s2[j*2-1]='Q';
         s2[j*2]='C';
         x-=2;
         y-=2;
      }
      for (j=l*2+1;j<=i;j++)
         s2[j]=y?'Q':'C';
      for (j=i+2;j<=i*2+1;j++)
        s2[j]=s2[i*2-j+2];
      t=0;
      for (j=1;j<=i*2+1;j++)
        if (s1[j]!=s2[j])
           p[++t]=j;
      if (!t)
         printf("0 0\n0 0\n");
      else if (t==2)
      {
         printf("0 0\n");
         swap(p[1],p[2]);
      }
      else
      {
         swap(p[1],p[2]);
         swap(p[3],p[4]);
      }
   }
   return 0;
}
