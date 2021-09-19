#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define filename_3 "../output/merge/result_3.txt"
#define filename_6 "../output/merge/result_6.txt"
#define filename_9 "../output/merge/result_9txt"
#define filename_12 "../output/merge/result_12.txt"
#define filename_15 "../output/merge/result_15.txt"
#define filename_18 "../output/merge/result_18.txt"
#define scale_3    (int)pow(2,3)            //问题规模取 2的 3，6，9，12，15，18 次方
#define scale_6    (int)pow(2,6)
#define scale_9    (int)pow(2,9)
#define scale_12   (int)pow(2,12)
#define scale_15   (int)pow(2,15)
#define scale_18   (int)pow(2,18)

#define BIGGER_THAN_MAX   pow(2,15) + 1 
void merge(int A[] ,int p,int q,int r){
      int length1,length2,i,j,k ;
      int *part1 ,*part2;
      length1 = q-p+1;
      length2 = r-q ;
      part1 = (int *)malloc((length1+2)*sizeof(int));
      part2 = (int *)malloc((length2+2)*sizeof(int));
      for (i = 0; i<length1 ;i++){
          part1[i] = A[p+i] ;
      }
      for (i = 0; i<length2 ;i++){
          part2[i] = A[q+1+i] ;
      }
      part1[length1] = BIGGER_THAN_MAX;
      part2[length2] = BIGGER_THAN_MAX; 
      i = 0 ;
      j = 0 ;
      for(k = p ; k <=  r ; k++){
          if(part1[i]<part2[j]){
               A[k] = part1[i];
               i++;
          }else
          {
              A[k] = part2[j];
              j++ ;
          }
      }
      free(part1);
      free(part2);
      return ;     

}
void merge_sort(int A[],int p,int r){
    int q;
    if(p<r){
        q= (p+r)/2;       
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    } 
    return ;       
}
void print(const char* filename , int SCALE){
    FILE *fp;
    if((fp=fopen("../input/input.txt", "r"))==NULL){
         printf("can't open file ../input/input.txt!\n");
         exit(0);
    }  

    int *sort;
    sort = (int*)malloc(SCALE*sizeof(int));
    for(int i=0;i<SCALE ;i++){
        fscanf(fp,"%d", &sort[i]);
    }   
     merge_sort(sort,0,SCALE-1);
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
    free(sort);

    fclose(fp1);
}
int main (){
    clock_t begintime , endtime ;
    double duration ;
    
    FILE *fp2;
    if((fp2=fopen("../output/merge/time.txt", "w+"))==NULL){
         printf("can't open file ../output/merge/time.txt");
         exit(0);
    }

    begintime = clock();    
    print(filename_3,scale_3);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^3 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    print(filename_6,scale_6);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^6 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    print(filename_9,scale_9);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^9 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    print(filename_12,scale_12);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^12 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    print(filename_15,scale_15);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^15 scale problem costs %lf s ...\n",duration );
    //run time write back

    begintime = clock();    
    print(filename_18,scale_18);
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^18 scale problem costs %lf s ...\n",duration );
    //run time write back
   
    fclose(fp2);
    return 0; 
}