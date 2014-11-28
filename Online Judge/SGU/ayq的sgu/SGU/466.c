#include <stdio.h>
#include <stdlib.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   int l,r,q,st,len;
}p[200001];
int rec[100001],rst[100001],rlen[100001];
char str[100005];
int pst,plen,tot=0;

void left(int *now)
{
   int son=p[*now].r;
   p[*now].r=p[son].l;
   p[son].l=*now;
   *now=son;
}

void right(int *now)
{
   int son=p[*now].l;
   p[*now].l=p[son].r;
   p[son].r=*now;
   *now=son;
}

void ins(int *now,int st,int len)
{
   if (*now==0)
   {
      *now=++tot;
      p[tot]=(struct case1){0,0,rand(),st,len};
   }
   else if (len<p[*now].len||len==p[*now].len&&st<p[*now].st)
   {
      ins(&p[*now].l,st,len);
      if (p[p[*now].l].q<p[*now].q)
         right(now);
   }
   else
   {
      ins(&p[*now].r,st,len);
      if (p[p[*now].r].q<p[*now].q)
         left(now);
   }
}

void get(int now,int len)
{
   if (now)
      if (p[now].len<len)
         get(p[now].r,len);
      else
      {
         if (p[now].len<plen||p[now].len==plen&&p[now].st<pst)
         {
            pst=p[now].st;
            plen=p[now].len;
         }
         get(p[now].l,len);
      }
}

void del(int *now,int st,int len)
{
   if (p[*now].l==0&&p[*now].r==0)
      *now=0;
   else if (p[*now].st==st&&p[*now].len==len)
      if (p[*now].r==0||p[*now].l&&p[p[*now].l].q<p[p[*now].r].q)
      {
         right(now);
         del(&p[*now].r,st,len);
      }
      else
      {
         left(now);
         del(&p[*now].l,st,len);
      }
   else if (len<p[*now].len||len==p[*now].len&&st<p[*now].st)
      del(&p[*now].l,st,len);
   else
      del(&p[*now].r,st,len);
}

int main()
{
   int i=1,j,t,st,en,tl,tr,n,q,l,r,root=0;
   scanf("%d%d\n",&n,&q);
   gets(str+1);
   if (str[1]=='.')
   {
      for (i=n;i>=1&&str[i]=='.';i--);
      t=i+1;
   }
   else
      t=n+1;
   if (!i)
   {
      rec[1]=n;
      rec[n]=1;
      ins(&root,1,n);
   }
   else
      for (i=1;i<t;i=j+1)
      {
         j=i;
         if (str[i]=='.')
         {
            while (j<t&&str[j+1]=='.')
               j++;
            if (i==1&&t<=n)
               st=t;
            else
               st=i;
            rec[j]=st;
            rec[st]=j;
            ins(&root,st,j-st+n*(j<st)+1);
         }
      }
   for (i=1;i<=q;i++)
   {
      gets(str+1);
      t=0;
      if (str[1]=='P')
      {
         for (j=6;str[j];j++)
            t=t*10+str[j]-'0';
         plen=oo;
         get(root,t);
         if (plen<oo)
         {
            if (pst+t-1>n)
            {
               if (pst+t-1==n+1)
                  printf("1");
               else
                  printf("1-%d",pst+t-1-n);
               putchar(',');
            }
            if (pst==min(n,pst+t-1))
               printf("%d",pst);
            else
               printf("%d-%d",pst,min(n,pst+t-1));
            puts("");
            del(&root,pst,plen);
            if (t<plen)
            {
               rec[rec[pst]]=(pst+t-1)%n+1;
               rec[(pst+t-1)%n+1]=rec[pst];
               rec[pst]=0;
               ins(&root,(pst+t-1)%n+1,plen-t);
            }
            else
               rec[pst]=rec[(pst+t-2)%n+1]=0;
            rst[i]=pst;
            rlen[i]=t;
         }
         else
            puts("NO ROOM");
      }
      else
      {
         for (j=7;str[j];j++)
            t=t*10+str[j]-'0';
         st=rst[t];
         en=(rst[t]+rlen[t]-2)%n+1;
         l=(rst[t]+n-2)%n+1;
         r=(rst[t]+rlen[t]-1)%n+1;
         if (rec[l]==r)
         {
            root=rec[l]=rec[r]=0;
            rec[n]=1;
            rec[1]=n;
            ins(&root,1,n);
         }
         else if (rec[l]&&rec[r])
         {
            del(&root,rec[l],l-rec[l]+n*(l<rec[l])+1);
            del(&root,r,rec[r]-r+n*(rec[r]<r)+1);
            ins(&root,rec[l],rec[r]-rec[l]+n*(rec[r]<rec[l])+1);
            tl=rec[l];
            tr=rec[r];
            rec[l]=rec[r]=0;
            rec[tl]=tr;
            rec[tr]=tl;
         }
         else if (rec[l])
         {
            del(&root,rec[l],l-rec[l]+n*(l<rec[l])+1);
            ins(&root,rec[l],en-rec[l]+n*(en<rec[l])+1);
            tl=rec[l];
            rec[l]=0;
            rec[tl]=en;
            rec[en]=tl;
         }
         else if (rec[r])
         {
            del(&root,r,rec[r]-r+n*(rec[r]<r)+1);
            ins(&root,st,rec[r]-st+n*(rec[r]<st)+1);
            tr=rec[r];
            rec[r]=0;
            rec[tr]=st;
            rec[st]=tr;
         }
         else
         {
            ins(&root,st,en-st+n*(en<st)+1);
            rec[st]=en;
            rec[en]=st;
         }
      }
   }
   return 0;
}
