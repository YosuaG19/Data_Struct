#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct tree{
    int value;
    tree *right;
    tree *left;
};

void infix(tree *root){
    if (root == NULL) return;
    infix(root->left);
    printf("%d ", root->value);
    infix(root->right);
}

tree *createNode(int value){
    tree *current = (tree *)malloc(sizeof(tree));
    current->value = value;
    current->left = current->right = NULL;
    
    return current;
}

tree *Build_BST(tree *root, int value){
    if (root == NULL){
        return createNode(value);
    }
    if (root->value < value){
        root->right = Build_BST(root->right, value);
    }else if (root->value > value){
        root->left = Build_BST(root->left, value);
    }

    return root;
}

int search(tree *root, int value){
    if (root == NULL){
        return -1;
    }
    if (root->value == value){
        return 1;
    }else if (root->value < value){
        search(root->right, value);
    }else if (root->value > value){
        search(root->left, value);
    }

    return 1;
}

tree *del_node(tree *root, int value){
    if (root == NULL){
        return NULL;
    }
    if (root->value < value){
        root->right = del_node(root->right, value);
    }else if (root->value > value){
        root->left = del_node(root->left, value);
    }
    
    else if (root->value == value){
        if (root->left == NULL && root->right == NULL){
            free(root);root = NULL;
        }else if (root->left != NULL){
            tree *temp = root->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            root->value = temp->value;
            root->left = del_node(root->left, temp->value);
        }else if (root->right != NULL){
            tree *temp = root->right;
            while(temp->left != NULL){
                temp = temp->left;
            }
            root->value = temp->value;
            root->right = del_node(root->right, temp->value);
        }
    }

    return root;
}


int main(){
    tree *root = NULL;
    root = Build_BST(root, 20);
    root = Build_BST(root, 19);
    root = Build_BST(root, 16);
    root = Build_BST(root, 18);
    root = Build_BST(root, 17);

    infix(root);
    puts("");

    del_node(root, 19);
    infix(root);
}