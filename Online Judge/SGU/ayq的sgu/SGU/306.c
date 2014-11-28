#include <stdio.h>

int a[101],b[101],c[101];
int std;

void print(int a[])
{
   int i;
   if (a[0])
      printf("%d",a[1]);
   for (i=2;i<=a[0];i++)
      printf("+%d",a[i]);
}

void work2(int a[],int b[],int d)
{
   int A[101]={0},B[101]={0},C[101]={0},D[101]={0},E[101]={0},F[101]={0};
   char ha[101]={0},hb[101]={0};
   int i;
   if (a[0]+b[0]==1)
   {
      for(i=1;i<=d;i++)
         printf("  ");
      printf("fake %d\n",a[0]?a[1]:b[1]);
   }
   else if (a[0]==1&&b[0]==1)
   {
      for(i=1;i<=d;i++)
         printf("  ");
      printf("weigh %d vs %d\n",a[1],std);
      for(i=1;i<=d;i++)
         printf("  ");
      printf("case <:\n");
      for(i=1;i<=d+1;i++)
         printf("  ");
      printf("fake %d\n",a[1]);
      for(i=1;i<=d;i++)
         printf("  ");
      printf("case =:\n");
      for(i=1;i<=d+1;i++)
         printf("  ");
      printf("fake %d\n",b[1]);
      for(i=1;i<=d;i++)
         printf("  ");
      puts("end");
   }
   else
   {
      for (i=1;i<=(a[0]+b[0]+1)/3;i++)
         if (i*2<=a[0])
         {
            A[++A[0]]=a[i*2-1];
            C[++C[0]]=a[i*2];
            ha[i*2-1]=ha[i*2]=1;
         }
         else
         {
            B[++B[0]]=b[(i-a[0]/2)*2-1];
            D[++D[0]]=b[(i-a[0]/2)*2];
            hb[(i-a[0]/2)*2-1]=hb[(i-a[0]/2)*2]=1;
         }
      for (i=1;i<=a[0];i++)
         if (!ha[i])
            E[++E[0]]=a[i];
      for (i=1;i<=b[0];i++)
         if (!hb[i])
            F[++F[0]]=b[i];
      for(i=1;i<=d;i++)
         printf("  ");
      printf("weigh ");
      print(A);
      if (A[0]&&B[0])
         printf("+");
      print(B);
      printf(" vs ");
      print(C);
      if (C[0]&&D[0])
         printf("+");
      print(D);
      puts("");
      for(i=1;i<=d;i++)
         printf("  ");
      printf("case <:\n");
      work2(A,D,d+1);
      if (E[0]+F[0])
      {
         for(i=1;i<=d;i++)
            printf("  ");
         printf("case =:\n");
         work2(E,F,d+1);
      }
      for(i=1;i<=d;i++)
         printf("  ");
      printf("case >:\n");
      work2(C,B,d+1);
      for(i=1;i<=d;i++)
         printf("  ");
      puts("end");
   }
}

void work1(int v[],int d)
{
   int a[101]={0},b[101]={0},c[101]={0};
   int i;
   if (v[0]==1)
   {
      for (i=1;i<=d;i++)
         printf("  ");
      printf("fake %d\n",v[1]);
   }
   else
   {
      for (i=1;i<=v[0]/3;i++)
         a[++a[0]]=v[i];
      for (i=v[0]/3+1;i<=v[0]/3*2;i++)
         b[++b[0]]=v[i];
      for (i=v[0]/3*2+1;i<=v[0]/3*3;i++)
         c[++c[0]]=v[i];
      if (v[0]%3==1)
      {
         a[++a[0]]=v[v[0]];
         b[++b[0]]=std;
      }
      else if (v[0]%3==2)
      {
         a[++a[0]]=v[v[0]-1];
         b[++b[0]]=std;
         c[++c[0]]=v[v[0]];
      }
      for(i=1;i<=d;i++)
         printf("  ");
      printf("weigh ");
      print(a);
      printf(" vs ");
      print(b);
      puts("");
      if (b[b[0]]==std)
         b[0]--;
      for(i=1;i<=d;i++)
         printf("  ");
      printf("case <:\n");
      work2(a,b,d+1);
      if (c[0])
      {
         for(i=1;i<=d;i++)
            printf("  ");
         printf("case =:\n");
         work1(c,d+1);
      }
      for(i=1;i<=d;i++)
         printf("  ");
      printf("case >:\n");
      work2(b,a,d+1);
      for(i=1;i<=d;i++)
         printf("  ");
      puts("end");
   }
}

int main()
{
   int i,n,ans=0,t=1;
   scanf("%d",&n);
   while (t<2*n)
   {
      ans++;
      t*=3;
   }
   printf("need %d weighings\n", ans);
   for (i=1;i<=(n+1)/3;i++)
      a[++a[0]]=i;
   for (i=(n+1)/3+1;i<=(n+1)/3*2;i++)
      b[++b[0]]=i;
   for (i=(n+1)/3*2+1;i<=n;i++)
      c[++c[0]]=i;
   printf("weigh ");
   print(a);
   printf(" vs ");
   print(b);
   puts("");
   printf("case <:\n");
   std=c[1];
   work2(a,b,1);
   printf("case =:\n");
   std=a[1];
   work1(c,1);
   printf("case >:\n");
   std=c[1];
   work2(b,a,1);
   puts("end");
   return 0;
}
