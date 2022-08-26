#include "Header.h"//#include 를 이용하여 Header.h 헤더파일을 불러옴
void print(int *num_count)
{for(int i=0;i<10;i++)//0부터 9까지 for문이 돔
 {
   printf("%d ",num_count[i]);
 //page_calculator를 통해 계산한 num_count[i]를 출력한다.
}
printf("\n"); //num_count를 다 출력후 다음줄에 출력하도록 미리 엔터키를 출력
}
        
