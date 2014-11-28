#include <stdio.h>

struct case1
{
   long num,flag,size,l,r;
}p[130003]={{0,0,0,0,0}};
long n,tot=0;

void maintain(long now)
{
  long t;
  if(p[now].flag)
  {
     t=p[now].r;
     p[now].r=p[now].l;
     p[now].l=t;
     p[p[now].l].flag^=1;
     p[p[now].r].flag^=1;
     p[now].flag=0;
  }
}

void left(long *now)
{
   long son;
   maintain(*now);
   son=p[*now].r;
   maintain(son);
   p[*now].r=p[son].l;
   p[son].l=*now;
   p[*now].size=p[p[*now].l].size+p[p[*now].r].size+1;
   p[son].size=p[p[son].l].size+p[p[son].r].size+1;
   *now=son;
}

void right(long *now)
{
   long son;
   maintain(*now);
   son=p[*now].l;
   maintain(son);
   p[*now].l=p[son].r;
   p[son].r=*now;
   p[*now].size=p[p[*now].l].size+p[p[*now].r].size+1;
   p[son].size=p[p[son].l].size+p[p[son].r].size+1;
   *now=son;
}

void rot(long *now,long s)
{
   maintain(*now);
   if(s==p[p[*now].l].size+1)
      return;
   if (s<=p[p[*now].l].size)
   {
      rot(&p[*now].l,s);
      right(now);
   }
   else
   {
      rot(&p[*now].r,s-p[p[*now].l].size-1);
      left(now);
   }
}

void print(long now)
{
   if(!now)
      return;
   maintain(now);
   print(p[now].l);
   if(p[now].num>=1&&p[now].num<=n)
      printf("%ld%c",p[now].num,((++tot)==n)?'\n':' ');
   print(p[now].r);
}

long build(long st,long en,long layer)
{
   long now=++tot,mid=(st+en)>>1;
   p[now].num=mid;
   if (st<mid)
      p[now].l=build(st,mid-1,layer+1);
   if (mid<en)
      p[now].r=build(mid+1,en,layer+1);
   p[now].size=p[p[now].l].size+p[p[now].r].size+1;
   return now;
}

int main()
{
   long i,m,x,y,head;
   scanf("%ld%ld",&n,&m);
   head=build(0,n+1,0);
   for(i=1;i<=m;i++)
   {
      scanf("%ld%ld",&x,&y);
      rot(&head,x);
      rot(&head,y+2);
      maintain(head);
      maintain(p[head].l);
      p[p[p[head].l].r].flag^=1;
   }
   tot=0;
   print(head);
   return 0;
}
