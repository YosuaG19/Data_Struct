#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodes {
    char value;
    struct nodes* right;
    struct nodes* left;
};

// Function to check if a character is an operator
int is_opt(char value) {
    return (value == '+' || value == '-' || value == '*' || value == '/' || value == '^');
}

// Function to create a new node
struct nodes* createnew(char value) {
    struct nodes* curr = (struct nodes*)malloc(sizeof(struct nodes));
    curr->value = value;
    curr->left = NULL;
    curr->right = NULL;
    return curr;
}

// Function to perform preorder traversal
void prefix(struct nodes* root) {
    if (root == NULL) return;
    prefix(root->left);
    printf("%c ", root->value);
    prefix(root->right);
}

// Function to build expression tree from prefix notation
struct nodes* build_pre(char value[], int *pos) {
    if (value[*pos] == NULL) return NULL; // Base case
    
    struct nodes* root = createnew(value[*pos]);

    if (is_opt(value[*pos])) { // If operator, build left and right subtree
        (*pos)++;
        root->left = build_pre(value, pos);
        (*pos)++;
        root->right = build_pre(value, pos);
    }

    return root;
}


struct nodes* build_post(char value[], int *pos) {
    if (value[*pos] == NULL) return NULL; // Base case
    
    struct nodes* root = createnew(value[*pos]);

    if (is_opt(value[*pos])) { // If operator, build left and right subtree
        (*pos)--;
        root->right = build_post(value, pos);
        (*pos)--;
        root->left = build_post(value, pos);
    }

    return root;
}


// struct nodes* push_in(){

// }


void convert_in_post(char string[]){
    for (int i = 0 ; string[i] != NULL ; i++){
        if (is_opt(string[i])){
            char temp = string[i];
            string[i] = string[i+1];
            string[i+1] = temp;
            i++;
        }
    }
}

int main() {
    char prefeq[] = "+*234"; // Prefix expression
    struct nodes* root = NULL;
    int pos = 0;


    puts("--------------------------------------");
    root = build_pre(prefeq, &pos);
    printf("Preorder Traversal: %s\n", prefeq);
    printf("Inorder Traversal: ");
    prefix(root);
    printf("\n");


    puts("--------------------------------------");
    char posteq[] = "23*4+";
    printf("Postorder Traversal: %s\n", posteq);
    pos = strlen(posteq) -1;
    root = build_post(posteq, &pos);

    printf("Inorder Traversal: ");
    prefix(root);
    printf("\n");


    puts("--------------------------------------");
    char ineq[] = "2*3+4";
    pos = strlen(ineq) -1;
    convert_in_post(ineq);

    printf("InOrder Traversal: %s\n", ineq);
    root = build_post(ineq, &pos);
    printf(" Traversal: ");
    prefix(root);
    printf("\n");
    return 0;
}
