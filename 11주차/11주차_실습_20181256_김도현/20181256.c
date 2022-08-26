#include <stdio.h>
#include <stdlib.h>
#include <time.h>
FILE* fp; //파일 불러오기

int main() {
    int WIDTH ; // 미로의 가로 길이를 의미
    int HEIGHT; //미로의 세로 길이를 의미
    printf("Input the maze_width: "); //가로길이를 scanf를 통해 받아온다.
    scanf("%d", &WIDTH);
    printf("Input the maze_height: "); //세로길이를 scanf를 통해 받아온다.
    scanf("%d", &HEIGHT);

    fp = fopen("maze.maz", "wt"); //maze.maz 파일을 생성하여 여기에 미로를 입력할 것이다.
    
    srand((unsigned int)time(NULL)); //rand 함수가 실제로 실행될때마다 난수 값이 다르게 받아와야하기 때문에 srand함수를 통해 rand 난수를 입력받는다.
    
    for (int i = 0; i < WIDTH; i++) //가장 윗 줄을 입력받는 반목문이다.
    {printf("+-");
        fprintf(fp,"+-");
    }
    printf("+\n"); //마지막에 +를 적어주고 엔터를 쳐서 1행을 받을 수 있도록 한다. 
    fprintf(fp,"+\n");
    
    int* maze=(int*)malloc(sizeof(int)*WIDTH); //maze 배열 동적할당을 받아 여기에 한 방에 속해있는 집합을 저장한다.
    int* side=(int*)malloc(sizeof(int)*(WIDTH - 1)); //side 배열 동적할당을 받아 side 벽을 세울지 말지 결정한다.
    int* under=(int*)malloc(sizeof(int)*WIDTH); //under 배열 동적할당을 받아방에 따라 수직경로를 만들지 말지 결정한다. 즉 under 벽을 의미한다. 여기에는 집합을 통해 비교한다.
    
    for (int i = 0; i < WIDTH; i++) //가장 처음 maze배열에 서로 다른 집합 원소를 저장해놓는다.
    {
        maze[i] = i;
    }
    
    int set_number = WIDTH-1; //set_count 는 새로운 집합 number가 생성되었을 때 이를 사용하여 기존에 없는 집합숫자를 부여한다. 
    int under_flag = 0; //under_flag는 수직경로에서 현재 집합 중에 수직경로가 생성되어있는지 없는지 판단하는 flag이다. 없다면 최소한 1개는 수직경로를 생성해야한다.
    
  
    
    for (int j = 0; j < HEIGHT; j++) { //높이 크기만큼 반복문을 돌린다.
        printf("| "); //가장 처음 행에 벽을 세워 테두리를 만든다.
        fprintf(fp,"| ");
        
        
        for (int i = 0; i < WIDTH - 1; i++)
            side[i] = 1; //side벽을 모두 1로 초기화 시켜서 벽이 존재하게 한다. 
        
        for (int i = 0; i < WIDTH; i++)
        {
            if (i < WIDTH - 1) { //여기서는 side 벽을 결정해야 하기 때문에 인덱스 크기가 WIDTH-1 인 side에 i<WIDTH-1 을 사용하여 인덱스 오류가 나지 않게 한다.
                
                
                    if (maze[i] != maze[i + 1]) { //만약 인접한 방 사이의 집합이 다를 경우
                    
                    if (rand() % 2||j==HEIGHT-1) //rand 함수를 이용하여 50프로 확률로 벽을 지우거나 만약 j=HEIGHT-1 즉 가장 마지막 행을 입력할 for문이 시작된다면 무조건 벽을 지워야 한다.
                    {
                        side[i] = 0; //side[i] 를 0으로 하여 벽을 지울 수 있게 한다.
                        if(maze[i+1]>maze[i]) //만약 오른쪽 방의 집합이 왼쪽 방의 집합보다 크다면 더 작은 쪽으로 집합들을 모두 바꿔준다.
                        {
                            int same_set=maze[i+1]; //maze[i+1] 과 같은 집합들을 모두 찾아 
                            for(int k=0;k<WIDTH;k++)
                            {
                                if(maze[k]==same_set)
                            {
                                maze[k]=maze[i]; //이들 모두 집합을 maze[i] 로 바꿔준다.
                            }   
                            }
                        }
                        
                        else{
                            int same_set=maze[i]; //maze[i] 와 같은 집합을 모두 찾아
                            for(int k=0;k<WIDTH;k++)
                            {if(maze[k]==same_set)
                                maze[k]=maze[i+1];} //이들 모두 집합을 maze[i+1]로 바꿔준다.
                        }                     
                    }
                }
                if (side[i] == 0) //만약 side가 0이라면 side벽을 지워야한다는 의미로 스페이스바를 출력하고
                {printf("  ");
                    fprintf(fp,"  ");
                }
                else { //만약 side가 1이라면 side벽이 있어야 한다는 의미로 '|' 벽을 출력한다.
                    printf("| ");
                    fprintf(fp,"| ");
                }
            
            }
            
        }

        printf("|\n"); //한 행의 가장 마지막 열의 테두리 벽을 출력하고 엔터를 쳐 다음 under벽을 그릴 수 있게 한다.
        fprintf(fp,"|\n");
        for (int i = 0; i < WIDTH; i++) //반복문을 WIDTH 만큼 돌아 수직경로를 탐색한다.
        {
                if (i > 0) //index 오류가 나지 않게 첫번째 방과 구분지었다.
                {
                    if (maze[i] == maze[i - 1]) //인접한 왼쪽방과 오른쪽방의 집합이 같다면
                    {
                        if (rand() % 2) //50프로 확률로
                        {
                            under_flag = 1; //under_flag 가 1이라는 것은 해당 집한에 수직경로가 최소한 1개는 있다는 의미이다.
                            under[i] = maze[i]; //under[i]을 maze[i]와 같은 집합으로 둔다.
                        }
                        else {
                            set_number+=1; //그렇지 않다면 set_number를 1 추가하여
                            under[i] = set_number; //under[i] 에 set_number를 넣어 아랫방에 새로운 집합을 가지게 한다.
                        }}
                    else {
                        if (under_flag == 0) //인접한 왼쪽방과 오른쪽 방이 다르다면 under_flag가 0일 때
                        {
                            under[i - 1] = maze[i - 1]; //집함당 최소한 1개의 수직경로를 생성하기 위해 이전 집합의 마지막 방에 수직경로를 생성한다. 
                        }
                        under_flag = 0; //undfer_flag를 0으로 초기화 하여 다른 집합의 수직경로 생성여부를 판별한다.
                        if (rand() % 2) //50 프로 확률로
                        {
                            under_flag = 1; //under_flag를 1로 두어 수직경로가 생성되었음을 알림
                            under[i] = maze[i]; //under[i]을 maze[i]와 같은 집합으로 둔다.
                        }
                        else {
                            set_number+=1; //그렇지 않다면 set_number를 1 추가하여
                            under[i] = set_number;//under[i] 에 set_number를 넣어 아랫방에 새로운 집합을 가지게 한다.
                        }}

                }
                else { //index가 1, 즉 한행에서 첫번째 방일때
                    if(maze[i]==maze[i+1]) //인접한 왼쪽방과 오른쪽방의 집합이 같다면
                    {if (rand() % 2)//50 프로 확률로
                    {
						under_flag = 1; //under_flag를 1로 두어 수직경로가 생성되었음을 알림
						under[i] = maze[i]; //under[i]을 maze[i]와 같은 집합으로 둔다.
                    }
                    else { //그렇지 않다면 
                        set_number+=1; //그렇지 않다면 set_number를 1 추가하여
                        under[i] = set_number;//under[i] 에 set_number를 넣어 아랫방에 새로운 집합을 가지게 한다.
                        under_flag=0; //수직경로는 아직 생성안되었다.
                    }}
                    else { //첫방과 두번째 방의 집합이 다르기 때문에 무조건 첫방에서 수직경로 생성
                        under[i]=maze[i];//under[i]을 maze[i]와 같은 집합으로 둔다.
                        under_flag=0; //다른 집합의 수직경로 판별여부를 위해 다시 0으로 초기화
                    }
                }
                if (i == WIDTH - 1)  //한 행의 가장 마지막 방에 도달했다면 이 방에 해당하는 집합에 수직경로가 없을 때 다음 방과 비교를 통해 값을 넣어 줄 수 없다. 
                {
                    if (under_flag == 0) //마지막 방이 아직 수직경로가 없다면
                    {
                        under[i] = maze[i]; //수직경로를 생성한다.
                    }
                }
                
        }
        if (j < HEIGHT - 1) //가장 마지막 줄은 수직경로가 아닌 테두리를 만들어야 하기 때문에 행 기준 HEIGHT-1개의 under 벽을 만듬
        {
            for (int i = 0; i < WIDTH; i++) //under벽은 WIDTH개 필요
            {
                if (under[i] == maze[i]) //만약 under 과 maze 배열 이 같다면 즉 위 방와 아래 방의 집합이 같다면
                {
                    printf("+ "); //스페이스 바를 출력하여 공간을 비운다
                    fprintf(fp,"+ ");
                }
                    
                else {printf("+-"); //아니라면 under 벽을 그린다.
                    fprintf(fp,"+-");
                }
                maze[i] = under[i]; //다음 행의 집합을 maze 배열에 다시 저장한다.
            }
            printf("+\n"); //반복문 후 가장 마지막에는 테두리를 그린다.
            fprintf(fp,"+\n");
        }

        
    }
    
    
    
    for (int i = 0; i < WIDTH; i++) //가장 밑 테두리를 그려준다.
    {
        printf("+-");
        fprintf(fp,"+-");
    }
   
    
    printf("+"); //가장 오른쪽 아래 테두리 끝을 그린다.
    fprintf(fp,"+");
    
    free(maze); //동적 메모리 할당 받은 배열들을 다시 free 시켜준다. 
    free(under);
    free(side);
    fclose(fp);
    return 0;
    
    
}

