/*
���ܺ�����ʵ��
*/

#include"haffman.h"

void MakeTree(int weight[],int n,haffmannode haffmantree[])
{
	int i,j,m1,m2,x1,x2;
	//��ʼ����n��Ҷ�ڵ�һ�� 2*n-1 ���ڵ㣩
	for(i=0;i < 2*n-1; i++)
	{
		if(i < n)  //���� n ��Ҷ�ӽڵ�
		{
			haffmantree[i].weight=weight[i];
		}
		else 
			haffmantree[i].weight=0;
		
		haffmantree[i].LeftChild = -1;  //��ʼʱ�������Һ��Ӻ�˫�׵��±�Ϊ -1 
		haffmantree[i].RightChild = -1;
		haffmantree[i].Parent = -1;
		haffmantree[i].flag = 0;  
	}
	
	//ÿ�δ���ѡ��Ȩֵ��С�ĺʹ�С�Ĺ���������������
	//���� n-1 ����Ҷ�ӽڵ�
	for(i=0; i < n-1;i++)
	{
		m1=m2=MAXWEIGHT;
		x1=x2=0;
		//����Ȩֵ�Ľڵ��в��� m1 �������Ȩֵ��С��, m2 �������Ȩֵ��С��, x1 �������Ȩֵ��С���±�, x2 �������Ȩֵ��С���±�
		for(j=0;j < n+i; j++)
		{
			if(haffmantree[j].weight < m1 && haffmantree[j].flag==0)
			{
				m2=m1; 
				x2=x1;
				m1=haffmantree[j].weight;
				x1=j;
			}
			else if(haffmantree[j].weight < m2 && haffmantree[j].flag==0)
			{
				m2=haffmantree[j].weight;
				x2=j;
			}
		}
		haffmantree[x1].Parent=n+i; // �����һ��˫�׽ڵ���±���� n �ڶ���˫�׽ڵ���±���� n+1 --------
		haffmantree[x2].Parent=n+i;
		haffmantree[x1].flag=1;
		haffmantree[x2].flag=1;
		haffmantree[n+i].weight=haffmantree[x1].weight + haffmantree[x2].weight;  //Ȩֵ���
		//printf("%d\n",haffmantree[n+i].weight);
		haffmantree[n+i].LeftChild=x1;
		haffmantree[n+i].RightChild=x2;	
	}
}

//����������ʵ�ֶԺշ�������Ľ��
void MakeCode(haffmannode haffmantree[],int n,HaffmanCode haffmancode[])
{
	int i,j;
	int Child,Parent;
	HaffmanCode *code;
	code=(HaffmanCode *)malloc(LEN_CODE);  //���������ʱ����
	for(i=0;i < n ;i++)
	{
		code->weight=haffmantree[i].weight;
		code->start=0; 
		Child=i;    
		Parent=haffmantree[Child].Parent;
		while(Parent != -1) //��˫�׽ڵ㲻Ϊ���ڵ�ʱ��
		{
			if(haffmantree[Parent].LeftChild==Child)  //�����ǰ�ڵ���˫�׽ڵ�����Ӿͽ�0���뵽�ñ�����������Һ��Ӿͽ�1���뵽������
				code->bits[code->start]=0;
			else
				code->bits[code->start]=1;
			code->start++;  
			Child=Parent;  //�Ե������ƶ��ж�
			Parent=haffmantree[Child].Parent;
		}
		for(j=0;j < code->start;j++) //�Ѹñ�����뵽��Ӧ�ı���������
		{
			haffmancode[i].bits[j]=code->bits[j];
		}
		haffmancode[i].weight=code->weight; //�Ѷ�Ӧ��Ȩֵ���뵽��Ӧ���������Ȩֵ��ȥ
		haffmancode[i].start=code->start; //������λ�ø��ƽ�ȥ
	}

	free(code);
	code = NULL;
}


void DispCode(char temp[],haffmannode tree[],HaffmanCode Code[],int n) //��������Ҫ����ʵ�ֹ�������������
{
	int i,j;
	printf("\n����շ�������:\n\n");
	for(i=0;i<n;i++)
	{
		printf("�ַ�= %c \tWeight= %d \t\n�ַ�= %c \tCode=",temp[i],tree[i].weight, temp[i]);
		for(j=(Code[i].start-1);j>=0;j--)//�������
		{
			printf("%d",Code[i].bits[j]);
		}
		printf("\n\n");
	}
}