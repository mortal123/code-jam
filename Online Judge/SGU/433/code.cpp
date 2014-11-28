#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 105;
const int MAXR = 1005, MAXC = 105, MAXT = MAXR * MAXC;

struct WAY
{
	int x, y, size, type;
	WAY(){}
	WAY(int _x, int _y, int _size, int _type) : x(_x), y(_y), size(_size), type(_type){}
}way[MAXR];

int N, M, K, length[10];
int num[MAXN][MAXN], RowNum = 0, mat[MAXR][MAXC];
int U[MAXT], D[MAXT], L[MAXT], R[MAXT], C[MAXT], S[MAXT], W[MAXT];
int choose[MAXT], size;

void MakeMatrix()
{
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			for(int k = 1; k <= K; k++)
			{
				// ºá×Å
				if (j + length[k] - 1 <= M)
				{
					RowNum++;
					way[RowNum] = WAY(i, j, length[k], 0);
					int x = i, y = j;
					for(int l = 1; l <= length[k]; l++)
					{
						mat[RowNum][num[x][y]] = 1;
						y++;
					}
				} 
				if (i + length[k] - 1 <= N)
				{
					RowNum++;
					way[RowNum] = WAY(i, j, length[k], 1);
					int x = i, y = j;
					for(int l = 1; l <= length[k]; l++)
					{
						mat[RowNum][num[x][y]] = 1;
						x++;
					}
				}
			}
}

void Build(int mat[MAXR][MAXC], int Row, int Col)
{
	R[0] = 1; L[0] = Col;
	for(int i = 1; i <= Col; i++)
	{
		L[i] = i - 1, R[i] = (i + 1) % (Col + 1);
		D[i] = U[i] = C[i] = i;
		S[i] = 0;
	}
	int idx = Col;
	for(int i = 1; i <= Row; i++)
	{
		int first = 0;
		for(int j = 1; j <= Col; j++)
			if (mat[i][j])
			{
				++idx;
				U[idx] = U[j]; D[idx] = j;
				D[U[j]] = idx; U[j] = idx;
				if (!first) 
					first = L[idx] = R[idx] = idx;
				else
				{
					L[idx] = L[first]; R[idx] = first; // ?
					R[L[first]] = idx; L[first] = idx;
				}
				W[idx] = i; C[idx] = j; S[j]++;
			}
	}
}

char ans[30][30], ans2[30][30];
int CNT = 0;

void remove(int col)
{
	//remove col column ans all row i where mat[i][col] == 1
	R[L[col]] = R[col];
	L[R[col]] = L[col];
	for(int i = D[col]; i != col; i = D[i])
	{
		for(int j = R[i]; j != i; j = R[j])
		{
			D[U[j]] = D[j];
			U[D[j]] = U[j];
			S[C[j]]--;
		}
	} 
}

void resume(int col)
{
	for(int i = U[col]; i != col; i = U[i])
	{
		for(int j = L[i]; j != i; j = L[j]) // change L[i] to R[i]
		{
			D[U[j]] = j;
			U[D[j]] = j;
			S[C[j]]++;
		}
	}
	L[R[col]] = col;
	R[L[col]] = col;
}

int dfs(int dep)
{
	CNT++;
	if (CNT > 10000)
		return 0;
	if (R[0] == 0)
	{
		size = dep - 1;
		return 1;
	}
	int mn = 2000000, mp;
	for(int i = R[0]; i; i = R[i])
		if (S[i] < mn)
			mn = S[i], mp = i;
	remove(mp);
	for(int i = D[mp]; i != mp; i = D[i])
	{
		choose[dep] = W[i];
		for(int j = R[i]; j != i; j = R[j])
			remove(C[j]);
		if (dfs(dep + 1))
			return 1;
		for(int j = L[i]; j != i; j = L[j])
			resume(C[j]);
	}
	resume(mp);
	return 0;
}

int vis[105];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &N, &M, &K);
	for(int i = 1; i <= K; i++)
		scanf("%d", &length[i]);
	// number
	int idx = 0;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			num[i][j] = ++idx;
	MakeMatrix();
	Build(mat, RowNum, N * M);
	if (!dfs(1))
		printf("NO\n");
	else
	{
		int idx = 1;
		for(int i = 1; i <= size; i++)
		{
			int c = choose[i];
			//printf("%d %d %d %d\n", way[c].x, way[c].y, way[c].size, way[c].type);
			int x = way[c].x, y = way[c].y;
			for(int j = 1; j <= way[c].size; j++)
			{
				ans[x][y] = idx;
				if (way[c].type == 0)
					y++;
				else
					x++;
			}
			++idx;
		}
		printf("YES\n");
		memset(ans2, 0, sizeof(ans2));
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= M; j++)
			{
				if (ans2[i][j])
					continue;
				memset(vis, 0, sizeof(vis));
				for(int k = 1; k <= N; k++)
					for(int l = 1; l <= M; l++)
						if (ans2[k][l])
						{
							if (ans[k + 1][l] == ans[i][j] || ans[k - 1][l] == ans[i][j] 
								|| ans[k][l - 1] == ans[i][j] || ans[k][l + 1] == ans[i][j])
							{
								vis[ans2[k][l] - 'a'] = 1;
							}
						}
				char ch = 'a';
				while(vis[ch - 'a'])
					ch++;
				for(int k = 1; k <= N; k++)
					for(int l = 1; l <= M; l++)
						if (ans[k][l] == ans[i][j])
							ans2[k][l] = ch;
			}
		for(int i = 1; i <= N; i++, printf("\n"))
			for(int j = 1; j <= M; j++)
				printf("%c", ans2[i][j]);
	}
	return 0;
}
