//queue.h

typedef struct elem {
    int x, y; //x, y좌표
    int depth; //시작 지점으로부터의 거리
    char backtrack[10001]; //최단경로 역추적을 위한 문자열 배열
} elem;

//노드 구조체 선언
typedef struct Node {
    elem item;
    struct Node *next;
} Node;

//큐 구조체 선언
typedef struct Queue {
    Node *first, *last;
    int size;
} Queue;

void init(Queue *q);
void push(Queue *q, elem item);
elem pop(Queue *q);
elem front(Queue *q);
int size(Queue *q);
int empty(Queue *q);
