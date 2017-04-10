//�����ļ�

#include "GraphLnk.h"

int main()
{
	CGraphLnk<char, int> gl;
	gl.insertVtx('A');
	gl.insertVtx('B');
	gl.insertVtx('C');
	gl.insertVtx('D');
	gl.insertVtx('E');

	gl.insertEdge('A', 'B', 1);
	gl.insertEdge('A', 'C', 1);
	gl.insertEdge('C', 'D', 1);
	gl.insertEdge('B', 'D', 1);
	//gl.insertEdge('E', 'A', 1);

	gl.showGraph();
	gl.removeVtx('B');
	gl.removeVtx('E');
	cout << "\nɾ��B��E��" << endl;
	gl.showGraph();
	cout << endl;

	gl.showGraph();
	gl.removeEdge('A', 'C');
	cout << "\nɾ��AC�ߺ�" << endl;
	gl.showGraph();
	cout << endl;	
	
	cout << gl.getElement(1) << endl;

	return 0;
}