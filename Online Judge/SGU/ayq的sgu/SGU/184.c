#include<stdio.h>
#define oo 2100000000
#define min(a,b) ((a)<(b)?(a):(b))

int main()
{
   long a,b,c,d,e,f,ans=oo;
   scanf("%ld%ld%ld%ld%ld%ld",&a,&b,&c,&d,&e,&f);
   ans=min(a/d,ans);
   ans=min(b/e,ans);
   ans=min(c/f,ans);
   printf("%ld\n",ans);
   return 0;
}
