#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define red  1
#define black 2
#define MAX_length 30
#define del_num  3
#define serch_num  3
typedef struct INT
{
   int left;
   int right;
}INT;

typedef struct Node
{
    /* data */
    INT interval;
    int max;
    int color ; 
    struct Node * l_child;
    struct Node * r_child;
    struct Node * parent;
}Node ; 

typedef struct INT_tree
{
    /* data */
    struct Node*  root;
    struct Node*  nil;
    
} INT_tree;

void Free_malloc(INT_tree* T,Node* root ){
     if(root == T->nil){
         return;
     }
     if(root->l_child == T->nil && root->r_child == T->nil){
          free(root);
          return;
      }
      Free_malloc(T,root->l_child );
      Free_malloc(T,root->r_child) ;
      free(root);
      return ;
} 
int getmax(int a,int b){
    int max;
    max = a > b ?  a :  b ;  
    return max;
}

void INT_max_fixup(INT_tree* T , Node* Curr){
     if(Curr == T->nil) return;
     while(Curr->parent != T->nil){
         Curr->parent->max = getmax(Curr->max,Curr->parent->max);
         Curr = Curr->parent;
     }
     return ;
}
void LEFT_rotate(INT_tree* T,Node* Curr){
     Node* tmp;
     tmp = Curr->r_child; //先指向右孩子准备下来 ;
     Curr->r_child = tmp->l_child;
     if(tmp->l_child != T->nil) tmp->l_child->parent = Curr;
     tmp->parent = Curr->parent;
     if(Curr->parent == T->nil) T->root = tmp;
     else if(Curr == Curr->parent->l_child)
     {
         Curr->parent->l_child = tmp;
     }else
     {
         Curr->parent->r_child = tmp;
     }
     tmp->l_child = Curr;
     Curr->parent = tmp; 
    
    //调整max
    Curr->max = getmax(Curr->interval.right,getmax(Curr->l_child->max,Curr->r_child->max));
    tmp->max = getmax(tmp->interval.right,getmax(tmp->l_child->max,tmp->r_child->max));
}
void RIGHT_rotate(INT_tree* T,Node* Curr){
     Node* tmp;
     tmp = Curr->l_child;
     Curr->l_child = tmp->r_child;
    if(tmp->r_child != T->nil) tmp->r_child->parent = Curr;
     tmp->parent = Curr->parent;
     if(Curr->parent == T->nil) T->root = tmp;
     else if(Curr == Curr->parent->l_child)
     {
         Curr->parent->l_child = tmp;
     }else
     {
         Curr->parent->r_child = tmp;
     }
     tmp->r_child = Curr;
     Curr->parent = tmp; 
      //调整max
     Curr->max = getmax(Curr->interval.right,getmax(Curr->l_child->max,Curr->r_child->max));
     tmp->max = getmax(tmp->interval.right,getmax(tmp->l_child->max,tmp->r_child->max));
}
void INT_insert_fixup(INT_tree* T,Node* Curr){
    Node* tmp;
    if(Curr->parent->parent != T->nil){
     while (Curr->parent->color == red)
     {
        if(Curr->parent == Curr->parent->parent->l_child) //他的父辈是 他父辈的父辈的左儿子
        {
            tmp = Curr->parent->parent->r_child ;  //指向父亲的兄弟
            if(tmp->color == red){  //case1  :父亲兄弟为红  ，则转为黑
                 Curr->parent->color = black;
                 tmp->color = black;
                 Curr->parent->parent->color = red;
                 Curr = Curr->parent->parent;
             }
             else {               //父亲兄弟为黑
                if(Curr == Curr->parent->r_child)  //父亲兄弟为黑 ,此时对Curr的左右性进行分支  
                {   //case 2:  如果是 右儿子
                    Curr = Curr->parent;
                    LEFT_rotate(T,Curr); 
                }   //如果是左儿子
                Curr->parent->color = black;
                Curr->parent->parent->color = red ;
                RIGHT_rotate(T,Curr->parent->parent); 
            }   

        }
        else
        {
             tmp = Curr->parent->parent->l_child ;  //指向父亲的兄弟
            if(tmp->color == red){  //case1  :父亲兄弟为红  ，则转为黑
                 Curr->parent->color = black;
                 tmp->color = black;
                 Curr->parent->parent->color = red;
                 Curr = Curr->parent->parent;
             }
             else {               //父亲兄弟为黑
                if(Curr == Curr->parent->l_child)  //父亲兄弟为黑 ,此时对Curr的左右性进行分支  
                {   //case 2:  如果是 左儿子
                    Curr = Curr->parent;
                    RIGHT_rotate(T,Curr); 
                }   //如果是右儿子
                Curr->parent->color = black;
                Curr->parent->parent->color = red ;
                LEFT_rotate(T,Curr->parent->parent); 
            }   

        }   
    }
    }
    T->root->color = black;   
}
void INT_insert(INT_tree* T ,Node*Curr){
     Node* x;
     Node* y;
     x = T->root;
     y = T->nil;
     while (x != T->nil)  //
     {
         y = x;
         if(Curr->interval.left < x->interval.left) //小于根节点
             x = x->l_child;        
         else                   //大于根节点  
             x = x->r_child;
     }                         //此时 y 是上一个有效的 x
     Curr->parent = y ;
     if(y == T->nil) T->root = Curr; 
     else if (Curr->interval.left < y->interval.left){
         y->l_child = Curr;
        }
     else{
         y->r_child = Curr;
        }  
     Curr->l_child = T->nil;
     Curr->r_child = T->nil;
     Curr->color = red ;
     //调整 max
     INT_max_fixup(T,Curr);

     INT_insert_fixup(T,Curr);
}

