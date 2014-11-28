#include <stdio.h>
#include <string.h>

struct case1
{
   long pos;
   char str[11];
}sort[801]={{0},{'\0'}};
char tmp[11]={'\0'},str[9001]={'\0'},nb[801][11]={'\0'},ng[801][11]={'\0'},rec[801][801][11]={'\0'};
long lb[801][801]={0},lg[801][801]={0},p[801]={0},f[801]={0};

void match(long x)
{
   long t;
   while (1)
   {
      p[x]++;
      if (!f[lb[x][p[x]]])
      {
         f[lb[x][p[x]]]=x;
         break;
      }
      else if (lg[lb[x][p[x]]][f[lb[x][p[x]]]]>lg[lb[x][p[x]]][x])
      {
         t=f[lb[x][p[x]]];
         f[lb[x][p[x]]]=x;
         match(t);
         break;
      }
   }
}

int main()
{
   long i,j,k,s,n,l,r,m;
   struct case1 t;
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
   {
      sort[i].pos=i;
      gets(str);
      for (k=0;str[k]!=' ';k++)
         nb[i][k]=sort[i].str[k]=str[k];
      for (j=1;j<=n;j++)
      {
         s=-1;
         for (k++;str[k]!=' '&&str[k];k++)
            rec[i][j][++s]=str[k];
      }
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (strcmp(sort[i].str,sort[j].str)>0)
         {
            t=sort[i];
            sort[i]=sort[j];
            sort[j]=t;
         }
   for (i=1;i<=n;i++)
   {
      gets(str);
      for (k=0;str[k]!=' ';k++)
         ng[i][k]=str[k];
      for (j=1;j<=n;j++)
      {
         s=-1;
         for (k++;str[k]!=' '&&str[k];k++)
            tmp[++s]=str[k];
         tmp[s+1]='\0';
         l=0;
         r=n;
         while (l<r-1)
         {
            m=(l+r)>>1;
            if (strcmp(sort[m].str,tmp)>=0)
               r=m;
            else
               l=m;
         }
         lg[i][sort[r].pos]=j;
      }
   }
   for (i=1;i<=n;i++)
   {
      sort[i].pos=i;
      strcpy(sort[i].str,ng[i]);
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (strcmp(sort[i].str,sort[j].str)>0)
         {
            t=sort[i];
            sort[i]=sort[j];
            sort[j]=t;
         }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         l=0;
         r=n;
         while (l<r-1)
         {
            m=(l+r)>>1;
            if (strcmp(sort[m].str,rec[i][j])>=0)
               r=m;
            else
               l=m;
         }
         lb[i][j]=sort[r].pos;
      }
   for (i=1;i<=n;i++)
      match(i);
   printf("YES\n");
   for (i=1;i<=n;i++)
      printf("%s %s\n",nb[f[i]],ng[i]);
   return 0;
}
