#include "Header.h"//#include 를 이용하여 Header.h 헤더파일을 불러옴

void page_calculator(int *num_count,int page_number)
{//num_count[i]에 각 i 들의 개수 저장, page_number 는 page 수
int j=1; //j=10*j, 즉 1의 자리, 10의 자리..등 몇의 자리를 표현하기 위함
int i=0; //for 문 돌리기
int a=0;//끝 자리 수들을 만들어 num_count[remainder] 계산에 쓰임
while(page_number) //page_number 가 0보다 클때까지 while문이 돌아감
{
int remainder=page_number%10; //page_number를 10으로 나눈 나머지
page_number=page_number/10; //page_number를 10으로 나누고 다시 저장
for(i=0;i<remainder;i++){
 /*나머지 보다 작은 i에 대해 num_count[i]에 (page_number+1)*j를 더한다

197(remainder:9,page_number:1)에서 10의 자리를  예로 들면 num_count[0] 에는 000~009,100~109  이렇게 10의 자리가 0인 개수 (page_number+1)*10을 넣는다. 즉 page_number+1는 백의 자리 개수(0,1)이다. 이 예시는 10의 자리 이기 때문에 j=10 이다.

거기에 어느자리(1,10,100...)인지 j 를 곱해 개수를 구한다 */
num_count[i]=num_count[i]+(page_number+1)*j;
}
num_count[remainder]=num_count[remainder]+page_number*j+a+1;
/*num_count[remainder] 는 가장 마지막이 remainder 이기 때문에 불안정하다.그래서 page_number*j에  구하고자 하는 자릿수의 이전 숫자인 a 를 도입하여 밑 자리 수를 따로  더한다.(a+1)
197의 10의 자리를 예로 들면 num_count[9]에는 090~099에서 10개를 더하고 190~197 즉 a+1(7+1) 을 더한다.
197의 100의 자리를 예로 들면 num_count[1]에는 100~197, 98 즉 a+1(97+1)을 더한다.*/
i++; //num_count[remainder+1] 개수를 구한다.
for(i;i<10;i++)
num_count[i]=num_count[i]+page_number*j;
/*i가 remainder 보다 크다는 것은 그 자리수에 page_number*j 만큼 개수가 있다는 뜻이다. 
197의 1의 자리를 예로 들면 num_count[8]에는 08, 18,...188 까지 0~18 개 즉 19개에 각 1개 씩 있다. 즉 page_umber*j(19*1) 이다. 
*/ 
num_count[0]=num_count[0]-j;
/* 실제 우리는 000을 세지 않기 때문에 num_count[0]에 자릿수 만큼 빼준다.
197의 10의 자리를 예로 들면 num_count[0] 에 000~009 를 위에서 더해줬지만 여기의 10의 자리 0은 원래 존재하지 않는 숫자이다. 1~9 범위이기 때문이다. 즉 10을 빼주면 된다.
197의 100의 자리를 예로 들면 num_count[0]에 000~099 를 위에서 더해줬지만 여기의 100의 자리 0 은 원래 존재하지 않는다. 그래서 100을 빼준다.
*/
a=a+remainder*j;
 /*구하고자 하는 자릿수보다 하나 아래 있는  숫자를 a로 한다.
197의 10의 자리 구할때는 a=7, 100의 자리 구할때는 a=97이다*/

j=j*10; //자릿수를 while문 마다 j=j*10 만큼 늘린다.
}
}

