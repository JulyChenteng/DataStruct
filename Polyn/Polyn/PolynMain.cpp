#include "Polyn.h"
#include <iostream>
using namespace std;

int main()
{
	Polyn pa;
	Polyn pb;
	Polyn pc;

	InitPolyn(pa);
	InitPolyn(pb);
	InitPolyn(pc);

	int m;
	int select = 1;
	while (select)
	{
		cout << "***********************************" << endl;
		cout << "*[1]��������ʽpa  [2]��������ʽpb *" << endl;
		cout << "*[3]��ʾ����ʽpa  [4]��ʾ����ʽpb *" << endl;
		cout << "*[5]����ʽ���    [6]����ʽ���   *" << endl;
		cout << "*[7]����ʽ���    [0]�˳�ϵͳ     *" << endl;
		cout << "***********************************" << endl;
		cout << "��ѡ��:>";
		cin >> select;

		switch (select)
		{
		case 1:
			cout << "���������ʽ��������>";
			cin >> m;
			CreatePolyn(pa, m);
			break;
		case 2:
			cout << "���������ʽ��������>";
			cin >> m;
			CreatePolyn(pb, m);
			break;
		case 3:
			cout << "pa = ";
			ShowPolyn(pa);
			cout << endl;	
			break;
		case 4:
			cout << "pb = ";
			ShowPolyn(pb);
			cout << endl;
			break;
		case 5:												 
			pc = PolynAdd(pa, pb);
			cout << "pc = ";
			ShowPolyn(pc);
			cout << endl;
			break;
		case 6:
			pc = PolynSub(pa, pb);
			cout << "pc = ";
			ShowPolyn(pc);
			cout << endl;
			break;
		case 7:
			pc = PolynMul(pa, pb);
			cout << "pc = ";
			ShowPolyn(pc);
			cout << endl;																	 
			break;
		case 0:
			exit(1);
			break;
		}
	}

	return 0;
}