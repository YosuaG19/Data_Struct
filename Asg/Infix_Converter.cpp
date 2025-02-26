#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct nodes{
    char value;
    nodes* right;
    nodes* left;
};


int evaluate(nodes* root){
    if(root->value == '+'){
        return evaluate(root->left) + evaluate(root->right);
    }
    else if(root->value == '-'){
        return evaluate(root->left) - evaluate(root->right);
    }
    else if(root->value == '*'){
        return evaluate(root->left) * evaluate(root->right);
    }
    else if(root->value == '/'){
        return evaluate(root->left) / evaluate(root->right);
    }
    else if(root->value == '^'){
        return (int) pow(evaluate(root->left), evaluate(root->right));
    }
    else{
        return root->value - '0';
    }
}

int value_converter(char eq){
    int value;
    
    if (eq == '^') value = 3;
    if (eq == '/' || eq == '*') value = 2;
    if (eq == '+' || eq == '-') value = 1;

    return value;
}

int is_opt(char eq) {
    return (eq == '+' || eq == '-' || eq == '*' || eq == '/' || eq == '^');
}

void prefix(struct nodes* root) {
    if (root == NULL) return;
    if (is_opt(root->value)) printf("(");
    prefix(root->left);
    printf("%c ", root->value);
    prefix(root->right);
    if (is_opt(root->value)) printf(")");
}

int search_root(char eq[], int start, int end){
    int index_t = strlen(eq), value_t = 10;
    // int index_t = 1000, value_t = 10;

    int index_n, value_n;
    if (end == start) return start;

    for (int i = start ; i >= end ; i--){
    // for (int i = start ; i >= end ; i--){   
        if (is_opt(eq[i])) {
            index_n = i, value_n = value_converter(eq[i]);
            // if (index_n < index_t && value_n <= value_t){
            if (index_n < index_t && value_n < value_t){
                index_t = index_n, value_t = value_n;
            }
        }
    }
    return index_t;
}

struct nodes* createnew(char value){
    nodes *curr = (nodes*) malloc (sizeof(nodes));
    curr->value = value;
    curr->left = curr->right = NULL;
    return curr;
}

struct nodes *push(char eq[], int max, int start){
    int mid = search_root(eq, max, start);
    if (mid < start || mid > max) return NULL;
    struct nodes* root =  createnew(eq[mid]);
    printf("%c ", root->value);
    
    root->left = push(eq, mid-1, start);
    root->right = push(eq, max, mid+1);
    return root;
}


int main(){
    char eq[] = "8*3-5^3/5";
    nodes* root = NULL;
    int max = strlen(eq)-1;
    // printf("%c",search_root(eq));
    printf("PostFix Notation : ");
    root =  push(eq, max, 0);
    puts("");

    printf("InFix Notation : ");
    prefix(root);
    puts("");

    printf("Evaluate : %d\n", evaluate(root));
}