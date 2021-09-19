#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define filename_3 "../output/counting/result_3.txt"
#define filename_6 "../output/counting/result_6.txt"
#define filename_9 "../output/counting/result_9.txt"
#define filename_12 "../output/counting/result_12.txt"
#define filename_15 "../output/counting/result_15.txt"
#define filename_18 "../output/counting/result_18.txt"
#define scale_3    (int)pow(2,3)            //问题规模取 2的 3，6，9，12，15，18 次方
#define scale_6    (int)pow(2,6)
#define scale_9    (int)pow(2,9)
#define scale_12   (int)pow(2,12) 
#define scale_15   (int)pow(2,15)
#define scale_18   (int)pow(2,18)
#define RANGE  128*256       //2 的15 次方

void counting_sort(const char *filename , int SCALE){
      FILE *fp;
    if((fp=fopen("../input/input.txt", "r"))==NULL){
         printf("can't open file ../input/input.txt!\n");
         exit(0);
    }  
    int rd_num, i;    
    int *before_sort; 
    int *sort ;
    before_sort = (int*)malloc(SCALE*sizeof(int));
    sort = (int*)malloc(SCALE*sizeof(int));
    int count[RANGE] ;
    for(i = 0; i< RANGE ;i++) count[i] = 0;
    for(i = 0 ; i < SCALE ; i++){   //统计个数
        fscanf(fp,"%d",&rd_num);
        before_sort[i] = rd_num ;
        count[rd_num]++ ;
    } 
    for(i = 1 ; i < RANGE ; i++ ){
        count[i] = count[i] + count[i-1] ;
    }
    for(i = SCALE-1 ;i >= 0 ;i--){
          sort[count[before_sort[i]]-1] = before_sort[i];
          count[before_sort[i]]--;
    }
    fclose(fp); 
    // write back
    FILE *fp1 ;
    if((fp1=fopen(filename, "w+"))==NULL){
         printf("can't open %s file",filename);
         exit(0);
    }
    for(int i=0 ; i<SCALE ;i++){
        fprintf(fp1,"%d\n",sort[i]);
    }
    fclose(fp1);

}
int main (){  
    clock_t begintime , endtime ;
    double duration ;

    FILE *fp2;
    if((fp2=fopen("../output/counting/time.txt", "w+"))==NULL){
         printf("can't open file ../output/counting/time.txt");
         exit(0);
    }

    begintime = clock();    
    counting_sort(filename_3,scale_3);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^3 scale problem costs %lf s ...\n",duration );
    //run time write back
    
    begintime = clock();    
    counting_sort(filename_6,scale_6);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^6 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    counting_sort(filename_9,scale_9);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^9 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    counting_sort(filename_12,scale_12);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^12 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    counting_sort(filename_15,scale_15);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^15 scale problem costs %lf s ...\n",duration );
    //run time write back
    begintime = clock();    

    counting_sort(filename_18,scale_18);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^18 scale problem costs %lf s ...\n",duration );
    //run time write back

    fclose(fp2);
    return 0; 
}