#include "tetris.h"

static struct sigaction act, oact;



int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));
    
    treeroot=(RecNode *)malloc(sizeof(RecNode));
    treeroot->lv=0;
    treeroot->score=0;
    
    
    
	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_EXIT: exit=1; break;
        case MENU_RANK: rank(); break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

        for(int m=0;m<VISIBLE_BLOCKS+1;m++)
        {
        nextBlock[m]=rand()%7;}



	//nextBlock[0]=rand()%7;
	//nextBlock[1]=rand()%7;
    //nextBlock[2]=rand()%7; //과제에서는 미리나오는 블록이 2개 이기 때문에 nextBlock을 2까지로 올린다. BLOCK_NUM 3으로 수정.
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;
    
    treeroot->f=field;
    recommend(treeroot);
	DrawOutline();
	DrawField();
    DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate); //과제에서는 블록과 그림자를 같이 그려야한다.
    //DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
    
     // nextblock[2] 를 그릴 공간 테두리를 그린다.
    DrawBox(10,WIDTH+10,4,8);
	
    /* score를 보여주는 공간의 태두리를 그린다.*/
	move(17,WIDTH+10); //score 공간을 실습에 비해 약간 내렸다.
	printw("SCORE");
	DrawBox(18,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(19,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){ //과제에서는 nextBlock을 받아와 [1] [2] 모두 그려야 한다. 때문에 기존의 코드를 복사하여 [1] 를 [2]로 바꾸고 move 위치도 임의로 지정해주었다.
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
 
    for( i = 0; i < 4; i++ ){
        move(11+i,WIDTH+13); //y 축 11+i, x축 Width+13에 nextblock[2] 를 그릴 것이다.
        for( j = 0; j < 4; j++ ){
            if( block[nextBlock[2]][0][i][j] == 1 ){ //nextblock[2] 를 그리는 과정이다.
                attron(A_REVERSE); //문자색을 반전하여 출력하는 attron, attroff가 쓰였다.
                printw(" ");
                attroff(A_REVERSE);
            }
            else printw(" ");
        }
    }
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
//블록이 회전이나 이동이 가능한지확인
	// user code
for(int i=0;i<BLOCK_HEIGHT;i++) //블록의 HEIGHT 만큼
{
        for(int j=0;j<BLOCK_WIDTH;j++) //블록의 WIDTH 만큼
        {if(block[currentBlock][blockRotate][i][j]==1){ //블록이 있는곳
                int y=i+blockY; //움직이고자 하는 y 값이 field 범위?
                int x=j+blockX; //움직이고자 하는 x 값이 field 범위?
                if(y>=HEIGHT) return 0;//y 가 범위 넘으면 return 0
                if(x>=WIDTH) return 0;  //x 가 범위 넘으면 return 0
                if(x<0) return 0; //x가 범위 넘으면 return 0
                if(f[y][x]==1) return 0; //이미 f 차있으면 return 0                     
                }
         }
}
return 1; //checktomove 가능
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
//shadow 도 같이 지워줘야 한다.


switch(command)
{
case KEY_UP:for(int i=0;i<BLOCK_HEIGHT;i++){ //key_up 의 이전인 (blockroate+3)%4 를 통해 이전 정보 찾고 지우기
            
                for(int j=0;j<BLOCK_WIDTH;j++)
                {
                if(block[currentBlock][(blockRotate+3)%4][i][j]==1&&i+blockY>=0) //블록 찾고 위치 적절한지 확인한다음
                {move(i+blockY+1,j+blockX+1);printw(".");
                    int shadow_y=blockY+1; //shadow_y로 현재 y좌표 다음 y좌표를 둔다. 현재 위치에서 쭉 내려 그림자를 확인하기 때문에 x좌표는 신경안쓴다.
                    while(1){ //계속해서 break 나오기 전까지  반복한다
                        if(CheckToMove(f,currentBlock,(blockRotate+3)%4,shadow_y,blockX)) //계속 y값을 하나씩 내릴 수 있는지 확인해본다,
                            shadow_y=shadow_y+1; //맞다면 shawdow_y를 하나 증가 시켜 다음 checktoMove에 들어가도록 +1 한다.
                        else break; //더이상 내려갈 수 없다면 그 곳에 그림자가 생기면 될 것이다.
                    }
                    move(i+shadow_y,j+blockX+1);printw("."); //그림자도 같이 지워준다
                    
                } //printw를 통해 지우기
                }
                }
break;

case KEY_DOWN:for(int i=0;i<BLOCK_HEIGHT;i++){ //key_down 의 이전인 blcokY-1 지우기
                for(int j=0;j<BLOCK_WIDTH;j++)
                {
                if(block[currentBlock][blockRotate][i][j]==1&&i+blockY-1>=0)
                {move(i+blockY,j+blockX+1);printw(".");
                    int shadow_y=blockY; //shadow_y로 현재 y좌표 다음 y좌표를 둔다. 현재 위치에서 쭉 내려 그림자를 확인하기 때문에 x좌표는 신경안쓴다.
                    while(1){ //계속해서 break 나오기 전까지  반복한다
                        if(CheckToMove(f,currentBlock,blockRotate,shadow_y,blockX)) //계속 y값을 하나씩 내릴 수 있는지 확인해본다,
                            shadow_y=shadow_y+1; //맞다면 shawdow_y를 하나 증가 시켜 다음 checktoMove에 들어가도록 +1 한다.
                        else break; //더이상 내려갈 수 없다면 그 곳에 그림자가 생기면 될 것이다.
                    }
                    move(i+shadow_y,j+blockX+1);printw("."); //그림자도 같이 지워준다
                    
                }
                }
                }
break;

case KEY_LEFT:for(int i=0;i<BLOCK_HEIGHT;i++){ //key_left 의 이전인 blockX+1 지우기
                for(int j=0;j<BLOCK_WIDTH;j++)
                {
                if(block[currentBlock][blockRotate][i][j]==1&&i+blockY>=0)
                {move(i+blockY+1,j+blockX+2);printw(".");
                    int shadow_y=blockY+1; //shadow_y로 현재 y좌표 다음 y좌표를 둔다. 현재 위치에서 쭉 내려 그림자를 확인하기 때문에 x좌표는 신경안쓴다.
                    while(1){ //계속해서 break 나오기 전까지  반복한다
                        if(CheckToMove(f,currentBlock,blockRotate,shadow_y,blockX+1)) //계속 y값을 하나씩 내릴 수 있는지 확인해본다,
                            shadow_y=shadow_y+1; //맞다면 shawdow_y를 하나 증가 시켜 다음 checktoMove에 들어가도록 +1 한다.
                        else break; //더이상 내려갈 수 없다면 그 곳에 그림자가 생기면 될 것이다.
                    }
                    move(i+shadow_y,j+blockX+2);printw(".");//그림자도 같이 지워준다
                    
                }
                }
                }
break;

case KEY_RIGHT:for(int i=0;i<BLOCK_HEIGHT;i++){ //key_right 의 이전버전인 blockX-1 지우기
                for(int j=0;j<BLOCK_WIDTH;j++)
                {
                if(block[currentBlock][blockRotate][i][j]==1&&i+blockY>=0)
                {move(i+blockY+1,j+blockX);printw(".");
                    int shadow_y=blockY+1; //shadow_y로 현재 y좌표 다음 y좌표를 둔다. 현재 위치에서 쭉 내려 그림자를 확인하기 때문에 x좌표는 신경안쓴다.
                    while(1){ //계속해서 break 나오기 전까지  반복한다
                        if(CheckToMove(f,currentBlock,blockRotate,shadow_y,blockX-1)) //계속 y값을 하나씩 내릴 수 있는지 확인해본다,
                            shadow_y=shadow_y+1; //맞다면 shawdow_y를 하나 증가 시켜 다음 checktoMove에 들어가도록 +1 한다.
                        else break; //더이상 내려갈 수 없다면 그 곳에 그림자가 생기면 될 것이다.
                    }
                    move(i+shadow_y,j+blockX);printw("."); //그림자도 같이 지운다
                }
                }
}
break;

default: break;
}
    
DrawBlockWithFeatures(blockY,blockX,currentBlock,blockRotate);
    //과제에서는 Drawblock이 아닌 Drawblockwithfeatures 함수를 이용해 그림자와 블록을 동시에 그릴 수 있도록 수정한다.
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
//DrawBlock(blockY,blockX,currentBlock,blockRotate, ' ');

	//3. 새로운 블록 정보를 그린다. 
move(HEIGHT,WIDTH+10); //커서를 밖으로 이동시켜주기
}

void BlockDown(int sig){
	// user code
    treeroot->lv=0;// treeroot 초기화
    treeroot->score=0; // treeroot 초기화
if(CheckToMove(field, nextBlock[0],blockRotate,blockY+1,blockX))//checktomove를 통해 nextBlock[0] 블록을 밑으로 내릴 수 있는지 확인
{
blockY=blockY+1;// blockY 값을 하나 증가시킴
DrawChange(field,KEY_DOWN, nextBlock[0],blockRotate,blockY,blockX); //blockY 값을 하나 증가시키고 drawchange로 그림
	//강의자료 p26-27의 플로우차트를 참고한다.
}
else{
if(blockY==-1) gameOver=1; //blockY==-1 이면 더이상 떨어질 곳이 없어 게임 종료
else{
    
    score=score+AddBlockToField(field, nextBlock[0],blockRotate,blockY,blockX)+DeleteLine(field);
    //과제에서는 score가 라인이 꽉 찼을 때만 추가되는 것이 아니라 그냥 블록이 바닥에 닿아 있는 것도 점수에 추가해줘서 AddBlockToField에서 score를 계산한 return 값도 score에 저장을 해준다.
    
    //AddBlockToField(field, nextBlock[0],blockRotate,blockY,blockX); //field에 블록 추가

for(int i=0;i<VISIBLE_BLOCKS;i++)
nextBlock[i]=nextBlock[i+1];
//for문으로 visible_blocks 에 따라 nextblock 다르게 할당
nextBlock[VISIBLE_BLOCKS]=rand()%7;
//nextBlock의 마지막 블록은 다음 새로운 것 받아로 것 추가

//nextBlock[0]=nextBlock[1]; //nextblock[0] 을 다음 블록으로 설정
//nextBlock[1]=nextBlock[2];// 과제에서는 nextblock이 2개 있기 때문에 nextBlock[1] 을 다음 블록으로 설정한다
  //  nextBlock[2]=rand()%7; // nextBlock[2]는 다음 새로운 것을 받아올 것을 추가해준다.
    
    //nextBlock[1]=rand()%7; //새로운 블록 추가
    
    treeroot->f=field; //treeroot 의 f 를 현재 field로 넣기
    recommend(treeroot); //recommend 함수 실행
    
    
blockRotate=0; //기존의 block 정보들 초기화
blockY=-1; //초기화
blockX=WIDTH/2-2;// 초기화
//score=score+DeleteLine(field); //score 추가 하기 위해 deleteline 호출
PrintScore(score); //점수 출력
DrawNextBlock(nextBlock); //다음 블록 해당 박스에 그리기
    //여기서는 이제 nextBlock[1] ,nextBlock[2] 를 그려준다.



}
DrawField(); //추가된 Field 다시 그리기
DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate); //과제에서는 블록과 그림자를 같이 그려야한다.
//DrawBlock(blockY,blockX,nextBlock[0],blockRotate, ' '); //다시 블록을 첫 시작에서 하도록
    treeroot->lv=0;// treeroot 초기화
    treeroot->score=0; // treeroot 초기화
}
timed_out=0; //시간 다시 0
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
    //void -> int로 return 값을 변경하였다.
    
    int counted=0; //바닥에 닿는 블록의 개수를 저장하기 위한 변수이다.
for(int i=0;i<BLOCK_HEIGHT;i++) //블록의 HEIGHT 만큼
{
        for(int j=0;j<BLOCK_WIDTH;j++) //블록의 WIDTH 만큼
        {if(block[currentBlock][blockRotate][i][j]==1){ //블록이 있는곳
      
          f[blockY+i][blockX+j]=1; //필드에 해당 공간을 채운다                     

            if(blockY+i==HEIGHT-1) counted++;//만약 현재의 Y값이 Height 보다 하나 작은 즉 마지막 줄에 닿는다면 해당 counted를 하나 늘린다.
             else if(f[blockY+i+1][blockX+j]!=0) counted++;
//만약 바닥면이 아닌 필드에 블록이 닿는 경우는 해당 블록의 하나 밑 필드가 비어있지 않을경우에도 count를 하나 늘린다.       
 }
         }
}
    int touchedScore=counted*10; //여기서는 touch한 수만큼 score를 10배로 준다.
    return touchedScore; //touchedScore를 리턴하여 BlockDown에 score 계산시 더해준다.
}


