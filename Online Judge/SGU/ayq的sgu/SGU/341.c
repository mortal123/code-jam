#include <stdio.h>
#include <string.h>

struct case1
{
   char a[66];
   int l,pos;
}tmp[5001];
char cmp[4][15]={"INPUT VALUES","INPUT(","OUTPUT("},*rec[5001],str[320005];
int f[5001],hash[5001],len[5001],que[5001],dff[5001],tdff[5001];
short link[5001][5001];
int s2=0,flag=0;

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=tmp[(x+y)>>1];
   if (x>=y)
      return;
   tmp[(x+y)>>1]=tmp[x];
   while (i<j)
   {
      while (i<j&&strcmp(tmp[j].a+1,t.a+1)>0)
         j--;
      if (i<j)
         tmp[i++]=tmp[j];
      while (i<j&&strcmp(tmp[i].a+1,t.a+1)<0)
         i++;
      if (i<j)
         tmp[j--]=tmp[i];
   }
   tmp[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int find()
{
   int l=0,r=s2,mid;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (strcmp(tmp[mid].a+1,str+1)>=0)
         r=mid;
      else
         l=mid;
   }
   return tmp[r].pos;
}

int dfs(int now)
{
   int i;
   if (hash[now]==flag)
      return f[now];
   if (rec[now][1]=='I')
      f[now]=str[link[now][0]]-'0';
   else if (rec[now][3]=='T')
      f[now]=!dfs(link[now][1]);
   else if (rec[now][1]=='A'||rec[now][2]=='A')
   {
      f[now]=1;
      for (i=1;i<=link[now][0];i++)
         f[now]&=dfs(link[now][i]);
      if (rec[now][1]!='A')
         f[now]^=1;
   }
   else if (rec[now][1]=='O'||rec[now][2]=='O')
   {
      f[now]=0;
      for (i=1;i<=link[now][0];i++)
         f[now]|=dfs(link[now][i]);
      if (rec[now][1]!='O')
         f[now]^=1;
   }
   else
      f[now]=dff[now];
   hash[now]=flag;
   return f[now];
}

int main()
{
   int i,j,l,n,s1=0,o1=0,o2=0;
   while (1)
   {
      gets(str+1);
      if (!strcmp(str+1,cmp[0]))
         break;
      else if (str[1]!='#'&&str[1])
      {
         l=strlen(str+1);
         rec[++s1]=(char*)malloc(sizeof(char)*(l+5));
         for (i=1;i<=l;i++)
            if (str[i]!=' ')
               rec[s1][++len[s1]]=str[i];
         rec[s1][len[s1]+1]=0;
         if (strncmp(rec[s1]+1,cmp[2],7))
         {
            tmp[++s2].pos=s1;
            if (!strncmp(rec[s1]+1,cmp[1],6))
               for (i=7;rec[s1][i]!=')';i++)
                  tmp[s2].a[++tmp[s2].l]=rec[s1][i];
            else
            {
               for (i=1;rec[s1][i]!='=';i++)
                  tmp[s2].a[++tmp[s2].l]=rec[s1][i];
               len[s1]=0;
               for (i=1;rec[s1][i]!='=';i++);
               for (i++;rec[s1][i];i++)
                  rec[s1][++len[s1]]=rec[s1][i];
               rec[s1][len[s1]+1]=0;
            }
         }
      }
   }
   qs(1,s2);
   for (i=1;i<=s1;i++)
      if (rec[i][1]=='I')
         link[i][0]=++o1;
      else if (rec[i][1]=='O'&&rec[i][2]=='U')
      {
         l=0;
         for (j=8;rec[i][j]!=')';j++)
            str[++l]=rec[i][j];
         str[l+1]=0;
         que[++o2]=find();
      }
      else
      {
         for (j=1;rec[i][j]!='(';j++);
         while (j<len[i])
         {
            l=0;
            for (j++;rec[i][j]!=','&&rec[i][j]!=')';j++)
               str[++l]=rec[i][j];
            str[l+1]=0;
            link[i][++link[i][0]]=find();
         }
      }
   while (gets(str+1)!=NULL)
      if (str[1])
      {
         flag++;
         for (i=1;i<=o2;i++)
            putchar('0'+dfs(que[i]));
         puts("");
         for (i=1;i<=s1;i++)
            if (rec[i][1]=='D')
               tdff[i]=dfs(link[i][1]);
         for (i=1;i<=s1;i++)
            if (rec[i][1]=='D')
               dff[i]=tdff[i];
      }
   return 0;
}
