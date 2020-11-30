# include <stdio.h>
/*
���õݹ�ʵ�ֶ��ֲ��ҷ�
*/

int BSearch(int a[], int x, int low, int high)
//low��high��Ϊ�����±�
{
	int mid;      

	if(low > high)
		return -1;

	mid = (low+high)/2;
	if (x == a[mid])
		return mid;
	else if (x < a[mid])
		return BSearch(a, x, low, mid-1);	//ǰ��������
	else
		return BSearch(a, x, mid+1, high);  //���������

}

/*�ǵݹ�ʵ�ֶ��ֲ���*/
int bin_search(int *a, int n, int x)
{
	int head = -1, tail = n, mid = -1;
	int pos = -1;

	while (head+1 != tail)
	{
		mid = (tail+head) / 2;

		if (x > a[mid])
			head = mid;
		else
			tail = mid;
	}

	pos = tail;
	if (pos >= n || a[pos] != x)
		pos = -1;

	return pos;
}

int main()
{
	int a[] = {1, 3, 4, 5, 17, 18, 31, 33};
	int x = 17;
	int bn;

	bn = BSearch(a, x, 0, 7);
	if (-1 == bn)
		printf("x������������a��\n");
	else
		printf("x������a�е��±�Ϊ%d\n", bn);

	return 0;
}