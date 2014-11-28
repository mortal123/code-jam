#include <stdio.h>
#include <string.h>

int oka[15][15][15],okb[15][15][15],rec[15],sign[15],la[15],lb[15],na[15][25][27],nb[15][25][27];
char a[15][15],b[15][15];
int n,m,s=0;

int dfs2(int now)
{
   int i,j,k;
   if (now==s+1)
   {
      for (i=2;i<=n;i++)
         if (oka[now-1][i][oka[now-1][i][0]]!=la[i])
            return 0;
      for (i=1;i<=m;i++)
         if (okb[now-1][i][okb[now-1][i][0]]==lb[i])
            return 0;
      return 1;
   }
   else
   {
      sign[now]=rec[now]-rec[now-1];
      for (i=2;i<=n;i++)
      {
         oka[now][i][0]=0;
         for (j=1;j<=oka[now-1][i][0]&&oka[now-1][i][j]+rec[now]-rec[now-1]+s-now<=la[i];j++)
            if (a[i][oka[now-1][i][j]+rec[now]-rec[now-1]]==a[1][rec[now]])
               oka[now][i][++oka[now][i][0]]=oka[now-1][i][j]+rec[now]-rec[now-1];
         if (!oka[now][i][0])
            goto loop;
      }
      for (i=1;i<=m;i++)
      {
         okb[now][i][0]=0;
         for (j=1;j<=okb[now-1][i][0]&&okb[now-1][i][j]+rec[now]-rec[now-1]+s-now<=lb[i];j++)
            if (b[i][okb[now-1][i][j]+rec[now]-rec[now-1]]==a[1][rec[now]])
               okb[now][i][++okb[now][i][0]]=okb[now-1][i][j]+rec[now]-rec[now-1];
      }
      if (dfs2(now+1))
         return 1;
      loop:
      for (i=rec[now]-rec[now-1]-1;i>=0;i--)
      {
         sign[now]=i;
         for (j=2;j<=n;j++)
         {
            oka[now][j][0]=0;
            for (k=na[j][oka[now-1][j][1]+i][a[1][rec[now]]-'a'];k&&k+s-now<=la[j];k=na[j][k][a[1][rec[now]]-'a'])
               oka[now][j][++oka[now][j][0]]=k;
            if (!oka[now][j][0])
               break;
         }
         if (j>n)
         {
            for (j=1;j<=m;j++)
            {
               okb[now][j][0]=0;
               if (okb[now-1][j][0])
                  for (k=nb[j][okb[now-1][j][1]+i][a[1][rec[now]]-'a'];k&&k+s-now<=lb[j];k=nb[j][k][a[1][rec[now]]-'a'])
                     okb[now][j][++okb[now][j][0]]=k;
            }
            if (dfs2(now+1))
               return 1;
         }
      }
   }
   return 0;
}

int dfs1(int now)
{
   int i;
   if (now>la[1])
   {
      if (dfs2(1))
         return 1;
   }
   else
   {
      if (now!=la[1]&&dfs1(now+1))
         return 1;
      rec[++s]=now;
      if (dfs1(now+1))
         return 1;
      s--;
   }
   return 0;
}

int main()
{
   int i,j,k,l;
   scanf("%d%d\n",&n,&m);
   for (i=1;i<=n;i++)
   {
      gets(a[i]+1);
      la[i]=strlen(a[i]+1);
      a[i][++la[i]]='z'+1;
      oka[0][i][0]=1;
      for (j=0;j<=la[i];j++)
         for (k=0;k<=26;k++)
         {
            for (l=j+1;l<=la[i]&&a[i][l]!=k+'a';l++);
            if (l<=la[i])
               na[i][j][k]=l;
         }
   }
   for (i=1;i<=m;i++)
   {
      gets(b[i]+1);
      lb[i]=strlen(b[i]+1);
      b[i][++lb[i]]='z'+1;
      okb[0][i][0]=1;
      for (j=0;j<=lb[i];j++)
         for (k=0;k<=26;k++)
         {
            for (l=j+1;l<=lb[i]&&b[i][l]!=k+'a';l++);
            if (l<=lb[i])
               nb[i][j][k]=l;
         }
   }
   if (dfs1(1))
      for (i=1;i<=s;i++)
      {
         if (sign[i]==rec[i]-rec[i-1])
            for (j=1;j<=sign[i]-1;j++)
               putchar('?');
         else
         {
            for (j=1;j<=sign[i];j++)
               putchar('?');
            putchar('*');
         }
         if (i<s)
            printf("%c",a[1][rec[i]]);
      }
   else
      printf("OOPS");
   puts("");
   return 0;
}
