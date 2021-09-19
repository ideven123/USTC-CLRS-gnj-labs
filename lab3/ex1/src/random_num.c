#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE  5000        //范围
#define NUM  512*512            //产生2的18次方个
#define APPLY 5
int main (){
    char ch;
    int duplicate_flag[RANGE] = {0};
    int apply_num[5] = {20,40,60,80,100} ;
    FILE *fp;
    if((fp=fopen("../input/input.txt", "w+"))==NULL){
         printf("can't open this file");
         exit(0);
    }
    srand((unsigned)time(NULL));
    

    for(int repeat_time =0 ;repeat_time < APPLY ; repeat_time++){
        /*core code*/
        int random,range ,i=0;
        while(i < apply_num[repeat_time]){
            random = rand() % RANGE  ;
            if(duplicate_flag[random]==0 ){
             duplicate_flag[random] = 1;   
            fprintf(fp,"%d ",random);
            i++;
            }
        }
    fprintf(fp,"\n");
    
    }
    fclose(fp);

    return 0;
}