#include <stdio.h>
#define oo 100000000000000LL
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long long add[6];
long long x,y,b,ans=oo;

long long check(long long dz)
{
   long long dx=x+dz,dy=y-dz,l=-1,r=oo,mid;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if ((1-b)*mid+max(max(add[0]-add[3]*b-x,add[4]-add[1]*b+y),add[2]-add[5]*b)>dz||(b-1)*mid+min(min(add[0]*b-add[3]-x,add[4]*b-add[1]+y),add[2]*b-add[5])<dz)
         l=mid;
      else
         r=mid;
   }
   return 6*r+max(2*add[0]-dx,2*add[3]+dx)+max(2*add[1]-dy,2*add[4]+dy)+max(2*add[2]-dz,2*add[5]+dz);
}

void work(long long d1,long long d2)
{
   long long l=-oo,r=oo,u,v,i;
   add[0]=add[1]=add[2]=add[3]=add[4]=add[5]=0;
   for (i=d1;;i=(i+1)%6)
   {
      add[i]=1;
      if (i==d2)
         break;
   }
   while (l<r-10000)
   {
      u=l+(r-l)/3;
      v=l+(r-l)*2/3;
      if (check(u)>=check(v))
         l=u;
      else
         r=v;
   }
   for (i=l;i<=r;i++)
      ans=min(ans,check(i));
}

int main()
{
   long long i,d1,d2;
   scanf("%I64d%I64d%I64d%I64d%I64d",&x,&y,&d2,&d1,&b);
   if (!x&&!y&&d1==d2)
   {
      puts("0");
      goto end;
   }
   work(d1,d2);
   work((d1+1)%6,d2);
   printf("%I64d\n",ans);
   end:
   return 0;
}
