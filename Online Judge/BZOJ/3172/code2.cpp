#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

char Trie[250001];
int num[2000001],ans[2000001],fail[2000001],queue[2000001],fa[2000001],st,en;
int son[2000001],next[2000001];
int ansnext[201];
bool visit[2000001];
int Ans[201];
int t,tt,i,j,k,n,tot,p,tmp,aim,ANS;
char ch;

void AC_build()
{
   int i,j;
   st=0;en=1;
   queue[1]=0;
   while(st<en)
   {
       ++st;
       for(i=son[queue[st]];i;i=next[i])
       {
           ++en;
           queue[en]=i;
           fa[en]=queue[st];
       }
       i=fa[st];
       while(i)
       {
           i=fail[i];
           for(j=son[i];j;j=next[j])if(Trie[j]==Trie[queue[st]])break;
           if(j)
           {
               fail[queue[st]]=j;
               break;
           }
       }
   }
}

void build_Trie()
{
   for(i=1;i<=n;++i)
   {
       ch=getchar();
       p=0;
       while(ch!='\n')
       {
           for(j=son[p];j;j=next[j])if(Trie[j]==ch)break;
           if(j==0)
           {
               ++tot;
               next[tot]=son[p];
               son[p]=tot;
               j=tot;
           }
           p=j;
           Trie[p]=ch;
           ++num[p];
           ch=getchar();
       }
       ansnext[i]=ans[p];
       ans[p]=i;
   }
}

int main()
{
	freopen("input.txt", "r", stdin);
   tot=0;
   memset(visit,true,sizeof(visit));
   scanf("%d\n",&n);
   build_Trie();
   AC_build();
   for(i=1;i<=tot;++i)
   {
       p=i;
       while(p)
       {
           for(j=ans[p];j;j=ansnext[j])
           Ans[j]+=num[i];
           p=fail[p];
       }
   }
   for(i=1;i<=n;++i)printf("%d\n",Ans[i]);
   //system("pause");
}
