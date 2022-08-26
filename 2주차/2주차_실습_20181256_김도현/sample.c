#include <stdio.h>

main(void)
{
int i;
double num;

for(i=0; i<5;i++)
{
num=i/2+i;
 //에러를 고치기 위해서는 (double)i/2+i; 변수 type 간의 연산 에러이다
printf("num is %f \n",num);
}
}

