/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node; //트리구성노드  

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int is_Empty(); //비었는지 검사하는 함수 
int is_Full(); // 꽉찼는지 검사하는 함수 



int main()
{
	char command;
	int key;
	Node* head = NULL;
	
	printf("[---------[2018038016] 이상호-----------]\n");

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
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr) //인오더 순회 함수 
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node) //재귀 호출 사용하지 않는 인오더 
{
	if (node ==NULL){ //tree에 노드가 없을 경우 
		 printf("트리에 노드가 없습니다. \n");
	}
	
	while(1) //무한 루프 
	{
		for(;node;node=node->left) // 제일 왼쪽 노드까지 루프 
		   push(node); //스택에 하나씩 삽입
		
		node = pop(); //스택에서 하나 팝한다 
		
		if(!node) // 스택이 공백일경우
		    break; //무한 루프 탈출
			
		printf("[%d]",node->key); // 팝한노드 하나씩 출력
		 	 
		node=node->right; //노드 의 오른쪽으로 이동   
	}
	
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //레벨 순서 순회 
{
	
	  int i; 
	  front= -1; 
	  rear = -1; //  초기값 설정 
	  
	  for(i=0;i<MAX_QUEUE_SIZE-1;i++)
	   {
	  	  queue[i] = NULL;  
	   }
	  
	  if(ptr==NULL) //공백트리면 
	      return;// 함수 종료 
	  
	  enQueue(ptr); //큐에 노드하나 삽입
	  
	  while(1)
	  {
	  	 ptr = deQueue(); //프론트에 값 삭제
		   
		 if(ptr) // 삭제할 값이 남아있다면 
		{
		 	 printf("[%d]",ptr->key); // 디큐한 노드 출력 
		 	 if(ptr->left) // 왼쪽 자식 노드가 존재할시
			     enQueue(ptr->left);//왼쪽 자식 노드를 큐에 넣는다
			 if(ptr->right) // 오른쪽 자식 노드가 존재할 시	 
			     enQueue(ptr->right); //오른쪽 자식 노드를 큐에 넣는다 
	  	}   
	    
		else break;  // 삭제할 값이 없으면 탈출 
      } 	     
}


int insert(Node* head, int key)
{
	//뉴노드 동적할당 
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	//리프노드 초기화 
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;
	Node* parentNode = NULL;
	
	while(ptr != NULL) {

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


int deleteNode(Node* head, int key)
{
	Node* temp;
	Node* parent;
	Node* child;
	Node* sub;
	Node* psub;
	
	temp = head->left; 
	parent=NULL; //부모노드 초기화
	
	//키값 갖는 노드 탐색	
	while((temp != NULL) && (temp->key != key))
	{
		parent=temp;
		if(key < parent->key) //입력한 키가 더작으면 
		   temp=parent->left; // 왼쪽으로 이동한다 
		
		else // 입력한 키가 더크다면 오른쪽으로 이동한다
		   temp=parent->right;   
	}
	
	if(temp==NULL) //키가 트리안에 없는 경우의 수
	{
		 printf("키가 노드에 존재 하지 않습니다.\n");
		 return 0;
	 } 
	 
	if(temp->left == NULL && temp->right == NULL) //리프노드일 경우 
	{
	     if(parent != NULL) //부모노드가 NULL이 아닐때 
	     {
	         if(parent->left == temp) 
		        parent->left =NULL ;
		     else 
			    parent->right = NULL;		  
		 }
		 else //부모노드가 NULL 일 경우 루트노드 이므로
		     head = NULL; 
	 } 
	
	else if(temp->left==NULL || temp->right==NULL) //자식이 하나인 경우
	{
		if(temp->left != NULL) //temp왼쪽 노드를 가질경우
		    child = temp->left;
		else
		    child = temp->right;
		
		if(parent != NULL) //부모노드가 NULL이 아닐경우
		{
			if(temp==parent->left)
			   parent->left=child;
			else
			   parent->left=child;    
		}
		
		else
		   head->left=child;		 
	 }
	 
	 else //자식이 두개인 경우
	 {
	 	psub=temp;
	 	sub=temp->right;
	 	while(sub->left != NULL)
	 	{
	 		psub=sub;
	 		sub=sub->right;
		 }
		if(psub->left==sub) //삭제할 노드의 부모와 노드이 자식과 연결 
		{
			psub->left=sub->right;
		}
		else
		{
			psub->right=sub->right;
		 } 
		
		temp->key=sub->key;
		temp=sub; 
	  } 
	  free(temp);
}


void freeNode(Node* ptr)
{
	if(ptr) { //포스트오더 방식으로 트리의 노드 동적 할당 해제 
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //트리에 노드가 없다면 
	{
		free(head);
		return 1;
	}

	Node* p = head->left; //루트노드 위치 저장 

	freeNode(p); // 노드 할당 해제 

	free(head); //헤드노드 메모리 해제 
	return 1;
}



Node* pop()
{
	if(top == -1) //스택이 비었을 경우 
	   return 0; // 함수 종료
	else //스택이 비어있지 않다면
	  return stack[top--]; //pop    
}

void push(Node* aNode)
{
	if(top == MAX_STACK_SIZE-1) //스택이 가득 차있을 경우
	   return ; //함수 종료
	else 
	   stack[++top]=aNode; //탑 증가후 값 저장 
}



Node* deQueue()
{
	 if(is_Empty()==1) //큐가 비어있을 경우
	     return NULL; 
	     
	 front=(front+1)%MAX_QUEUE_SIZE; //원형큐 인덱스 증가
	 return queue[front]; // 제거노드 리턴    
}

void enQueue(Node* aNode)
{
	rear=(rear+1)%MAX_QUEUE_SIZE; //원형큐 꼬리 인덱스 증가
	
	if(is_Full()==1) //가득차있다면
	   return; //함수종료
	
	queue[rear]=aNode; //가득 차있지 않으면 꼬리에 노드 삽입    
}

int is_Empty() 
{
	if(front == rear) //front와 rear가 같으면 원소가 비어있는 것이다
	{
		return 1; //원소가 비어있을 때는 1을 리턴한다
	}
	return 0;
}

int is_Full() 
{
	if(front == rear) //full 상태인경우 
	{
		if(rear == 0) 
		{
			rear = MAX_QUEUE_SIZE-1;
		}
		else
		{
			rear = rear-1;
		}
		return 1; //큐가 가득찼다면 함수종료 
	}
	return 0;
}
