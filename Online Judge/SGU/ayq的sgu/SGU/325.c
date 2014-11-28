#include <stdio.h>
#include <string.h>
#define oo 1000000000
#define lowbit(a) ((a)&(-(a)))

long *p[26]={NULL},tree[1000001]={0},st[26]={0},en[26]={0};
char hash[1000005]={'\0'},str[1000005]={'\0'};
long l;

long pos(long now)
{
   long s=0;
   for (;now;now-=lowbit(now))
      s+=tree[now];
   return s;
}

void add(long now,long add)
{
   for (;now<=l;now+=lowbit(now))
      tree[now]+=add;
}

int main()
{
   long long ans=0;
   long i,a,b,p1,p2,s=0;
   scanf("%s",str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
   {
      tree[i]=lowbit(i);
      en[str[i]-'A']++;
   }
   for (i=0;i<=25;i++)
      if (en[i]&1)
      {
         if (!s)
            s=1;
         else
         {
            ans=-1;
            goto end;
         }
      }
   for (i=0;i<=25;i++)
      p[i]=(long*)malloc(sizeof(long)*(en[i]+2));
   for (i=1;i<=l;i++)
      p[str[i]-'A'][++st[str[i]-'A']]=i;
   for (i=0;i<=25;i++)
      st[i]=1;
   p1=1;
   p2=l;
   for (i=1;i<=l/2;i++)
   {
      if (i==l/2)
         i=l/2;
      while (hash[p1])
         p1++;
      while (hash[p2])
         p2--;
      if (st[str[p2]-'A']<en[str[p2]-'A'])
         a=pos(p[str[p2]-'A'][st[str[p2]-'A']]);
      else
         a=oo;
      if (st[str[p1]-'A']<en[str[p1]-'A'])
         b=pos(p[str[p1]-'A'][en[str[p1]-'A']]);
      else
         b=-oo;
      if (a<=l+1-b)
      {
         ans+=a-i;
         add(p1,1);
         add(p[str[p2]-'A'][st[str[p2]-'A']],-1);
         hash[p[str[p2]-'A'][st[str[p2]-'A']++]]=1;
         hash[p[str[p2]-'A'][en[str[p2]-'A']--]]=1;
      }
      else
      {
         ans+=l-i+1-b;
         add(p[str[p1]-'A'][en[str[p1]-'A']],-1);
         hash[p[str[p1]-'A'][st[str[p1]-'A']++]]=1;
         hash[p[str[p1]-'A'][en[str[p1]-'A']--]]=1;
      }
   }
   end:
   printf("%I64d\n",ans);
   return 0;
}
