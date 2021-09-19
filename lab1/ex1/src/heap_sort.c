#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define filename_3 "../output/heap/result_3.txt"
#define filename_6 "../output/heap/result_6.txt"
#define filename_9 "../output/heap/result_9.txt"
#define filename_12 "../output/heap/result_12.txt"
#define filename_15 "../output/heap/result_15.txt"
#define filename_18 "../output/heap/result_18.txt"
#define scale_3    (int)pow(2,3)            //问题规模取 2的 3，6，9，12，15，18 次方
#define scale_6    (int)pow(2,6)
#define scale_9    (int)pow(2,9)
#define scale_12   (int)pow(2,12) 
#define scale_15   (int)pow(2,15)
#define scale_18   (int)pow(2,18)
void max_heapify(int sort[], int size,int i){
    int l,r,Largest = -1,tmp;
    l = 2*i+1 ;
    r = l+1 ;
    if(l < size && sort[l] > sort[i]){
         Largest = l;
    }else{
         Largest = i; 
    }
    if(r < size && sort[r] > sort[Largest]){
         Largest = r;
    }
    if(Largest != i){
        tmp = sort[Largest];
        sort[Largest] = sort[i];
        sort[i] = tmp;
        max_heapify(sort, size ,Largest);
    }
    return ;
}
void build_max_heap(int sort[] ,int size){
    int i;
    for(i = size-1/2 ; i>=0 ; i--){
        max_heapify(sort , size ,i);
    }
}
void heap_sort(const char *filename , int SCALE ){
    int tmp,heap_size = SCALE;
    int *sort ;  

    FILE *fp;
    if((fp=fopen("../input/input.txt", "r"))==NULL){
         printf("can't open file ../input/input.txt!\n");
         exit(0);
    } 

    sort = (int*)malloc(SCALE*sizeof(int));
    for(int i=0;i<SCALE ;i++){   //开始读数据
        fscanf(fp,"%d", &sort[i]);
    }
    build_max_heap(sort,SCALE);
    for(int i = SCALE-1 ; i>0 ;i--){   //开始排序
         tmp = sort[0];
         sort[0] = sort[i];
         sort[i] = tmp;
         heap_size = heap_size - 1;
         max_heapify(sort,heap_size,0);
    } 
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
    free(sort);

    fclose(fp); 
}
int main (){
    clock_t begintime , endtime ;
    double duration ; 

    FILE *fp2;
    if((fp2=fopen("../output/heap/time.txt", "w+"))==NULL){
         printf("can't open file ../output/heap/time.txt");
         exit(0);
    }

    begintime = clock();    
    heap_sort(filename_3,scale_3);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^3 scale problem costs %lf s ...\n",duration );
    //run time write back
    
     begintime = clock();    
    heap_sort(filename_6,scale_6);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^6 scale problem costs %lf s ...\n",duration );
    //run time write back
     begintime = clock();    
    heap_sort(filename_9,scale_9);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^9 scale problem costs %lf s ...\n",duration );
    //run time write back
     begintime = clock();    
    heap_sort(filename_12,scale_12);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^12 scale problem costs %lf s ...\n",duration );
    //run time write back

     begintime = clock();    
    heap_sort(filename_15,scale_15);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^15 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    heap_sort(filename_18,scale_18);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^18 scale problem costs %lf s ...\n",duration );
    //run time write back
 
    fclose(fp2);
    return 0; 
}