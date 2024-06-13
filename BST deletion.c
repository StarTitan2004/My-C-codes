#include <stdio.h>
#include <stdlib.h>
struct node {
  int data;
  struct node *left_child;
  struct node *right_child;
};

struct node *create_node(int data) {
  struct node *new_node = (struct node *)malloc(sizeof(struct node));
  new_node->data = data;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  return new_node;
}

void insert_node(struct node *root, int data) {
  if (root == NULL) {
    root = create_node(data);
  } else {
    if (data < root->data) {
      insert_node(root->left_child, data);
    } else {
      insert_node(root->right_child, data);
    }
  }
}

void print_tree(struct node *root) {
  if (root == NULL) {
    return;
  } else {
    printf("%d ", root->data);
    print_tree(root->left_child);
    print_tree(root->right_child);
  }
}

int main() {
  struct node *root = NULL;
  int data;
	int n;
  printf("Enter the number of elements: ");
  scanf("%d", &n);
	int i;
  for (i = 0; i < n; i++) {
    printf("Enter the data: ");
    scanf("%d", &data);
    insert_node(root, data);
  }

  printf("The binary tree is: ");
  print_tree(root);

  return 0;
}





struct node* find_minimum(struct node * root) {  
  if (root == NULL)  
    return NULL;  
  else if (root->left_child != NULL)  
    return find_minimum(root->left_child);  
  return root;  
}  

struct node* delete(struct node * root, int x) {  
  
  if (root == NULL)  
    return NULL;  
  if (x > root->data)  
    root->right_child = delete(root->right_child, x);  
  else if (x < root->data)  
    root->left_child = delete(root->left_child, x);  
  else {  
    if (root->left_child == NULL && root->right_child == NULL){      //Zero child
      free(root);  
      return NULL;  
    }  
    else if (root->left_child == NULL || root->right_child == NULL){  //One child
      struct node *temp;  
      if (root->left_child == NULL)  
        temp = root->right_child;  
      else  
        temp = root->left_child;  
      free(root);  
      return temp;  
    }  
    else {  
      struct node *temp = find_minimum(root->right_child);            //Two child
      root->data = temp->data;  
      root->right_child = delete(root->right_child, temp->data);  
    }  
  }  
  return root;  
}