int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
bool checkline=false;
int completedline=0;
for(int i=0;i<HEIGHT;i++)
{
checkline=true;
        for(int j=0;j<WIDTH;j++)
        {if(f[i][j]==1) //해당 필드의 [i][j]가 채워져 있으면 checkline=true, 아니면 checkline=false 하고 break; 다음 for문 돌아감
        {checkline=true;}
        else{checkline=false; break;}
        }
        if(checkline){ //checkline=true 이면
        completedline++; //완성줄 1개 추가
        for(int k=i;k>0;k--) //i 행 기준 그 위의 모든 블록들을 하나씩 내린다 
        {for(int s=0;s<WIDTH;s++){ //열은 그대로 한다
                f[k][s]=f[k-1][s]; //field 를 아래로 한칸 씩 내린다
} }
}
}
	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
int scored=completedline*completedline*100;
return scored;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// user code
    int shadow_y=y+1; //shadow_y로 현재 y좌표 다음 y좌표를 둔다. 현재 위치에서 쭉 내려 그림자를 확인하기 때문에 x좌표는 신경안쓴다.
    while(1){ //계속해서 break 나오기 전까지  반복한다
        if(CheckToMove(field,nextBlock[0],blockRotate,shadow_y,x)) //계속 y값을 하나씩 내릴 수 있는지 확인해본다,
            shadow_y=shadow_y+1; //맞다면 shawdow_y를 하나 증가 시켜 다음 checktoMove에 들어가도록 +1 한다.
        else break; //더이상 내려갈 수 없다면 그 곳에 그림자가 생기면 될 것이다.
    }
    DrawBlock(shadow_y-1,x,blockID,blockRotate,'/'); //drawBlock을 호출하여 (shadow_y, x)위치에 '/' 로 그림자블록을 그린다.
    
}

