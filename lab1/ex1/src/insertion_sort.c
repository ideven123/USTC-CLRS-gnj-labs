#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define filename_3 "../output/insert/result_3.txt"
#define filename_6 "../output/insert/result_6.txt"
#define filename_9 "../output/insert/result_9.txt"
#define filename_12 "../output/insert/result_12.txt"
#define filename_15 "../output/insert/result_15.txt"
#define filename_18 "../output/insert/result_18.txt"
#define scale_3   3            //问题规模取 2的 3，6，9，12，15，18 次方
#define scale_6   6      
#define scale_9   9      
#define scale_12  12      
#define scale_15  15
#define scale_18  18            

void insertion_sort(const char *filename ,int scale){
    
     int SCALE = pow(2,scale);
     FILE *fp;
    if((fp=fopen("../input/input.txt", "r"))==NULL){
         printf("can't open file ../input/input.txt!\n");
         exit(0);
    }  
    int rd_num,curr_scale;     
    int sort[SCALE] ;
    int left ,right , mid ,insert_point;
    fscanf(fp,"%d",&rd_num); //规模为0特殊处理 ;
    sort[0] = rd_num ;
    left = right = mid = 0;
    for(curr_scale=1;curr_scale<SCALE ; curr_scale++){
        fscanf(fp,"%d",&rd_num);
           
           // 查找插入点 
           left = 0;
           right = curr_scale - 1 ; 
           mid = (right + left)/2 ;
           while(left < mid){
               if(rd_num < sort[mid]){
                    right = mid ;
                    mid = (right + left)/2 ;
               }else if (rd_num > sort[mid])
               {
                    left = mid ; 
                    mid = (right + left)/2 ;
               }else{
                   insert_point = mid+1;
                   break ;
               }             
           }
           if(left == mid){ // left ,right 之外未找到相等
               if( rd_num < sort[right] && rd_num > sort[left]){
                    insert_point = right ;
               }else if (rd_num >= sort[right])
               {
                    insert_point = right + 1 ; 
               }else{
                    insert_point = left ;
               }               
           }
       
            //在 insert_point 到 curr_scale 插入            
            for(int j = curr_scale ; j > insert_point ;j--)    sort[j] = sort[j-1];
            sort[insert_point] = rd_num ; 
               
    }
    fclose(fp); 

    //write back
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
    //打开写回时间的文件  
    FILE *fp2;
    if((fp2=fopen("../output/insert/time.txt", "w+"))==NULL){
         printf("can't open file ../output/insert/time.txt");
         exit(0);
    }

    //scale = 3 
    begintime = clock();    
    insertion_sort(filename_3,scale_3);  
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^%d scale problem costs %lf s ...\n",scale_3,duration );
    //run time write back

    //scale = 6 
    begintime = clock();    
    insertion_sort(filename_6,scale_6);  
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^%d scale problem costs %lf s ...\n",scale_6,duration );
     //run time write back

     //scale = 9 
    begintime = clock();    
    insertion_sort(filename_9,scale_9);  
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^%d scale problem costs %lf s ...\n",scale_9,duration );
    //run time write back

    //scale = 12 
    begintime = clock();    
    insertion_sort(filename_12,scale_12);  
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^%d scale problem costs %lf s ...\n",scale_12,duration );
    //run time write back

    //scale = 15 
    begintime = clock();    
    insertion_sort(filename_15,scale_15);  
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^%d scale problem costs %lf s ...\n",scale_15,duration );
    //run time write back

    //scale = 18 
    begintime = clock();    
    insertion_sort(filename_18,scale_18);  
    endtime = clock();
    duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
    fprintf(fp2,"The 2^%d scale problem costs %lf s ...\n",scale_18,duration );
    //run time write back


    fclose(fp2);
    return 0; 
}