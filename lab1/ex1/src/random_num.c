#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE  32768      //2的15次方 
#define NUM    512*512       //产生2的18次方个
int main (){
    char ch;
    FILE *fp;
    if((fp=fopen("../input/input.txt", "w+"))==NULL){
         printf("can't open this file");
         exit(0);
    }
    srand((unsigned)time(NULL));
    int random,range ,i=0;
    while(i < NUM){
        random = rand() % RANGE  ;
        fprintf(fp,"%d\n",random);
        i++;
    }
    fclose(fp);
    
    return 0;  
}
