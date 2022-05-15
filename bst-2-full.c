#include <stdio.h>
#include <stdlib.h>

typedef struct node { //node구조체 생성
	int key; //int형 key 변수
	struct node *left;  //노드에 연결되어있는 왼쪽 노드를 가르킬 포인터
	struct node *right; //노드에 연결되어있는 오른쪽 노드를 가르킬 포인터
} Node; //Node로 호출가능

/* for stack */
#define MAX_STACK_SIZE		20 //stack의 MAX사이즈는 20
Node* stack[MAX_STACK_SIZE]; //노드형 포인터 배열 stack 생성
int top = -1; //int형 변수 top -1로 초기화 

Node* pop(); //노드포인터형 pop 함수
void push(Node* aNode); //void형 push함수 노드포인터형 aNode를 인자로 받는다

/* for queue */
#define MAX_QUEUE_SIZE		20 //Queue의 MAX사이즈는 20
Node* queue[MAX_QUEUE_SIZE]; //노드형 포인터배열 queue 생성
int front = -1; //int형 front 변수 생성후 -1로 초기화
int rear = -1; //int형 rear변수 생성후 -1로 초기화

Node* deQueue(); //Node포인터형 deQueue함수 생성
void enQueue(Node* aNode); //Node포인터형 enQueue함수 생성 Node포인터형 aNode를 인자로 받아온다.


int initializeBST(Node** h); //int형 initializeBST함수 Node이중포인터형 h를 인자로 받아온다.

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

void printStack(); //void형 printStack함수

