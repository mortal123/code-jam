#include <stdio.h>
#include <string.h>

int p[101][53],ti[101],sol[101],len[101],rec[101];
char name[101][105],str[301];

int main()
{
   int i,j,d,l,s,t,t2,x,tt,ss,ans;
   while (gets(str+1)!=NULL)
   {
      s=d=ans=0;
      l=strlen(str+1);
      for (i=l;!(str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z')||!(str[i-1]>='a'&&str[i-1]<='z'||str[i-1]>='A'&&str[i-1]<='Z');i--)
         s+=(str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z');
      while (1)
      {
         gets(str+1);
         l=strlen(str+1);
         x=0;
         for (i=1;i<=l&&str[i]!='+'&&str[i]!='-'&&str[i]!='.';i++)
            x=x*10+str[i]-'0';
         if (i>l)
            break;
         p[++d][0]=0;
         for (i=s;i>=1;i--)
         {
            while (str[l]==' ')
               l--;
            t=0;
            t2=1;
            while (str[l]>='0'&&str[l]<='9')
            {
               t+=t2*(str[l]-'0');
               t2*=10;
               l--;
            }
            if (str[l]!='+')
               p[d][++p[d][0]]=t*20+241;
            l--;
         }
         while (str[l]==' ')
            l--;
         ti[d]=0;
         t2=1;
         while (str[l]>='0'&&str[l]<='9')
         {
            ti[d]+=t2*(str[l]-'0');
            t2*=10;
            l--;
         }
         while (str[l]==' ')
            l--;
         sol[d]=0;
         t2=1;
         while (str[l]>='0'&&str[l]<='9')
         {
            sol[d]+=t2*(str[l]-'0');
            t2*=10;
            l--;
         }
         while (str[l]==' ')
            l--;
         for (i=1;str[i]==' ';i++);
         for (;str[i]>='0'&&str[i]<='9';i++);
         for (;str[i]==' ';i++);
         len[d]=0;
         for (;i<=l;i++)
            name[d][++len[d]]=str[i];
         name[d][len[d]+1]=0;
      }
      gets(str+1);
      for (l=1;strcmp(str+1,name[l]+1);l++);
      t2=x;
      for (t=1;t<=d;t++)
         for (i=1;i<p[t][0];i++)
            for (j=i+1;j<=p[t][0];j++)
               if (p[t][i]>p[t][j])
               {
                  p[t][i]^=p[t][j];
                  p[t][j]^=p[t][i];
                  p[t][i]^=p[t][j];
               }
      tt=ti[l];
      ss=sol[l];
      for (i=1;t2&&i<=p[l][0];i++)
      {
         tt+=p[l][i];
         ss++;
         t2--;
      }
      for (i=1;i<=d;i++)
         if (sol[i]>ss||sol[i]==ss&&ti[i]<tt)
         {
            t2-=s-sol[i];
            ans++;
         }
         else if (sol[i]<s)
            break;
      for (j=i;j<=d;j++)
         if (j!=l)
            t2-=ss-sol[j];
      for (j=i;j<=d;j++)
         if (j!=l&&t2>0)
         {
            t2-=s-ss;
            ans++;
         }
      printf("%d ",ans+1);
      t2=x;
      for (i=1;i<=d;i++)
         if (i!=l)
            t2-=s-sol[i];
      if (t2>=0&&sol[l]<s)
         printf("%d\n",d);
      else
      {
         for (i=1;sol[i]>sol[l]||sol[i]==sol[l]&&ti[i]<ti[l];i++);
         ans=i;
         t2=0;
         for (;i<=d;i++)
            if (i!=l)
            {
               t=ti[i];
               for (j=1;j<=sol[l]-sol[i];j++)
                  t+=p[i][j];
               if (t<ti[l]||sol[l]<s)
                  rec[++t2]=sol[l]-sol[i]+(t>=ti[l]);
            }
         for (i=1;i<t2;i++)
            for (j=i+1;j<=t2;j++)
               if (rec[i]>rec[j])
               {
                  rec[i]^=rec[j];
                  rec[j]^=rec[i];
                  rec[i]^=rec[j];
               }
         for (i=1;i<=t2;i++)
            if (x>=rec[i])
            {
               x-=rec[i];
               ans++;
            }
         printf("%d\n",ans);
      }
   }
   return 0;
}
