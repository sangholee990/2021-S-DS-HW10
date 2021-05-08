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
	
	printf("---------[2018038016] 이상호-----------\n");

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
	Node* lead = head->left; //루트노드 초기화 
	Node* pre=NULL; //바꿀 노드 위치 저장 
	Node* temp=NULL; //임시저장 포인터
	 

	
	if(lead==NULL){ //트리에 노드가 존재하지 않으면
	    printf("이 노드는 트리에 없습니다.\n");
	    return 0;
	}
	
	while(lead) //트리에 노드가 하나 이상일 때 
	{
		if(lead->key == key) //키값을 발견하면 반복문 탈출 
		{
			break;
		}
		
		else if((lead->key) > key) //노드의 키값보다 작은 경우 
		{
			if(lead->left != NULL) //리드노드의 다음 위치가 비어있지 않으면 
			{
				pre=lead; //리드의 이전위치 저장 
				lead=lead->left; // 리드를 이동 
			 } 
			 
			else // 리드노드의 다음위치가 비어있다면
			{
				printf("이 노드는 트리에 존재하지 않습니다.\n");
				return 0; 
			 } 
		}
		
		else if((lead->key) < key) //노드의 키값보다 큰 경우
		{
			if(lead->right != NULL) //리드의 다음 위치가 널이 아닌경우
			{
				pre=lead; //리드의 이전위치 저장
				lead=lead->right; //리드 이동 
			 } 
			
			else //리드의 다음위치가 비어있다면
			{
				printf("이 노드는 트리에 없습니다.\n");
				return 0; 
			 } 
		 } 
	}
	
	if((lead->left == NULL) && (lead->right == NULL)) //리프노드인 경우 
	{
		if(pre==NULL) //노드가 유일할때
		{
			free(lead);
			head->left=NULL; 
			return 0;
		 } 
		 
		if(lead->key > pre->key) //리프노드중에 부모노드의 오른쪽에 위치 했던 노드
		{
			free(lead);
			pre->right=NULL; 
		 }
		
		else // 왼쪽에 위치하던 노드  
		{
			free(lead);
			pre->left=NULL;
		}
	}
	
	else //리프노드가 아닌경우
	{
		 //자식노드가 한개인경우 
		 if(((lead->left != NULL) && (lead->right == NULL)) || ((lead->left == NULL) && (lead->right != NULL)))
		 {
		 	if(head->left == lead) //루트노드이 경우의 수 
		 	{
		 		if(lead->left != NULL) //왼쪽 자식 노드를 갖는 경우
				 {
				 	head->left = lead->left;
				 	free(lead); 
				  }
				
				else // 오른쪽 자식 노드를 갖는 경우   
				{
					head->left = lead->right;
					free(lead);
				}
			 }
			 
			 else //루트노드가 아닌경우 
			 {
			    if(lead->key > pre->key) //리드의 키가 이전키보다 큰경우 
				{
					if(lead->left != NULL) //왼쪽 자식 노드를 가질 때 
					{
						pre->right=lead->left;
						free(lead); 
					}
					
					else //오른쪽으로 가지는 경우
					{
						pre->right=lead->right;
						free(lead); 
					 } 
				} 
				 
				 else // 리드의 키가 이전 키보다 작을 경우
				{
				 	if(lead->left != NULL) //왼쪽 자식 노드를 한개 가지면
					{
						pre->left=lead->left;
						free(lead); 
					}
					
					else //오른쪽 자식노드를 한개 가지면
					{
						pre->left=lead->right;
						free(lead); 
					} 
				 	
				} 
			 }
		 }
		 
		 else //자식노드로 두개를 가질 경우의 수 
		 {
		 	 temp=lead;
			 pre=lead;
			 lead=lead->left; //왼쪽 노드중 제일 큰노드를 위로 올리는 방식
			 
			 if(!(lead->right)) //왼쪽 노드가 가장 큰 노드인 경우의 수
			 {
			 	if(lead->left == NULL) //왼쪽에 자식노드가 없으면
				 {
				 	pre->key=lead->key; 
					pre->left=NULL;
					free(lead); 
				 }
				 else //왼쪽에 자식노드가 있는 경우의 수 
				 {
				 	pre->key=lead->key;
					pre->left=lead->left;
					free(lead); 
				 }
				 
				 return 0;
			  } 
			  
			  while(lead->right) //오른쪽에 노드가 남았을때 끝까지
			  {
			  	   pre=lead; //이전노드 남기기 
			  	   lead=lead->right; //오른쪽 노드로 한칸씩 이동 
			   } 
			   
			  temp->key=lead->key;
			  
			  if(lead->left != NULL) //오른쪽 끝노드가 왼쪽 자식노드를 갖는 경우의 수
			  {
			  	   pre->right=lead->left;
				   free(lead);  
			  }
			  else // 왼쪽 자식 노드를 갖지 않으면 
			  {
			  	   pre->right=NULL;
			       free(lead); 
			  }
		 }
	 } 
	 	
		
	 return 0; 
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
