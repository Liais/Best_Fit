/**********************************
		����ϵͳ����������ѷ����㷨
		GitHub��Liais
		���ʱ�䣺2018-6-25
		���뻷����VS2010
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
	int flag;//�����־���ѷ���1,δ����0
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
	head->id = 0;//δ����
	pnode tail = head;

	int size;
	int id = 1;
	printf("�����ڴ��ܹ���1000M,�����ó���ģ��ʹ�������Ӧ�㷨���ڴ���ж�̬��������\n");
	printf("a:�����ڴ�,b:�����ڴ�,c:��ʾ��ǰ��ҵ�ڴ�������,d:�˳�����\n");
	while(1)
	{
		int taskid = 1;
		pnode p,index;
		char choice;
		int mindif = S;
		printf("���������:");
		cin>>choice;
		switch(choice)
		{
		case 'a':
			printf("����Ҫ�����ڴ�Ĵ�С:");
			cin>>size;
			if(size == 0)//����0Ҳ�����
				break;
			//�����ڴ�
			//pnode index;//��ѷ���Ŀ��ָ��
			p = head;
			index = NULL;
			mindif = S;//��С��
			
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
			if(index==NULL)//����ʧ��
			{
				printf("���������Է�������ݶΣ�����ʧ��\n\n");
				break;
			}
			else{
				//printf("%d\t%d\t%d\t%d\n",index->id,index->start,index->size,index->flag);
				index->size -=mindif;
				index->id = id++;
				index->flag = 1;//�ѷ���
				//���Ŀ��ڵ���ͷ��㣬�ֳ�δ���䲿����Ϊ�����ڵ�
				if(index->prior == NULL)
				{
					if(mindif != 0){
						//printf("���Ŀ��ڵ���ͷ��㣬�ֳ�δ���䲿����Ϊ�����ڵ�\n");
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
						//printf("ͷ����ѷ���\n");
					}
				}
				//Ҫ�������β�ڵ�
				else if(index->next == NULL)
				{
					if(mindif != 0){
						//printf("Ҫ�������β�ڵ�\n");
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
						//���÷����������������ٴ����µĽڵ㣬ֱ�ӽ����ڵ���Ϊ�ѷ��䣬id��Ϊ�����id����
						
					}
				}
				//Ҫ������������ͷ��β���ڲ��ڵ�
				else{
					//printf("Ҫ������������ͷ��β���ڲ��ڵ�\n");
					if(mindif !=0 ){
						if(index->next->flag == 0)
						{
							//����һ���ڵ���δ����ڵ㣬��ʣ��ռ�ӵ���һ���ڵ���
							index->next->size  += mindif;
							index->next->start -= mindif;
						}
						else
						{
							//����һ���ڵ����ѷ���ڵ㣬��ʣ��ռ䵥����һ�ڵ�
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

				//����֮����ʾ��ǰ�ڴ�������
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
			//���սڵ�
			printf("������Ҫ���յ���ҵ��id:");
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
				//Ҫ���յĽڵ����׽ڵ�
				if(index->next != NULL){
					//��������в���ֻ��һ���ڵ�
					index->flag = 0;
					index->id = 0;
					if(index->next->flag==0){
						//���ڶ����ڵ��ǿսڵ�
						index->size += index->next->size;
						if(index->next->next!=NULL)//������ֻ�������ڵ㣬�ڶ����ڵ�û����һ���ڵ�
							index->next->next->prior = index;
						pnode temp = index->next;//������գ��������Ұָ��
						index->next = index->next->next;
						free(temp);
						
					}
					else{
						//���ڶ����ڵ㲻�ǿսڵ�,ʲô�����ø�
						
					}
				}
				
				else{
					//������ֻ��һ���ڵ㣬������ռ���
					index->flag = 0;
					index->id = 0;
				}
			}
			else if(index->next == NULL){
				//Ҫ���յĽڵ���β�ڵ�
				index->flag = 0;
				index->id = 0;
				if(index->prior->flag == 0){
					//��������ڶ����ڵ��ǿսڵ�,����ϲ�
					pnode temp = index;
					index->prior->size += index->size;
					index->prior->next = NULL;
					
					temp->prior = NULL;temp->next = NULL;
					free(temp);

				}
			}
			else{
				//Ҫ���յĽڵ��Ƿ�ͷ��β���м�ڵ�
				index->flag = 0;
				index->id = 0;
				if(index->next->flag == 0){
					//��һ���ڵ��ǿսڵ�
					index->size +=index->next->size;
					//������һ���ڵ㣬����ɾ��
					pnode temp = index->next;
					index->next = index->next->next;
					if(index->next!=NULL)//���һ���ڵ�û����һ���ڵ�
						index->next->prior = index;
					temp->prior = NULL;temp->next = NULL;
					free(temp);
				}
				if(index->prior->flag == 0){
					//ǰһ���ڵ��ǿսڵ㣬�����Ⱥ���ǰ��������ǰ���ǿսڵ��޷��ϲ���һ���սڵ�
					index->prior->size += index->size;
					pnode temp = index;
					index->prior->next = index->next;
					
					temp->prior = NULL;temp->next = NULL;
					free(temp);
				}
			}
			
			//����֮����ʾ��ǰ�ڴ�������
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
