#include<cstdio>

const int MAXN = 3001;
const double DINF = 1e100;

double q[MAXN],dp[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
    for(int t,n;~scanf("%d%d",&n,&t);)
    {
        for(int i=1;i<=n;i++)scanf("%lf",&q[i]);
        dp[n+1]=0;
        for(int i=n;i;i--)
        {            
            double sum = t+1+q[i]+(1-q[i])*dp[i+1];
            double inc = 1+q[i];//记录与k有关的
            double p = 1-q[i];
            dp[i]=sum;
            if (i == 1)
            printf("%.8lf\n\n", sum / (1 - q[i]));
            for(int k=2;i+k<=n+1;k++)
            {
                sum=sum-p*dp[i+k-1]+p*q[i+k-1]*(dp[i+k-1]+1)+p*(1-q[i+k-1])*dp[i+k]+inc;
                inc+=p*q[i+k-1];
                p*=(1-q[i+k-1]);
                if(sum<dp[i])dp[i]=sum;
                if (i == 1)
                	printf("%.8lf\n\n", sum / (1 - q[i]));
            }
            dp[i]/=(1-q[i]);
        }
        //for(int i = 1;i <= n + 1;i++)
        //	printf("%.8f\n",dp[i]);
        printf("%.8f\n",dp[1]);
    }
    return 0;
}