void DrawBlockWithFeatures(int y, int x, int blockID,int blockRotate){
    DrawBlock(y,x,blockID, blockRotate,' ');// block과 shadow를 그려준다.
    DrawBlock(recommendY, recommendX, blockID, recommendR,'R'); //추천 기능 블록을 r로 그려준다
    DrawShadow(y,x,blockID,blockRotate);
}

void createRankList(){
    // 목적: Input파일인 "rank.txt"에서 랭킹 정보를 읽어들임, 읽어들인 정보로 랭킹 목록 생성
    // 1. "rank.txt"열기
    // 2. 파일에서 랭킹정보 읽어오기
    // 3. LinkedList로 저장
    // 4. 파일 닫기
    FILE *fp;
    int i, j;

    //1. 파일 열기
    fp = fopen("rank.txt", "r");
    if(fp==NULL)
        {fp=fopen("rank.txt","w+");
        fprintf(fp,"%d\n",0);
}   
 // 2. 정보읽어오기
     //fscanf(fp,"%d",&ranknumber); //global 변수 ranknumber에 데이터 수 읽어옴
    /* int fscanf(FILE* stream, const char* format, ...);
     stream:데이터를 읽어올 스트림의 FILE 객체를 가리키는 파일포인터
    format: 형식지정자 등등
    변수의 주소: 포인터
    return: 성공할 경우, fscanf 함수는 읽어들인 데이터의 수를 리턴, 실패하면 EOF리턴 */
    // EOF(End Of File): 실제로 이 값은 -1을 나타냄, EOF가 나타날때까지 입력받아오는 if문
    char name[NAMELEN+1]; //임시로 name 과 score에 저장하여 node에 넣어주기
    int score;
    top =NULL; //top 과 prev를 이용하여 노드 만들기
    scorenode* prev=NULL; //prev를
    
    if (fscanf(fp,"%d",&ranknumber) != EOF) {
        for(int i=0;i<ranknumber;i++)
        {
            fscanf(fp, "%s %d",name, &score); //fscanf로 name과 score 읽어들이기
            scorenode* newnode=(scorenode*)malloc(sizeof(scorenode));
            //newnode=NULL ; // 이름이 없을 경우에 대비하여 초기화를 시킨다
            strcpy(newnode->rankname,name); //newnode의 rankname 에 name 넣고
            newnode->rankscore=score; //rankscore 에 받아온 score 넣는다
            newnode->link=NULL;
            if(top!=NULL) {
                prev->link=newnode; //prev의 link를 newnode로 하고
                prev=newnode; // prev를 newnode로 하여 서로 연결해줌
            }
            else{
                top=newnode; //top이 null 이라면 newnode를 top으로 두고
                prev=top; //prev도 top으로 두어 for문 다음부터 연결이 되도록 한다
                top->link=NULL;  //top->link를 null로 둔다         
 }
        }
        
    }
    else{
        move(50,0);
        printw("No data"); //데이터가 없다는 메세지를 보냄
        return;
    }
    // 4. 파일닫기
    fclose(fp);
}

