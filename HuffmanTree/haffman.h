/*
����������ʵ�ֶԺշ��������������Ĳ���
��Ҫ���裺
 1 ����һ���ڵ���������������Ľڵ���Ϣ
 2 ��ʼ��
 3 �����ҳ�Ȩֵ��С��Ȩֵ��С�ڵ�Ȼ�������������ڵ��˫�׽ڵ�Ȩֵ��С�ڵ��Ǹ�˫�׽ڵ�����Ӵ�СΪ�Һ���Ȼ�󽫸�˫�׽ڵ���뵽�ڵ������в����Ϊ�Ѽ���
 4 �ظ�������֪���շ���������ɹ�
*/
#include<stdio.h>
#include<malloc.h>
#define LEN_CODE sizeof(HaffmanCode)
#define LEN_NODE sizeof(haffmannode)
#define MAXWEIGHT 1000 //�����洢����Ȩֵ��
#define MaxBits 30 //�����洢ת����ı���

typedef struct HaffManTree
{
	int weight;  //��Žڵ��Ȩֵ
	int LeftChild,RightChild,Parent;  //���÷���ָ�뷽����Žڵ�����Һ��Ӻ�˫���±�
	int flag;  //�����жϸýڵ��Ƿ��Ѿ������˺շ�������( 0��ʾδ���룬1��ʾ�Ѿ����� )
}haffmannode;

typedef struct HaffMancode
{
	int bits[MaxBits]; //������ű���
	int weight;  //������Ŷ�Ӧ��Ȩֵ
	int start; //��ű������ʼλ��
}HaffmanCode;

void MakeTree(int weight[],int n,haffmannode haffmantree[]);
void MakeCode(haffmannode haffmantree[],int n,HaffmanCode haffmancode[]);
void DispCode(char temp[],haffmannode tree[],HaffmanCode Code[],int n);