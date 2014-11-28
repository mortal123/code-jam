#include <stdio.h>

int main()
{
   unsigned long x,y,z,i=0;
   while (scanf("%lu%lu%lu",&x,&y,&z)!=EOF)
   {
      printf("Case #%lu: ",++i);
      if (x>y)
      {
         x^=y;
         y^=x;
         x^=y;
      }
      if (x>z)
      {
         x^=z;
         z^=x;
         x^=z;
      }
      if (y>z)
      {
         y^=z;
         z^=y;
         y^=z;
      }
      if (y==1)
         printf("%lu\n",z-1);
      else if (x==1)
         printf("%lu\n",2*y*z-y-z+(y-2)/2*2+(z-2)/2*2+2*(y&z&1)-((y>2||z>2)&&!(y&1)&&!(z&1)));
      else if (x==2)
         printf("%lu\n",x*y*(z-1)+x*z*(y-1)+y*z*(x-1)+(y-2)*(z-2)+3);
      else if (x==3)
         printf("%lu\n",x*y*(z-1)+x*z*(y-1)+y*z*(x-1)+6+2*(y+z-4)+2*(y-2)*(z-2)-(y-2)/2*2-(z-2)/2*2-(y-2)*(z-2)/2*2);
      else
         printf("%lu\n",x*y*(z-1)+x*z*(y-1)+y*z*(x-1)+12+(x-2)*(y-2)/2*2+(y-2)*(z-2)/2*2+(x-2)*(z-2)/2*2-!((x*y)&1)-!((y*z)&1)-!((x*z)&1));
   }
   return 0;
}
