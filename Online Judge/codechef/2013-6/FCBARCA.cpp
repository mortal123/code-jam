#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000, MAXK = 10;
const long long mod = 1000000007;

int n, k;
long long f[MAXN + 5][MAXK + 5];

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d %d", &n, &k);
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 0; j <= k; j++)
				for(int l = 0; l <= k; l++)
					if (j != l)
						f[i][l] = (f[i][l] + f[i - 1][j]) % mod;
		printf("%I64d\n", f[n][0]);
	}
	return 0;
}
