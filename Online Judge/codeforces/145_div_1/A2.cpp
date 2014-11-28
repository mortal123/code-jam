#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 200;

int M, K, hash[MAXN], N;
struct node
{
    char name[MAXN];
    int ML, MR;
}movie[MAXN];

void Init()
{
    memset(hash, 0, sizeof(hash));
    scanf("%d %d", &M, &K);
    for(int i = 1;i <= K;i++)
    {
        int tmp;
        scanf("%d", &tmp);
        hash[tmp] = 1;
    }
}

void Work()
{
    int MaxL = -1, MaxR = -1;
    scanf("%d", &N);
    for(int i = 1;i <= N;i++)
    {
        scanf("\n");
        gets(movie[i].name + 1);
        int d, a, cnt = 0, bak = 0, op1 = K, op2 = M - K;
        scanf("%d", &d);
        movie[i].ML = movie[i].MR = 0;
        for(int j = 1;j <= d;j++)
        {
            scanf("%d", &a);
            if (a == 0)
                cnt++;
            else
            if (hash[a])
                bak++, op1--;
            else
                op2--;
        }
        movie[i].ML = bak;
        if (cnt > op2)
            movie[i].ML += cnt - op2;
        movie[i].MR = bak + min(cnt, op1);
        MaxL = max(movie[i].ML, MaxL);
        MaxR = max(movie[i].MR, MaxR);
    }

    for(int i = 1;i <= N;i++)
    {
        if (movie[i].ML >= MaxR)
            printf("0\n");
        else
        if (movie[i].MR >= MaxL)
            printf("2\n");
        else
            printf("1\n");
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Init();
    Work();
    return 0;
}