Node* Tree_minnum(INT_tree* T , Node *root){
     Node* tmp;
     if(root->l_child == T->nil || root == T->nil) return root;
     tmp = root;
     while (tmp->l_child != T->nil)
     {
         tmp = tmp->l_child;
     }
     return  tmp;
}
void INT_del_fixup(INT_tree* T ,Node* Curr){
    Node* tmp;
      while (Curr != T->root && Curr->color == black) 
      {
         if(Curr == Curr->parent->l_child){
            tmp = Curr->parent->r_child;
            if(tmp->color == red){
                tmp->color = black;
                Curr->parent->color = red;
                LEFT_rotate(T,Curr->parent);
                tmp = Curr->parent->r_child;
            }
            if(tmp->l_child->color == black && tmp->r_child->color == black){
                tmp->color = red;
                Curr = Curr->parent;
            }else {
                if(tmp->r_child->color == black){
                    tmp->l_child->color = black;
                    tmp->color = red;
                    RIGHT_rotate(T,tmp);
                    tmp = Curr->parent->r_child;
                }
                tmp->color = Curr->parent->color;
                Curr->parent->color = black;
                tmp->r_child->color = black;
                LEFT_rotate(T,Curr->parent);
                Curr = T->root;  //结束标志;
            }
         }else
         {
            tmp = Curr->parent->l_child;
            if(tmp->color == red){
                tmp->color = black;
                Curr->parent->color = red;
                RIGHT_rotate(T,Curr->parent);
                tmp = Curr->parent->l_child;
            }
            if(tmp->r_child->color == black && tmp->l_child->color == black){
                tmp->color = red;
                Curr = Curr->parent;
            }else {
                if(tmp->l_child->color == black){
                    tmp->r_child->color = black;
                    tmp->color = red;
                    LEFT_rotate(T,tmp);
                    tmp = Curr->parent->l_child;
                }
                tmp->color = Curr->parent->color;
                Curr->parent->color = black;
                tmp->l_child->color = black;
                RIGHT_rotate(T,Curr->parent);
                Curr = T->root;  //技术标志;
            }            
         }
      }
      Curr->color = black; 
}
void INT_delete(INT_tree* T , Node* Curr){
      Node* del_storage;
      Node* tmp;
      int del_origin_color ;
     
      if(Curr->l_child == T->nil || Curr->r_child == T->nil){
          del_storage = Curr;
      }else
      {
          del_storage = Tree_minnum(T,Curr->r_child);
      }
      if(del_storage->l_child != T->nil){
          tmp = del_storage->l_child;
      }else
      {
          tmp = del_storage->r_child;
      }
      tmp->parent = del_storage->parent;
      if(del_storage->parent == T->nil){
           T->root = tmp ;
      }else
      {
           if(del_storage == del_storage->parent->l_child) del_storage->parent->l_child = tmp ;
           else del_storage->parent->r_child = tmp;  
      }
      if(del_storage != Curr){
          Curr->interval.left = del_storage->interval.left;
          Curr->interval.right = del_storage->interval.right;
          Curr->max = getmax(del_storage->interval.right,getmax(Curr->l_child->max,Curr->r_child->max));
      }
       //调整 max
     INT_max_fixup(T,tmp);
      if(del_storage->color == black){
          INT_del_fixup(T,tmp);
      }
      
}
Node* Serch_num(INT_tree* T, Node* root,int key){
      Node* FIND;
      if(root == T->nil) return T->nil;
      if(root->interval.left > key){ //小于根 ;
          FIND = Serch_num(T,root->l_child,key);
          return FIND;
      }else
      if(root->interval.left < key){ //大于根 ;
          FIND = Serch_num(T,root->r_child,key);
          return FIND;
      }
      else
      {
          return root;
      }
}

