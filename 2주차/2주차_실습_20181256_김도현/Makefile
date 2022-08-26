cc = gcc #gcc를 하여 컴파일하겠다
target = animal_exe #실행파일 이름을 정함
objects = main.o dog.o blackcow.o turtle.o  # make 하기위한 .o 파일의 모음

$(target) : $(objects) #.o 파일이 없어도 자동으로 생성
	$(cc) -o $(target) $(objects) 

$(objects) : animal.h #헤더파일 변경 시 objects들도 다시 생성

.PHONY : clean #.PHONY는 recipe 대표 이름, 돌발상황 방지
clean :
	rm $(target) $(objects)        

