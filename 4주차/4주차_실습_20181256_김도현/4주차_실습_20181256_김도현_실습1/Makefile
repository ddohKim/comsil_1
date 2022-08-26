cc=g++ #g++을 이용해서 컴파일 하겠다
target=a.out #실행파일을 a.out으로 하겠다
objects=main.o #컴파일을 위한 .o 파일은 main.o
$(target):$(objects) #target의 prerequisites 를 objects로 둠
	$(cc) -o $(target) $(objects)
#g++ -o 명령
$(objects):LinkedList.h #header 파일은 LinkedList.h
.PHONY : clean #.PHONY 로 에러 방지
clean : # make clean 으로 tareget, object 파일들 삭제
	rm $(target)$(objects)	
