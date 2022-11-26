#pragma once
#include "Class.h"

//������ڵ�
struct node {
	int weight = 0;
	XY xy;
	std::vector<struct node*> nexts;
};

typedef struct node* Node;

//��ʼ��ͷ���
void initHead(Node head);

//��ӡ
void printTreeNode(Node head, std::string info);

//����
int find(std::vector<struct node*>& nexts, XY xy);

//���
void AddToTree(Node head, std::vector<XY>& data);

//����Ȩ��
int setWeight(Node head, int count);