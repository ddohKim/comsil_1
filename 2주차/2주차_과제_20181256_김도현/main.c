#include "Header.h" //#include 를 이용해서 Header.h 헤더파일을 불러옴

int main(){ //테스트 케이스 및 페이지 수를 입력받고 출력하는  main 함수

int test_number; //테스트 케이스 개수
int *page_number; //테스트 케이스를 저장할 배열 생성

scanf("%d",&test_number); //몇개의 테스트 케이스를 받을건지 입력한다
//malloc 을 이용하여 테스트 케이스 개수만큼 동적 메모리 할당으로 배열 만듬
page_number=(int*)malloc(sizeof(int)*test_number); 

if(page_number==NULL){//만약 메모리부족으로 배열을 만들지 못한다면
printf("Error, No Memory!\n"); //에러메세지 출력
free(page_number); //에러를 방지하기 위한 page_number 배열 해제
exit(-1); //프로그램을 끝냄
}

for(int i=0;i<test_number;i++){ //테스트 케이스 개수만큼 for 문 돌림
scanf("%d",&page_number[i]);
 //페이지 수를 입력받고 page_number배열에 순차적으로 저장
}

for(int i=0;i<test_number;i++){//테스트 케이스 개수만큼 for 문 돌림
int num_count[10]={0};//0~9까지 몇개 들어있는지 확인하는 배열을 초기화.
//num_count[1] 에 1이 몇개 들어있는지 넣는다.
page_calculator(num_count,page_number[i]);
 //page_calculator 함수로 num_count[i] 에 i가 몇개 들어있는지 계산. 0<=i<=9
print(num_count);//print 함수를 이용해서 num_count 출력 
}

free(page_number); //malloc을 통해 할당된 page_number의 동적 메모리 해제
}
