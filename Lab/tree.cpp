#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct student{
    int id;
    student *right;
    student *left;
};

void preorder(student *root){
    if (root == NULL) return;
    puts("------------------------------------------");
    printf("Student id : %d \n", root->id);
    puts("------------------------------------------");
    preorder(root->left);
    preorder(root->right);
}

void postorder(student *root){
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    puts("------------------------------------------");
    printf("Student id : %d \n", root->id);
    puts("------------------------------------------");
}

void inorder(student *root){
    if (root == NULL) return;
    inorder(root->left);
    puts("------------------------------------------");
    printf("Student id : %d \n", root->id);
    puts("------------------------------------------");
    inorder(root->right);
}

student *search(student *root, int id){
    if (root == NULL){
        puts("Not found");
        return root;
    }
    else if (root->id == id){
        puts("Found!");
        return root;
    }
    else if (root->id < id) search(root->right, id);
    else if (root->id > id) search(root->left, id);

    return root;
}

student *create_new(int id){
    student *s_new = (student *) malloc (sizeof(student));
    s_new -> id = id;
    s_new -> left = s_new -> right = NULL;
    return s_new;
}

student *push(student *root, int id){
    // blm ada data
    if (root == NULL){
        return create_new(id);
    }
    // id curr lebih besar
    else if (id > root ->id){
        root ->right = push(root->right, id);
    }
    else{
        root -> left = push(root->left, id);
    }

    return root;
}

student *update(student *root, int id){
    if (root == NULL){
        puts("Not Found");
        return NULL;
    }
    else if(root->id == id){
        puts("Found");
        // strcpt(root->name, name);
        return root;
    }
    else if (id > root ->id){
        root ->right = update(root->right, id);
    }
    else{
        root -> left = update(root->left, id);
    }
}


int main(){
    student *root = NULL;

    root = push(root, 6);
    root = push(root, 5);
    root = push(root, 4);
    root = push(root, 3);
    root = push(root, 2);
    root = push(root, 1);

    inorder(root);

    search(root, 1);
}