#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std ;
#define scale1 8
#define scale2 64
#define scale3 128
#define scale4 512
#define scale_num 4
#define MAX_EDG 512*512/2
typedef struct edge
{
    int weight;
    int u;
    int v;
}edge;
int p[MAX_EDG] = {0}; //记录集合的 最祖先结点
int rk[MAX_EDG] = {0};  //记录集合的秩
vector <edge> MST_edge ;

//不想交集合森林 make_set
void make_set(int x){
    p[x] = x ;
    rk[x] = 0;
}
//find_set
int find_set(int x){
     if(x != p[x]){
         p[x] = find_set(p[x]) ;
     }
     return p[x];
}

//union_set
void link(int x,int y){
    if(rk[x] > rk[y]){
        p[y] = x;
    }else
    {
        p[x] = y;
        if(rk[x] == rk[y]) 
            rk[y] = rk[y] +1;
    } 
}
void union_set(int x,int y){
    link(find_set(x) , find_set(y) );
}

int MyCompare(edge e1, edge e2){
     return e1.weight < e2.weight ;
}
void kruskal(edge* edge_list,int edge_num ){  //结果存放在 全局变量 vector::MST_tree 中。
    int i;
    for( i = 0;i < edge_num ; i++){
        make_set(i);
    }
    sort(edge_list,edge_list+edge_num,MyCompare);
    for(i = 0 ; i < edge_num ; i++){
         if(find_set(edge_list[i].u) != find_set(edge_list[i].v)){
         MST_edge.push_back(edge_list[i]);
         union_set(edge_list[i].u , edge_list[i].v) ;
         }
    }
}
int main(){
    FILE *scan_fp , *rslt_fp , *time_fp ;
    clock_t begintime , endtime ;
    double duration ;
    char infilename[scale_num][20] = {"../input/input1.txt","../input/input2.txt","../input/input3.txt","../input/input4.txt"};
    char outfilename[scale_num][25] = {"../output/result1.txt","../output/result2.txt","../output/result3.txt","../output/result4.txt"};
    edge edge_list[MAX_EDG];   
    int scale[scale_num]= { scale1 ,scale2,scale3, scale4};
    int i,j,k, curr_edge,u,v,weigh,MST_edgenum;
    if((time_fp=fopen("../output/time.txt", "w" )) == NULL){
          printf("can't open file ../output/time.txt!");
          exit(0);
    }
    
    for(k = 0;k< scale_num ;k++){  //直接建立四个图。
        //清空一些公共的容器
        curr_edge = 0;
        for(i = 0;i < MAX_EDG ; i++){
            p[i] = 0;
            rk[i] = 0;
        }
        if((scan_fp = fopen(infilename[k], "r" )) == NULL){
            printf("can't open file ../input/input.txt!");
            exit(0);
        } //打开要扫描的文件
        if((rslt_fp = fopen(outfilename[k], "w" )) == NULL){
            printf("can't open file ../input/input.txt!");
            exit(0);
        } //打开要扫描的文件
        while (fscanf(scan_fp, "%d %d %d", &u ,&v ,&weigh) == 3){ //生成了边的集合
            edge_list[curr_edge].u = u;
            edge_list[curr_edge].v = v;
            edge_list[curr_edge].weight = weigh;
            curr_edge++ ;
        }
        
        //kruskal的时间
        begintime = clock();    
        kruskal(edge_list , curr_edge);
        endtime = clock();
        duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
        fprintf(time_fp,"The %d scale problem of kruskal get the MST costs %lf s ...\n",scale[k], duration );

        //打印结果
        MST_edgenum = MST_edge.size();
        for(int i = 0; i < MST_edgenum ; i++){            
            fprintf(rslt_fp,"%d %d %d\n",MST_edge[i].u,MST_edge[i].v,MST_edge[i].weight);
        }
        MST_edge.clear();

        //关闭指针
        fclose(scan_fp);
        fclose(rslt_fp);
    }
    fclose(time_fp);

    return 0;
}