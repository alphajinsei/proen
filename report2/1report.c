#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<math.h>

struct node {
    int operation;
    int number;
    struct node *left;
    struct node *right;
};

double read_number(int *pos,char *s){//posが今の位置、ctは文字数-1
    int ct=0;
    while(('0'<=s[(*pos)+ct]&&s[(*pos)+ct]<='9')||s[(*pos)+ct]=='.'){
        ct++;
    }
    ct--;
    char cuts[10];
    int i;
    for(i=0;i<=ct;i++){
        cuts[i]=s[(*pos)+i];
    }
    (*pos)=(*pos)+ct+1;
    ct=0;
    while(s[(*pos)+ct]==','||s[(*pos)+ct]==']') ct++;
    (*pos)=(*pos)+ct;
    return atof(cuts);
}

int read_operation(int *pos,char *s){
    char *Plus="Plus[";//1
    char *Times="Times[";//2
    char *Subtract="Subtract[";//3
    char *Divide="Divide[";//4
    char *Sin="Sin[";//5
    char *Cos="Cos[";//6
    char *Exp="Exp[";//7
    char *Log="Log[";//8
    char *Power="Power[";//9

    if(strncmp(Plus,s+(*pos),5)==0){
        (*pos)=(*pos)+5;
        return 1;
    }else if(strncmp(Times,s+(*pos),6)==0){
        (*pos)=(*pos)+6;
        return 2;
    }else if(strncmp(Subtract,s+(*pos),9)==0){
        (*pos)=(*pos)+9;
        return 3;
    }else if(strncmp(Divide,s+(*pos),7)==0){
        (*pos)=(*pos)+7;
        return 4;
    }else if(strncmp(Sin,s+(*pos),4)==0){
        (*pos)=(*pos)+4;
        return 5;
    }else if(strncmp(Cos,s+(*pos),4)==0){
        (*pos)=(*pos)+4;
        return 6;
    }else if(strncmp(Exp,s+(*pos),4)==0){
        (*pos)=(*pos)+4;
        return 7;
    }else if(strncmp(Log,s+(*pos),4)==0){
        (*pos)=(*pos)+4;
        return 8;
    }else if(strncmp(Power,s+(*pos),6)==0){
        (*pos)=(*pos)+6;
        return 9;
    }else{
        return 0;
    }
}

struct node *create_node(int *pos, char *s) {
    struct node *point;
    point=(struct node*)malloc(sizeof(struct node));
    if('0'<=s[*pos]&&s[*pos]<='9'){
        point->number=read_number(pos,s);
        point->operation=NULL;
        point->left=NULL;
        point->right=NULL;
    }else{
        point->operation=read_operation(pos,s);
        point->number=NULL;
        point->left=create_node(pos,s);
        if(5<=(point->operation)&&(point->operation)<=8) point->right=NULL;
        else point->right=create_node(pos,s);
    }
    return point;
}


int main() {
    char *str="Plus[Times[Sin[13.4],3],2]";
    int p = 0;
    struct node *root = create_node(&p, str);
    //traverse(root);
    //printf(" = ");
    //printf("%f\n",calculate(root));
}
