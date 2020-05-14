/*
 * cirdou.c
 *
 *  Created on: 2020. 5. 14.
 *      Author: user
 */

/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("sunyilin 2016039102 software");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;

	listNode* prev = NULL;
	while (p != h) {
		prev = p;
		p = p->rlink;

		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == NULL)
	{
		h->rlink = node;
		node->rlink=h;
		return 1;
	}

	listNode* n = h->rlink;
	while (n->rlink != h) {
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;//마지막 노드하고 첫번째 노드 연결
	node->rlink = h;
	h->llink = node;
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->rlink;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if (n->rlink == h) {
		h->rlink = h;
		free(n);

	return 1;
	}

	/* 마지막 노드까지 이동 */
	while (n->rlink != h) {
		trail = n;
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = h;
	h->llink = trail; //마지막 노드하고 첫번째 노드 연결
	free(n);

	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if (h->rlink==h)
	{
		h->rlink = node;
		h->llink = node;
		node->llink = h;
		node->rlink = h;

		return 1;
	}
	node->rlink = h->rlink;
	h->rlink->llink = node;
	h->rlink = node;
	node->llink = h;

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 1;
	}
	listNode* n = h->rlink;
	h->rlink = n->rlink;
	n->rlink->llink = h;

	free(n);

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	if (h->rlink == h) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode* head = h->rlink;
	listNode* n = h->rlink;
	listNode* trail = NULL;
	listNode* middle = NULL;

	while (n != h) {
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}
	h->rlink=middle;//이전의 첫번째 노드는 이제 마지막 노드가 이다
	h->llink=head;
	head->rlink=h;

	return 0;
//	listNode* n = h->rlink;
//	while (n->rlink != h) {
//		n = n->rlink;
//	}
//	listNode* begin = h->rlink;
//	listNode* end = n;
//	listNode* swap = (listNode*)malloc(sizeof(listNode));
//	swap->llink = NULL;
//	swap->rlink = NULL;
//	while (begin != end && begin->llink != end) {//첫 노드하고 마지막 노드가 교환한다.
//		swap->key = begin->key;
//		begin->key = end->key;
//		end->key = swap->key;
//		begin = begin->rlink;
//		end = end->llink;
//		}
//		free(swap);
//		return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)
	{
		h->rlink = node;
		node->llink = h;
		h->llink=node;
		node->rlink=h;
		return 0;
	}

	listNode* n = h->rlink;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != h) {
		if (n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->rlink) {
				insertFirst(h, key);
			}
			else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink=node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if (h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while (n != h) {
		if (n->key == key) {
			if (n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			}
			else if (n->rlink == h) { /* 마지막 노드인 경우 */
				deleteLast(h);
			}
			else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


