/*生成4种规模的图的信息，
规定图的最大权重为 1000
无环;
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE  512        //范围
#define weightrange 51
#define scale1 27
#define scale2 81
#define scale3 243
#define scale4 729
#define scale_number 4
#define deg_num 2

int main (){
    int N;
    FILE *fp;

    char filename[scale_number][deg_num][25] = {"../input/input11.txt","../input/input12.txt","../input/input21.txt","../input/input22.txt","../input/input31.txt","../input/input32.txt","../input/input41.txt","../input/input42.txt"};
    int scale[scale_number]= { scale1 ,scale2,scale3, scale4};
    int out_degree[scale_number][2] = {2,1,2,2,3,2,4,3};     //
    int enable_flag[scale4] = {0};
   
    srand((unsigned)time(NULL));
    int random0,random1 , random2 ,range , i = 0 , j ,k ,n;
    //生成第一个图
    
    for(k = 0; k<scale_number ; k++){
        for(j = 0;j<deg_num ;j++){
            if((fp=fopen(filename[k][j], "w+"))==NULL){
                printf("can't open this file");
                exit(0);
            }
            for( i = 0 ; i < scale[k]; i++){  //从每个顶点开始
                N = out_degree[k][j]; //每个顶点的出度
                for(n = 0; n < scale[k] ; n++ ){   //确定还可以链接的顶点
                    enable_flag[n] = 0   ;
                }
                while(N > 0){
                    random1 = rand() % scale[k]  ;  //先确定 到达边的顶点
                    if((enable_flag[random1] == 0) && (random1 != i)){    //非自身成环 ,无重边
                    enable_flag[random1] = 1;
                    random2 = rand() % weightrange  ; //确定边的权重
                    fprintf(fp,"%d %d %d\n",i,random1,random2);
                    N--;
                    }    
                }
                 //小于0 直接结束。
            }   
            fclose(fp);
        }    
    }
    
    return 0;
}