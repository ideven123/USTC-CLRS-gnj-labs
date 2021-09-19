#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define filename_3  "../output/quick/result_3.txt"
#define filename_6  "../output/quick/result_6.txt"
#define filename_9  "../output/quick/result_9.txt"
#define filename_12 "../output/quick/result_12.txt"
#define filename_15 "../output/quick/result_15.txt"
#define filename_18 "../output/quick/result_18.txt"
#define scale_3    (int)pow(2,3)            //问题规模取 2的 3，6，9，12，15，18 次方
#define scale_6    (int)pow(2,6)
#define scale_9    (int)pow(2,9)
#define scale_12   (int)pow(2,12)
#define scale_15   (int)pow(2,15)
#define scale_18   (int)pow(2,18)
int partition(int A[] ,int p,int r){
    int  can ,tmp ,left_part;
    left_part = p - 1;
    can = A[r];
    for(int j = p ; j < r ; j++){     //寻找 划分的位置
        if(A[j]<= can){
             left_part = left_part + 1;
             tmp = A[left_part];
             A[left_part] = A[j];
             A[j] = tmp ;
        }         
    }
    A[r] = A[left_part + 1];
    A[left_part+1] = can ;
    return left_part + 1 ;
}
void quick(int A[],int p,int r){
    int q;
    if(p<r){
        q = partition(A,p,r);
        quick(A,p,q-1);
        quick(A,q+1,r);
    } 
    return ;       
}
void quick_sort(const char *filename ,int SCALE,double *t){
   
    clock_t begintime , endtime ;
    double duration ;
    FILE *fp;
    begintime = clock();  

    if((fp=fopen("../input/input.txt", "r"))==NULL){
         printf("can't open file ../input/input.txt!\n");
         exit(0);
    }     
    int *sort;
    sort = (int*)malloc(SCALE*sizeof(int));
    for(int i=0;i<SCALE ;i++){
        fscanf(fp,"%d", &sort[i]);
    }
    quick(sort,0,SCALE-1);
    fclose(fp); 

    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    *t = duration;

    // write back
    FILE *fp1 ;
    if((fp1=fopen(filename, "w+"))==NULL){
         printf("can't open %s file",filename);
         exit(0);
    }
    for(int i=0 ; i<SCALE ;i++){
        fprintf(fp1,"%d\n",sort[i]);
    }
    free(sort);

    fclose(fp1);
}
int main(){
    
    clock_t begintime , endtime ;
    
    double duration ;
    double *t ;
    t = &duration;
    
    FILE *fp2;
    if((fp2=fopen("../output/quick/time.txt", "w+"))==NULL){
         printf("can't open file ../output/quick/time.txt");
         exit(0);
    }


    quick_sort(filename_3,scale_3,t); 
    fprintf(fp2,"The 2^3 scale problem costs %lf s ...\n",duration );
    //run time write back
        
    quick_sort(filename_6,scale_6,t);
     fprintf(fp2,"The 2^6 scale problem costs %lf s ...\n",duration );
    //run time write back
   
    quick_sort(filename_9,scale_9,t);
     fprintf(fp2,"The 2^9 scale problem costs %lf s ...\n",duration );
    //run time write back

    quick_sort(filename_12,scale_12,t);
    fprintf(fp2,"The 2^12 scale problem costs %lf s ...\n",duration );
    //run time write back

    quick_sort(filename_15,scale_15,t);
    fprintf(fp2,"The 2^15 scale problem costs %lf s ...\n",duration );
    //run time write back
    
    quick_sort(filename_18,scale_18,t);
    fprintf(fp2,"The 2^18 scale problem costs %lf s ...\n",duration );
    //run time write back

    fclose(fp2);
    return 0; 
}

/* 
    begintime = clock();    
    quick_sort(filename_3,scale_3,t);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^3 scale problem costs %lf s ...\n",duration );
    //run time write back
    
    begintime = clock();    
    quick_sort(filename_6,scale_6,t);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^6 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    quick_sort(filename_9,scale_9,t);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^9 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    quick_sort(filename_12,scale_12,t);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^12 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    quick_sort(filename_15,scale_15,t);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^15 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    quick_sort(filename_18,scale_18,t);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^18 scale problem costs %lf s ...\n",duration );
    //run time write back
*/