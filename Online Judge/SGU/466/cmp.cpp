#include<stdio.h>
#include<set>
#include<algorithm>
using namespace std;

void output(int l,int r)
{
    if(l==r)
        printf("%d",l);
    else
        printf("%d-%d",l,r);
}

set <pair <int,int> > cluster,used;
//cluster: first->len second->pos
//used:    first->pos second->len
char data[100001],opt[12];
int parked[100001][2];
int main()
{
    int n,q,i,a;
    set <pair <int,int> > :: iterator j;
    freopen("input.txt","r",stdin);
    freopen("output2.txt","w",stdout);
    scanf("%d%d%*c",&n,&q);
    scanf("%s",data);
    for(i=0;i<n&&data[i]=='.';++i);
    if(i<n)
        while(i<n)
        {
            used.insert(make_pair(i,1));
            int j;
            for(j=1;data[(i+j)%n]=='.';++j);
            if(j>1)
                cluster.insert(make_pair(j-1,(i+1)%n));
            i+=j;
        }
    else
        cluster.insert(make_pair(n,0));
    
    for(i=0;i<q;++i)
    {
        scanf("%s%d%*c",opt,&a);
        if(opt[0]=='P')
        {
            j=cluster.lower_bound(make_pair(a,-1));
            if(j==cluster.end())
            {
                parked[i][0]=-1;
                printf("NO ROOM\n");
            }
            else
            {
                if(j->second+a<=n)
                {
                    output(j->second+1,j->second+a);
                    printf("\n");
                }
                else
                {
                    output(1,j->second+a-n);
                    printf(",");
                    output(j->second+1,n);
                    printf("\n");
                }
                used.insert(make_pair(j->second,a));
                parked[i][0]=j->second;
                parked[i][1]=a;
                if(a<j->first)
                    cluster.insert(make_pair(j->first-a,(j->second+a)%n));
                cluster.erase(j);
            }
        }
        else
        {
            a--;
            if(parked[a][0]==-1)
                continue;
            used.erase(make_pair(parked[a][0],parked[a][1]));
            if(used.empty())
            {
                cluster.clear();
                cluster.insert(make_pair(n,0));
            }
            else
            {
                j=used.lower_bound(make_pair(parked[a][0],parked[a][1]));
                if(j==used.end())
                    j=used.begin();
                int l,r=j->first;
                if(j==used.begin())
                    j=used.end();
                j--;
                l=(j->first+j->second-1)%n;
                if((l+1)%n!=parked[a][0])
                    cluster.erase(make_pair((parked[a][0]-l-1+n)%n,(l+1)%n));
                if((parked[a][0]+parked[a][1])%n!=r)
                    cluster.erase(make_pair((r-parked[a][0]-parked[a][1]+2*n)%n,(parked[a][0]+parked[a][1])%n));
                cluster.insert(make_pair((r-l-1+n)%n,(l+1)%n));
            }
        }
    }
    return 0;
}
