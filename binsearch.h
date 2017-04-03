#ifndef BSEARCH_TREE
#define BSEARCH_TREE
/****************************简单的建立一棵二叉搜索树,当没有查找到相同的元素则插入，否则不插入。同时可以删除指定结点*******************************************/
/**********  此处按照元素的输入顺序自己建立一颗搜索（排序）二叉树，它的深度和元素输入顺序有关**************/
#include"tree.h"
/*******二叉搜索树删除结点有三种情况：一是删除叶节点，直接删除即可。二是删除结点只有左子树或者右子树，删除后将左子树或右子树移接。三是删除结点
既有左子树，又有右子树，则要找到待删除结点的直接前驱，或者直接后继，令删除结点等于前驱或者后继，删除前驱或后继，再重接子树*********/
template<typename T>
class Bstree :public BiTree<T>     //继承基本的二叉树类
{
public:
	//若树中Tree存在关键字key,则删除key并返回true，否则返回false
	bool DeleteBST(BiTnode<T> * &Tree, T key);

	//在树中Tree寻找关键字key,f指向Tree的双亲，当Tree为根结点时，f=NULL，当找到key时，返回true，p指向key所在的结点，
	//否则返回false,p指向所查找路径的叶节点(以便插入)
	bool SearchBST(BiTnode<T> * &Tree, T key, BiTnode<T> * f, BiTnode<T> * &p);

	//若二叉搜索树中没有e,则插入e并返回true，否则返回false
	bool InsertBST(T e);

private:
	void Delete(BiTnode<T> * &Tree);           //具体删除实现，三种情况都包含
};
template<typename T>
bool Bstree<T>::DeleteBST(BiTnode<T> * &Tree, T key)
{
	if (Tree == NULL)
		return false;
	else
	{
		if (key == Tree->element)
		{
			Delete (Tree);  //调用函数void Delete(BiTnode<T> * &Tree)
			return true;
		}
		else if (key < Tree->element)
			return DeleteBST(Tree->lchild, key);
		else
			return DeleteBST(Tree->rchild, key);
		
	}
}
template<typename T>
void Bstree<T>::Delete(BiTnode<T> * &Tree)
{
	BiTnode<T> * s,* p = Tree;
	if (Tree->rchild == NULL)
	{
		Tree = Tree->lchild;
		delete p;
	}
	else if (Tree->lchild == NULL)
	{
		Tree = Tree->rchild;
		delete p;
	}
	else                   //此处是找待删除结点的直接前驱
	{
		s = Tree->lchild;
		while (s->rchild != NULL)
		{
			p = s;
			s = s->rchild;
		}
		Tree->element = s->element;
		if (Tree == p)  //待删除结点的左孩子没有右子树
			p->lchild = s->lchild;
		else
			p->rchild = s->lchild;
		delete s;
	}
	Treesize--;
}
template<typename T>
bool Bstree<T>::SearchBST(BiTnode<T> * &Tree, T key, BiTnode<T> * f, BiTnode<T> * &p)
{
	if (!Tree)
	{
		p = f;
		return false;
	}
	else if (key == Tree->element)
	{
		p = Tree;
		return true;
	}
	else if (key < Tree->element)
		return SearchBST(Tree->lchild, key, Tree, p);
	else
		return SearchBST(Tree->rchild, key, Tree, p);
}
template<typename T>
bool Bstree<T>::InsertBST(T e)
{
	BiTnode<T> *p, *s;
	if (!SearchBST(root, e, NULL, p))  //此处当没有查找到e时p为所在查找路径的叶节点，或者为空，也就是树为空
	{
		s = new BiTnode < T > ;
		s->element = e;
		s->lchild = s->rchild = NULL;
		if (!p)      //树为空，e作为根结点
			root = s;
		else if (e < p->element)
			p->lchild = s;
		else
			p->rchild = s;
		Treesize++;
		return true;
	}
	else
		return false;
}

#endif //BSEARCH_TREE
