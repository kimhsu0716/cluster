//main.c

#include <stdio.h>
#include <stdlib.h>
#include "queue.h" //queue.h 헤더파일
#define MAX_SIZE 100

int n, m;

int isInside(int x, int y){
    return (x >= 0 && x < m && y >= 0 && y < n); //매개변수로 입력된 좌표가 미로 내부에 있는지 검사하는 함수
}

int main(){
    while(1){
        char maze[MAX_SIZE][MAX_SIZE]; //미로를 입력받을 2차원 배열
        int visited[MAX_SIZE][MAX_SIZE] = {0, }; //해당 좌표를 방문했는지 기록하는 2차원 배열

        int goal_x = -1, goal_y = -1; //도착지점의 좌표

        elem first = {-1, -1, 0}, item = {0, }; //first는 시작지점의 좌표, item은 while문 안에서 사용하기 위해 선언
        Queue *queue = (Queue *)malloc(sizeof(Queue)); //큐에 동적 메모리 할당
        init(queue); //큐 초기화

        printf("미로의 크기를 입력하세요 (종료하려면 0 0 을 입력하세요):\n");
        scanf("%d %d", &n, &m);
        if(n == 0) break;

        printf("미로의 모양을 입력하세요: (1: 벽, 0: 빈칸, S: 시작지점, G: 도착지점)\n");

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                scanf(" %c", &maze[i][j]);
                if(maze[i][j] == 'S'){
                    first.x = j;
                    first.y = i;
                }
                if(maze[i][j] == 'G'){
                    goal_x = j;
                    goal_y = i;
                }
            }
        }

        //미로 모양 출력
        printf("\n□");
        for(int i = 0; i < m; i++) printf("□");
        printf("□\n");
        for(int i = 0; i < n; i++){
            printf("□");
            for(int j = 0; j < m; j++){
                if(maze[i][j] == 'S') printf("●");
                else if(maze[i][j] == 'G') printf("★");
                else if(maze[i][j] == '0') printf("  ");
                else printf("■");
            }
            printf("□\n");
        }
        for(int i = 0; i <= m; i++) printf("□");
        printf("□\n");

        //잘못된 입력이 있으면 오류메시지 출력 후 재시작
        if(first.x == -1){
            printf("시작지점이 없습니다!\n");
            continue;
        }
        if(goal_x == -1){
            printf("도착지점이 없습니다!\n");
            continue;
        }

        push(queue, first); //큐에 시작지점의 좌표를 삽입

        while(1){
            if(empty(queue)){ //큐가 비어있으면 올바른 미로가 아님
                printf("탈출 불가능한 미로!\n");
                break;
            }

            item = pop(queue); //큐에서 요소를 하나 뽑아 item에 저장

            if(item.x == goal_x && item.y == goal_y) break; //item의 좌표가 도착지점이라면 반복문 종료
            int nx, ny; //새로 큐에 집어넣을 좌표
            elem newItem = item; //새로 큐에 집어넣을 newItem을 만들고 item의 값을 그대로 저장

            newItem.depth++; //newItem의 depth를 1 증가시킴

            //오른쪽 칸이 벽이 아니고 미로 내부에 있으며 방문한 적이 없으면 큐에 집어넣음
            nx = item.x + 1;
            ny = item.y;
            if(isInside(nx, ny) && maze[ny][nx] != '1' && visited[ny][nx] == 0){
                visited[ny][nx] = 1;
                newItem.x = nx;
                newItem.y = ny;
                newItem.backtrack[item.depth] = 'R'; //최단경로 역추적을 위해 문자열의 마지막에 'R'을 덧붙임
                push(queue, newItem);
            }

            //왼쪽 칸이 벽이 아니고 미로 내부에 있으며 방문한 적이 없으면 큐에 집어넣음
            nx = item.x - 1;
            ny = item.y;
            if(isInside(nx, ny) && maze[ny][nx] != '1' && visited[ny][nx] == 0){
                visited[ny][nx] = 1;
                newItem.x = nx;
                newItem.y = ny;
                newItem.backtrack[item.depth] = 'L'; //최단경로 역추적을 위해 문자열의 마지막에 'L'을 덧붙임
                push(queue, newItem);
            }

            //아래쪽 칸이 벽이 아니고 미로 내부에 있으며 방문한 적이 없으면 큐에 집어넣음
            nx = item.x;
            ny = item.y + 1;
            if(isInside(nx, ny) && maze[ny][nx] != '1' && visited[ny][nx] == 0){
                visited[ny][nx] = 1;
                newItem.x = nx;
                newItem.y = ny;
                newItem.backtrack[item.depth] = 'D'; //최단경로 역추적을 위해 문자열의 마지막에 'D'를 덧붙임
                push(queue, newItem);
            }

            //위쪽 칸이 벽이 아니고 미로 내부에 있으며 방문한 적이 없으면 큐에 집어넣음
            nx = item.x;
            ny = item.y - 1;
            if(isInside(nx, ny) && maze[ny][nx] != '1' && visited[ny][nx] == 0){
                visited[ny][nx] = 1;
                newItem.x = nx;
                newItem.y = ny;
                newItem.backtrack[item.depth] = 'U'; //최단경로 역추적을 위해 문자열의 마지막에 'U'를 덧붙임
                push(queue, newItem);
            }
        }

        while(!empty(queue)) pop(queue); //큐가 빌 때까지 pop을 하여 남은 요소를 제거
        free(queue); //동적 메모리 해제

        printf("\n최단 경로의 길이: %d\n", item.depth); //최단 경로의 길이 출력
        printf("\n이동 경로:\n%s\n", item.backtrack); //이동 경로 출력
        printf("=================================\n\n");
    }
    printf("프로그램을 종료합니다...\n");
    return 0;
}
