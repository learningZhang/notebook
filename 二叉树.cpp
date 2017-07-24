#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

typedef int elemType;

struct BtNode
{
	BtNode *rightNode;
	elemType data;
	BtNode *leftNode;
};


//遍历树
void proOrder(BtNode *node)
{
	if(node != NULL)
	{
		cout<<node->data<<" ";
		proOrder(node->leftNode);
		proOrder(node->rightNode);
	}
}

void inOrder(BtNode *node)
{
	if(node != NULL)
	{
		inOrder(node->leftNode);
		cout<<node->data<<" ";
		inOrder(node->rightNode);
	}
}

void pastOrder(BtNode *node)
{
	if(node != NULL)
	{
		pastOrder(node->leftNode);
		pastOrder(node->rightNode);
		cout<<node->data<<" ";
	}
}

void NicePreOrder(BtNode *p)//先根非递归
{
	if (p == NULL) return ;
	stack<BtNode *> stack;
	stack.push(p);
	while(!stack.empty())
	{
		p = stack.top(); stack.pop();
		cout<<p->data<<" ";
		if (p->rightNode != NULL)
		{
			stack.push(p->rightNode);
		}
		if (p->leftNode != NULL)
		{
			stack.push(p->leftNode);
		}

	}
}

void NiceInOrder(BtNode *ptr)//中根非递归
{
	stack<BtNode *> st;
	while (!st.empty() || ptr != NULL)
	{
		while (ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftNode;
		}
		ptr = st.top(); st.pop();
		cout<<ptr->data<<" ";
		ptr = ptr->rightNode;
	}
}

void NicePastOrder(BtNode *ptr)//后根非递归
{
	BtNode *p = NULL;
	stack<BtNode *> st;
	while (!st.empty() || ptr!=NULL)
	{
		while (ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftNode;
		}

		ptr = st.top(); st.pop();

		if (ptr->rightNode==NULL || ptr->rightNode == p)
		{
			cout<<ptr->data<<" ";
			p = ptr;
			ptr = NULL;
		}
		else
		{
			st.push(ptr);
			ptr = ptr->rightNode;
		}
	}
}


struct StkNode
{
	BtNode *pnode;
	int     popnum;
public:
	StkNode(BtNode *p = NULL):pnode(p),popnum(0){}
};

void StkNicePastOrder(BtNode *p)
{
	if(NULL == p) return ;
	stack<StkNode> st;
	st.push(StkNode(p));

	while(!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if(++node.popnum == 3)
		{
			cout<<node.pnode->data<<" ";
		}
		else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftNode != NULL)
			{
				st.push(StkNode(node.pnode->leftNode));
			}
			else if(node.popnum == 2 &&node.pnode->rightNode != NULL)
			{
				st.push(StkNode(node.pnode->rightNode));
			}
		}
	}
	cout<<endl;
}

void StkNiceInOrder(BtNode *p)
{
	if(NULL == p) return ;
	stack<StkNode> st;
	st.push(StkNode(p));
	while(!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if(++node.popnum == 2)
		{
			cout<<node.pnode->data<<" ";
			if(node.pnode->rightNode != NULL)
			{
				st.push(StkNode(node.pnode->rightNode));
			}
		}
		else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftNode != NULL)
			{
				st.push(StkNode(node.pnode->leftNode));
			}
		}
	}
	cout<<endl;
}


void NiceLevelOrder(BtNode *p)
{
	queue<BtNode *> ptr;
	ptr.push(p);
	while (!ptr.empty())
	{
		BtNode *tmp = ptr.front();
		ptr.pop();
		cout<<tmp->data;

		if (tmp->leftNode != NULL)
		{
			ptr.push(tmp->leftNode);
		}

		if (tmp->rightNode != NULL)
		{
			ptr.push(tmp->rightNode);
		}
	}
}

void Print_K_Item(BtNode *p,int k)
{
	if (k == 1)
	{
		cout<<p->data<<" ";
	}
	else
	{
		if (p->leftNode != NULL)
		{
			Print_K_Item(p->leftNode,k-1);
		}
		if (p->rightNode != NULL)
		{
			Print_K_Item(p->rightNode,k-1);
		}
	}
}

//建立树
BtNode *createNode()
{	
	BtNode *tmp = (BtNode *)malloc(sizeof(BtNode));
	assert(tmp != NULL);
	memset(tmp, 0, sizeof(BtNode));
	return tmp;
}

BtNode *createTree(const char *&str)
{
	if (*str!='\0' && *str!='#')
	{
		BtNode *tmp = createNode();
		tmp->data = *str-'0';

		tmp->leftNode = createTree(++str);
		tmp->rightNode = createTree(++str);
		return tmp;
	}
	return NULL;
}

int findIndex(char *str, char ch, int num)
{
	for(int i=0; i<num; ++i,++str)
	{
		if (*str == ch)
		{
			return i;
		}
	}
	return -1;
}

BtNode *createTreeByProIn(char *pro, char *in, int n)
{
	if (n == 0)
	{
		return NULL;
	}
	BtNode *root = createNode();
	root->data = *pro-'0';
	int index = findIndex(in, pro[0], n);
	root->leftNode = createTreeByProIn(pro+1, in, index);
	root->rightNode = createTreeByProIn(pro+index+1, in+index+1, n-index-1);
	return root;
}

