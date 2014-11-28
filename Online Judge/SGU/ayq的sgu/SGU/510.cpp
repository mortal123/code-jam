#include <iostream>
#include <map>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

map<string,bool>hash;
string str;
long n;

long count(long len)
{
   long i,j,s=0;
   hash.clear();
   for (i=1;i<=len;i++)
      for (j=1;i+j-1<=len;j++)
         if (!hash.count(str.substr(j,i)))
            hash[str.substr(j,i)]=1;
         else
            s++;
   return s;
}

bool find(long now,long tot,long last)
{
   long i,tmp=count(now-1);
   if (tot-tmp<n||now*(now-1)/2-tmp>n)
      return 0;
   if (now==str.size())
   {
      if (now*(now-1)/2-tmp==n)
      {
         cout<<str.substr(1,now-1)<<endl;
         return 1;
      }
   }
   else
      for (i=1;i<=last+1;i++)
      {
         str[now]='a'+i-1;
         if (find(now+1,tot,max(last,i)))
            return 1;
      }
   return 0;
}

int main()
{
   long i;
   cin>>n;
   for (i=1;i<=n;i++)
   {
      str.clear();
      str.resize(i+1);
      if (find(1,i*(i+1)/2,0))
         break;
   }
   return 0;    
}
