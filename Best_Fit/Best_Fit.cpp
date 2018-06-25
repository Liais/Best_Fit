/**********************************
		操作系统代码任务：最佳分配算法
		GitHub：Liais
		完成时间：2018-6-25
		编译环境：VS2010
***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define  S 1000
typedef struct node{
	int id;
	int start;
	int size;
	int flag;//分配标志，已分配1,未分配0
	struct node * next;
	struct node * prior;
}node,*pnode;

int main()
{
	pnode head = (pnode)malloc(sizeof(node));
	head->id = 0;
	head->size = S;
	head->start = 0;
	head->flag = 0;
	head->next = NULL;
	head->prior = NULL;
	head->id = 0;//未分配
	pnode tail = head;

	int size;
	int id = 1;
	printf("假设内存总共有1000M,现在用程序模拟使用最佳适应算法对内存进行动态分区分配\n");
	printf("a:分配内存,b:回收内存,c:显示当前作业内存分配情况,d:退出程序\n");
	while(1)
	{
		int taskid = 1;
		pnode p,index;
		char choice;
		int mindif = S;
		printf("请输入操作:");
		cin>>choice;
		switch(choice)
		{
		case 'a':
			printf("输入要分配内存的大小:");
			cin>>size;
			if(size == 0)//否则0也会分配
				break;
			//分配内存
			//pnode index;//最佳分配的块的指针
			p = head;
			index = NULL;
			mindif = S;//最小差
			
			while(p!=NULL)
			{
				//system("pause");
				if(p->size>=size&&(p->size-size)<mindif&&p->flag==0)
				{
					index = p;
					mindif = p->size - size;
				}
				p = p->next;
			}
			//printf("mindif:%d\n",mindif);
			if(index==NULL)//分配失败
			{
				printf("不存在足以分配的数据段，分配失败\n\n");
				break;
			}
			else{
				//printf("%d\t%d\t%d\t%d\n",index->id,index->start,index->size,index->flag);
				index->size -=mindif;
				index->id = id++;
				index->flag = 1;//已分配
				//如果目标节点是头结点，分出未分配部分作为单独节点
				if(index->prior == NULL)
				{
					if(mindif != 0){
						//printf("如果目标节点是头结点，分出未分配部分作为单独节点\n");
						pnode n = (pnode)malloc(sizeof(node));
						n->id = 0;
						n->flag = 0;
						n->next = index->next;
						n->prior = index;
						n->size = mindif;
						n->start = index->start + index->size;

						if(index->next!=NULL){
							index->next->prior = n;
						}
							
						index->next = n;
						//printf("头结点已分配\n");
					}
				}
				//要分配的是尾节点
				else if(index->next == NULL)
				{
					if(mindif != 0){
						//printf("要分配的是尾节点\n");
						pnode n = (pnode)malloc(sizeof(node));
						n->flag = 0;
						n->id = 0;
						n->next = NULL;
						n->prior = index;
						n->size = mindif;
						n->start = index->start + index->size;

						index->next = n;
					}
					else{
						//正好分配完的情况，不用再创建新的节点，直接将本节点设为已分配，id设为分配的id即可
						
					}
				}
				//要分配的是链表非头非尾的内部节点
				else{
					//printf("要分配的是链表非头非尾的内部节点\n");
					if(mindif !=0 ){
						if(index->next->flag == 0)
						{
							//若下一个节点是未分配节点，将剩余空间加到下一个节点上
							index->next->size  += mindif;
							index->next->start -= mindif;
						}
						else
						{
							//若下一个节点是已分配节点，将剩余空间单独成一节点
							pnode t = (pnode)malloc(sizeof(node));
							t->flag = 0;
							t->id = 0;
							t->next = index->next;
							t->prior = index;
							t->size = mindif;
							t->start = index->start + index->size;

							index->next->prior = t;
							index->next = t;
						}
					}
				}

				//分配之后显示当前内存分配情况
				p = head;
				printf("id\tstart\tsize\talloced?\n");
				while(p!=NULL){
					char alloced ;
					if(p->flag == 0)
						alloced = 'N';
					else
						alloced = 'Y';
					printf("%d\t%d\t%d\t%c\n",p->id,p->start,p->size,alloced);
					p = p->next;
				}
				printf("\n");
				
			break;
		case 'b':
			//回收节点
			printf("请输入要回收的作业的id:");
			cin>>id;
			p = head;
			index = NULL;
			while(p!=NULL){
				if(p->id == id){
					index = p;
					break;
				}
				p = p->next;
			}
			printf("%d\t%d\t%d\t%d\n",p->id,p->start,p->size,p->flag);
			if(index->prior == NULL){
				//要回收的节点是首节点
				if(index->next != NULL){
					//如果链表中不是只有一个节点
					index->flag = 0;
					index->id = 0;
					if(index->next->flag==0){
						//若第二个节点是空节点
						index->size += index->next->size;
						if(index->next->next!=NULL)//若链表只有两个节点，第二个节点没有下一个节点
							index->next->next->prior = index;
						pnode temp = index->next;//方便回收，避免产生野指针
						index->next = index->next->next;
						free(temp);
						
					}
					else{
						//若第二个节点不是空节点,什么都不用干
						
					}
				}
				
				else{
					//链表中只有一个节点，将其回收即可
					index->flag = 0;
					index->id = 0;
				}
			}
			else if(index->next == NULL){
				//要回收的节点是尾节点
				index->flag = 0;
				index->id = 0;
				if(index->prior->flag == 0){
					//如果倒数第二个节点是空节点,将其合并
					pnode temp = index;
					index->prior->size += index->size;
					index->prior->next = NULL;
					
					temp->prior = NULL;temp->next = NULL;
					free(temp);

				}
			}
			else{
				//要回收的节点是非头非尾的中间节点
				index->flag = 0;
				index->id = 0;
				if(index->next->flag == 0){
					//下一个节点是空节点
					index->size +=index->next->size;
					//保存下一个节点，方便删除
					pnode temp = index->next;
					index->next = index->next->next;
					if(index->next!=NULL)//最后一个节点没有下一个节点
						index->next->prior = index;
					temp->prior = NULL;temp->next = NULL;
					free(temp);
				}
				if(index->prior->flag == 0){
					//前一个节点是空节点，必须先后再前，否则若前后都是空节点无法合并后一个空节点
					index->prior->size += index->size;
					pnode temp = index;
					index->prior->next = index->next;
					
					temp->prior = NULL;temp->next = NULL;
					free(temp);
				}
			}
			
			//回收之后显示当前内存分配情况
			p = head;
			printf("id\tstart\tsize\talloced?\n");
			while(p!=NULL){
				char alloced ;
				if(p->flag == 0)
					alloced = 'N';
				else
					alloced = 'Y';
				printf("%d\t%d\t%d\t%c\n",p->id,p->start,p->size,alloced);
				p = p->next;
			}
			printf("\n");
			break;
		case 'd':
			exit(0);
		case 'c':
			p = head;
			printf("id\tstart\tsize\talloced?\n");
			while(p!=NULL){
				char alloced ;
				if(p->flag == 0)
					alloced = 'N';
				else
					alloced = 'Y';
				printf("%d\t%d\t%d\t%c\n",p->id,p->start,p->size,alloced);
				p = p->next;
			}
			printf("\n");
			break;
		default:
			break;
			}
		}
		}
	return 0;
}
