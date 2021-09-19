#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define SCAL_NUM 5
#define MAX_SIZE 25
#define MAX_INT 9223372036854775807
long int Matrix_chain(int scale ,long int *p ,int path[MAX_SIZE][MAX_SIZE]){
    int  first ,length ,last ,curr_break_point ;
    long int cost[MAX_SIZE][MAX_SIZE] = { 0 };
    long int q;
     for(length = 1;length < scale  ; length++){
         for ( first = 0; first < scale - length ; first++)
         {
              last = first + length;
              cost[first][last] = MAX_INT;
              for(curr_break_point = first ; curr_break_point < last ; curr_break_point++){
                   q = cost[first][curr_break_point] + cost[curr_break_point+1][last] + p[first] * p[curr_break_point+1] * p[last+1];
                   if(q < cost[first][last]) { 
                        cost[first][last] = q;
                        path[first][last] = curr_break_point ; 
                    }    
               }     
         }
    }
    //打印规模为 5 时的结果 。
    if(scale == 5){
        printf("==============规模为5时的结果 =================\n");
        for(int i = 0;i <scale ; i++){
            for(int j = 0 ;j < scale ;j++){
                printf ("%ld\t ", cost[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        for(int i = 0;i <scale ; i++){
            for(int j = 0 ;j < scale ;j++){
                printf ("%d\t ", path[i][j]);
            }
            printf("\n");
        }
    }
  
    return cost[0][scale-1] ;
}     

void print_opt_parens(FILE * fp,int path[MAX_SIZE][MAX_SIZE],int left,int right ){
    if( left == right) fprintf(fp ,"A%d", left);
    else {
        fprintf(fp ,"(");
        print_opt_parens(fp,path,left,path[left][right]);
        print_opt_parens(fp,path,path[left][right]+1 ,right);
         fprintf(fp ,")");
    }
    
}
int main(){
    //读文件到数组 
    FILE *scan_fp , *rslt_fp , *time_fp ;
    if((scan_fp=fopen("../input/2_1_input.txt", "r" )) == NULL){
          printf("can't open file ../input/2_1_input.txt!");
          exit(0);
    }
    int i, j ;
    int scale[SCAL_NUM] = { 0 } ;
    int path[MAX_SIZE][MAX_SIZE] = { 0 };
    long int p[SCAL_NUM][MAX_SIZE+1]={0} ;
    long int result ;
    clock_t begintime , endtime ;
    double duration ;
    //初始化 ，更好看。
    for(i = 0 ; i < SCAL_NUM ; i++ )
    {
        fscanf(scan_fp, "%d ", &scale[i] );
        for(int j = 0 ; j <= scale[i] ;j++)
            fscanf(scan_fp, "%ld ", &p[i][j] ); 
    }
    fclose(scan_fp);

/*
   for(i = 0; i < SCAL_NUM ;i++){
        printf ("%d ",scale[i]);
    }
    printf("\n");
    for(i = 0;i<SCAL_NUM ; i++){
        for(j = 0 ;j < MAX_SIZE+1 ;j++){
            printf ("%d ",p[i][j]);
        }
        printf("\n");
    }
 */   
    //调用 计算代价的函数 Matrix_chain 。
    if((rslt_fp=fopen("../output/result.txt", "w" )) == NULL){
          printf("can't open file ../output/reslut.txt!");
          exit(0);
    }
    if((time_fp=fopen("../output/time.txt", "w" )) == NULL){
          printf("can't open file ../output/time.txt!");
          exit(0);
    }

    for(i = 0 ;i<SCAL_NUM ;i++){

       begintime = clock();    
       result =  Matrix_chain(scale[i], p[i] , path );
       endtime = clock();
       duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
       fprintf(time_fp,"The %d scale problem costs %lf s ...\n",scale[i], duration );
       fprintf(rslt_fp,"%ld\n" ,result);
       print_opt_parens(rslt_fp,path,0,scale[i]-1);
       fprintf(rslt_fp,"\n");
    }

    fclose(rslt_fp);
    fclose(time_fp); 

    //计算结果输出
}