#include <stdio.h>
#include <string.h>

struct case1
{
   long x,y;
}p[2501]={0,0};
char map[55][55]={0},tmp[10001]={0},str[10001]={0},func[26][10001]={0};
long x,y,n,m,face=0,tot=0;

void walk(char s)
{
   if (s=='R')
      face=(face+1)%4;
   else if (s=='L')
      face=(face+3)%4;
   else if (!face&&x>1)
      x--;
   else if (face==1&&y<m)
      y++;
   else if (face==2&&x<n)
      x++;
   else if (face==3&&y>1)
      y--;
   if (map[x][y]=='*')
   {
      map[x][y]='~';
      p[++tot]=(struct case1){x,y};
   }
}

void work(long now,char p1,char p2)
{
   long i;
   char s1,s2;
   for (i=1;func[now][i];i++)
      if ((func[now][i]=='L'||func[now][i]=='R'||func[now][i]=='C')&&func[now][i-1]!='('&&func[now][i-1]!=',')
         walk(func[now][i]);
      else if (func[now][i]=='1'&&func[now][i-1]!='('&&func[now][i-1]!=',')
         walk(p1);
      else if (func[now][i]=='2'&&func[now][i-1]!='('&&func[now][i-1]!=',')
         walk(p2);
      else if (func[now][i]==')')
         if (func[now][i-1]=='(')
            work(func[now][i-2]-'a',0,0);
         else if (func[now][i-2]=='(')
         {
            if (func[now][i-1]=='1')
               s1=p1;
            else if (func[now][i-1]=='2')
               s1=p2;
            else
               s1=func[now][i-1];
            work(func[now][i-3]-'a',s1,0);
         }
         else
         {
            if (func[now][i-3]=='1')
               s1=p1;
            else if (func[now][i-3]=='2')
               s1=p2;
            else
               s1=func[now][i-3];
            if (func[now][i-1]=='1')
               s2=p1;
            else if (func[now][i-1]=='2')
               s2=p2;
            else
               s2=func[now][i-1];
            work(func[now][i-5]-'a',s1,s2);
         }
}

int main()
{
   long i,j,k,t,l=0,s=0;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
      scanf("%s",map[i]+1);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (map[i][j]=='R')
         {
            x=i;
            y=j;
            map[i][j]='~';
         }
   while (gets(tmp+1)!=NULL)
   {
      l+=strlen(tmp+1);
      strcat(str+1,tmp+1);
   }
   for (i=1;i<=l;i++)
      if (str[i]!=' ')
         str[++s]=str[i];
   for (i=1;i<=s;i=j+1)
   {
      j=i;
      while (str[j]!='}')
         j++;
      if (str[i+2]==')')
      {
         t=0;
         for (k=i+4;k<j;k++)
            func[str[i]-'a'][++t]=str[k];
      }
      else if (str[i+3]==')')
      {
         t=0;
         for (k=i+5;k<j;k++)
            if (str[k]!=str[i+2])
               func[str[i]-'a'][++t]=str[k];
            else
               func[str[i]-'a'][++t]='1';
      }
      else
      {
         t=0;
         for (k=i+7;k<j;k++)
            if (str[k]==str[i+2])
               func[str[i]-'a'][++t]='1';
            else if (str[k]==str[i+4])
               func[str[i]-'a'][++t]='2';
            else
               func[str[i]-'a'][++t]=str[k];
      }
   }
   work('m'-'a',0,0);
   printf("%ld\n",tot);
   for (i=1;i<=tot;i++)
      printf("%ld %ld\n",p[i].x,p[i].y);
   return 0;
}
