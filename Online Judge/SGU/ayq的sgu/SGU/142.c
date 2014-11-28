#include<stdio.h>
#include<math.h>
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long l,r,deep;
}trie[1000001]={{0,0,0}};
char str[500005]={'\0'};
long tot=1;

void insert(long now,char ch[],long len)
{
   if (len)
   {
      if (ch[0]=='a')
      {
         if (trie[now].l==0)
            trie[now].l=++tot;
         insert(trie[now].l,ch+1,len-1);
      }
      else
      {
         if (trie[now].r==0)
            trie[now].r=++tot;
         insert(trie[now].r,ch+1,len-1);
      }
   }
   trie[now].deep=min(trie[trie[now].l].deep,trie[trie[now].r].deep)+1;
}

void dfs(long now)
{
   if (now)
   {
      if (trie[trie[now].l].deep==trie[now].deep-1)
      {
         printf("a");
         dfs(trie[now].l);
      }
      else
      {
         printf("b");
         dfs(trie[now].r);
      }
   }
}

int main()
{
   long i,l,max;
   scanf("%ld",&l);
   getchar();
   max=log(l)/log(2)+1;
   gets(str+1);
   for (i=1;i<=l;i++)
      insert(1,str+i,min(l+1,i+max)-i);
   printf("%ld\n",trie[1].deep);
   dfs(1);
   printf("\n");
   return 0;
}
