/*
	2012-9-18
	star 22:02
	end 0:24
	wa 无数次
	总结：
		做的很无语的一道题，首先由于最小表示法和扩展kmp的不熟悉而去复习了一下
		但是由于过了凌晨，实在想睡觉。。。效率低下
		不过依然无法逃避我的一些问题
		总是犯小错误
		所以要加紧调试锻炼 
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 2200000;

int N, M;
char s1[MAXN], s2[MAXN], s[MAXN];
int MinRep(char s[], int N)
{
	int i = 1, j = 2, k = 0;
	while(i <= N && j <= N)
	{
		if (s[i + k] == s[j + k])
			k++;
		else
		{
			if (s[i + k] < s[j + k])
				j = j + k + 1;
			else
				i = i + k + 1;
			if (i == j)
				j++;
			k = 0;
		}
	}
	if (i < j)
		return i;
	return j;
	
}
void Init()
{
	scanf("%d %d\n", &M, &N);
	gets(s2 + 1);
	gets(s1 + 1);	
	for(int i = 1;i <= N;i++)
		s1[i + N] = s1[i];
	int pos = MinRep(s1, N);
	for(int i = pos;i <= N;i++)
		s[i - pos + 1] = s1[i];
	for(int i = 1;i < pos;i++)
		s[N - pos + 1 + i] = s1[i];

	for(int i = 1;i <= M;i++)
		s2[i + M] = s2[i];
	M *= 2;
}

int a[MAXN], b[MAXN], next[MAXN], ex[MAXN];

void Calc(char s1[], char s2[], int p[])
{
	for(int i = 1;i <= N;i++)
		next[i] = 0;
	for(int i = 1;i <= M;i++)
		ex[i] = 0;
	
	next[1] = N; next[2] = N - 1;
	for(int i = 1;i < N;i++)
		if (s1[i] != s1[i + 1])
		{
			next[2] = i - 1;
			break;
		}
		
	int j = 2, k = next[2];
	
	for(int i = 3;i <= N;i++)
	{
		if (k >= i)
			next[i] = min(k - i + 1, next[i - j + 1]);
		while(i + next[i] <= N && s1[i + next[i]] == s1[1 + next[i]])
			next[i]++;
		if (i + next[i] - 1 > k)
			k = i + next[i] - 1, j = i;
	}
	ex[1] = N;
	
	for(int i = 1;i <= N && i <= M;i++)
		if (s1[i] != s2[i])
		{
			ex[1] = i - 1;
			break;
		}
	
	j = 1, k = ex[1];
	for(int i = 2;i <= M;i++)
	{
		if (k >= i)
			ex[i] = min(k - i + 1, next[i - j + 1]);
		while(i + ex[i] <= M && 1 + ex[i] <= N && s2[i + ex[i]] == s1[1 + ex[i]])
			ex[i]++;
		if (i + ex[i] - 1 > k)
			k = i + ex[i] - 1, j = i;
	}
	for(int i = 1;i <= M;i++)
		p[i] = ex[i];
}

void rev(int a[], int len)
{
	for(int i = 1;i <= len / 2;i++)
		swap(a[i], a[len - i + 1]);
}
void rev(char a[], int len)
{
	for(int i = 1;i <= len / 2;i++)
		swap(a[i], a[len - i + 1]);
}

void Work()
{
	Calc(s, s2, a);
	rev(s, N);
	rev(s2, M);
	
	Calc(s, s2, b);
	rev(b, M);
	rev(s, N);
	rev(s2, M);
	int mi = 10000000, pos = 1000000000;
	for(int i = 1;i <= M / 2;i++)
		if (a[i] + b[i + N - 1] >= N - 1)
		{
			if (i - 1 <= mi)
				mi = i - 1, pos = i;
			if (M / 2 - i + 1 < mi)
				mi = M / 2 - i + 1, pos = i;
		}
	for(int i = 1;i <= N;i++)
		printf("%c", s[i]);
	printf("\n");
	for(int i = pos;i <= pos + M / 2 - 1;i++)
		printf("%c", s2[i]);
	printf("\n");
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
}
