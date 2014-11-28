#include <stdio.h>

struct case1
{
   char flag;
   long l,r;
   long long num,sum;
}p[2000005]={{'\0'},{0,0},{0,0}};
char str[51]={'\0'};
long pos,num,tot=0;

long build(long st,long en)
{
   long mid=(st+en)>>1,now=++tot;
   if (st<en-1)
   {
      p[now].l=build(st,mid);
      p[now].r=build(mid,en);
   }
   return now;
}

void clean(long now,long st,long en,long l,long r)
{
   long mid=(l+r)>>1;
   if (l==st&&r==en||p[now].flag)
   {
      p[now].num=p[now].sum=0;
      p[now].flag=1;
   }
   else
   {
      if (mid>=en)
         clean(p[now].l,st,en,l,mid);
      else if (mid<=st)
         clean(p[now].r,st,en,mid,r);
      else
      {
         clean(p[now].l,st,mid,l,mid);
         clean(p[now].r,mid,en,mid,r);
      }
      p[now].num=p[p[now].l].num+p[p[now].r].num;
      p[now].sum=p[p[now].l].sum+p[p[now].r].sum;
   }
}

void ins(long now,long pos,long add,long l,long r)
{
   long mid=(l+r)>>1;
   if (l==r-1)
   {
      p[now].num+=add;
      p[now].sum+=(long long)pos*add;
   }
   else
   {
      if (p[now].flag)
      {
         p[now].flag=0;
         p[p[now].l].flag=p[p[now].r].flag=1;
         p[p[now].l].num=p[p[now].r].num=p[p[now].l].sum=p[p[now].r].sum=0;
      }
      if (pos<mid)
         ins(p[now].l,pos,add,l,mid);
      else
         ins(p[now].r,pos,add,mid,r);
      p[now].num=p[p[now].l].num+p[p[now].r].num;
      p[now].sum=p[p[now].l].sum+p[p[now].r].sum;
   }
}

long long find(long now,long tot,long l,long r)
{
   long long rec;
   long mid=(l+r)>>1;
   if (p[now].num==tot)
   {
      pos=r-1;
      num=0;
      return p[now].sum;
   }
   if (l==r-1)
   {
      pos=l-1;
      num=tot;
      return (long long)tot*l;
   }
   if (p[now].flag)
   {
      p[now].flag=0;
      p[p[now].l].flag=p[p[now].r].flag=1;
      p[p[now].l].num=p[p[now].r].num=p[p[now].l].sum=p[p[now].r].sum=0;
   }
   p[now].num=p[p[now].l].num+p[p[now].r].num;
   p[now].sum=p[p[now].l].sum+p[p[now].r].sum;
   if (tot<=p[p[now].l].num)
      return find(p[now].l,tot,l,mid);
   return p[p[now].l].sum+find(p[now].r,tot-p[p[now].l].num,mid,r);
}

int main()
{
   long i,a;
   long long rec,b;
   build(1,1000001);
   while (gets(str+1)!=NULL)
   {
      a=b=0;
      for (i=((str[1]=='A')?8:5);str[i]!=' ';i++)
         a=a*10+str[i]-'0';
      for (i++;str[i];i++)
         b=b*10+str[i]-'0';
      if (str[1]=='A')
         ins(1,b,a,1,1000001);
      else if (p[1].num>=a)
      {
         rec=find(1,a,1,1000001);
         if (rec<=b)
         {
            printf("HAPPY\n");
            clean(1,1,pos+1,1,1000001);
            if (num)
               ins(1,pos+1,-num,1,1000001);
         }
         else
            printf("UNHAPPY\n");
      }
      else
         printf("UNHAPPY\n");
   }
   return 0;
}
