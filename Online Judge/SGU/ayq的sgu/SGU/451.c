#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   int dis,fa,ma,son,dau,x;
   char flag,sex;
}p[4000001];
char tmp[201],str[17][20]={"father","mother","son","daughter","husband","wife","brother","sister","grandfather","grandmother","grandson","granddaughter","uncle","aunt","nephew","niece"};
int pair[4000001],rec[11],l[17][4]={{1,1},{1,2},{1,3},{1,4},{2,3,1},{2,3,2},{2,1,3},{2,1,4},{2,5,1},{2,5,2},{2,6,3},{2,6,4},{3,5,1,3},{3,5,1,4},{3,1,6,3},{3,1,6,4}};
int min=oo,max=0,tot=1,o=0;
void dfs();

int set(int dis,int fa,int ma,int son,int dau,int x,char flag,char sex)
{
   p[++tot]=(struct case1){dis,fa,ma,son,dau,x,flag,sex};
   return tot;
}

void dfs2(int x,int now,int relate,int flag)
{
   if (now==l[rec[relate]][0]+1)
      dfs(x,relate+1);
   else if (l[rec[relate]][now]==1)
   {
      if (p[x].fa==0)
      {
         if (p[x].ma)
         {
            p[x].fa=set(p[p[x].ma].dis,0,0,p[p[x].ma].son,p[p[x].ma].dau,p[p[x].fa].x,1,0);
            pair[p[x].ma]=p[x].fa;
            pair[p[x].fa]=p[x].ma;
         }
         else
            p[x].fa=set(p[x].dis+1,0,0,0,0,x,1,0);
      }
      dfs2(p[x].fa,now+1,relate,p[x].flag);
   }
   else if (l[rec[relate]][now]==2)
   {
      if (p[x].ma==0)
      {
         if (p[x].fa)
         {
            p[x].ma=set(p[p[x].fa].dis,0,0,p[p[x].fa].son,p[p[x].fa].dau,p[p[x].fa].x,1,1);
            pair[p[x].ma]=p[x].fa;
            pair[p[x].fa]=p[x].ma;
         }
         else
            p[x].ma=set(p[x].dis+1,0,0,0,0,x,1,1);
      }
      dfs2(p[x].ma,now+1,relate,p[x].flag);
   }
   else if (l[rec[relate]][now]==3)
   {
      if (p[x].son==0)
         p[x].son=p[pair[x]].son=set(p[x].dis+1,p[x].sex?pair[x]:x,p[x].sex?x:pair[x],0,0,0,0,0);
      dfs2(p[x].son,now+1,relate,0);
      if (!flag&&p[x].x&&!p[p[x].x].sex)
         dfs2(p[x].x,now+1,relate,0);
   }
   else if (l[rec[relate]][now]==4)
   {
      if (p[x].dau==0)
         p[x].dau=p[pair[x]].dau=set(p[x].dis+1,p[x].sex?pair[x]:x,p[x].sex?x:pair[x],0,0,0,0,1);
      dfs2(p[x].dau,now+1,relate,0);
      if (!flag&&p[x].x&&p[p[x].x].sex)
         dfs2(p[x].x,now+1,relate,0);
   }
   else if (l[rec[relate]][now]==5)
   {
      if (p[x].fa==0)
      {
         if (p[x].ma)
         {
            p[x].fa=set(p[p[x].ma].dis,0,0,p[p[x].ma].son,p[p[x].ma].dau,p[p[x].fa].x,1,0);
            pair[p[x].ma]=p[x].fa;
            pair[p[x].fa]=p[x].ma;
         }
         else
            p[x].fa=set(p[x].dis+1,0,0,0,0,x,1,0);
      }
      dfs2(p[x].fa,now+1,relate,p[x].flag);
      if (p[x].ma==0)
      {
         if (p[x].fa)
         {
            p[x].ma=set(p[p[x].fa].dis,0,0,p[p[x].fa].son,p[p[x].fa].dau,p[p[x].fa].x,1,1);
            pair[p[x].ma]=p[x].fa;
            pair[p[x].fa]=p[x].ma;
         }
         else
            p[x].ma=set(p[x].dis+1,0,0,0,0,x,1,1);
      }
      dfs2(p[x].ma,now+1,relate,p[x].flag);
   }
   else
   {
      if (p[x].son==0)
         p[x].son=p[pair[x]].son=set(p[x].dis+1,p[x].sex?pair[x]:x,p[x].sex?x:pair[x],0,0,0,0,0);
      dfs2(p[x].son,now+1,relate,0);
      if (p[x].dau==0)
         p[x].dau=p[pair[x]].dau=set(p[x].dis+1,p[x].sex?pair[x]:x,p[x].sex?x:pair[x],0,0,0,0,1);
      dfs2(p[x].dau,now+1,relate,0);
      if (!flag&&p[x].x)
         dfs2(p[x].x,now+1,relate,0);
   }
}

void dfs(int x,int now)
{
   int i;
   if (now==o+1)
   {
      min=min(min,p[x].dis);
      max=max(max,p[x].dis);
   }
   else
      dfs2(x,1,now,0);
}

int main()
{
   int i,x,t,s=1;
   gets(tmp+1);
   while (1)
   {
      x=oo;
      for (i=0;i<=15;i++)
         if (strstr(tmp+s,str[i])!=NULL&&strstr(tmp+s,str[i])-tmp<x)
         {
            x=strstr(tmp+s,str[i])-tmp;
            t=i;
         }
      if (x==oo)
         break;
      rec[++o]=t;
      s=x+1;
      while (tmp[s]&&tmp[s]!=' ')
         s++;
   }
   p[1].flag=1;
   if (rec[1]!=4)
      dfs(1,1);
   if (rec[1]!=5)
      dfs(1,p[1].sex=1);
   printf("%d %d\n",max,min);
   return 0;
}
