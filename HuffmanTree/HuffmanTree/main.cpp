#include <stdlib.h>
#include"haffman.h"

#define MAX 255

void main()
{
	int i,flag=1,n=0;
	int *weight;
	char *temp=(char*)malloc(sizeof(char)*MAX); //��������û�������ַ�

	while(flag)
	{
		printf("\n�������ַ�: ");
		n=0,i=0;
		while(1)
		{
			scanf("%c",&temp[i]);
			i++,n++;
			if(getchar() == '\n') { break; }
		}

		if (n==0 || n==1)
		{
			printf("����Ϊ�ջ����ֻ��һ���ڵ㣡\n");
			exit(0);
		}

		weight=(int*)malloc(sizeof(int)*n);
		printf("\n������%d���ַ�Ȩֵ: ",n);
		for(i=0;i<n;i++)
		{
			scanf("%d",&weight[i]);
			getchar();
		}
		
		system("cls");
		haffmannode *tree=(haffmannode *)malloc((2*n-1)*LEN_NODE);  //����շ��������ܽڵ���
		HaffmanCode *code=(HaffmanCode *)malloc(LEN_CODE * n); //�����Ӧ�ı�������

		MakeTree(weight,n,tree); //���ɺշ�����

		MakeCode(tree,n,code); //���ɶ�Ӧ�ı�������

		DispCode(temp,tree,code,n);  //����շ�������

		printf("\n");
		printf("�˳��밴(E),����������: ");
		char c = getchar();
		getchar();
		if (c== 'E' || c == 'e')
		{
			flag = 0;
		}
	}
}