#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct case1
{
   int f,v;
}p[201],rec[25001],tmp[201];
char str[201][25],name[101][25],name2[201][25],hash[201];
int n;

int check(int x)
{
   int i;
   for (i=1;i<=n;i++)
      if (!strcmp(str[i]+3,name[x]+1))
         return 0;
   for (i=1;i<x;i++)
      if (!strcmp(name[i]+1,name[x]+1))
         return 0;
   return 1;
}

int main()
{
   int i,j,k,o,ans=0,s=0,cur=0,cnew=0;
   struct case1 t;
   scanf("%d\n",&n);
   for (i=1;i<=n;i++)
   {
      gets(str[i]+1);
      if (str[i][1]=='=')
         for (j=3;str[i][j]>='0'&&str[i][j]<='9';j++)
            p[i].v=p[i].v*10+str[i][j]-'0';
      else
      {
         p[i].f=1-2*(str[i][1]=='-');
         for (j=1;j<i&&strcmp(str[j]+3,str[i]+3);j++);
         if (j==i)
         {
            p[i].v=++s;
            strcpy(name2[s]+1,str[i]+3);
         }
         else
            p[i].v=p[j].v;
      }
   }
   for (i=1;i<=100;i++)
      do
         for (j=1;j<=16;j++)
            name[i][j]=rand()%26+'a';
      while (!check(i));
   for (i=1;i<=n;i++)
      if (p[i].f==-1)
      {
         if (!hash[p[i].v])
         {
            rec[++ans]=(struct case1){1,p[i].v};
            cur++;
         }
         rec[++ans]=(struct case1){-1,p[i].v};
         hash[p[i].v]=0;
         cur--;
      }
      else if (p[i].f==1)
      {
         if (hash[p[i].v])
         {
            rec[++ans]=(struct case1){-1,p[i].v};
            cur--;
         }
         rec[++ans]=(struct case1){1,p[i].v};
         hash[p[i].v]=1;
         cur++;
      }
      else
      {
         o=0;
         for (j=1;j<=s;j++)
            if (hash[j])
            {
               for (k=i+1;k<=n;k++)
                  if (p[k].v==j)
                     if (p[k].f==1)
                        break;
                     else if (p[k].f==-1)
                        goto out;
               tmp[++o]=(struct case1){j,k};
               out:;
            }
         for (j=1;j<o;j++)
            for (k=j+1;k<=o;k++)
               if (tmp[j].v>tmp[k].v)
               {
                  t=tmp[j];
                  tmp[j]=tmp[k];
                  tmp[k]=t;
               }
         for (j=1;j<=o;j++)
            if (cur>p[i].v)
            {
               rec[++ans]=(struct case1){-1,tmp[j].f};
               hash[tmp[j].f]=0;
               cur--;
            }
         while (cnew&&cur>p[i].v)
         {
            rec[++ans]=(struct case1){-2,cnew--};
            cur--;
         }
         for (j=1;j<=s;j++)
            if (cur>p[i].v&&hash[j])
            {
               for (k=i+1;k<=n&&(!p[k].f||p[k].v!=j);k++);
               if (k>n)
               {
                  rec[++ans]=(struct case1){-1,j};
                  hash[j]=0;
                  cur--;
               }
            }
         o=0;
         for (j=1;j<=s;j++)
            if (hash[j])
            {
               for (k=i+1;!p[k].f||p[k].v!=j;k++);
               tmp[++o]=(struct case1){j,k};
            }
         for (j=1;j<o;j++)
            for (k=j+1;k<=o;k++)
               if (tmp[j].v<tmp[k].v)
               {
                  t=tmp[j];
                  tmp[j]=tmp[k];
                  tmp[k]=t;
               }
         for (j=1;j<=o;j++)
            if (cur>p[i].v)
            {
               rec[++ans]=(struct case1){-1,tmp[j].f};
               hash[tmp[j].f]=0;
               cur--;
            }
         o=0;
         for (j=1;j<=s;j++)
            if (!hash[j])
            {
               for (k=i+1;k<=n;k++)
                  if (p[k].v==j)
                     if (p[k].f==-1)
                        break;
                     else if (p[k].f==1)
                        goto out2;
               tmp[++o]=(struct case1){j,k};
               out2:;
            }
         for (j=1;j<o;j++)
            for (k=j+1;k<=o;k++)
               if (tmp[j].v>tmp[k].v)
               {
                  t=tmp[j];
                  tmp[j]=tmp[k];
                  tmp[k]=t;
               }
         for (j=1;j<=o;j++)
            if (cur<p[i].v)
            {
               rec[++ans]=(struct case1){1,tmp[j].f};
               hash[tmp[j].f]=1;
               cur++;
            }
         while (cur<p[i].v)
         {
            rec[++ans]=(struct case1){2,++cnew};
            cur++;
         }
         rec[++ans]=(struct case1){0,p[i].v};
      }
   printf("%d\n",ans);
   for (i=1;i<=ans;i++)
      if (rec[i].f==-2)
         printf("- %s\n",name[rec[i].v]+1);
      else if (rec[i].f==-1)
         printf("- %s\n",name2[rec[i].v]+1);
      else if (rec[i].f==2)
         printf("+ %s\n",name[rec[i].v]+1);
      else if (rec[i].f==1)
         printf("+ %s\n",name2[rec[i].v]+1);
      else
         printf("= %d\n",rec[i].v);
   return 0;
}
