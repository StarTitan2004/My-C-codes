#include <stdio.h>
#include <stdlib.h>


struct treenode {
	int data;
	struct treenode * left;
	struct treenode * right;
};

struct treenode * createnode (int value){
	struct treenode * node;
	node = (struct treenode *)malloc (sizeof(struct treenode));
	node -> data= value;
	node->left=NULL;
	node->right=NULL;
}

struct treenode *insert (struct treenode * root , int value) {
	if (root==NULL){
		return createnode (value);
	}	
	if(value>=root->data){
		root->right= insert(root->right, value);
	}
	else{
		root->left =insert(root->left , value);
	}
	return root;
}

void preorder (struct treenode * root){
	if(root!=NULL){
		printf("%d ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}


void Inorder (struct treenode * root){
	if(root!=NULL){
		
		Inorder(root->left);
		printf("%d ",root->data);
		Inorder(root->right);
	}
}


void postorder (struct treenode * root){
	if(root!=NULL){
		
		preorder(root->left);
		preorder(root->right);
		printf("%d ",root->data);
	}
}
int main(){
	struct treenode * root = NULL;
	root = insert(root,2);
	root=insert(root,3);
	root=insert(root,1);
	
	printf("\nInorder\n");
	Inorder(root);
	printf("\npreorder\n");
	
	preorder(root);
	
	printf("\npostorder\n");
	postorder(root);
	
}