BtNode *CreateIL(char *is,char *ls,int n)
{
	BtNode *s = NULL;
	if(n > 0)
	{
		s = createNode();
		s->data = ls[n-1];
		int pos = findIndex(is,n,ls[n-1]);
		if(pos == -1) exit(1);
		s->leftNode = CreateIL(is,ls,pos);
		s->rightNode = CreateIL(is+pos+1,ls+pos,n-pos-1);
	}
	return s;
}
BtNode * CreateTreeIL(char *is,char *ls,int n)
{
	if(is == NULL || ls == NULL || n < 1)
		return NULL;
	else
		return CreateIL(is,ls,n);
}

BtNode * CreatePI(char *ps,char *is,int n)
{
	BtNode *s = NULL;
	if(n > 0)
	{
		s = createNode();
		s->data = ps[0];
		int pos = findIndex(is,n,ps[0]);
		if(pos == -1) exit(1);
		s->leftNode = CreatePI(ps+1,is,pos);
		s->rightNode = CreatePI(ps+pos+1,is+pos+1,n-pos-1);
	}
	return s;
}
BtNode * CreateCreatePI(char *ps,char *is,int n)
{
	if(ps == NULL || is == NULL || n < 1)
		return NULL;
	else
		return CreatePI(ps,is,n);
}

//树的性质
int depth(BtNode *p)
{
	if (p != NULL)
	{
		int i = depth(p->leftNode);
		int j = depth(p->rightNode);
		return i>j?i+1:j+1;
	}
	return 0;
}

int size(BtNode *p)
{
	if (p != NULL)
	{
		return size(p->leftNode)+size(p->rightNode)+1;
	}
	return 0;
}

bool Is_Full_BinaryTree(BtNode *p)//是否为完全二叉树
{
	if (p == NULL) return false;
	double full_size = -2*(1-pow(2,depth(p)-1))+1;
	if (full_size == size(p))
	{
		return true;
	}
	return false;
}

bool Is_Full_BinaryTree2(BtNode *p)
{
	return  (p == NULL) ||
		(p->leftNode == NULL && p->rightNode == NULL) ||
		(p->leftNode != NULL && p->rightNode != NULL &&
		Is_Full_BinaryTree(p->leftNode) &&
		Is_Full_BinaryTree(p->rightNode) && 
		depth(p->leftNode) == depth(p->rightNode));
}

bool Is_Equal(BtNode *pa,BtNode *pb)
{
	return (pa == NULL && pb == NULL) ||
		(pa != NULL && pb != NULL && pa->data == pb->data &&
		Is_Equal(pa->leftNode,pb->leftNode) &&
		Is_Equal(pa->rightNode,pb->rightNode) );
}

void Destroy(BtNode *ptr)
{
	if (ptr != NULL)
	{
		Destroy(ptr->leftNode);
		Destroy(ptr->rightNode);
		free(ptr);
	}
}

BtNode * Copy(BtNode *ptr)
{
	if(ptr != NULL)
	{
		BtNode* pt = createNode();
		pt->data = ptr->data;

		pt->leftNode = Copy(ptr->leftNode);
		pt->rightNode = Copy(ptr->rightNode);
		return pt;
	}
	return NULL;
}

BtNode *findNode(BtNode * ptr, elemType value)
{
	if(ptr == NULL || ptr->data == value)
	{
		return ptr;
	}
	BtNode *tmp = findNode(ptr->leftNode, value);
	if(tmp == NULL)
	{
		tmp = findNode(ptr->rightNode, value);
	}
	return tmp;
}

static BtNode *find_pa(BtNode *root, BtNode *value)
{
	if (root == NULL || root->leftNode == value || root->rightNode == value)
	{
		return root;
	}
	else
	{
		BtNode *t = find_pa(root->leftNode, value);
		if (t == NULL)
		{
			t =  find_pa(root->rightNode, value);
		}
		return t;
	}
}

BtNode * findParent(BtNode* ptr, BtNode *value)
{
	if (value == NULL || ptr == NULL)
		return NULL;
	else if(ptr == value)//根节点没有父节点
		return ptr;
	else
		return find_pa(ptr, value);
}

BtNode * FindNearParent(BtNode *ptr, BtNode *child1,BtNode *child2);

bool Is_SubTree(BtNode *ptr,BtNode *sub);

bool Is_Comp_BinaryTree(BtNode *p);

bool Is_Balance_BinaryTree(BtNode *p);//平衡二叉树


int main()
{
	//const char *str = "12##3";
	//const char* str = "";
	const char *str = "124##5#6##3##";//+
	//const char *str = "127##4##35##6##";
	//const char *str = "124##5#67##8##3##";
	BtNode *h = createTree(str);
	//Print_K_Item(h,4);
	StkNicePastOrder(h);
	StkNiceInOrder(h);
	Destroy(h);
}
//	char *in_str = "3241657";
//	char *pro_str="1234567";
//	//BtNode *h = createTree(str);
//	BtNode *h = createTreeByProIn(pro_str, in_str, strlen(in_str));
//	//LevelOrder(head);
//	//elemType t = 5;
//
//	//BtNode *tmp = findNode(h,2);
//	//BtNode *tt = findParent(h, tmp);
//	
//	//cout<<tt->data<<endl;
//	//
//	//inScan(h);
//	//NicePastOrder(h);
//	//NicePreOrder(h);
//	//cout<<endl;
//	pastOrder(h);
//	//NiceInOrder(h);
//	//cout<<size(h)<<endl;
//	//cout<<depth(h)<<endl;
//	//if (Is_Full_BinaryTree(h))  
//	//	cout<<"yes"<<endl;
//	//putToStack(h, s);//引用的是s,将s耗尽	
//	//BtNode* p = Copy(h);
//	//proOrder(h);
//	//cout<<endl;
//	Destroy(h);
//}