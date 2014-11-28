#include <stdio.h>

struct case1
{
   int a,b,v;
}p[40001];
struct case2
{
   int a,v;
}x[40001],res[18][400001];
int rec[40001],r2[18][40001],n2[18][40001],hash[40001],f[40001],fa[40001],tmp[40001],tot[18];
char in[40001];
int ans=0,flag=1,f2=0;

int getf(int now)
{
   if (hash[now]!=flag)
   {
      hash[now]=flag;
      f[now]=now;
   }
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

int getfa(int d,int now)
{
   if (fa[now]==now)
      return now;
   res[d][++tot[d]]=(struct case2){now,fa[now]};
   return fa[now]=getfa(d,fa[now]);
}

void qs(int x,int y)
{
   int i=x,j=y,t=rec[(x+y)>>1];
   if (x>=y)
      return;
   rec[(x+y)>>1]=rec[x];
   while (i<j)
   {
      while (i<j&&(p[rec[j]].v>p[t].v||p[rec[j]].v==p[t].v&&rec[j]>t))
         j--;
      if (i<j)
         rec[i++]=rec[j];
      while (i<j&&(p[rec[i]].v<p[t].v||p[rec[i]].v==p[t].v&&rec[i]<t))
         i++;
      if (i<j)
         rec[j--]=rec[i];
   }
   rec[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void work(int d,int l,int r)
{
   int i,t,a,b,c,o=0;
   tot[d]=0;
   flag++;
   f2++;
   for (i=l;i<=r;i++)
      tmp[x[i].a]=f2;
   r2[d][0]=r2[d-1][0];
   for (i=1;i<=r2[d][0];i++)
   {
      r2[d][i]=r2[d-1][i];
      if (tmp[r2[d][i]]==f2)
         f[getf(getfa(d,p[r2[d][i]].a))]=getf(getfa(d,p[r2[d][i]].b));
      else
         rec[++o]=r2[d][i];
   }
   for (i=0;i<=n2[d-1][0];i++)
      n2[d][i]=n2[d-1][i];
   qs(1,o);
   for (i=1;i<=o;i++)
      if ((a=getf(getfa(d,p[rec[i]].a)))!=(b=getf(getfa(d,p[rec[i]].b))))
      {
         f[a]=b;
         res[d][++tot[d]]=(struct case2){getfa(d,p[rec[i]].a),fa[getfa(d,p[rec[i]].a)]};
         fa[getfa(d,p[rec[i]].a)]=getfa(d,p[rec[i]].b);
      }
   a=b=0;
   for (i=1;i<=r2[d][0];i++)
      if (getfa(d,p[r2[d][i]].a)!=getfa(d,p[r2[d][i]].b))
         r2[d][++a]=r2[d][i];
   r2[d][0]=a;
   for (i=1;i<=n2[d][0];i++)
      if (fa[n2[d][i]]==n2[d][i])
         n2[d][++b]=n2[d][i];
   n2[d][0]=b;
   o=c=0;
   for (i=1;i<=r2[d][0];i++)
      if (tmp[r2[d][i]]!=f2)
         rec[++o]=r2[d][i];
      else
         r2[d][++c]=r2[d][i];
   qs(1,o);
   flag++;
   for (i=1;i<=o;i++)
      if ((a=getf(getfa(d,p[rec[i]].a)))!=(b=getf(getfa(d,p[rec[i]].b))))
      {
         f[a]=b;
         r2[d][++c]=rec[i];
      }
   r2[d][0]=c;
   if (l==r)
   {
      t=(r2[d][0]==2&&tmp[r2[d][1]]==f2)?r2[d][2]:r2[d][1];
      if (in[x[l].a]&&!in[t]&&(x[l].v>p[t].v||x[l].v==p[t].v&&x[l].a>t))
      {
         in[x[l].a]=0;
         in[t]=1;
         ans+=p[t].v-p[x[l].a].v;
      }
      else if (!in[x[l].a]&&in[t]&&(x[l].v<p[t].v||x[l].v==p[t].v&&x[l].a<t))
      {
         in[x[l].a]=1;
         in[t]=0;
         ans+=x[l].v-p[t].v;
      }
      else if (in[x[l].a])
         ans+=x[l].v-p[x[l].a].v;
      p[x[l].a].v=x[l].v;
      printf("%d\n",ans);
   }
   else
   {
      work(d+1,l,(l+r)>>1);
      work(d+1,((l+r)>>1)+1,r);
   }
   for (i=tot[d];i>=1;i--)
      fa[res[d][i].a]=res[d][i].v;
}

int main()
{
   int i,n,m,a,b,q;
   scanf("%d%d",&n,&m);
   n2[0][0]=n;
   r2[0][0]=m;
   for (i=1;i<=n;i++)
      fa[i]=n2[0][i]=i;
   for (i=1;i<=m;i++)
   {
      scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].v);
      rec[i]=r2[0][i]=i;
   }
   qs(1,m);
   for (i=1;i<=m;i++)
      if ((a=getf(p[rec[i]].a))!=(b=getf(p[rec[i]].b)))
      {
         f[a]=b;
         in[rec[i]]=1;
         ans+=p[rec[i]].v;
      }
   scanf("%d",&q);
   for (i=1;i<=q;i++)
      scanf("%d%d",&x[i].a,&x[i].v);
   work(1,1,q);
   return 0;
}
