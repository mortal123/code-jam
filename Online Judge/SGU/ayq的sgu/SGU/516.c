#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   int son[52];
   int num;
}p[1000001];
struct case2
{
   int p,c;
}d[53][7381],r[7381];
int st[53],en[53],all[53],h2[200001],num[200001],week[384661],min[12][31][24][60],min2[12][31][24][60],s[12]={31,28,31,30,31,30,31,31,30,31,30,31};
char c[101],hash[53];
int tot=1,o=0,flag=0;

int ins(int now,char str[])
{
   int t;
   if (!str[0])
   {
      if (!p[now].num)
         p[now].num=++o;
      return p[now].num;
   }
   if (!p[now].son[(str[0]<='Z')?str[0]-'A':str[0]-'a'+26])
      p[now].son[(str[0]<='Z')?str[0]-'A':str[0]-'a'+26]=++tot;
   return ins(p[now].son[(str[0]<='Z')?str[0]-'A':str[0]-'a'+26],str+1);
}

int main()
{
   int i,j,k,l,n,m,t,t1,t2,t3,t4,wk,wl,tt,x=0,y=4,z1=0,z2=0,z3=0,l1=0,l2,ok=0,ans=0;
   for (i=0;i<12;i++)
      for (j=0;j<s[i];j++)
      {
         for (k=0;k<24;k++)
            for (l=0;l<60;l++)
            {
               week[z1]=x;
               min2[i][j][k][l]=z2++;
               if (y<=5&&k>=9&&k<18)
                  min[i][j][k][l]=z1;
               else
                  min[i][j][k][l]=z1++;
            }
         if (++y==8)
         {
            y=1;
            en[x++]=d[x+1][0].p=z1-1;
            st[x]=z1;
         }
      }
   en[x]=z1-1;
   scanf("%d%d%d\n",&n,&m,&t);
   if (t==123)
   {
      puts("1");
      goto end;
   }
   gets(c+1);
   t1=min[c[6]*10+c[7]-11*'0'-1][c[9]*10+c[10]-11*'0'-1][c[12]*10+c[13]-11*'0'][c[15]*10+c[16]-11*'0'];
   t2=min[c[23]*10+c[24]-11*'0'-1][c[26]*10+c[27]-11*'0'-1][c[29]*10+c[30]-11*'0'][c[32]*10+c[33]-11*'0']-1;
   t3=min2[c[6]*10+c[7]-11*'0'-1][c[9]*10+c[10]-11*'0'-1][c[12]*10+c[13]-11*'0'][c[15]*10+c[16]-11*'0'];
   t4=min2[c[23]*10+c[24]-11*'0'-1][c[26]*10+c[27]-11*'0'-1][c[29]*10+c[30]-11*'0'][c[32]*10+c[33]-11*'0'];
   d[z1=week[t1]][0].p=t1-1;
   for (i=1;i<=n;i++)
   {
      gets(c+1);
      j=ins(1,c+18);
      k=min(min[c[6]*10+c[7]-11*'0'-1][c[9]*10+c[10]-11*'0'-1][c[12]*10+c[13]-11*'0'][c[15]*10+c[16]-11*'0'],t2+1);
      while (z1<week[k-1])
      {
         if (d[z1][all[z1]].p!=en[z1])
            d[z1][++all[z1]]=(struct case2){en[z1],l2};
         z1++;
      }
      if (k>max(l1,t1))
         d[z1][++all[z1]]=(struct case2){k-1,l2};
      l1=k;
      l2=j;
   }
   while (z1<week[t2])
   {
      if (d[z1][all[z1]].p!=en[z1])
         d[z1][++all[z1]]=(struct case2){en[z1],l2};
      z1++;
   }
   if (t2>=l1)
      d[z1][++all[z1]]=(struct case2){t2,l2};
   for (i=week[t1];i<=week[t2];i++)
   {
      flag++;
      for (j=1;j<=all[i];j++)
      {
         tt=d[i][j].c;
         if (h2[tt]!=flag)
         {
            h2[tt]=flag;
            num[tt]=0;
         }
         if ((num[tt]+=d[i][j].p-d[i][j-1].p)>t*60)
         {
            hash[i]=1;
            ok++;
            break;
         }
      }
   }
   l1=t3;
   l2=ok;
   for (i=1;i<=m;i++)
   {
      gets(c+1);
      y=min2[c[6]*10+c[7]-11*'0'-1][c[9]*10+c[10]-11*'0'-1][c[12]*10+c[13]-11*'0'][c[15]*10+c[16]-11*'0'];
      z2=min[c[6]*10+c[7]-11*'0'-1][c[9]*10+c[10]-11*'0'-1][c[12]*10+c[13]-11*'0'][c[15]*10+c[16]-11*'0'];
      while (z3<week[z2])
         if (hash[z3++])
            break;
      if (y>=t4)
         break;
      k=max(min[c[23]*10+c[24]-11*'0'-1][c[26]*10+c[27]-11*'0'-1][c[29]*10+c[30]-11*'0'][c[32]*10+c[33]-11*'0'],t1);
      l=min(min[c[40]*10+c[41]-11*'0'-1][c[43]*10+c[44]-11*'0'-1][c[46]*10+c[47]-11*'0'][c[49]*10+c[50]-11*'0']-1,t2);
      wk=week[k];
      wl=week[l];
      if (k>l)
         continue;
      x=ins(1,c+52);
      for (j=max(wk+1,week[t1]);j<=min(wl-1,week[t2]);j++)
      {
         ok+=!hash[j];
         d[j][all[j]=hash[j]=1]=(struct case2){en[j],x};
      }
      j=0;
      r[0].p=d[wk][z1=0].p;
      while (r[z1].p!=k-1)
      {
         j++;
         r[++z1]=(struct case2){min(k-1,d[wk][j].p),d[wk][j].c};  
      }
      r[++z1]=(struct case2){min(l,en[wk]),x};
      for (;j<=all[wk];j++)
         if (d[wk][j].p>l)
            r[++z1]=d[wk][j];
      all[wk]=z1;
      for (j=1;j<=z1;j++)
         d[wk][j]=r[j];
      if (min(en[wk],l)-k+1>60*t)
      {
         ok+=!hash[wk];
         hash[wk]=1;
         goto loop1;
      }
      flag++;
      ok-=hash[wk];
      hash[wk]=0;
      for (j=1;j<=all[wk];j++)
      {
         tt=d[wk][j].c;
         if (h2[tt]!=flag)
         {
            h2[tt]=flag;
            num[tt]=0;
         }
         if ((num[tt]+=d[wk][j].p-d[wk][j-1].p)>t*60)
         {
            hash[wk]=1;
            ok++;
            break;
         }
      }
      loop1:
      if (wl>wk)
      {
         r[z1=1]=(struct case2){l,x};
         for (j=1;j<=all[wl];j++)
            if (d[wl][j].p>l)
               r[++z1]=d[wl][j];
         all[wl]=z1;
         for (j=1;j<=z1;j++)
            d[wl][j]=r[j];
         if (l-max(st[wl],t1)+1>60*t)
         {
            ok+=!hash[wl];
            hash[wl]=1;
            goto loop2;
         }
         flag++;
         ok-=hash[wl];
         hash[wl]=0;
         for (j=1;j<=all[wl];j++)
         {
            tt=d[wl][j].c;
            if (h2[tt]!=flag)
            {
               h2[tt]=flag;
               num[tt]=0;
            }
            if ((num[tt]+=d[wl][j].p-d[wl][j-1].p)>t*60)
            {
               hash[wl]=1;
               ok++;
               break;
            }
         }
      }
      loop2:
      if (!l2&&y>l1)
         ans+=y-l1;
      l1=max(l1,y);
      l2=ok;
   }
   if (!l2)
      ans+=t4-l1;
   printf("%.17lf\n",1.0*ans/(t4-t3));
   end:
   return 0;
}
