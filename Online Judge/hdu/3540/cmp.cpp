#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

inline int min(int a,int b){return a<b?a:b;}

const int MAXN = 1000010;

char A[MAXN],B[1010];
int dp[2][1010];

int main()
{
    freopen("input.txt","r",stdin);
    int lim;
    while(~scanf("%s%s",A+1,B+1))
    {
        scanf("%d",&lim);
        //dp[i,j] = min{ dp[i-1,j]+1 , dp[i,j-1]+1 , dp[i-1,j-1]+(A[i]!=B[j]) }
        //dp[i,0] = 0
        //ans = min{ dp[i,len] }
        for(int j=0;j<=lim;j++)dp[0][j] = j;
        int len = strlen(B+1);
        int ans = lim+1,last = min(lim,len);//last记录上一次最后计算的位置 当前最多计算的位置为last+1
        int pre = 0,now = 1;
        for(int i=1,j;A[i];i++)
        {
            dp[now][0] = 0;
            for(j=1;j<=last;j++)
            {
                dp[now][j] = min(dp[pre][j],dp[now][j-1])+1;
                dp[now][j] = min(dp[now][j],dp[pre][j-1]+(A[i]!=B[j]));
            }
            //j = last+1
            dp[now][j] = min(dp[now][j-1]+1,dp[pre][j-1]+(A[i]!=B[j]));
            if(j>=len)ans = min(ans,dp[now][len]);
            last = min(len,last+1);
            while(dp[now][last]>lim)last--;            
            swap(pre,now);            
            //printf("%d\n", last);
        }
        printf("%d\n",ans>lim?-1:ans);
    }
    return 0;
}
