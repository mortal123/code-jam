#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
 
const int MAXN = 110000;
const int MAXM = 510000;
 
int visit[MAXN];
int n, m, dep[MAXN], fat[MAXN], fanum[MAXN];
long long ne[MAXM], v[MAXN], nv[MAXN];
int hash[MAXM];
struct eglist
{
    int other[MAXM * 2], succ[MAXM * 2], last[MAXM * 2], sum;
    void clear()
    {
        memset(last, 0, sizeof(last));
        sum = 1;
    }
    void AddEdge(int a, int b)
    {
        other[++sum] = b, succ[sum] = last[a], last[a] = sum;
        other[++sum] = a, succ[sum] = last[b], last[b] = sum;
    }
}e;
 
int lx, ly, le, exd;
 
int aabs(int x)
{
    if (x < 0)
        return -x;
    return x;
}
 
void dfs(int x, int fa)
{
    fat[x] = fa;
    dep[x] = dep[fa] + 1;
    visit[x] = 1;
    for(int i = e.last[x]; i; i = e.succ[i])
    {
        int y = e.other[i];
        if (y == fa)
            continue;
        if (visit[y])
        {
            if (hash[i / 2])
                continue;
            hash[i / 2] = 1;
            exd++;
            if (aabs(dep[y] - dep[x]) % 2 == 0)
                lx = x, ly = y, le = i / 2;
            continue;
        }
        fanum[y] = i / 2;
        dfs(y, x);
        ne[i / 2] = 2 * (v[y] - nv[y]);
        nv[x] += ne[i / 2] / 2;
    }
}
 
int main()
{
    scanf("%d %d", &n, &m);
    //printf("%d %d\n", n, m);
    for(int i = 1; i <= n; i++)
        scanf("%lld", &v[i]);
    e.clear();
    for(int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        e.AddEdge(a, b);
        //e.AddEdge(b, a);
    }
    memset(visit, 0, sizeof(visit));
    memset(nv, 0, sizeof(nv));
    memset(hash, 0, sizeof(hash));
     
    for(int i = 1; i <= n; i++)
        if (!visit[i])
        {
            lx = -1;
            exd = 0;
            dfs(i, 0);
            if (lx != -1 && exd > 1)
            {
                printf("0\n");
                return 0;
            }
            if (nv[i] != v[i])
            {
                if (lx == -1)
                {
                    printf("0\n");
                    return 0;
                }
                long long tmp = v[i] - nv[i];
                if (dep[lx] < dep[ly])
                    swap(lx, ly);
                ne[le] = tmp;
                long long tmpx = tmp, tmpy = tmp;
                int xx = lx, yy = ly;
                while(dep[xx] > dep[yy])
                    xx = fat[xx];
                while(xx != yy)
                    xx = fat[xx], yy = fat[yy];
                if (dep[xx] % 2 == 0)
                    tmpx *= -1, tmpy *= -1; 
                while(lx != i)
                {
                    tmpx *= -1;
                    ne[fanum[lx]] += tmpx;
                    lx = fat[lx];
                }
                while(ly != i)
                {
                    tmpy *= -1;
                    ne[fanum[ly]] += tmpy;
                    ly = fat[ly];
                }
            }
        }
    for(int i = 1; i <= m; i++)
        printf("%lld\n", ne[i]);
    return 0;
}
