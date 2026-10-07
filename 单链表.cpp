#include<stdio.h>
#include<stdlib.h>  //包含malloc函数
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,  *LinkList;   //typedef的重命名
LinkList List_Tailnsert() {  //尾插法
	LinkList L = (LNode*)malloc(sizeof(LNode));//创建头结点
	if (L == NULL) {
		printf("内存分配失败\n");
		return NULL;
	}
		
	L->next = NULL;
	LNode* s,*r;//r是尾指针
	r = L;
	int x;
	scanf_s("%d", &x);
	while (x != 100) {
		s = (LNode*)malloc(sizeof(LNode));//申请新结点
		s->data = x;
		s->next = NULL;
		r->next = s;
		r = s;//尾指针后移
		scanf_s("%d", &x);
	}
	return L;
}
bool ListInsert(LinkList& L, int i, int e) {  //按位插入
	if (i < 1)   //检查i
		return false;
	LNode* p = L;  //找到i-1的指针
	int j=0;    //同类型允许与i-1比较
	while(p != NULL && j < i - 1) {
		p = p->next;
		j++;  //与p指向的结点下标一致
	}
	if (p ==NULL) //越界保护
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));//创建一个新结点
	if (s == NULL)  //内存分配失败保护
		return false;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool ListDelete(LinkList& L, int i, int& e) {  //按位删除
	LNode* p = L,*q;  //p最后指向第i-1结点，q指向第i结点
	int j = 0;
	if (i < 1)
		return false;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL&&p->next==NULL)//p既不能指向NULL也不能指向最后一个结点
		return false;
	e = p->next->data;//返回第i结点的值
	q = p->next;
	p->next = q->next;
	free(q);//空间释放
	return true;
}
int LocateElem(LinkList L, int e) { //按值查找
	LNode* p = L->next;//p要指向真实的结点
	int j = 1;
	while (p != NULL ) {
		if (p->data == e) {
			return j;//返回位置
		}
		p = p->next;
		j++;
	}
	
	return 0;//整个链表都没有这个值返回0
}
void PrintfList(LinkList L) { //打印链表函数
	if (L == NULL) {
		printf("链表不存在\n");
		return;
	}
	LNode* p = L->next;
	printf("当前链表:");
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->next;
	}
	printf("NULL\n");
}

int main() {
	
	printf("---1.开始创建链表（输入100时停止创建）---\n");
	LinkList L = List_Tailnsert();
	PrintfList(L);
	printf("---2.测试插入操作---\n");
	if (ListInsert(L, 2, 999)) {
		printf("插入成功，在第二个位置插入999\n");
	}
	else {
		printf("插入失败\n");
	}
	PrintfList(L);
	printf("---3.测试删除操作---\n");
	int deletedVal;
	if (ListDelete(L, 2,deletedVal)) {
		printf("删除成功，删除的值为%d\n", deletedVal);
	}
	else {
		printf("删除失败\n");
	}
	PrintfList(L);
	printf("---4.按值查找测试---\n");
	int target = 2;
	int pos = LocateElem(L, target);
	if (pos != 0) {
		printf("查找成功，值为 %d 的结点在第 %d 个位置\n",target,pos);
	}
	else {
		printf("查找失败，链表中没有值为  %d 的结点\n", target);
	}
	target = 999; //测一个不存在的值
	pos = LocateElem(L, target);
	if (pos == 0) {
		printf("测试成功，值 %d 不在该链表中\n", target);
	}
	return 0;

}

