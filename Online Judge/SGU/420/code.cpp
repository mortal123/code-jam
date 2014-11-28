#include <cstdio>
#include <cstdlib>

const int MAXN = 200;

struct block
{
	long long l, lead;
	int sl, tl, num[10];
}p[MAXN];
int tot;
long long L, R, Ans = 0;

void Init()
{
	scanf("%I64d %I64d", &L, &R);
	while(L <= R)
	{
		p[++tot].lead = L;
		p[tot].l = L;
		long long tmp = 1;
		while(L + tmp * 10 - 1 <= R && p[tot].lead % 10 == 0)
		{
			tmp *= 10;
			p[tot].lead /= 10;
			p[tot].tl++;
		}
		L += tmp;
		tmp = p[tot].lead;
		while(tmp)
		{
			p[tot].num[tmp % 10]++;
			tmp /= 10;
			p[tot].sl++;
		}
	}
}

int num2[10];

void Work()
{
	for(int i = 1;i <= tot;i++)
	if (p[i].tl == 2)
	{
		for(int j = 0;j < 10;j++)
			for(int k = j + 1;k < 10;k++)
			{
				int cnt = 1;
				for(int l = 0;l < 10;l++)
					num2[l] = p[i].num[l];
				num2[j]++;
				num2[k]++;
				for(int l = 1;l <= tot;l++)
					if (i != l && p[i].sl + p[i].tl == p[l].sl + p[l].tl)
					{
						int flag = 1;
						for(int w = 0;w < 10;w++)
							if (num2[w] < p[l].num[w])
								flag = 0;
						if (flag)
						{
							cnt++;
							break;
						}
					}
				if (cnt == 1)
					Ans += 2;
			}
	}
	for(int i = 1;i <= tot;i++)
		if (p[i].tl == 0)
		{
			long long tmp = p[i].l;
			int cnt = 0;
			for(int j = 0;j < 10;j++)
				num2[j] = p[i].num[j];
			for(int j = 1;j <= tot;j++)
				if (i != j && p[i].sl + p[i].tl == p[j].sl + p[j].tl)
				{
					int kind = 0;
					for(int k = 0;k < 10;k++)
						if (num2[k] > p[j].num[k])
						{
							kind++;
						}
						else
						if (num2[k] < p[j].num[k])
						{
							kind = -1;
							break;
						}
						
					if (kind < 0)
						continue;
					if (kind <= 1)
						cnt ++;
					else
					{
						cnt += 2;
						break;
					}
				}
			if (cnt == 1)
				Ans++;
		}
	for(int i = 1;i <= tot;i++)
		if (p[i].tl)
		{
			for(int j = 0;j < 10;j++)
			{
				int cnt = 0;
				for(int k = 0;k < 10;k++)
					num2[k] = p[i].num[k];
				num2[j] += p[i].tl;
				
				for(int k = 1;k <= tot;k++)
					if (i != k && p[i].sl + p[i].tl == p[k].sl + p[k].tl)
					{
						int kind = 0;
						for(int l = 0;l < 10;l++)
							if (num2[l] > p[k].num[l])
							{
								kind += 1;
							}
							else
							if (num2[l] < p[k].num[l])
							{
								kind = -1;
								break;
							}
						if (kind < 0)
							continue;
						if (kind <= 1)
							cnt++;
						else
						{
							cnt += 2;
							break;
						}
					}
				if (cnt == 1)
					Ans++;
			}
		}
	printf("%I64d\n", Ans);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
}
