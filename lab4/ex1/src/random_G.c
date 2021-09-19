/*生成4种规模的图的信息，
规定图的最大权重为 1000
无环;
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE  512        //范围
#define weightrange 20
#define scale1 8
#define scale2 64
#define scale3 128
#define scale4 512
#define scale_number 4
int main (){
    int N;
    FILE *fp;
    int gene_new = 0;
    char filename[scale_number][20] = {"../input/input1.txt","../input/input2.txt","../input/input3.txt","../input/input4.txt"};
    int scale[scale_number]= { scale1 ,scale2,scale3, scale4};
    int degree[scale_number][scale4] = {0};     //
    int weight[scale_number][scale4][scale4] = { 0 };//
    int enable_flag[scale4] = { 0 };                 //可以生成的标志
    srand((unsigned)time(NULL));
    int random0,random1 , random2 ,range , i = 0 , j ,k;
    //生成第一个图
    
    for(k = 0; k<scale_number ; k++){
        if((fp=fopen(filename[k], "w+"))==NULL){
            printf("can't open this file");
            exit(0);
        }
    
    N = scale[k] / 2;
    for( i = 0 ; i < scale[k]; i++){
        for(j = 0; j < scale[k] ; j++ ){   //确定还可以链接的顶点
            enable_flag[j] = !(( weight[k][i][j] == 0 )&&(degree[k][j] < N)&&( j!=i )) ;
        }
        random0 = 1 + rand() % N;    //随机生成几条边 , 也就是度数
        gene_new = random0 - degree[k][i] ;  //减去之前以已连接的度数。
        while(gene_new > 0){
            random1 = rand() % scale[k]  ;  //先确定 边的顶点
            if(enable_flag[random1] == 0){  //random1 可以生成，
               enable_flag[random1] = 1; 
               random2 = 1 + rand() % weightrange  ; //确定边的权重
               fprintf(fp,"%d %d %d\n",i,random1,random2);
               weight[k][i][random1] = random2;
               weight[k][random1][i] = random2;
               degree[k][random1]++ ;
               degree[k][i]++ ;
               gene_new-- ;
            }    
        }
         //小于0 直接结束。
    }
/*    fprintf(fp,"%d\n",scale[k]);
    for(i = 0;i < scale[k] ; i++){
        fprintf(fp,"%d,%d  ",i,degree[k][i]);
        for(j = 0 ;j < scale[k]; j++){
           if(weight[k][i][j] != 0){
               fprintf(fp,"%d,%d ",j,weight[k][i][j]);
           }
        }
        fprintf(fp,"\n");
    }
*/    
    fclose(fp);
    }
    
    return 0;
}