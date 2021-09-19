#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE  51        //范围
#define NUM  30          //产生2的18次方个
#define vector_div 2 
#define APPLY 5
int main (){
    char ch;
    FILE *fp;
    int duplicate_flag[RANGE] = {0};
    if((fp=fopen("../input/input.txt", "w+"))==NULL){
         printf("can't open this file");
         exit(0);
    }
    srand((unsigned)time(NULL));
    int random1,range , i = 0;
    int random2 = 0;
    while( i < NUM){
        /*core code*/

        random1 = rand() % RANGE  ;
        if(duplicate_flag[random1] == 0){
            if(random1 < 25){
                random2 = random1 + 1 + rand() % (25-random1); 
                fprintf(fp,"%d %d \n",random1,random2);
                duplicate_flag[random1] = 1; 
                i++ ;
                continue;
            }else if(random1 >= 30 && random1 != 50)
            {
                random2 = random1 + 1 + rand() % (50-random1); 
                fprintf(fp,"%d %d \n",random1,random2);
                 duplicate_flag[random1] = 1; 
                i++ ;
                continue;
            }
        }
    }
    fclose(fp);
    return 0;
}