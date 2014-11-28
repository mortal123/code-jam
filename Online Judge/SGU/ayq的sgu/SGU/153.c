#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))

long pos[1201]={0},f[1201]={0},a[11]={0};

int main()
{
    long i,j,k,n,q,m,s;
    scanf("%ld",&q);
    a[1]=f[0]=1;
    while (q--)
    {
       scanf("%ld%ld",&k,&n);
       n++;
       m=1;
       memset(pos,0,sizeof(pos));
       for (i=2;i<=n;i++)
       {
          scanf("%ld",&a[i]);
          m=max(a[i],m);
       }
       for (i=1;i<=k;i++)
       {
          for (j=1;j<=n;j++)
             if (i>=a[j]&&!f[i-a[j]])
                break;
          f[i]=(j<=n);
          if (i>=m-1)
          {
             s=0;
             for (j=i-m+1;j<=i;j++)
                s+=(1<<(j-i+m-1))*f[j];
             if (pos[s])
                break;
             pos[s]=i;
          }
       }
       if (i>k&&f[k]||i<=k&&f[(k-pos[s])%(i-pos[s])+pos[s]])
          printf("FIRST PLAYER MUST WIN\n");
       else
          printf("SECOND PLAYER MUST WIN\n");
    }
    return 0;
}