int main()
{
	char command; //command받아올 char형 변수
	int key; //int형 key 변수
	Node* head = NULL; //head노드 생성후 NULL로 초기화
	printf("[----- [Your Name] [Student ID] -----]");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command입력받기

		switch(command) {
		case 'z': case 'Z': //z일때 initializeBST함수호출후 head주소 인자로 넣어준다
			initializeBST(&head);
			break;
		case 'q': case 'Q': //q일때 freeBST함수호출후 head 인자로 넣어준다
			freeBST(head); 
			break;
		case 'i': case 'I': //i일때 key값 받고 insert함수호출후 head, key 인자로 넣어준다
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': //d일때 key값 받고 deleteNode함수호출후 head, key 인자로 넣어준다
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': //r일때 recursiveInorder함수호출후 head->left 인자로 넣어준다
			recursiveInorder(head->left);
			break;
		case 't': case 'T': //t일때 iterativeInorder함수호출후 head->left 인자로 넣어준다
			iterativeInorder(head->left);
			break;

		case 'l': case 'L': //l일때 levelOrder함수호출후 head->left 인자로 넣어준다
			levelOrder(head->left);
			break;

		case 'p': case 'P': //p일때 printStack함수호출
			printStack();
			break;

		default: //위 case랑 다른 글자가 들어오면 오류 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q일때 종료

	return 1;
}

int initializeBST(Node** h) { //Node의 주소를 잡는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //head노드의 주소를 malloc으로 잡고
	(*h)->left = NULL;	/* root */ //노드의 각 변수들을 초기화해주는 모습
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1; // top을 -1로 초기화

	front = rear = -1; //front rear도 -1로 초기화

	return 1;
}



void recursiveInorder(Node* ptr) //recursive방식으로 찾는방법
{
	if(ptr) { //ptr이 true라면
		recursiveInorder(ptr->left); //recursiveInorder함수호출 ptr->left인자로 넣어주기
		printf(" [%d] ", ptr->key); //ptr->key값 출력
		recursiveInorder(ptr->right); //recursiveInorder함수호출후 ptr->right인자로 넣어주기
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //iterative방식으로 찾는방법
{
	for(;;)
	{
		for(; node; node = node->left) //node를 왼쪽으로 이동시키면서
			push(node); //push함수 호출후 node인자로 넣어주기
		node = pop(); //node에 pop()호출한 값 넣어주기

		if(!node) break; //node가 아닐경우 중지
		printf(" [%d] ", node->key); //node->key출력

		node = node->right; //노드 오른쪽으로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //level 방식으로 찾는 방법
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); //enQueue함수 호출후 ptr인자로 넣어주기

	for(;;)
	{
		ptr = deQueue(); //deQueue함수 호출후 ptr에 넣어주기
		if(ptr) { //만약 ptr이 true라면
			printf(" [%d] ", ptr->key); //ptr->key출력

			if(ptr->left) //만약 ptr->left가 true라면
				enQueue(ptr->left); //ptr->left를 enQueue함수에 넣어주기
			if(ptr->right) //만약 ptr->right가 true라면
				enQueue(ptr->right); //ptr->right를 enQueue함수에 넣어주기
		}
		else //아니면 정지
			break;

	}

}


int insert(Node* head, int key) //구조체에 key값 넣어주는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //key값 넣을 newNode생성 malloc으로 주소잡아줌
	newNode->key = key; //key값 newNode의 key에 넣어주기
	newNode->left = NULL; //left의 값을 NULL로 초기화
	newNode->right = NULL; //right의 값을 NULL로 초기화

	if (head->left == NULL) { //만약 head의 left가 NULL이라면
		head->left = newNode; //head의 left에 newNode넣어주기
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //Node포인터형 ptr에 head의 left값을 넣어준다

	Node* parentNode = NULL; //부모노드 생성후 NULL로 초기화
	while(ptr != NULL) { //ptr이 NULL이 아니라면

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) 
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) 
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) //key값을 가진 노드를 삭제하는 함수
{
	if (head == NULL) { //Head가 NULL이라면
		printf("\n Nothing to delete!!\n"); //삭제할것이 ㅇ벗다는 오류
		return -1;
	}

	if (head->left == NULL) { //head의 left가 NULL이라면
		printf("\n Nothing to delete!!\n"); //오류 출력
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //Node의 root를 head의 left로 넣어준다.



	Node* parent = NULL; //Node형 포인터 parent를 NULL로 초기화
	Node* ptr = root; //Node형 포인터 ptr을 root로 초기화

	while((ptr != NULL)&&(ptr->key != key)) { //ptr이 NULL이 아니고 ptr의 key가  key값이 아닐떄
		if(ptr->key != key) { //만약 ptr의 key가 key값이라면 

			parent = ptr;	/* save the parent */ //parent에 ptr을 넣어준다

			if(ptr->key > key) //ptr의 key값이 key값보다 크다면
				ptr = ptr->left; //노드를 왼쪽으로 이동
			else 
				ptr = ptr->right; //노드를 오른쪽으로 이동
 		}
	}

	/* there is no node for the key */ 
	if(ptr == NULL) //만약 ptr이 NULL이라면
	{
		printf("No node for key [%d]\n ", key); //key값인 노드가 없다는 오류출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)  //만약 ptr의 left가 NULL이고 ptr의 left가 NULL이라면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) //부모의 left가 ptr이라면
				parent->left = NULL; //NULL로 초기화
			else
				parent->right = NULL; //오른쪽이라면 오른쪽을 초기화
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; //head의 left를 초기화

		}

		free(ptr); //ptr을 free
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //만약 ptr의 left가 NULL이거나 ptr의 left가 NULL이라면
	{
		Node* child; //Node포인터형의 child를 선언
		if (ptr->left != NULL) //만약 ptr의 left가 NULL이 아니라면
			child = ptr->left; //child에 ptr의 left 넣어줌 
		else
			child = ptr->right; //아닐경우 ptr의 right를 child에 넣어준다.

		if(parent != NULL) //만약 parent가 NULL이 아닐경우
		{
			if(parent->left == ptr) //parent의 left가 ptr이라면
				parent->left = child; //parent의 left에 child를 넣어준다.
			else //다른경우
				parent->right = child; //parent의 right에 child를 넣어준다
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr); //ptr을 초기화해줌
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr) //노드를초기화시켜주는 함수
{
	if(ptr) { //만약ptr이 true라면
		freeNode(ptr->left); //freeNode에 ptr->left넣어주기
		freeNode(ptr->right); //freeNode에 ptr->right넣어주기
		free(ptr); //남은 ptr초기화하기
	}
}

int freeBST(Node* head) //노드의 해드를 초기화해주는 함수
{

	if(head->left == head) //해드의 left가 head라면
	{
		free(head); //head를 초기화
		return 1;
	}

	Node* p = head->left; //p 노드포인터의 head의 left를 넣어준다.

	freeNode(p); //p를 freeNode함수에 넣어준다 

	free(head); //head를 초기화시켜준다
	return 1;
}



Node* pop() //pop하는 함수
{
	if (top < 0) return NULL; //만약 top이 0보다 작다면 NULL를 return
	return stack[top--]; //아니면 stack의 top을 return하고 top을 작게만듬
}

void push(Node* aNode) //push하는 함수
{
	stack[++top] = aNode; //stack의 top을 증가신킨곤에 aNode를 넣는다.
}


void printStack() //STack을 출력하는 함수
{
	int i = 0; //int형 변수를 0으로 초기화
	printf("--- stack ---\n");
	while(i <= top) //만약 i가 top보다 작거나 같을때까지 실행
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); //stack[i]->key가 i번째에 있다는거 출력
		i++;
	}
}


Node* deQueue() //deQueue하는 함수
{
	if (front == rear) { //front가 rear라면 오류출력후 정지
		printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front에 front +1 를 멕스값으로 나누거 나머지를 넣어줌
	return queue[front]; //queue[front]를 return

}

void enQueue(Node* aNode) //deQueue하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear에 front +1 를 멕스값으로 나누거 나머지를 넣어줌
	if (front == rear) { //front가 rear라면 오류출력후 정지
		printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //queue[rear]에 aNode를 넣어줌
}





