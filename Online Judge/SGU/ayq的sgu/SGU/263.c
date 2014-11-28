#include <stdio.h>
#define lowbit(a) ((a)&(-(a)))

long st[1000005]={0},en[1000005]={0};
long long sum[1000005]={0};
char str[51]={'\0'};

void ins(long p[],long i,long add)
{
   for (;i<=1000000;i+=lowbit(i))
      p[i]+=add;
}

long que(long p[],long i)
{
   long s=0;
   for (;i;i-=lowbit(i))
      s+=p[i];
   return s;
}

void ins_sum(long i,long add)
{
   for (;i<=1000000;i+=lowbit(i))
      sum[i]+=add;
}

long long que_sum(long i)
{
   long long s=0;
   for (;i;i-=lowbit(i))
      s+=sum[i];
   return s;
}

long find(long p[],long x)
{
   long l=0,r=1000000,mid;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (que(p,mid)>=x)
         r=mid;
      else
         l=mid;
   }
   return r;
}

long read(long *i)
{
   long s=0;
   while (str[*i]>='0'&&str[*i]<='9')
   {
      s=s*10+str[*i]-'0';
      (*i)++;
   }
   (*i)++;
   return s;
}

int main()
{
   long q,i,a,b,c,f1,f2,ans=0;
   scanf("%ld\n",&q);
   while (q--)
   {
      gets(str+1);
      if (str[1]=='p')
      {
         i=5;
         a=read(&i);
         b=read(&i);
         c=que_sum(a)-que_sum(a-1);
         ins_sum(a,b);
         f1=(a!=1&&que(en,a-1)-que(en,a-2));
         f2=(a!=1000000&&que(st,a+1)-que(st,a));
         if (!c)
         {
            if (f1&&f2)
               ans--;
            if (!f1&&!f2)
               ans++;
            if (f1)
               ins(en,a-1,-1);
            else
               ins(st,a,1);
            if (f2)
               ins(st,a+1,-1);
            else
               ins(en,a,1);
         }
      }
      else if (str[2]=='p')
      {
         i=6;
         a=read(&i);
         b=read(&i)+find(st,a)-1;
         c=read(&i);
         ins_sum(b,c);
      }
      else if (str[2]=='o')
         printf("%ld towers\n",ans);
      else if (str[1]=='c')
      {
         i=7;
         a=read(&i);
         b=find(st,a);
         c=find(en,a);
         printf("%I64d cubes in %ldth tower\n",que_sum(c)-que_sum(b-1),a);
      }
      else if (str[1]=='l')
      {
         i=8;
         a=read(&i);
         b=find(st,a);
         c=find(en,a);
         printf("length of %ldth tower is %ld\n",a,c-b+1);
      }
      else
      {
         i=8;
         a=read(&i);
         b=read(&i);
         c=find(st,a)+b-1;
         printf("%I64d cubes in %ldth column of %ldth tower\n",que_sum(c)-que_sum(c-1),b,a);
      }
   }
   return 0;
}
