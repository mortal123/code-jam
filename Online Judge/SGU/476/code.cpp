#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 4000;
const int MAXK = 22;
const int Size = 2000, rp = 10000;

int N, K;
vector <int> triple[MAXN];
int add[MAXN];
int visit[MAXN];

struct bigNum
{
	int dat[Size], len;	
	void clear()
	{
		memset(dat, 0, sizeof(dat));
		len = 1;
	}
	void operator *= (int k)
	{
		for(int i = 1; i <= len; i++)
			dat[i] *= k;
		for(int i = 1; i <= len; i++)
		{
			if (dat[i] >= rp)
			{
				dat[i + 1] += dat[i] / rp;
				dat[i] %= rp;
				if (i + 1 > len)
					len = i + 1;
			}
		}
	}
	void operator /= (int k)
	{
		for(int i = len; i >= 1; i--)
		{
			dat[i - 1] += dat[i] % k * rp;
			dat[i] /= k;
		}
		while(len > 1 && dat[len] == 0)
			len--;
	}
	void operator -= (const bigNum o)
	{
		for(int i = 1; i <= len; i++)
			dat[i] -= o.dat[i];
		for(int i = 1; i <= len; i++)
		{
			if (dat[i] < 0)
			{
				dat[i] += rp;
				dat[i + 1]--;
			}
		}
		while(len > 1 && dat[len] == 0)
			len--;
	}
	void operator += (const bigNum o)
	{
		len = max(len, o.len);
		for(int i = 1; i <= len; i++)
			dat[i] += o.dat[i];
		for(int i = 1; i <= len; i++)
		{
			if (dat[i] >= rp)
			{
				dat[i + 1] += dat[i] / rp;
				dat[i] %= rp;
				if (i + 1 > len)
					len = i + 1;
			}
		}	
	}
	void print()
	{
		printf("%d", dat[len]);
		for(int i = len - 1; i >= 1; i--)
			printf("%04d", dat[i]);
		printf("\n");
	}
};

bigNum Ans, Tmp, Trans;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d\n", &N, &K);
	for(int i = 0; i < K; i++)
	{
		for(int j = 1; j <= 3; j++)
		{
			int x;
			scanf("%d", &x);
			triple[i].push_back(x);
		}
	}
	for(int i = 0; i < (1 << K); i++)
	{
		int flag = 1, cnt = N, c = 0;
		for(int j = 0; j < K; j++)
		if (i & (1 << j))
		{
			c ^= 1;
			for(int k = 0; k < 3; k++)
			{
				if (visit[triple[j][k]])
					flag = 0;
				visit[triple[j][k]] = 1;	
			}
			cnt--;
		}
		for(int j = 0; j < K; j++)
		if (i & (1 << j))
		{
			for(int k = 0; k < 3; k++)
				visit[triple[j][k]] = 0;	
		}
		if (!flag)
			continue;
		if (c == 0)
			add[cnt]++;
		else
			add[cnt]--;
	}
	Ans.clear();
	Tmp.clear(); Tmp.dat[1] = 1;
	Trans.clear();
	for(int i = 0; i <= N; i++)
	{
		if (add[i] > 0)
		{
			Trans = Tmp;
			Trans *= abs(add[i]);
			Ans += Trans;
		}	
		Tmp *= (3 * i + 1);
		Tmp *= (3 * i + 2);
		Tmp /= 2;	
	}
	//Ans.print();
	Tmp.clear(); Tmp.dat[1] = 1;
	Trans.clear();
	for(int i = 0; i <= N; i++)
	{
		if (add[i] < 0)
		{
			Trans = Tmp;
			Trans *= abs(add[i]);
			Ans -= Trans;
		}		
		Tmp *= (3 * i + 1);
		Tmp *= (3 * i + 2);
		Tmp /= 2;	
	}
	Ans.print();
	return 0;
} 