Node* INT_serch(INT_tree*T, Node* root ,int left ,int right){
     Node* tmp ;
     tmp = root ;
     while(tmp != T->nil &&  (tmp->interval.right < left || tmp->interval.left > right)){
         if(tmp->l_child != T->nil && tmp->l_child->max >= left){
             tmp = tmp->l_child;
         } 
         else
         {
             tmp = tmp->r_child;
         }
     }
     return tmp;
}

void in_order_trvl(FILE* fp,INT_tree* T,  Node* root ){
      if(root == T->nil) return;
      if(root->l_child == T->nil && root->r_child == T->nil ){
          fprintf(fp,"%d  %d   %d\n",root->interval.left,root->interval.right,root->max);
          return;
      }
      in_order_trvl(fp,T,root->l_child);
          fprintf(fp,"%d  %d   %d\n",root->interval.left,root->interval.right,root->max);
//      fprintf(fp,"%d  ",root->interval.left);
      in_order_trvl(fp,T,root->r_child);
      return;
}
/*
void pre_order_trvl(INT_tree* T,  Node* root ){
      if(root == T->nil) return;
      if(root->l_child == T->nil && root->r_child == T->nil ){
          printf("%d  %d   %d\n",root->interval.left,root->interval.right,root->max);
          return;
      }  
      printf("%d  %d   %d\n",root->interval.left,root->interval.right,root->max);
      pre_order_trvl(T,root->l_child);  
//     fprintf(fp,"%d  ",root->interval.left);
      pre_order_trvl(T,root->r_child);
      return;
}
*/
INT_tree* creat_INT(int scale ,int data[MAX_length][2]){  
   INT_tree *T;
   Node *Curr ;
   T = (INT_tree*)malloc(sizeof(INT_tree));
   Node NIL;
   NIL.color = black;
   NIL.l_child = &NIL;
   NIL.r_child = &NIL;
   NIL.max = -1;
   T->nil = &NIL  ;
   T->root = T->nil ; //初始化一颗红黑树
   int i =0;
   for(i = 0 ; i < scale ;i++ ){
        //创建结点 ;
        Curr =(Node *) malloc(sizeof(Node));
        Curr->interval.left = data[i][0];
        Curr->interval.right = data[i][1];
        Curr->max = data[i][1];
        //插入;
        INT_insert(T, Curr);
   }
   return T;
}
int main(){
    /*读取数据*/
    FILE *scan_fp , *rslt_fp , *serch_fp ,*dele_fp;
    if((scan_fp = fopen("../input/input.txt", "r" )) == NULL){
          printf("can't open file ../input/input.txt!");
          exit(0);
    }
    INT_tree* T;
     Node* del_node;
     Node* serch_node;
    int data[MAX_length][2] = {0}; 
    int duplicate_flag[MAX_length] = {0};
    int del_ith[del_num] = {0};
    int serch_int[serch_num][2];
    int i , j ,random;
    for(i = 0 ; i < MAX_length ; i++ )
    {
        fscanf(scan_fp, "%d", &data[i][0]);
        fscanf(scan_fp, "%d", &data[i][1]); 
    }
    fclose(scan_fp);

/*      
        for(j = 0 ;j < MAX_length ;j++){
            printf ("%d  %d\n",data[j][0],data[j][1]);
        }
*/ 
    if((rslt_fp=fopen("../output/inorder.txt", "w" )) == NULL){
          printf("can't open file ../output/reslut.txt!");
          exit(0);
    } 
    if((dele_fp=fopen("../output/delete_data.txt", "w" )) == NULL){
          printf("can't open file ../output/delete_data.txt!");
          exit(0);
    }
    if((serch_fp=fopen("../output/search.txt", "w" )) == NULL){
          printf("can't open file ../output/search.txt!");
          exit(0);
    }

    T = creat_INT(MAX_length,data);
    in_order_trvl( rslt_fp, T,T->root);
//    pre_order_trvl(T,T->root);

    //产生删除的 序列号 
    srand((unsigned)time(NULL)); //种一个伪随机种子。
    for (j = 0; j < MAX_length; j++) { duplicate_flag[j] = 0 ;}
    fprintf(dele_fp,"随机删除的数据为: \n");
    j = 0;
    while(j < del_num){
            random = rand() % MAX_length ;
            if(duplicate_flag[random]==0 ){ //不重复
              duplicate_flag[random] = 1;
              del_ith[j] = random ;
              fprintf(dele_fp,"%d  %d\n",data[random][0],data[random][1]);
              j++;
            }
    }
    for(j = 0; j < del_num ;j++){
        del_node = Serch_num(T,T->root,data[del_ith[j]][0]); 
        INT_delete(T,del_node);
    }
    fprintf(dele_fp,"删除后中序遍历的结果为: \n");
    in_order_trvl(dele_fp,T,T->root);

    //  搜索区间 。 
    int random1 ,random2;
    random1 = 26 + rand()%3;
    random2 = random1 + 1 + rand()% (29 - random1);
    serch_int[0][0] = random1;
    serch_int[0][1] = random2;
    for(j = 1 ; j < serch_num ; j++){
        random1 = rand()%100;
        random2 = random1 + 1 + rand()%(100-random1); 
        serch_int[j][0] = random1;
        serch_int[j][1] = random2;
    }    
   
   fprintf(serch_fp,"搜索的区间为 :  \n"); 
   for( j = 0 ; j < serch_num ; j++){
       fprintf(serch_fp,"%d  %d \n",serch_int[j][0],serch_int[j][1]);
   }
   fprintf(serch_fp,"搜索的结果为 :  \n"); 
    for(j = 0; j < serch_num ; j++){
      serch_node = INT_serch(T,T->root,serch_int[j][0],serch_int[j][1]);
 //     printf("%d   %d  \n",serch_int[j][0],serch_int[j][1]);
      if(serch_node == T->nil) fprintf(serch_fp,"Null \n");
      else
      {
          fprintf(serch_fp,"%d  %d\n",serch_node->interval.left,serch_node->interval.right);
      }  
    }

    Free_malloc(T,T->root); 
    free(T);
    fclose(rslt_fp);
    fclose(dele_fp);
    fclose(serch_fp);
    return 0;
}