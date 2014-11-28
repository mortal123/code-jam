#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 210;

int N, cnt;
long long P;
long long Mat[MAXN][MAXN];

void Init()
{
	for(int i = 1;i <= N;i++)
		for(int j = 1;j <= N;j++)
			scanf("%lld", &Mat[i][j]), Mat[i][j] = (Mat[i][j] % P + P) % P;
}

void Work()
{
	cnt = 0;
	for(int i = 1;i <= N;i++)
	{
		int l;
		if (Mat[i][i] == 0)
		{
			for(l = i + 1;l <= N;l++)
				if (Mat[l][i] != 0)
					break;
			if (l > N)
				continue;
			for(int j = 1;j <= N;j++)
				swap(Mat[i][j], Mat[l][j]);
			cnt++;
		}
		for(int j = i + 1;j <= N;j++)
		{
			while(Mat[j][i] != 0)
			{
				for(int k = 1;k <= N;k++)
					swap(Mat[i][k], Mat[j][k]);
				long long tmp = Mat[j][i] / Mat[i][i];	
				//printf("tmp: %I64d %I64d %I64d\n", tmp, Mat[j][i], Mat[i][i]);
				for(int k = 1;k <= N;k++)
					Mat[j][k] -= Mat[i][k] * tmp, Mat[j][k] = (Mat[j][k] % P + P) % P;
				cnt++;
			}
		}
	}
	long long Ans = 1;
	for(int i = 1;i <= N;i++)
		Ans = Ans * Mat[i][i] % P;
	if (cnt % 2 == 1)
		Ans = (-Ans + P) % P;
	printf("%lld\n", Ans);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(scanf("%d %lld", &N, &P) == 2)
	{
		Init();
		Work();
	}
	return 0;
}
