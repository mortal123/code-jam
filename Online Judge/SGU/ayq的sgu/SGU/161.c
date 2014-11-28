#include <stdio.h>
#include <string.h>

long f[101][101]={0},d[101]={0},rec[101][101]={0},hash[101]={0},du[101]={0},mat[101][101][3]={0},num[257]={0},stack[257]={0},pos[27]={0},c[27]={0};
char sign[257]={'\0'},v[257]={'\0'},str[257]={'\0'};
long n,s,zero,pc,tot=0;

void dfs(long now,long last)
{
   long i,j;
   rec[++tot][0]=now-1;
   for (i=1;i<now;i++)
      rec[tot][i]=d[i];
   for (i=last+1;i<=n;i++)
      if (!hash[i])
      {
         for (j=i+1;j<=n;j++)
            if (f[i][j]||f[j][i])
               hash[j]++;
         d[now]=i;
         dfs(now+1,i);
         for (j=i+1;j<=n;j++)
            if (f[i][j]||f[j][i])
               hash[j]--;
      }
}

long find()
{
   long i,j;
   for (i=1;;i++)
      if (s==rec[i][0])
      {
         for (j=1;j<=s&&rec[i][j]==d[j];j++);
         if (j==s+1)
            return i;
      }
}

long check(long now)
{
   long i,j,t,top=0;
   if (now==pc+1)
   {
      for (i=1;i<=s;i++)
         if (v[i]=='0')
            stack[++top]=zero;
         else if (v[i]=='1')
            stack[++top]=1;
         else if (v[i]>='A'&&v[i]<='Z')
            stack[++top]=c[pos[v[i]-'A']];
         else if (v[i]=='~')
            stack[top]=mat[stack[top]][zero][0];
         else if (v[i]!='=')
         {
            if (v[i]=='>')
               stack[top-1]=mat[stack[top-1]][stack[top]][0];
            else if (v[i]=='&')
               stack[top-1]=mat[stack[top-1]][stack[top]][1];
            else if (v[i]=='|')
               stack[top-1]=mat[stack[top-1]][stack[top]][2];
            top--;
         }
         else
         {
            t=mat[mat[stack[top-num[i]]][stack[top-num[i]+1]][0]][mat[stack[top-num[i]+1]][stack[top-num[i]]][0]][1];
            for (j=num[i]-1;j>=1;j--)
               t=mat[t][mat[mat[stack[top-j]][stack[top-j+1]][0]][mat[stack[top-j+1]][stack[top-j]][0]][1]][1];
            stack[top-=num[i]]=t;
         }
      if (stack[1]!=1)
         return 0;
   }
   else
      for (i=1;i<=tot;i++)
      {
         c[now]=i;
         if (!check(now+1))
            return 0;
      }
   return 1;
}

int main()
{
   long i,j,k,l,m,a,b,top,flag=100;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      f[i][i]=1;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      du[a]++;
      f[a][b]=1;
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         for (k=1;k<=n;k++)
            f[j][k]|=(f[j][i]&f[i][k]);
   dfs(1,0);
   for (i=1;i<=tot;i++)
      for (j=1;j<=tot;j++)
      {
         s=0;
         for (k=1;k<=rec[j][0];k++)
         {
            for (l=1;l<=rec[i][0]&&!f[rec[j][k]][rec[i][l]];l++);
            if (l==rec[i][0]+1)
               d[++s]=rec[j][k];
         }
         mat[i][j][0]=find();
      }
   for (i=1;i<=tot;i++)
      for (j=i;j<=tot;j++)
      {
         s=0;
         flag++;
         for (k=1;k<=rec[i][0];k++)
            hash[rec[i][k]]=flag;
         for (k=1;k<=rec[j][0];k++)
            hash[rec[j][k]]=flag;
         for (k=1;k<=n;k++)
            if (hash[k]==flag)
            {
               for (l=1;l<=n&&(l==k||!f[k][l]||hash[l]!=flag);l++);
               if (l==n+1)
                  d[++s]=k;
            }
         mat[i][j][1]=mat[j][i][1]=find();
      }
   for (i=1;i<=tot;i++)
      for (j=i;j<=tot;j++)
      {
         s=0;
         flag++;
         for (k=1;k<=n;k++)
         {
            for (l=1;l<=rec[i][0]&&!f[k][rec[i][l]];l++);
            if (l<=rec[i][0])
            {
               for (l=1;l<=rec[j][0]&&!f[k][rec[j][l]];l++);
               if (l<=rec[j][0])
                  hash[k]=flag;
            }
         }
         for (k=1;k<=n;k++)
            if (hash[k]==flag)
            {
               for (l=1;l<=n&&(l==k||!f[k][l]||hash[l]!=flag);l++);
               if (l==n+1)
                  d[++s]=k;
            }
         mat[i][j][2]=mat[j][i][2]=find();
      }
   s=0;
   for (i=1;i<=n;i++)
      if (!du[i])
         d[++s]=i;
   zero=find();
   scanf("%ld\n",&n);
   while (n--)
   {
      gets(str+1);
      l=strlen(str+1);
      s=top=pc=0;
      flag++;
      for (i=1;i<=l;i++)
      {
         if (str[i]=='0'||str[i]=='1'||str[i]>='A'&&str[i]<='Z')
         {
            v[++s]=str[i];
            if (str[i]>='A'&&str[i]<='Z'&&hash[str[i]-'A']!=flag)
            {
               pos[str[i]-'A']=++pc;
               hash[str[i]-'A']=flag;
            }
         }
         else
         {
            if (str[i]=='&')
               while (top&&(sign[top]=='~'||sign[top]=='&'))
                  v[++s]=sign[top--];
            else if (str[i]=='&'||str[i]=='|')
               while (top&&(sign[top]=='~'||sign[top]=='&'||sign[top]=='|'))
                  v[++s]=sign[top--];
            else if (str[i]=='='&&str[i+1]=='>')
            {
               i++;
               while (top&&(sign[top]=='~'||sign[top]=='&'||sign[top]=='|'))
                  v[++s]=sign[top--];
            }
            else if (str[i]=='=')
               while (top&&(sign[top]=='~'||sign[top]=='&'||sign[top]=='|'||sign[top]=='>'))
                  v[++s]=sign[top--];
            else if (str[i]==')')
            {
               while (sign[top]!='('&&sign[top]!='=')
                  v[++s]=sign[top--];
               if (sign[top]=='=')
               {
                  num[++s]=0;
                  v[s]='=';
                  while (sign[top]=='=')
                  {
                     num[s]++;
                     top--;
                  }
               }
               top--;
            }
            if (str[i]!=' '&&str[i]!=')')
               sign[++top]=str[i];
         }
      }
      while (top&&sign[top]!='=')
         v[++s]=sign[top--];
      if (sign[top]=='=')
      {
         num[++s]=0;
         v[s]='=';
         while (sign[top]=='=')
         {
            num[s]++;
            top--;
         }
      }
      if (!check(1))
         printf("in");
      printf("valid\n");
   }
   return 0;
}
