#include <stdio.h>
#include <stdlib.h>
struct node {
    char value;
    struct node *left;
    struct node *right;
};
void traverse(struct node *n) {
    printf("%c",n->value);
    if(n->left!=NULL) traverse(n->left);
    if(n->right!=NULL) traverse(n->right);
}

struct node *create_node(int *pos, char *s) {
    struct node *point;
    point=(struct node*)malloc(sizeof(struct node));
    point->value=s[*pos];
    if('0'<=s[*pos]&&s[*pos]<='9'){
        point->left=NULL;
        point->right=NULL;
    }else if(s[*pos]=='+'||s[*pos]=='-'||s[*pos]=='*'||s[*pos]=='/'){
        (*pos)++;
        point->left=create_node(pos,s);
        (*pos)++;
        point->right=create_node(pos,s);
    }
    return point;
}

double calculate(struct node *n){
    if(n->value=='+'){
        return calculate(n->left)+calculate(n->right);
    }else if(n->value=='-'){
        return calculate(n->left)-calculate(n->right);
    }else if(n->value=='*'){
        return calculate(n->left)*calculate(n->right);
    }else if(n->value=='/'){
        return calculate(n->left)/calculate(n->right);
    }else
        //if('0'<=n->value&&n->value<='9')
    {
        return atof(&n->value);
    }
    
}

int main() {
    char *str = "+/9*84-*84+73"; // 22.281250
    int p = 0;
    struct node *root = create_node(&p, str);
    traverse(root);
    printf(" = ");
    printf("%f\n",calculate(root));
}
