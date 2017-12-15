#include<string>

using namespace std;

struct Data
{
	string name;
	string address;
	unsigned salary;
};

class Node
{
	public:
		Data info;
		Node* right;
		Node* left;
		Node(){right=left=NULL;};
		Node(Data in){info=in;right=left=NULL;};

	private:
};

class tree
{
	public:
	void insert(Data);
	void printtree();
	tree(){root=NULL;};

	private:
	Node* root;
	void insert(Node*&,Data);
	void printtree(Node*);
};

//public
void tree::insert(Data in)
{
	insert(root,in);
}

void tree::printtree()
{
	printtree(root);
}

//private
void tree::insert(Node*& n,Data in)
{
	if(n==NULL)
		n=new Node(in);
	if(in.name>n->info.name)
		insert(n->right,in);
	if(in.name<n->info.name)
		insert(n->left,in);
}

void tree::printtree(Node* n)
{
	if(n!=NULL)
	{
		printtree(n->left);
		cout<<n->info.name<<endl;
		cout<<n->info.address<<endl;
		cout<<n->info.salary<<endl;
		printtree(n->right);
	}
	return;
}
