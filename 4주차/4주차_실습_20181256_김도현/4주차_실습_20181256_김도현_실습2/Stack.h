#include "LinkedList.h"
#include <string>

//1. 템플릿 클래스로 확장해야함
//2. Stack형식으로 Delete 함수 재정의해야함
//주의: first, current_size는 class의 멤버 변수이기 때문에 this 포인터를 사용하여 가져와야함

//LinkedList class를 상속받음
template <class T> class Stack : public LinkedList<T>{
	public:
		bool Delete (T &element){
			//first가 0이면 false반환
			if(this->first==0)return false;			
// LinkedList와 달리 Stack은 current가 가리키는 곳을 삭제
                        Node<T> *current=this->first; 
//current를 first로 생각
                        this->first=current->link;
 //first를 current->link로 재지정
                        element=current->data; 
//element를 current-<data로 지정
                        delete current; //current 삭제
                        this->current_size--; //current_size 1개 뺌
			return true;
			}
};
