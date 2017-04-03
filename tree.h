#ifndef TREE_H
#define TREE_H
/************************基本的二叉树，此创建二叉树要按照前序(或中序后序)按顺序输入二叉树***************************/
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template <typename T>
struct BiTnode       //树的链式存储结构，表式树的一个结点，一个数据域，两个指针域
{
	T  element;
	BiTnode<T> * lchild, *rchild;
};
template<typename T>                          //作为一个函数指针传入遍历函数中
void visit(BiTnode<T>* &node)
{
	cout << node->element << "    ";
}
template <typename T>
struct BiTNodePost                            //非递归后序遍历结构
{
	BiTnode<T> * biTree;
	char tag;
};

template<typename T>
class BiTree
{
public:
	 BiTree()  { root = NULL; Treesize = 0; }
	~BiTree() { erase(root); }

	void CreateBiTree(BiTnode <T>* &node);
	void erase(BiTnode<T> * &node);

	bool empty() const{ return Treesize == 0; }
	int  size() const{ return Treesize; }


	//递归遍历方法
	void preOrder(BiTnode <T>* &node);
	void inOrder(BiTnode <T>* &node);
	void postOrder(BiTnode <T>* &node);
	//非递归遍历方法
	void preOrderstack(BiTnode<T>* node, void(*visit)(BiTnode<T>* &)); //传入了一个函数指针
	void inOrderstack(BiTnode <T>* node, void(*visit)(BiTnode<T>* &));
	void postOrderstack(BiTnode<T>* node, void(*visit)(BiTnode<T>* &));
	void levelOrderqueue(BiTnode<T>* node, void(*visit)(BiTnode<T>* &));
	//遍历时对每个节点的操作
	void  operator_(BiTnode<T>* &node);
	//深度
	int Treedepth(BiTnode <T>*node) const;
	//访问根结点
	BiTnode<T> * & Root(){ return root; }   //此处返回的为引用，当不是引用是返回的是root的复制品，也就是一个临时变量，并不能改变root本身。
protected:
	BiTnode <T>* root;
	int Treesize;
};

/********************************************递归方法创建二叉树*****************************************/
//开始这块是传值，结果总不能创建二叉树，如果要创建二叉树或者改变树的结点，此处必须是传址（也就是双重指针）或者传引用。
template<typename T>
void BiTree<T>::CreateBiTree(BiTnode <T> * &node)
{
	T e;
	cin >> e;
	if (e == '#')
		node = NULL;  //保证是叶结点
	else
	{
		node = new BiTnode<T>;
		node->element = e;//生成结点
		Treesize++;
		CreateBiTree(node->lchild);//构造左子树
		CreateBiTree(node->rchild);//构造右子树
	}

}

/*******************************************递归方法删除node所指的二叉树****************************************/
template <typename T>
void BiTree<T>::erase(BiTnode <T>* &node)
{
	if (node != NULL)
	{
		erase(node->lchild);
		erase(node->rchild);
		delete node;
		Treesize--;
		node = NULL;
	}

}
/***********************************此处操作只是简单打印结点的元素,当然也可以对其树的结点进行修改,注意参数是传值还是传址或传引用***********************************/
template<typename T>
void  BiTree<T>::operator_(BiTnode<T>* &node)
{
	cout << node->element << "    ";
}

/*************************************递归前序，中序，后序遍历********************************/
template<typename T>
void BiTree<T>::preOrder(BiTnode <T>* &node)
{
	if (node != NULL)
	{
		operator_(node);
		preOrder(node->lchild);
		preOrder(node->rchild);
	}
}
template<typename T>
void BiTree<T>::inOrder(BiTnode<T>* &node)
{
	if (node != NULL)
	{
		inOrder(node->lchild);
		operator_(node);
		inOrder(node->rchild);
	}
}
template<typename T>
void BiTree<T>::postOrder(BiTnode <T>* &node)
{
	if (node != NULL)
	{
		postOrder(node->lchild);
		postOrder(node->rchild);
		operator_(node);
	}
}

/*******************************非递归层序，前序，中序，后序遍历**************************************/
template<typename T>
void BiTree<T>::preOrderstack(BiTnode<T>* node, void(*visit)(BiTnode<T>* &))
{
	stack<BiTnode<T> *> s;
	BiTnode<T> * p = node;                          //p是遍历指针
	while (p || !s.empty())               //p不为空或者栈不空时循环
	{
		if (p != NULL)
		{
			s.push(p);
			visit(p);
			p = p->lchild;
		}

		else
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}

}
template<typename T>
void BiTree<T>::inOrderstack(BiTnode<T> * node, void(*visit)(BiTnode<T>* &))
{
	stack<BiTnode<T> *> s;
	BiTnode<T> * p = node;
	while (p || !s.empty())
	{
		if (p != NULL)
		{
			s.push(p);
			p = p->lchild;
		}
		else
		{
			p = s.top();
			visit(p);      //对树中的结点进行操作
			s.pop();
			p = p->rchild;
		}
	}
}

template<typename T>
void BiTree<T>::postOrderstack(BiTnode<T> * node, void(*visit)(BiTnode<T>* &))
{
	stack<BiTNodePost <T>*>s;
	BiTnode<T> * p = node;
	BiTNodePost <T> *BT;
	while (p != NULL || !s.empty())
	{
		//遍历左子树
		while (p != NULL)
		{
			BT = new BiTNodePost<T>;
			BT->biTree = p;
			BT->tag = 'L';
			s.push(BT);
			p = p->lchild;
		}
		//左右子树访问完毕访问根节点
		while (!s.empty() && (s.top())->tag == 'R')
		{
			BT = s.top();
			visit(BT->biTree);
			s.pop();
		}
		//遍历右子树
		if (!s.empty())
		{
			BT = s.top();
			BT->tag = 'R';
			p = BT->biTree;
			p = p->rchild;
		}
	}
}

template<typename T>
void BiTree<T>::levelOrderqueue(BiTnode<T> * node, void(*visit)(BiTnode<T>* &))
{
	queue<BiTnode <T>*> q;           //此处为队列
	BiTnode<T> * p = node;
	q.push(p);                    //队列不空循环
	while (!q.empty())
	{
		p = q.front();
		visit(p);
		q.pop();
		if (p->lchild != NULL)
			q.push(p->lchild);
		if (p->rchild != NULL)
			q.push(p->rchild);
	}
}

/*********************************************递归方法返回树的深度***************************************/
template<typename T>
int BiTree<T>::Treedepth(BiTnode<T> *node) const
{
	int hl, hr;
	if (node == NULL)
		return 0;
	hl = Treedepth(node->lchild);
	hr = Treedepth(node->rchild);
	return hl>hr ? ++hl : ++hr;
}

#endif // TREE_H
