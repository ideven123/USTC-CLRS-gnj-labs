#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define SCAL_NUM 6
#define MAX_SIZE 256
#define MAX_INT 9223372036854775807
#define PI 3.1415926535
/*为使用蝴蝶操作 ，先做必要的 二进制 逆序*/
void bit_reverse_copy(int scale ,double *a,double *rev_a ){
     int i ,ith , last_bit ,left_bit, ex_scal = 0;
     int rev[MAX_SIZE]={0};
     left_bit = scale;
     while(left_bit > 1){
         ex_scal++;
         left_bit /=2; 
     }
     
     left_bit = ith;
     for( ith = 0;ith < scale ;ith++){
     left_bit = ith;
     for(i = 0;i <ex_scal ;i++){  //计算ith的 逆序写到rev ith
        
         last_bit = left_bit & 1;
         rev[ith] += last_bit * pow(2,(ex_scal-i-1));
         left_bit = left_bit >> 1;
     }
     rev_a[rev[ith]] = a[ith] ;
     }
}
/*针对是2的整数次幂的FFT算法*/
void FFT(int scale ,double *coef, double *rev_coef){     
    double  rev_coef_i[MAX_SIZE] = {0};
    int tmp ,ex_scal = 0,s,m , k ,j;
    double wm_r ,wm_i ,w_r ,w_i , t_r ,t_i ,u_r ,u_i ,tmp_r,tmp_i;
     bit_reverse_copy(scale, coef,rev_coef);
     tmp = scale;
     while(tmp > 1){
         ex_scal++;
         tmp /=2; 
     }
//     printf("%d" ,ex_scal);
     for(s = 1 ; s <= ex_scal ;s++ ){
         m = pow(2,s);
         wm_r = cos(2*PI/m);
         wm_i = sin(2*PI/m);
         for(k = 0 ; k < scale ; k = k + m){
            w_r = 1;
            w_i = 0;
            for( j = 0 ; j < m/2 ; j++){
                t_r = w_r * rev_coef[k+j+m/2] - w_i*rev_coef_i[k+j+m/2] ;
                t_i = w_r * rev_coef_i[k+j+m/2] + w_i*rev_coef[k+j+m/2] ;

                u_r = rev_coef[k+j];
                u_i = rev_coef_i[k+j];

                rev_coef[k+j] = t_r + u_r;
                rev_coef_i[k+j] = t_i + u_i ;

                rev_coef[k+j+m/2] = u_r - t_r;
                rev_coef_i[k+j+m/2] = u_i - t_i ;
  
                tmp_r = w_r*wm_r - w_i*wm_i ; 
                tmp_i = w_r*wm_i + w_i*wm_r ; 
                w_r = tmp_r;
                w_i = tmp_i;             
            }
         }
     }
}
int main(){
 FILE *scan_fp , *rslt_fp , *time_fp ;
    if((scan_fp=fopen("../input/2_2_input.txt", "r" )) == NULL){
          printf("can't open file ../input/2_2_input.txt!");
          exit(0);
    }
    int i, j ;
    int scale[SCAL_NUM] = { 0 } ;
    double p[SCAL_NUM][MAX_SIZE]={0} ;
    double rev_coef[MAX_SIZE];
    clock_t begintime , endtime ;
    double duration ;
    //初始化 ，更好看。
    for(i = 0 ; i < SCAL_NUM ; i++ )
    {
        fscanf(scan_fp, "%d", &scale[i] );
        for(int j = 0 ; j < scale[i] ;j++)
            fscanf(scan_fp, "%lf", &p[i][j] ); 
    }
    fclose(scan_fp);

    //调用 输出
    if((rslt_fp=fopen("../output/result.txt", "w" )) == NULL){
          printf("can't open file ../output/reslut.txt!");
          exit(0);
    }
    if((time_fp=fopen("../output/time.txt", "w" )) == NULL){
          printf("can't open file ../output/time.txt!");
          exit(0);
    }


    for(i = 0 ;i <SCAL_NUM  ;i++){

       begintime = clock();    

       FFT(scale[i], p[i] ,rev_coef);
       if(i == 0){
           for(j=0 ; j < 8 ;j++){
               printf("%6lf \t" ,rev_coef[j]);
           }
       }

       endtime = clock();
       duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
       fprintf(time_fp,"The %d scale problem costs %lf s ...\n",scale[i], duration );       
       
       for(j = 0;j < scale[i] ;j++){
            fprintf(rslt_fp,"%6lf  " , rev_coef[j] );
       }
       fprintf(rslt_fp,"\n");
    }

    fclose(rslt_fp);
    fclose(time_fp); 

/*   测试bit_reverse
    int rev[MAX_SIZE] = { 0 } ;
    bit_reverse_copy(scale[0], p[0] ,rev);
    for(j = 0 ;j < MAX_SIZE ;j++){
            printf ("%d ",rev[j]);
        }
*/
/*   测试 fscanf 。
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
    
    return 0;
}
