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
double f[MAXN + 10][base + 10];
int vec[MAXN + 10][base + 10]; 
int K;

const int Size = 20;
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

int proce[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &K);
	for(int i = 0; i <= K; i++)
		for(int j = 0; j <= base; j++)
			f[i][j] = 1e20, vec[i][j] = 0;
	for(int i = 1; i <= base; i++)
		logPrim[i] = log(prim[i]);
	f[1][0] = log(1.0);
	for(int i = 1; i <= base; i++) 
		for(int j = 1; j <= K; j++)
		{
			int cnt = 0; double tmp = -logPrim[i];
			for(int k = j; k <= K; k += j)
			{
				++cnt;
				tmp += logPrim[i];
				if (f[j][i - 1] + tmp < f[k][i])
				{
					f[k][i] = f[j][i - 1] + tmp;
					vec[k][i] = cnt - 1;
				}
			}
		}
	double res = 1e20;
	int ch = -1;
	for(int i = 1; i <= base; i++)
		if (f[K][i] < res)
			res = f[K][i], ch = i;
	Ans.dat[1] = 1;
	//print(vec[K][ch]);
	while(ch)
	{
		int tmp = vec[K][ch];
		if (tmp)
			Calc(prim[ch], tmp);
		K /= (tmp + 1);
		ch--;
	}

	Ans.print();
	return 0;
} 