void rank(){
    //목적: rank 메뉴를 출력하고 점수 순으로 X부터~Y까지 출력함
    //1. 문자열 초기화
    createRankList();//createdRanklist 함수 불러오기
    int X=1, Y=ranknumber, ch, i, j;
    clear();
    //2. printw()로 3개의 메뉴출력
    mvprintw(0,0,"1. list ranks from X to Y\n");
    printw("2. list ranks by a specific name\n");
    printw("3. delete a specific rank\n");
    //3. wgetch()를 사용하여 변수 ch에 입력받은 메뉴번호 저장
   
    ch=wgetch(stdscr); //숫자 하나 입력 받음
    
    //4. 각 메뉴에 따라 입력받을 값을 변수에 저장
    //4-1. 메뉴1: X, Y를 입력받고 적절한 input인지 확인 후(X<=Y), X와 Y사이의 rank 출력
    if (ch == '1') {
        echo(); //입력 받은 문자를 출력하도록
        printw("X: "); //X: 입력받기
        scanw("%d", &X);
        printw("Y: "); //Y: 입력받기
        scanw("%d", &Y);
        noecho(); //다시 nonecho 로 설정
        printw("     name          |    score    \n");
        printw("----------------------------------\n");
        if(X>Y||ranknumber==0||X>ranknumber)//X가 더 크거나 X, Y가 해당 범위를 넘으면, ranknumber==0 이라면
        {printw("search failure: no rank in the list"); }//error 메세지 출력
        else{
        if(X=='\0'||X<1) X=1; //X가 안받아졌다면 자동으로 rank 1
        if(Y=='\0'||Y>ranknumber) Y=ranknumber; //Y가 안받아졌거나 Y가 ranknumber보다 크다면  자동으로 마지막 ranknumber
        scorenode* currentnode=top;// currentnode를 통해 linkedlist 탐색
            for(int i=1;i<=Y;i++) //i는 1부터 Y까지만 for문을 돌면 됨
            {if(X<=i) //i가 X보다 크거나 같은 시점부터 프린트함
                printw(" %-18s|  %-10d\n",currentnode->rankname,currentnode->rankscore);
                currentnode=currentnode->link; //top 노드에서 하나 앞으로 감
            }
            
        }
    
    
    }

    //4-2. 메뉴2: 문자열을 받아 저장된 이름과 비교하고 이름에 해당하는 리스트를 출력
    else if ( ch == '2') {
        char str[NAMELEN+1]; //scanw를 통해 str에 넣어줄 것이다
        int check = 0;//check를 통해 이름이 동일한 node가 없다면 check가 0이기 때문에 search failure 메세지를 출력할 것이다.
        echo(); //입력 받은 문자를 출력하도록(보이도록)
        printw("input the name: "); //printw로 이름을 입력하라고 출력해준다
        scanw("%s",str); //scanw로 이름 받아와 str에 저장한다.
        noecho(); //다시 noecho로 입력 문자 안보이도록 해준다.
        printw("     name          |    score    \n");
        printw("----------------------------------\n"); //해당 예시에 맞는 창을 출력하기
        scorenode* currentnode=top; //currentnode를 통해 linkedlist 탐색을 한다
        for(int i=1;i<=ranknumber;i++) //top 노드부터 마지막 노드까지 전부 다 이름이 같은지 확인해야 한다.
        {
            if(strcmp(currentnode->rankname,str)==0) //만약 currentnode의 rankname과 입력받은 문자 즉 str과 같다면, strcmp 즉 string compare 을 한다.
            {printw(" %-18s|  %-10d\n",currentnode->rankname,currentnode->rankscore); //해당 이름이 같은 node의 rankname과 rankscore를 예시에 맞게 화면에 출력해준다.
                check=check+1; //그리고 check를 1을 올려 이름이 같은 node를 1번 추가로 화면에 출력했음을 flag한다. 즉 이 코드가 실행된다면 search failure 메세지를 출력하지 않는다는 의미이다.
            }
            currentnode=currentnode->link; //currentnode를 하나 다음 node로 이동시켜 linkedlist를 탐색한다.
        }
        if(check==0) //만약 check==0이라면 입력받은 이름에 대해 node가 출력되지 않았다는 의미이기에
            printw("search failure: no name in the list"); //search failure 메세지만 출력해준다.
    }

    //4-3. 메뉴3: rank번호를 입력받아 리스트에서 삭제
    else if ( ch == '3') {
        int num;
        echo(); //입력 받은 문자를 출력하도록
        printw("input the rank: "); //printw로 삭제를 원하는 rank의 번호를 입력하라고 출력해준다
        scanw("%d", &num); //scanw로 rank 번호를 받아와 num에 저장한다.
        noecho(); //다시 noecho로 입력 문자 안보이도록 해준다.
        if(num<1||num>ranknumber) //만약 입력 받은 num이 1보다 작거나 ranknumber 보다 크다면 삭제될 노드가 존재하지 않다는 의미이다.
            printw("search failure: the rank not in the list"); //search failure 메세지를 출력해준다.
        else{
            scorenode* currentnode=top; //currentnode를 통해 linkedlist 탐색을 한다
            scorenode* prev=NULL;//prevnode는 currentnode 하나 이전 node를 의미하고 이 역시 linkedlist 탐색에 이용한다.
            for(int i=1;i<=ranknumber;i++){ //삭제될 노드는 최소 1(top) 부터 최대 ranknumber에 해당하는 node이기 때문에 최대 ranknumber 만큼의 for문이 돌아야 한다.
                if(num==1)//top노드를 지워야할 때는 top을 변경시켜야 한다.
                {
                    top=currentnode->link; //top을 currentnode->link즉 top->link로 다음 노드로 이동시킨다.
                    currentnode=NULL; //연결을 끊는다
                    free(currentnode); //currentnode 를 free로 삭제시켜준다.
                    
                    ranknumber=ranknumber-1; //노드를 하나 지웠으니 ranknumber를 1 빼준다.
                    writeRankFile(); //바뀐 정보를 새로 rank.txt에 입력해준다.
                    printw("result: the rank deleted"); //성공적으로 해당 rank가 지워졌음을 화면에 출력해준다.
                    break; //for 문을 나간다
                }
                else if(num==i) //만약 num과 i 가 같다면 i번째 해당 node, 즉 num 번째 해당 node를 지우면 될것이다.
                {
                    prev->link=currentnode->link;//currentnode가 지워져야 하기 때문에 바로 prev->link 즉 currentnode 이전 노드의 link가 currentnode->link를 가리키면 된다.
                    currentnode=NULL; //연결을 끊는다
                    free(currentnode); //currentnode 를 free로 삭제시켜준다.
                    
                    ranknumber=ranknumber-1; //노드를 하나 지웠으니 ranknumber를 1 빼준다.
                    writeRankFile(); //바뀐 정보를 새로 rank.txt에 입력해준다.
                    printw("result: the rank deleted"); //성공적으로 해당 rank가 지워졌음을 화면에 출력해준다.
                    break; //for 문을 나간다
            }
                else{
                    prev=currentnode;//prev를 currentnode로 두고
                    currentnode=currentnode->link; //curretnode를 currentnode->link 즉 다음 노드로 놔두고 탐색을 계속해 나간다
                }
                }
        
    }
    }

    getch();

}

