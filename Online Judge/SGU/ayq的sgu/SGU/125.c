#include<stdio.h>
#define F(x,y) for (a[x][y]=1;a[x][y]<=9;a[x][y]++)
#define M(x,y,p,q) if (a[x][y]>a[p][q])
#define C(x,y,a,b) (map[x][y]>=(a)&&map[x][y]<=(b))

long map[5][5]={0},a[5][5]={0},s[5][5]={0};
long n;

long check()
{
   long i,j;
   memset(s,0,sizeof(s));
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         if (i>1&&a[i-1][j]>a[i][j])
            s[i][j]++;
         if (j>1&&a[i][j-1]>a[i][j])
            s[i][j]++;
         if (i<n&&a[i+1][j]>a[i][j])
            s[i][j]++;
         if (j<n&&a[i][j+1]>a[i][j])
            s[i][j]++;
      }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (map[i][j]!=s[i][j])
            return 0;
   return 1;
}

int main()
{
   long i,j;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         scanf("%ld",&map[i][j]);
   if (n==1)
   {
      if (!map[1][1])
         printf("1\n");
      else
         printf("NO SOLUTION\n");
   }
   else if (n==2)
   {
      F(1,1) F(1,2) F(2,1) F(2,2)
         if (check())
         {
            printf("%ld %ld\n%ld %ld\n",a[1][1],a[1][2],a[2][1],a[2][2]);
            goto end;
         }
      printf("NO SOLUTION\n");
   }
   else
   {
      if (C(1,1,0,2)&&C(1,2,0,3)&&C(1,3,0,2)&&C(2,1,0,3)&&C(2,2,0,4)&&C(2,3,0,3)&&C(3,1,0,2)&&C(3,2,0,3)&C(3,3,0,2))
         F(1,1) F(1,2)
         {
            M(1,2,1,1) map[1][1]--;
            M(1,1,1,2) map[1][2]--;
            if (C(1,1,0,1)&&C(1,2,0,2))
               F(2,1)
               {
                  M(2,1,1,1) map[1][1]--;
                  M(1,1,2,1) map[2][1]--;
                  if (C(1,1,0,0)&&C(2,1,0,2))
                     F(1,3)
                     {
                        M(1,3,1,2) map[1][2]--;
                        M(1,2,1,3) map[1][3]--;
                        if (C(1,2,0,1)&&C(1,3,0,1))
                           F(3,1)
                           {
                              M(3,1,2,1) map[2][1]--;
                              M(2,1,3,1) map[3][1]--;
                              if (C(2,1,0,1)&&C(3,1,0,1))
                                 F(2,2)
                                 {
                                    M(2,2,1,2) map[1][2]--;
                                    M(2,2,2,1) map[2][1]--;
                                    M(1,2,2,2) map[2][2]--;
                                    M(2,1,2,2) map[2][2]--;
                                    if (C(1,2,0,0)&&C(2,1,0,0)&&C(2,2,0,2))
                                       F(2,3)
                                       {
                                          M(2,3,1,3) map[1][3]--;
                                          M(2,3,2,2) map[2][2]--;
                                          M(1,3,2,3) map[2][3]--;
                                          M(2,2,2,3) map[2][3]--;
                                          if (C(1,3,0,0)&&C(2,2,0,1)&&C(2,3,0,1))
                                             F(3,2)
                                             {
                                                M(3,2,3,1) map[3][1]--;
                                                M(3,2,2,2) map[2][2]--;
                                                M(3,1,3,2) map[3][2]--;
                                                M(2,2,3,2) map[3][2]--;
                                                if (C(3,1,0,0)&&C(2,2,0,0)&&C(3,2,0,1))
                                                   F(3,3)
                                                   {
                                                      M(3,3,3,2) map[3][2]--;
                                                      M(3,3,2,3) map[2][3]--;
                                                      M(3,2,3,3) map[3][3]--;
                                                      M(2,3,3,3) map[3][3]--;
                                                      if (C(3,2,0,0)&&C(2,3,0,0)&&C(3,3,0,0))
                                                      {
                                                         for (i=1;i<=3;i++)
                                                            printf("%ld %ld %ld\n",a[i][1],a[i][2],a[i][3]);
                                                         goto end;
                                                      }
                                                      M(3,3,3,2) map[3][2]++;
                                                      M(3,3,2,3) map[2][3]++;
                                                      M(3,2,3,3) map[3][3]++;
                                                      M(2,3,3,3) map[3][3]++;
                                                   }
                                                M(3,2,3,1) map[3][1]++;
                                                M(3,2,2,2) map[2][2]++;
                                                M(3,1,3,2) map[3][2]++;
                                                M(2,2,3,2) map[3][2]++;
                                             }
                                          M(2,3,1,3) map[1][3]++;
                                          M(2,3,2,2) map[2][2]++;
                                          M(1,3,2,3) map[2][3]++;
                                          M(2,2,2,3) map[2][3]++;
                                       }
                                    M(2,2,1,2) map[1][2]++;
                                    M(2,2,2,1) map[2][1]++;
                                    M(1,2,2,2) map[2][2]++;
                                    M(2,1,2,2) map[2][2]++;
                                 }
                              M(3,1,2,1) map[2][1]++;
                              M(2,1,3,1) map[3][1]++;
                           }
                        M(1,3,1,2) map[1][2]++;
                        M(1,2,1,3) map[1][3]++;
                     }
                  M(2,1,1,1) map[1][1]++;
                  M(1,1,2,1) map[2][1]++;
               }
            M(1,2,1,1) map[1][1]++;
            M(1,1,1,2) map[1][2]++;
         }
      printf("NO SOLUTION\n");
   }
   end:
   return 0;
}
