#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *left;
	struct node *right;
};
struct node *create(int a){
	struct node *newnode;
	newnode=(struct node *)malloc(sizeof(struct node *));
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->data=a;
};
struct node *insert_left(struct node *root,int v){
	root->left=create(v);
	return root->left;
}
struct node *insert_right(struct node *root,int v){
	root->right=create(v);
	return root->right;
}
void preorder_traversal(struct node *root){
	if(root==NULL){
		return;
	}
	printf("%d",root->data);
	preorder_traversal(root->left);
	preorder_traversal(root->right);
}

void postorder_traversal(struct node *root){
	if(root==NULL){
		return;
	}
	preorder_traversal(root->left);
	preorder_traversal(root->right);
	printf("%d",root->data);
}

void inorder_traversal(struct node *root){
	if(root==NULL){
		return;
	}
	preorder_traversal(root->left);
	printf("%d",root->data);
	preorder_traversal(root->right);
}

struct node *find_min(struct node *root){
	if (root==NULL){
		return NULL;
	}
	else if(root->left!=NULL){
		return find_min(root->left);
		return root;
	}
}

struct node *find_max(struct node *root){
	if (root==NULL){
		return NULL;
	}
	else if(root->right!=NULL){
		return find_max(root->right);
		return root;
	}
}

struct node *delete_node(struct node *root,int val){
	if (root==NULL){
		return NULL;
	}
	if(val>root->data){
		root->right=delete_node(root->right,val);
	}
	else if(val<root->data){
		root->left=delete_node(root->right,val);
	}
	else{
		if(root->left==NULL && root->right==NULL){
			free(root);
			return NULL;
		}
		else if(root->left==NULL || root->right==NULL){
			struct  node *temp;
			if(root->left==NULL){
				temp=root->right;
			}
			else{
				temp=root->left;
			}
			free(root);
			return NULL;
		}
		else{
			struct node *temp=find_min(root->right);
			root->data=temp->data;
			root->right=delete_node(root->right,temp->data);
		}
	}
	return root;
}

int main(){
	struct node *root=create(5);
	insert_left(root,1);
	insert_right(root,2);
	insert_left(root->left,7);
	insert_right(root->left,8);
	insert_left(root->right,9);
	insert_right(root->right,3);
	preorder_traversal(root);
	printf("\n");
	postorder_traversal(root);
	printf("\n");
	inorder_traversal(root);
	printf("\n");
	find_min(root);
	delete_node(root,9);
	find_max(root);
}
