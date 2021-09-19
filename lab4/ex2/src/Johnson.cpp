#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std ;
#define scale1 27
#define scale2 81
#define scale3 243
#define scale4 729
#define scale_num 4
#define deg_num 2
#define MAX_EDG 729*4
#define infinity 729*200*2
typedef struct edge
{
    int weight;
    int u;
    int v;
}edge;

typedef struct Vertex
{    
    int ith;
    int d;
    Vertex* p;
    vector<int> adj;
}Vertex;

typedef struct Graph
{
     int vex_num;
     int edge_num;
     Vertex vex[scale4 + 1];
//     vector<Vertex> vex;
     vector<edge> edge_list;
     int weight[scale4+1][scale4+1];
}Graph;

edge edge_lt[MAX_EDG]; 

void Relax(Vertex* u,Vertex* v,int w){
    if(v->d > u->d + w){
        v->d = u->d + w;
        v->p = u;
    }
}

void ININIAL_S(Graph* G, int s){
    int i;
    for( i = 0; i < G->vex_num ;i++){  //初始化
        G->vex[i].d = infinity;
        G->vex[i].p = NULL ;
    }
    G->vex[s].d = 0;
}    

void MIN_heapify(Graph *G,int *V ,int V_size ,int i){
    int left ,right ,smallest;
    int tmp;
    left = i*2 + 1 ;
    right = i*2 + 2 ;
    if(left < V_size && G->vex[V[left]].d < G->vex[V[i]].d ){
        smallest = left;
    }else
    {
        smallest = i;
    }
    if(right < V_size && G->vex[V[right]].d < G->vex[V[smallest]].d){
        smallest = right ;
    }
    if(smallest != i){
         tmp = V[i];
         V[i] = V[smallest];
         V[smallest] = tmp;
         MIN_heapify(G,V,V_size,smallest);
    }  
}
void Build_Heap(Graph* G, int* V ,int V_size){
    for(int i = V_size/2 -1;i>=0 ;i--){
         MIN_heapify(G,V,V_size,i);
    } 
}
int Extract_min(Graph*G ,int *V , int V_size){
    int u;
    if(V_size <= 0){
         cout<<"heap underflow"<<endl;
         exit(0);
    }
    u = V[0];
    V[0] = V[V_size-1];
    MIN_heapify(G,V, V_size-1 ,0);
    return u;
}
void Dijkstra( Graph* G,int s){ //从点 s 开始的单元最短路径
     ININIAL_S(G , s) ; //初始化
     vector<Vertex> S ; //存放已经达到的最小路径
     //自己实现最小优先队列。
     int V[scale4+1] ;
     int u;
     int V_size = G->vex_num;
     for(int i=0 ; i < G->vex_num ;i++){
         V[i] = i;
     }
     Build_Heap(G,V , V_size);
     while(V_size != 0){
        u = Extract_min(G,V , V_size);
        V_size-- ; //得到最小的
        S.push_back(G->vex[u]);
        // 迭代S 输出最小距离 
        
        vector<int>::iterator v;
        for(v = G->vex[u].adj.begin();v != G->vex[u].adj.end() ;v++){
              Relax(&G->vex[u] , &G->vex[*v] , G->weight[u][*v]);
        }// 此时 u.d v.d 是在变的。所以最小堆已经不是最小堆了。
        Build_Heap(G,V,V_size); //重新维护最小堆性质。
     }
}
bool Bellman_Ford(Graph* G){
    int i,j;
    vector<edge>::iterator it ;
    ININIAL_S(G,G->vex_num-1); //初始化 , 
    for( i = 0 ; i < G->vex_num - 1;i++){  //vex_num -1 次 轮 遍历 
        for(it = G->edge_list.begin() ; it!=G->edge_list.end() ; it++)  //对每条边遍历。
            Relax(&G->vex[it->u] , &G->vex[it->v] ,it->weight);
    }
    for(it = G->edge_list.begin() ; it!=G->edge_list.end() ; it++){
        if(G->vex[it->v].d > G->vex[it->u].d + it->weight){
            cout<<"deleat edge: ("<<it->u<<","<<it->v<<","<<it->weight<<")"<<endl;
            //在u 的邻接表里删掉 v ;
            vector<int>::iterator v;
            for(v = G->vex[it->u].adj.begin();v != G->vex[it->u].adj.end() ;v++){
                if( *v == it->v ){
                    G->vex[it->u].adj.erase(v);
                    break;
                }
            }
            G->weight[it->u][it->v] = infinity; 
            G->edge_list.erase(it);
            G->edge_num--;
            return false;
        }
    }
    return true;
}
void Johnson(FILE* fp ,Graph* G , int D[scale4][scale4]  ){ // D作参数  存放结果。
    //构造G‘
    int i,curr_edge,new_vex;
    int h[scale4+1];
    new_vex = G->vex_num;
    G->vex_num++;
    curr_edge = G->edge_num;
    for(i = 0; i < G->vex_num ; i++){ //扩展边 权重是0
        G->vex[new_vex].adj.push_back(i);
        G->weight[new_vex][i] = 0; 
        edge_lt[curr_edge].u = new_vex;
        edge_lt[curr_edge].v = i;
        edge_lt[curr_edge].weight = 0;
        G->edge_list.push_back(edge_lt[curr_edge]);
        curr_edge++ ;
    }
    G->edge_num = curr_edge;

    while(Bellman_Ford(G) == false) ;  //默认有限次删除后 会没有负环。
    
    //计算h(x) ;
    for(i = 0 ; i < G->vex_num ;i++){
        h[i] = G->vex[i].d;
    }
    vector<edge>::iterator it;
    for(it = G->edge_list.begin() ; it!=G->edge_list.end() ; it++){//对每条边重新计算权重
          it->weight = it->weight + h[it->u] - h[it->v];
          G->weight[it->u][it->v] =  G->weight[it->u][it->v] + h[it->u] - h[it->v];
    }  //此时 edge_list 好像已经没用了。
    G->vex_num-- ; //求完h(x) 后将点删掉 。
    int curr=0;
    for(i = 0 ; i < G->vex_num ; i++){
        Dijkstra(G,i);
        for(int v = 0 ; v < G->vex_num ;v++){
            
            vector<int> store_result;
            D[i][v] = G->vex[v].d + h[v] - h[i];
             //打印结果
            if(v != i){
                curr = v; 
                while(G->vex[curr].p != NULL ){
                    store_result.push_back(G->vex[curr].ith);
                    curr = G->vex[curr].p->ith;
                }
                if(curr == i){
                    fprintf(fp,"(%d",i); 
                    for(int k = store_result.size()-1 ; k >= 0 ; k--){
                        fprintf(fp,",%d",store_result[k]); 
                    }
                    fprintf(fp," %d)\n",D[i][v]); 
                    store_result.clear();
                }
                else{
                    fprintf(fp,"(%d  %d):there is no shortest path.\n",i,v); 
                }
            }
        }
    }
}
int main(){
    FILE *scan_fp , *rslt_fp , *time_fp ;
    clock_t begintime , endtime ;
    double duration ;
    char infilename[scale_num][deg_num][25] = {"../input/input11.txt","../input/input12.txt","../input/input21.txt","../input/input22.txt","../input/input31.txt","../input/input32.txt","../input/input41.txt","../input/input42.txt"};
    char outfilename[scale_num][deg_num][25] = {"../output/result11.txt","../output/result12.txt","../output/result21.txt","../output/result22.txt","../output/result31.txt","../output/result32.txt","../output/result41.txt","../output/result42.txt"};
    Graph G;   
    int scale[scale_num]= { scale1 ,scale2,scale3, scale4};
    int result[scale4][scale4];
    int i,j,k, curr_edge,u,v,weigh,MST_edgenum;
    if((time_fp=fopen("../output/time.txt", "w" )) == NULL){
          printf("can't open file ../output/time.txt!");
          exit(0);
    }
    
    for(k = 0;k< scale_num ;k++){  //直接建立四个图。
        for(j = 0 ; j < deg_num ; j++ ){
            //对G初始化；
            G.vex_num = 0;
            G.edge_num = 0;
            G.edge_list.clear();
            for(int i = 0;i<= scale4 ;i++){
                G.vex[i].ith = i;
                for(int n = 0; n < scale4 ; n++)
                 G.weight[i][n] = infinity; 
            }
            //清空一些公共的容器
            curr_edge = 0;
            if((scan_fp = fopen(infilename[k][j], "r" )) == NULL){
                printf("can't open file ../input/input.txt!");
                exit(0);
            } //打开要扫描的文件
            if((rslt_fp = fopen(outfilename[k][j], "w" )) == NULL){
                printf("can't open file ../input/input.txt!");
                exit(0);
            } //打开要扫描的文件
            while (fscanf(scan_fp, "%d %d %d", &u ,&v ,&weigh) == 3){ //生成了边的集合
                G.vex[u].adj.push_back(v);
                G.weight[u][v] = weigh; 
                edge_lt[curr_edge].u = u;
                edge_lt[curr_edge].v = v;
                edge_lt[curr_edge].weight = weigh;
                G.edge_list.push_back(edge_lt[curr_edge]);
                curr_edge++ ;
            }
            G.vex_num = scale[k];
            G.edge_num = curr_edge;
            //Johnson的时间
            begintime = clock(); 
            Johnson(rslt_fp ,&G , result);
            endtime = clock();
            duration = (double) (endtime - begintime)/CLOCKS_PER_SEC ;
            fprintf(time_fp,"The %d scale series %d problem   costs %lf s ...\n",scale[k],j, duration );
            //打印结果 
            //关闭指针
            fclose(scan_fp);
            fclose(rslt_fp);
        }
    }
    fclose(time_fp);
    return 0;
}