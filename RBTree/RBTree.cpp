// RBTree.cpp : 定义控制台应用程序的入口点。
#include"RBTree.h"
#include"iostream"
using namespace std;
void testRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	size_t size = sizeof(array) / sizeof(array[1]);
	RBTree<int, int>tree;
	for (size_t i = 0; i < size; i++)
	{
		tree.Insert(array[i], i);
		cout << "IsRBTree ?" << array[i] << "->" << tree.IsRBTree() << endl;
	}
	tree.InOrder();
	cout << "IsRBTree?" << tree.IsRBTree() << endl;   //1
	cout << "Find(9)?" << tree.Find(9) << endl;       //1
	cout << "Find(16)?" << tree.Find(16) << endl;     //1
	cout << "Find(20)?" << tree.Find(20) << endl;     //0
}
int main()
{
	testRBTree();
	system("pause");
	return 0;
}