void writeRankFile(){
    // 목적: 추가된 랭킹 정보가 있으면 새로운 정보를 "rank.txt"에 쓰고 없으면 종료
    int sn, i;
    //1. "rank.txt" 연다
    FILE *fp = fopen("rank.txt", "w");
    fscanf(fp,"%d",&sn); //sn을 확인하여 변경할 것이 있는지 없는지 확인
    //2. 랭킹 정보들의 수를 "rank.txt"에 기록

    //3. 탐색할 노드가 더 있는지 체크하고 있으면 다음 노드로 이동, 없으면 종료
    scorenode* currentnode=top;
    if(currentnode==NULL){
        fprintf(fp,"%d\n",0); //ranknumber 자리에 0 기입
    }
    if ( sn == ranknumber) return; //ranknumber와 sn 비교하여 동일한지 확인
    else { //다르기 때문에 다시 기입해줘야함
        fprintf(fp,"%d\n",ranknumber); //ranknumber 기입
        while(1)
        {if(currentnode!=NULL)
        {fprintf(fp,"%s %d\n",currentnode->rankname,currentnode->rankscore);
            currentnode=currentnode->link;
        } //currentnode를 top부터 하나씩 움직이면서 전체적인 것을 다시 기입
        else break; //currentnode가 null이면 그만 while문을 돈다
        }
    }
    
    scorenode* tmp=NULL;
    while(top!=NULL) //linkedlist를 free 시킨다
    {
        tmp=top; //tmp를 현재 노드로 두고
        top=top->link; //계속 탐색
        free(tmp); //free
    }
    
   // for ( i= 1; i < score_number+1 ; i++) {
  //      free(a.rank_name[i]);
 //   }
  //  free(a.rank_name);
 //   free(a.rank_score);
    fclose(fp); //fp를 닫는다
}

