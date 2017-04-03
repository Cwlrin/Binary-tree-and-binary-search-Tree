#include <iostream>
#include "tree.h"
#include "binsearch.h"
using namespace std;
/******************基本的二叉树程序测试，输入是按前序输入二叉树**************************/
void testbitree()
{
	cout << "以前序遍历的方式创建一颗二叉树：" << endl;
	BiTree<char>  tree;
	tree.CreateBiTree(tree.Root());
	cout << "树的结点数目为" << tree.size() << endl;
	cout << "树的深度为：" << tree.Treedepth(tree.Root()) << endl;
	cout << "以递归方法遍历二叉树：" << endl;
	cout << "前序遍历结果：";
	tree.preOrder(tree.Root());
	cout << endl;
	cout << "中序遍历结果：";
	tree.inOrder(tree.Root());
	cout << endl;
	cout << "后序遍历结果：";
	tree.postOrder(tree.Root());
	cout << endl;
	cout << "以非递归方法遍历二叉树：" << endl;
	cout << "前序遍历结果：";
	tree.preOrderstack(tree.Root(), visit);
	cout << endl;
	cout << "中序遍历结果：";
	tree.inOrderstack(tree.Root(), visit);
	cout << endl;
	cout << "后序遍历结果：";
	tree.postOrderstack(tree.Root(), visit);
	cout << endl;
	cout << "层序遍历结果：";
	tree.levelOrderqueue(tree.Root(), visit);
	cout << endl;
	tree.erase(tree.Root());
	cout << "从根结点删除后，树的结点数目为" << tree.size() << endl;

}

/***************搜索二叉树的测试，按元素输入的顺序建立搜索二叉树********************/
void testbstree()
{
	int i;
	int a[11] = { 62, 88, 58, 47, 35, 73, 51,88, 99, 37, 93 };
	Bstree<int> b;
	for (i = 0; i < 11; i++)
		b.InsertBST(a[i]);
	b.DeleteBST(b.Root(), 93);  //删除93的结点
	cout << "树的结点数目为" << b.size() << endl;
	cout << "树的深度为：" << b.Treedepth(b.Root()) << endl;
	cout << "以递归方法遍历二叉树：" << endl;
	cout << "前序遍历结果：";
	b.preOrder(b.Root());
	cout << endl;
	cout << "中序遍历结果：";
	b.inOrder(b.Root());
	cout << endl;
	cout << "后序遍历结果：";
	b.postOrder(b.Root());
	cout << endl;
}
int main()
{
	cout << "/****************创建基本的二叉树*********************/" << endl;
	testbitree();
	cout << "/****************创建二叉搜索树***********************/" << endl;
	testbstree();
	return 0;
}

