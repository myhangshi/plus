// A recursive C program to find LCA of two nodes n1 and n2.
#include <stdio.h>
#include <stdlib.h>
 
struct node
{
    int data;
    struct node* left, *right;
};
 
/* Function to find LCA of n1 and n2. The function assumes that both
   n1 and n2 are present in BST */
struct node *lca(struct node* root, int n1, int n2)
{
    struct node* result; 

    if (root == NULL) return NULL;

     if (root->data == n1 || root->data == n2) {
            //return root;
            return NULL; 
    }
 
    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->data > n1 && root->data > n2) {
        result = lca(root->left, n1, n2);
        return result ? result : root; 
    }
 
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2) {
        result = lca(root->right, n1, n2);
        return result ? result : root; 
    }
 
    return root;
}
 
/* Helper function that allocates a new node with the given data.*/
struct node* newNode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data  = data;
    node->left  = node->right = NULL;
    return(node);
}
 
/* Driver program to test lca() */
int main()
{
    // Let us construct the BST shown in the above figure
    struct node *root        = newNode(1);
    //root->left               = newNode(8);
    root->right              = newNode(2);
    root->right->right       = newNode(3);
 
    int n1 = 2, n2 = 3;
    struct node *t = lca(root, n1, n2);
    printf("LCA of %d and %d is %d \n", n1, n2, t->data);
 
    
 
    getchar();
    return 0;
}