void newRank(int score){
    // 목적: GameOver시 호출되어 사용자 이름을 입력받고 score와 함께 리스트의 적절한 위치에 저장
    createRankList();
    char str[NAMELEN+1];
    int i, j;
    clear();
    //1. 사용자 이름을 입력받음
    echo(); //입력문자 보이게
    printw("Your name: "); //이름 받아들이기
    scanw("%s",str);
    //2. 새로운 노드를 생성해 이름과 점수를 저장, score_number가
    noecho(); //다시 echo를 지워 안보이게
    scorenode* currentnode=top; //top과 prev 이용하여 노드 찾기
    scorenode* prev;
    scorenode* newnode=(scorenode*)malloc(sizeof(scorenode)); //newrank에서 받아온 것을 newnode에 넣기
    //newnode=NULL; // newnode 초기화를 시킨다
    strcpy(newnode->rankname,str); // 이름 받아온거 넣기
    newnode->rankscore=score;
    
    if(top==NULL) //top이 비었다면
    {
        top=newnode;
        top->link=NULL;
    }
    else
        {
    if(top->rankscore <= newnode->rankscore) 
        { //top보다 newnode가 크거나 같을때
        newnode->link=top;
        top=newnode;
        }
    else { //그 외 경우
        //currentnode=currentnode->link; //top이 아니기 때문에 한칸 이동
        while(1)
        {
            if(currentnode==NULL){//currentnode가 없다면
                prev->link=newnode; //prev->link를 newnode로 두고
                newnode->link=NULL; //newnode 다음을 null로 설정
                break;
            }
            else if(currentnode->rankscore <= newnode->rankscore)
            {
                newnode->link=currentnode; //newnode가 currentnode보다 크거나같기 때문에 newnode->link를 currentnode
                prev->link=newnode; //prev->link는 newnode
                break; //newnode의 rankscore가 더 크거나 같을때 중지
                
            }
            else{
                prev=currentnode; //계속 탐색해 나감
                currentnode=currentnode->link; //current node로 계속 탐색
            }
        }
    }
    }
    ranknumber=ranknumber+1; //ranknumber를 1 더해준다
    writeRankFile(); //rank.txt에 입력
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
    int recommendScore=0;// 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

    // user code
    int k=-1; //child[k]를 탐색할 때 사용하는 index 변수 k 이다.
    int rec_x; //현재 추천 x 좌표를 의미한다
    int rec_r; //현재 추천 r rotation 을 의미한다.
    
    RecNode **child=root->c; //root->c 를 RecNode **child 로 선언했다.
    for(int i=0;i<CHILDREN_MAX;i++)//각 child[i]에 동적 메모리가 필요한 부분에 메모리를 할당해준다. 각 child 노드의 메모리와 child[i]의 안의 field 에 메모리를 줘야한다.
    {
        child[i]=(RecNode *)malloc(sizeof(RecNode));
        child[i]->f=(char (*)[WIDTH])malloc(sizeof(char)*WIDTH*HEIGHT);
    }
    
    
    for(rec_r=0;rec_r<NUM_OF_ROTATE;rec_r++) //rotation 0,1,2,3을 먼저 for문을 두어 0부터 순차적으로 accumulatedScore를 계산해본다
    {
        for(rec_x=-1;rec_x<WIDTH;rec_x++) //다음은 rec_x 즉 x좌표를 가장 왼쪽부터 오른쪽까지 순차적으로 이동시키면서 accumulatedScore를 계산해본다
        {
            int accumulatedScore=0; //accumulatedScore 초기화
            int rec_y=0; //for문이 실행될때 마다 y값을 초기화 시킨다(blockY가 -1부터 시작하니 그보다 한 칸 아래인 0으로 설정했다)
            if(!CheckToMove(root->f,nextBlock[root->lv],rec_r,rec_y+1,rec_x)) continue; //우선 CheckToMove 함수를 실행하여 rec_y+1 을 하였을 때 한칸 내려갈 수 있는지 확인했다. 만약 내려 갈 수 없다면 아래로 처음부터 움직일 수 없다는 의미거나 rec_x 가 field 범위를 넘어갔다는 것이다. 이때는 continue를 사용하여 해당 for문이 계속 실행되지 않고 다음 rec_x+1 에 대해 실행을 해주었다. 이 과정이 없다면 child[i]를 최대 CHILDREN_MAX 까지 할당했는데 현재 2중 for문에서 rec_r*rec_x 가 CHILDREN_MAX보다 더 커 segmantation fault 발생
            
            while(1){ //계속해서 break 나오기 전까지  반복한다
                if(CheckToMove(root->f,nextBlock[root->lv],rec_r,rec_y+1,rec_x)) //계속 y값을 하나씩 내릴 수 있는지 확인해본다,
                    rec_y=rec_y+1; //맞다면 rec_y를 하나 증가 시켜 다음 checktoMove에 들어가도록 +1 한다. 최종적으로 내려갈 수 있는 최대 y 값인 rec_y가 완성된다
                else break;
            }
                k++; //다음 child[k+1] node 로 갈 수 있도록 k 값을 1 증가시켜준다
               child[k]->lv=root->lv+1; //child의 leveㅣ을 root level 보다 하나 증가시킨다
        
            for( int i =0; i<HEIGHT;i++) //2중 for문을 이용하여 child Node의 field를 root의 field로 채운다.
                for(int j=0;j<WIDTH;j++)
                    child[k]->f[i][j]=root->f[i][j];
           
            accumulatedScore+=(AddBlockToField(child[k]->f,nextBlock[root->lv],rec_r,rec_y,rec_x)+DeleteLine(child[k]->f));
           //accumulatedScore는 안쪽 for문이 실행될때마다 초기화 된다. 그래서 여기에 rec_r,rec_y,rec_x 즉 해당 2중 for문으로 부터 구할 수 있는 rotation, y,x 좌표를 통해 score 점수를 계산해 저장한다
            if(child[k]->lv<VISIBLE_BLOCKS) //만약 child 노드의 level 이 VISIBILE_BLOCKS 즉 최대 level 보다 작다면 재귀함수 recommend(child[k])를 넣어 child[k]의 또 child 노드들의 recommend 함수를 통해 계산된 점수를 누적해서 accumulatedScore에 저장한다.
                accumulatedScore+=recommend(child[k]);
      
            child[k]->score=accumulatedScore;//accumulatedScore를 child[k]의 score에 저장한다
            
        if(recommendScore==accumulatedScore) //만약 최종적으로 최대 점수를 return 시키는 recommendScore변수 값과 현재의 accumulatedScore가 같다면
        {
            if(root->lv==0){ //만약 root->lv이 0이라면 가장 parent node이기 때문에
                if(rec_y>recommendY){ //recommendY 값과 rec_y값을 비교해 만약 recommendY 값이 더 작다면 최종 추천 블록의 y 값이 더 작다는 의미로 위쪽 블록을 의미한다. 이는 게임 상 블록이 위로 쌓일 수록 빨리 죽을 가능성이 높기 때문에 고려하였다.
                    recommendX=rec_x;recommendY=rec_y;recommendR=rec_r;
                }// 더 아래쪽에 블록이 쌓일 수 있도록 현재 2중 for문에서 얻는 rotation, x,y 값을 최종 값인 recommendR, recommendX,recommendY에 저장.
                recommendScore=accumulatedScore; //recommendScore역시 accumulatedScore로 변경해준다 (이 경우는 같을 경우여서 값 변화는 없다)
            }
        }
        if(recommendScore<accumulatedScore)
        {//만약 최종적으로 최대 점수를 return 시키는 recommendScore변수 값과 현재의 accumulatedScore가 같다면
            if(root->lv==0){//만약 root->lv이 0이라면 가장 parent node이기 때문에
                recommendX=rec_x;recommendY=rec_y;recommendR=rec_r;
            }//현재 2중 for문에서 얻는 rotation, x,y 값을 최종 값인 recommendR, recommendX,recommendY에 저장.
            recommendScore=accumulatedScore;//recommendScore역시 accumulatedScore로 변경해준다
        }
            
        }
    }
    
    for(int i=0;i<CHILDREN_MAX;i++) //위에서 할당한 child[i] 메모리를 다시 free 시켜주는 과정이다. 메모리 절약을 위해서는 필요한 과정이다.
    {
        free(child[i]->f); //먼저 child[i]안에 있는 f 부터 메모리 free 시키고
        free(child[i]); //child[i] 를 free 시킨다
    }

    return recommendScore; //점수 계산에 사용되는 재귀함수에서 해당 recommend함수 실행 결과를 받을 수 있게 recommendScore를 return 해준다.
}

void recommendedPlay(){
	// user code
}
