#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<math.h>


struct node {
    int operation;
    double number;
    struct node *left;
    struct node *right;
};
double read_number(int *pos,char *s);
int read_operation(int *pos,char *s);
void print_operation(int n);
struct node *create_node(int *pos, char *s);
void traverse(struct node *p);
double calculate_number(struct node *p);
double calculate_function(struct node *p,double x);
struct node *differentiate_node(struct node *p);
struct node *copy_node(struct node *p);
struct node *substitute(struct node *p,double x);
double search(double x,struct node *df,struct node *ddf);
void number_of_x(struct node *p,int *n);
int iffunc(struct node *p);
struct node *optimise_node(struct node *p);


double read_number(int *pos,char *s){//posが今の位置、ctは文字数-1
    int ct=0;
    while(('0'<=s[(*pos)+ct]&&s[(*pos)+ct]<='9')||s[(*pos)+ct]=='.'||s[(*pos)+ct]=='x'||s[(*pos)+ct]=='-'){
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

void print_operation(int n){
    switch (n){
        case 1:
            printf("Plus[");
            break;
        case 2:
            printf("Times[");
            break;
        case 3:
            printf("Subtract[");
            break;
        case 4:
            printf("Divide[");
            break;
        case 5:
            printf("Sin[");
            break;
        case 6:
            printf("Cos[");
            break;
        case 7:
            printf("Exp[");
            break;
        case 8:
            printf("Log[");
            break;
        case 9:
            printf("Power[");
            break;
        default:
            break;
    }
}

struct node *create_node(int *pos, char *s) {
    struct node *point;
    point=(struct node*)malloc(sizeof(struct node));
    if('0'<=s[*pos]&&s[*pos]<='9'||s[*pos]=='-'){
        point->number=read_number(pos,s);
        point->operation=0;
        point->left=NULL;
        point->right=NULL;
    }else if(s[*pos]=='x'){
        point->number=read_number(pos,s);
        point->operation=10;
        point->left=NULL;
        point->right=NULL;
    }else{
        point->number=0;
        point->operation=read_operation(pos,s);
        point->left=create_node(pos,s);
        if(5<=(point->operation)&&(point->operation)<=8) point->right=NULL;
        else point->right=create_node(pos,s);
    }
    return point;
}

void traverse(struct node *p){
    if(1<=(p->operation)&&(p->operation)<=9){
        print_operation(p->operation);//cf:Plus[
        if(p->left!=NULL) traverse(p->left);
        if(p->right!=NULL) {
            printf(",");
            traverse(p->right);
        }
        printf("]");
    }else if((p->operation)==10){
        printf("x");
    }else{
        printf("%.1f",p->number);
    }
}

double calculate_number(struct node *p){
    switch (p->operation){
        case 1:
            return calculate_number(p->left)+calculate_number(p->right);
            break;
        case 2:
            return calculate_number(p->left)*calculate_number(p->right);
            break;
        case 3:
            return calculate_number(p->left)-calculate_number(p->right);
            break;
        case 4:
            return calculate_number(p->left)/calculate_number(p->right);
            break;
        case 5:
            return sin(calculate_number(p->left));
            break;
        case 6:
            return cos(calculate_number(p->left));
            break;
        case 7:
            return exp(calculate_number(p->left));
            break;
        case 8:
            return log(calculate_number(p->left));
            break;
        case 9:
            return pow(calculate_number(p->left),calculate_number(p->right));
            break;
        default:
            return p->number;
    }
}


struct node *differentiate_node(struct node *p){
        struct node *point;
        point=(struct node*)malloc(sizeof(struct node));
    if(p->operation==1){
        struct node *a=copy_node(p->left);
        struct node *b=copy_node(p->right);

        point->operation=1;
        point->left=differentiate_node(a);
        point->right=differentiate_node(b);

    }else if(p->operation==2){
        struct node *a1=copy_node(p->left);
        struct node *a2=copy_node(p->left);
        struct node *b1=copy_node(p->right);
        struct node *b2=copy_node(p->right);
        struct node *point2;
        struct node *point3;
        point2=(struct node*)malloc(sizeof(struct node));
        point3=(struct node*)malloc(sizeof(struct node));
        
        point->operation=1;
        point->left=point2;
        point->right=point3;
        
        point2->operation=2;
        point2->left=differentiate_node(a1);
        point2->right=b1;
        
        point3->operation=2;
        point3->left=a2;
        point3->right=differentiate_node(b2);

    }else if(p->operation==3){
        struct node *a=copy_node(p->left);
        struct node *b=copy_node(p->right);

        point->operation=3;
        point->left=differentiate_node(a);
        point->right=differentiate_node(b);

    }else if(p->operation==4){
        struct node *a1=copy_node(p->left);
        struct node *a2=copy_node(p->left);
        struct node *b1=copy_node(p->right);
        struct node *b2=copy_node(p->right);
        struct node *b3=copy_node(p->right);
        struct node *point2;
        struct node *point3;
        struct node *point4;
        struct node *point5;
        struct node *point6;
        point2=(struct node*)malloc(sizeof(struct node));
        point3=(struct node*)malloc(sizeof(struct node));
        point4=(struct node*)malloc(sizeof(struct node));
        point5=(struct node*)malloc(sizeof(struct node));
        point6=(struct node*)malloc(sizeof(struct node));

        point->operation=4;
        point->left=point2;
        point->right=point5;

        point2->operation=3;
        point2->left=point3;
        point2->right=point4;

        point3->operation=2;
        point3->left=differentiate_node(a1);
        point3->right=b1;

        point4->operation=2;
        point4->left=a2;
        point4->right=differentiate_node(b2);

        point5->operation=9;
        point5->left=b3;
        point5->right=point6;

        point6->operation=0;
        point6->number=2;
        point6->left=NULL;
        point6->right=NULL;

    }else if(p->operation==5){
        struct node *a1=copy_node(p->left);
        struct node *a2=copy_node(p->left);
        struct node *point2;
        point2=(struct node*)malloc(sizeof(struct node));

        point->operation=2;
        point->left=point2;
        point->right=differentiate_node(a2);

        point2->operation=6;
        point2->left=a1;
        point2->right=NULL;

    }else if(p->operation==6){
        struct node *a1=copy_node(p->left);
        struct node *a2=copy_node(p->left);
        struct node *point2;
        struct node *point3;
        struct node *point4;
        point2=(struct node*)malloc(sizeof(struct node));
        point3=(struct node*)malloc(sizeof(struct node));
        point4=(struct node*)malloc(sizeof(struct node));
        point->operation=2;
        point->left=point2;
        point->right=differentiate_node(a2);

        point2->operation=2;
        point2->left=point3;
        point2->right=point4;

        point3->operation=0;
        point3->number=-1;
        point3->left=NULL;
        point3->right=NULL;

        point4->operation=5;
        point4->left=a1;
        point4->right=NULL;

    }else if(p->operation==7){
        struct node *a1=copy_node(p->left);
        struct node *a2=copy_node(p->left);
        struct node *point2;
        point2=(struct node*)malloc(sizeof(struct node));

        point->operation=2;
        point->left=point2;
        point->right=differentiate_node(a2);

        point2->operation=7;
        point2->left=a1;
        point2->right=NULL;

    }else if(p->operation==8){
        struct node *a1=copy_node(p->left);
        struct node *a2=copy_node(p->left);

        point->operation=4;
        point->left=differentiate_node(a1);
        point->right=a2;

    }else if(p->operation==9){
        if(p->right->operation==0&&p->right->number==0){
            struct node *a1=copy_node(p->left);
            struct node *point2;
            point2=(struct node*)malloc(sizeof(struct node));

            point->operation=2;
            point->number=0;
            point->left=differentiate_node(a1);
            point->right=point2;

            point2->operation=0;
            point->number=1;
            point->left=0;
            point->right=0;

        }else if(p->right->operation==0&&p->right->number!=0){
            struct node *a1=copy_node(p->left);
            struct node *a2=copy_node(p->left);
            struct node *point2;
            struct node *point3;
            struct node *point4;
            struct node *point5;
            point2=(struct node*)malloc(sizeof(struct node));
            point3=(struct node*)malloc(sizeof(struct node));
            point4=(struct node*)malloc(sizeof(struct node));
            point5=(struct node*)malloc(sizeof(struct node));
            double n=p->right->number;

            point->operation=2;
            point->number=0;
            point->left=point2;
            point->right=differentiate_node(a2);

            point2->operation=2;
            point2->number=0;
            point2->left=point3;
            point2->right=point4;

            point3->operation=0;
            point3->number=n;
            point3->left=NULL;
            point3->right=NULL;

            point4->operation=9;
            point4->number=0;
            point4->left=a1;
            point4->right=point5;

            point5->operation=0;
            point5->number=n-1;
            point5->left=NULL;
            point5->right=NULL;
            
        }else{

        struct node *a1=copy_node(p->left);
        struct node *a2=copy_node(p->left);
        struct node *a3=copy_node(p->left);
        struct node *a4=copy_node(p->left);
        struct node *b1=copy_node(p->right);
        struct node *b2=copy_node(p->right);
        struct node *b3=copy_node(p->right);
        struct node *point2;
        struct node *point3;
        struct node *point4;
        struct node *point5;
        struct node *point6;
        struct node *point7;
        point2=(struct node*)malloc(sizeof(struct node));
        point3=(struct node*)malloc(sizeof(struct node));
        point4=(struct node*)malloc(sizeof(struct node));
        point5=(struct node*)malloc(sizeof(struct node));
        point6=(struct node*)malloc(sizeof(struct node));
        point7=(struct node*)malloc(sizeof(struct node));

        point->operation=2;
        point->left=point2;
        point->right=point3;

        point2->operation=9;
        point2->left=a1;
        point2->right=b1;

        point3->operation=1;
        point3->left=point4;
        point3->right=point6;

        point4->operation=2;
        point4->left=differentiate_node(b2);
        point4->right=point5;
        
        point5->operation=8;
        point5->left=a2;
        point5->right=NULL;

        point6->operation=2;
        point6->left=b3;
        point6->right=point7;

        point7->operation=4;
        point7->left=differentiate_node(a3);
        point7->right=a4;
        }

    }else if(p->operation==10){
        point->operation=0;
        point->number=1;
        point->left=NULL;
        point->right=NULL;
    }else{
        point->operation=0;
        point->number=0;
        point->left=NULL;
        point->right=NULL;
    }
    return point;
}

struct node *copy_node(struct node *p){
    struct node *point;
    point=(struct node*)malloc(sizeof(struct node));
    point->number=p->number;
    point->operation=p->operation;
    if(p->left==NULL){
        point->left=NULL;
    }else{
        point->left=copy_node(p->left);
    }
    if(p->right==NULL){
        point->right=NULL;
    }else{
        point->right=copy_node(p->right);
    }
}

double calculate_function(struct node *p,double x)
{
    struct node *func=substitute(p,x);
    return calculate_number(func);
}

struct node *substitute(struct node *p,double x){
    struct node *point;
    point=(struct node*)malloc(sizeof(struct node));
    if(p->operation!=10){
        point->number=p->number;
        point->operation=p->operation;
    }else if(p->operation==10){
        point->number=x;
        point->operation=0;
    }
    if(p->left==NULL){
        point->left=NULL;
    }else{
        point->left=substitute(p->left,x);
    }
    if(p->right==NULL){
        point->right=NULL;
    }else{
        point->right=substitute(p->right,x);
    }
}


double search(double x,struct node *df,struct node *ddf){
    double df_x=calculate_function(df,x);
    double ddf_x=calculate_function(ddf,x);
    if(fabs(df_x/ddf_x)<0.00001){
        return x;
    }else{
        return search(x-(df_x/ddf_x),df,ddf);
    }
}


void number_of_x(struct node *p,int *n){
    if(p->operation==10){
        (*n)++;
    }else{
        if(p->left!=NULL) number_of_x(p->left,n);
        if(p->right!=NULL) number_of_x(p->right,n);
    }
}

int iffunc(struct node *p){//iffunc==0 -> number
    int n=0;
    number_of_x(p,&n);
    int number=n;
    return number;
}

struct node *optimise_node(struct node *p){
    struct node *point;
    point=(struct node*)malloc(sizeof(struct node));
    if(iffunc(p)==0){
        point->number=calculate_number(copy_node(p));
        point->operation=0;
        point->left=NULL;
        point->right=NULL;   
    }else if(p->operation==2&&p->left->operation==0&&p->left->number==0){
        point->number=0;
        point->operation=0;
        point->left=NULL;
        point->right=NULL;
    }else{
        point->number=p->number;
        point->operation=p->operation;
        if(p->left==NULL){
            point->left=NULL;
        }else{
            point->left=optimise_node(p->left);
        }
        if(p->right==NULL){
            point->right=NULL;
        }else{
            point->right=optimise_node(p->right);
        }
    }

}

int main(int argc,char* argv[]) {
    //char *str="Plus[Times[x,3],Times[x,-1]]";
    char *str="Plus[Times[Sin[13.4],3],2]";
    //char *str="Exp[Cos[Log[Sin[x]]]]";
    //char *str="Power[x,x]";
    //char *str="Plus[Exp[Times[-1,x]],Power[x,2]]";
    //char *str="Plus[Log[Plus[1,Power[x,2]]],Power[Plus[x,1],2]]";
    //char *str="x";

    int p=0;
    struct node *f=create_node(&p,argv[1]);
    struct node *df=optimise_node(optimise_node(differentiate_node(f)));
    struct node *ddf=optimise_node(optimise_node(differentiate_node(df)));

    printf("f(x) = ");
    traverse(f);
    if(iffunc(f)==0) printf(" = %f",calculate_number(f));
    printf("\n");
    
    printf("f'(x) = ");
    traverse(df);
    printf("\n");

    printf("f''(x) = ");
    traverse(ddf);
    printf("\n");

    double x0=-3;
    double solution=search(x0,df,ddf);
    if(calculate_function(ddf,solution)<0){
        printf("f|max = f(%.5f) = %.5f\n",solution,calculate_function(f,solution));
    }else{
        printf("f|min = f(%.5f) = %.5f\n",solution,calculate_function(f,solution));

    }


    return 0;
}
