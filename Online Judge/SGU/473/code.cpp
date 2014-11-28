#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int base = 16;
const int MAXN = 100000;

int prim[20] ={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,51,53};
double logPrim[20];
double f[2][MAXN + 10];
int vec[base + 10][MAXN + 10]; 
int K;

const int Size = 30;
const int rp = 10000;

struct bigNum
{
	int dat[Size + 10], len;
	void clear()
	{
		memset(dat, 0, sizeof(dat));
		len = 1;
	}
	bigNum()
	{
		memset(dat, 0, sizeof(dat));
		len = 1;
	}
	bigNum operator*(const bigNum o)
	{
		bigNum c;
		for(int i = 1; i <= len; i++)
			for(int j = 1; j <= o.len; j++)
			{
				c.dat[i + j - 1] += dat[i] * o.dat[j];
				if (c.dat[i + j - 1] >= rp)
				{
					c.dat[i + j] += c.dat[i + j - 1] / rp;
					c.dat[i + j - 1] %= rp;
				}
			}
		c.len = len + o.len;
		while(c.len > 1 && c.dat[c.len] == 0)
			c.len--;
		return c;
	}
	void print()
	{
		printf("%d", dat[len]);
		for(int i = len - 1; i >= 1; i--)
			printf("%04d", dat[i]);
		printf("\n");
	}
}cons, Ans, Tmpo;

void Calc(int v, int c)
{ 
	Tmpo.clear();
	Tmpo.dat[1] = v;
	while(c)
	{
		if (c & 1)
			Ans = Ans * Tmpo;
		c >>= 1;
		Tmpo = Tmpo * Tmpo;
	}
}

void print(vector<int> o)
{
	for(int i = 0; i < o.size(); i++)
		printf("%d ", o[i]);
	printf("\n");
}


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &K);
	for(int i = 0; i <= K; i++)
		for(int j = 0; j <= base; j++)
		{
			if (j <= 1)
				f[j][i] = 1e20;
			vec[j][i] = 0; 
		} 
	for(int i = 1; i <= base; i++)
		logPrim[i] = log(prim[i]);
	f[0][1] = log(1.0);
	double res = 1e20;
	int ch = -1;
	for(int i = 1; i <= base; i++) 
	{
		int now = i % 2, old = now ^ 1;
		for(int j = 0; j <= K; j++)
			f[now][j] = 1e20;
		for(int j = 1; j <= K; j++)
		{
			int cnt = 0; double tmp = f[old][j] - logPrim[i];
			for(int k = j; k <= K; k += j)
			{
				++cnt;
				tmp += logPrim[i];
				if (tmp < f[now][k])
				{
					f[now][k] = tmp;
					vec[i][k] = cnt - 1;
				}
			}
		}
		if (f[now][K] < res)
			res = f[now][K], ch = i;
	}
	Ans.dat[1] = 1;
	//print(vec[K][ch]);
	while(ch)
	{
		int tmp = vec[ch][K];
		if (tmp)
			Calc(prim[ch], tmp);
		K /= (tmp + 1);
		ch--;
	}

	Ans.print();
	return 0;
}
