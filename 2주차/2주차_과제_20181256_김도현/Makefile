cc = gcc #gcc 를 이용해서 컴파일하겠다
target = main #실행파일 이름을 main 으로 하겠다
objects= main.o calculator.o printer.o 
#컴파일을 하기 위한 .o 파일 모음
$(target) : $(objects) #target의 prerequisites 를 objects 로 둠
	$(cc) -o $(target) $(objects)
#gcc -o 명령어
#.c 파일 없이도 자동으로 생성됨
$(objects) : Header.h #헤더 파일 바껴도 object 다시 생성가능

.PHONY: clean #.PHONY를 이용해 오류 방지
clean : #make clean 으로 target, objects 파일 삭제
	rm $(target) $(objects)
