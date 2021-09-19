#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define SCALE_NUM 5
#define MAX_length 100
#define red  1
#define black 2

typedef struct RB_tree
{
    /* data */
    struct Node*  root;
    struct Node*  nil;
    
} RB_tree;

typedef struct Node
{
    /* data */
    int key ;
    int color ; 
    struct Node * l_child;
    struct Node * r_child;
    struct Node * parent;
}Node ; 

void LEFT_rotate(RB_tree* T,Node* Curr){
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
}
void RIGHT_rotate(RB_tree* T,Node* Curr){
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
}
void in_order_trvl(FILE* fp,RB_tree* T,  Node* root ){
      if(root == T->nil) return;
      if(root->l_child == T->nil && root->r_child == T->nil ){
          fprintf(fp,"%d  ",root->key);
          return;
      }
      in_order_trvl(fp,T,root->l_child);
      fprintf(fp,"%d  ",root->key);
      in_order_trvl(fp,T,root->r_child);
      return;
}
void Free_malloc(RB_tree* T,Node* root ){
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
void RB_insert_fixup(RB_tree* T,Node* Curr){
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
void RB_insert(RB_tree* T,Node* Curr){
     Node* x;
     Node* y;
     x = T->root;
     y = T->nil;
     while (x != T->nil)  //
     {
         y = x;
         if(Curr->key < x->key) //小于根节点
             x = x->l_child;        
         else                   //大于根节点  
             x = x->r_child;
     }                         //此时 y 是上一个有效的 x
     Curr->parent = y ;
     if(y == T->nil) T->root = Curr; 
     else if (Curr->key < y->key){
         y->l_child = Curr;
        }
     else{
         y->r_child = Curr;
        }  
     Curr->l_child = T->nil;
     Curr->r_child = T->nil;
     Curr->color = red ;
     RB_insert_fixup(T,Curr);
     
}

Node* Tree_minnum(RB_tree* T , Node *root){
     Node* tmp;
     if(root->l_child == T->nil || root == T->nil) return root;
     tmp = root;
     while (tmp->l_child != T->nil)
     {
         tmp = tmp->l_child;
     }
     return  tmp;
}
void RB_transplant(RB_tree* T ,Node* u ,Node* v){ //无左右孩子信息更改 。
     if(u->parent == T->nil) T->root = v;
     else if (u == u->parent->l_child)
     {
         u->parent->l_child = v;
     }else  u->parent->r_child = v ;
     v->parent = u->parent;   
} 
void RB_del_fixup(RB_tree* T ,Node* Curr){
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
void RB_delete(RB_tree* T , Node* Curr){
      Node* del_storage;
      Node* tmp;
      int del_origin_color ;
      /* 
      有问题的 delete
      del_storage = Curr;
      del_origin_color =  del_storage->color;
      if(Curr->l_child == T->nil ){   //左儿子为nil
           tmp = Curr->r_child;
           RB_transplant(T , Curr ,Curr->r_child); 
      }else if (Curr->r_child == T->nil)    //右儿子为 nil
      {
           tmp = Curr->l_child;
           RB_transplant(T,Curr,Curr->l_child);
      }else
      {
         del_storage = Tree_minnum(T,Curr->r_child);
//         printf("%d  ",del_storage->key);
         del_origin_color = del_storage->color ;
         tmp = del_storage->r_child;
         if(del_storage->parent == Curr) tmp->parent = del_storage;  //有用？
         else
         {
            RB_transplant(T,del_storage,del_storage->r_child);
            //用y  替换  z;
            del_storage->r_child = Curr->r_child;
            del_storage->r_child->parent = del_storage;
         }
         RB_transplant(T,Curr,del_storage);
         del_storage->l_child = Curr->l_child;
         del_storage->l_child->parent = Curr;
         del_storage->color = Curr->color;
      }
      */
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
          Curr->key = del_storage->key;
      }
      if(del_storage->color == black){
          RB_del_fixup(T,tmp);
      }
      
}

RB_tree* creat_RB(int scale ,int *data){  
   RB_tree *T;
   Node *Curr ;
   T = (RB_tree*)malloc(sizeof(RB_tree));
   Node NIL;
   NIL.color = black;
   NIL.l_child = &NIL;
   NIL.r_child = &NIL;
   T->nil = &NIL  ;
   T->root = T->nil ; //初始化一颗红黑树

   int i =0;
  
   for(i = 0 ; i < scale ;i++ ){
        //创建结点 ;
        Curr =(Node *) malloc(sizeof(Node));
        Curr->key = data[i];
        //插入;
        RB_insert(T, Curr);
   }
   return T;
}

Node* Serch_num(RB_tree* T, Node* root,int key){
      Node* FIND;
      if(root == T->nil) return T->nil;
      if(root->key > key){ //小于根 ;
          FIND = Serch_num(T,root->l_child,key);
          return FIND;
      }else
      if(root->key < key){ //大于根 ;
          FIND = Serch_num(T,root->r_child,key);
          return FIND;
      }
      else
      {
          return root;
      }
}

int main(){
    /*读取数据*/
    FILE *scan_fp , *rslt_fp , *time1_fp ,*time2_fp ,*dele_fp;
    if((scan_fp = fopen("../input/input.txt", "r" )) == NULL){
          printf("can't open file ../input/input.txt!");
          exit(0);
    }
    RB_tree *T;
    Node* del_node;
    int i, j ,random;
    int duplicate_flag[MAX_length] = {0};
    int delete_data[MAX_length/4] = {0};
    int scale_ith;
    int given_scale[SCALE_NUM]={20,40,60,80,100};  //存入给定规模
    int data[SCALE_NUM][MAX_length]={0};
    clock_t begintime , endtime ;
    double duration ;
    //初始化 ，更好看。
    for(scale_ith = 0 ;scale_ith<SCALE_NUM ;scale_ith++){
        for(i = 0 ; i < given_scale[scale_ith] ; i++ )
        {
                fscanf(scan_fp, "%d", &data[scale_ith][i]); 
        }
    }
    fclose(scan_fp);

/* 
    for(i = 0;i< SCALE_NUM ; i++){
        for(j = 0 ;j < given_scale[i] ;j++){
            printf ("%d ",data[i][j]);
        }
        printf("\n");
    }
*/
   
    if((rslt_fp=fopen("../output/inorder.txt", "w" )) == NULL){
          printf("can't open file ../output/reslut.txt!");
          exit(0);
    }
    if((time1_fp=fopen("../output/time1.txt", "w" )) == NULL){
          printf("can't open file ../output/time.txt!");
          exit(0);
    }
    if((dele_fp=fopen("../output/delete_data.txt", "w" )) == NULL){
          printf("can't open file ../output/delete_data.txt!");
          exit(0);
    }
    if((time2_fp=fopen("../output/time2.txt", "w" )) == NULL){
          printf("can't open file ../output/time2.txt!");
          exit(0);
    }

   
    srand((unsigned)time(NULL)); //种一个伪随机种子。
 
    for(i = 0 ;i < SCALE_NUM ;i++){
      
       begintime = clock();    
       T = creat_RB(given_scale[i],data[i]);
       endtime = clock();
       duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
       fprintf(time1_fp,"The %d scale problem creat RB_tree costs %lf s ...\n",given_scale[i], duration );
      
       in_order_trvl(rslt_fp, T ,T->root);
       fprintf(rslt_fp,"\n");

       //产生 n/4 个随机删除 的数据的 次序
       
       for (j = 0; j < MAX_length; j++){ duplicate_flag[j] = 0 ;}
       j = 0;
       fprintf(dele_fp,"规模为 %d 的问题 ,随机删除的数据为: ",given_scale[i]);
       while(j < given_scale[i]/4){
            random = rand() % given_scale[i]  ;
            if(duplicate_flag[random]==0 ){ //不重复
              duplicate_flag[random] = 1;
              delete_data[j] = data[i][random];
              fprintf(dele_fp,"%d ",delete_data[j]);
              j++;
            }
        }

         begintime = clock();    
        //删除结点 
        for(j = 0 ;j<given_scale[i]/4 ;j++){
            del_node = Serch_num(T,T->root,delete_data[j]);
//           fprintf(dele_fp,"%p   , %d   .",del_node,del_node->key);
            RB_delete(T,del_node);
        }   

        endtime = clock();
        duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
        fprintf(time2_fp,"The %d scale problem delete N/4 RB_tree randomly costs %lf s ...\n",given_scale[i], duration );
        
         fprintf(dele_fp,"\n删除后中序遍历的结果为: ");
         in_order_trvl(dele_fp,T,T->root);
         fprintf(dele_fp,"\n");
         Free_malloc(T,T->root); 
     
    }
    
    free(T);
    fclose(rslt_fp);
    fclose(time1_fp); 
    fclose(dele_fp);
    fclose(time2_fp);
    return 0;
}