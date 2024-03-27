#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#include <string.h>
#define vertices_number 200
#define INFINITY 10000
char unvisited[100][100], visited[100][100];
typedef struct Table
{
    char visited[100];
    int dist;
    char previous[100];
}Table;

typedef struct Edges
{
    char from[100],to[100];
    int dist;
} Edge;
typedef struct City{
    int num;
    char name[100];
}City;
int isExists(char n[], char unvisited[][100], int num)
{
    for (int i=0; i<num; i++)
    {
        if(strcmp(n,unvisited[i])==0)
            return 1;
    }
    return 0;
}

void inisializeTable(Table t[],char source[], int size){
    for (int i=0; i<size; i++){
        strcpy(t[i].visited, unvisited[i]);
        strcpy(t[i].previous, "unknown");
        if(strcmp(t[i].visited, source)==0){
            t[i].dist = 0;
        }
        else{
            t[i].dist = INFINITY;
        }
    }
}

int isUnVisited(char n[], int numOfUnVisited){
    for (int i=0; i<numOfUnVisited; i++){
        if(strcmp(n, unvisited[i])==0){
            return 1;
        }
    }
    return 0;
}

int getDistance(char n1[], char n2[],Edge e[], int edgeNum){
    for (int i=0; i<edgeNum; i++){
        if(strcmp(n1, e[i].from)==0){
            if(strcmp(n2, e[i].to)==0){
                return e[i].dist;
            }
        }
        if(strcmp(n1, e[i].to)==0){
            if(strcmp(n2, e[i].from)){
                return e[i].dist;
            }
        }
    }
    return 0;
}

int getIndex(char n[], Table t[], int size){
    for(int i=0; i<size; i++){
        if(strcmp(n, t[i].visited)==0){
            return i;
        }
    }
    return 0;
}

void Dijkistra(char n[], Edge ed[],Table t[], int edgeNum, int unvisitedSize, int size, int visitedNum){
    int val = 0, calc_dist;
    int distination;
    char connectedNodes[100][100];
    char finalNodes[100][100], newArr[100][100];
    int final_dist;
    for(int i=0; i<edgeNum; i++){
        if(strcmp(ed[i].from, n)==0){
            strcpy(connectedNodes[val], ed[i].to);
            val++;
        }
        if(strcmp(ed[i].to, n)==0){
            strcpy(connectedNodes[val], ed[i].from);
            val++;
        }
    }
    int val1 = 0;
    for (int i=0; i<val; i++){
        if(isUnVisited(connectedNodes[i],unvisitedSize)==1){
            strcpy(finalNodes[val1],connectedNodes[i]);
            val1++;
        }
    }
    val = val1;
    for(int i=0; i<val; i++){
        strcpy(connectedNodes[i], finalNodes[i]);
    }
    for (int i=0; i<size;i++){
        if(strcmp(n, t[i].visited)==0){
            calc_dist = t[i].dist;
        }
    }
    for (int i=0; i<val; i++){
        distination = getDistance(n, connectedNodes[i], ed, edgeNum);
        final_dist = distination + calc_dist;
        for(int j=0; j<size; j++){
            if(strcmp(connectedNodes[i], t[j].visited)==0){
                if(t[j].dist > final_dist){
                    t[j].dist = final_dist;
                    strcpy(t[j].previous, n);
                }
            }
        }
    }
    for(int i=0;i<size;i++){
        if(strcmp(n, t[i].previous)==0){
            printf("%s  %s   %d\n",t[i].previous, t[i].visited, t[i].dist);
        }
    }
    strcpy(visited[visitedNum], n);
    visitedNum++;
    int val2 = 0;
    for (int i=0; i<size; i++){
        if(strcmp(unvisited[i], n) != 0){
            strcpy(newArr[val2], unvisited[i]);
            val2++;
        }
    }
    unvisitedSize = val2;
    for (int i=0; i<unvisitedSize; i++){
        strcpy(unvisited[i], newArr[i]);
    }
    if(unvisitedSize > 0){
        int index = getIndex(unvisited[0], t, size);
        int min_path = t[index].dist;
        for(int i=0; i<unvisitedSize; i++){
            int index2 = getIndex(unvisited[i], t, size);
            if(min_path > t[index2].dist){
                index = getIndex(unvisited[i], t, size);
                min_path = t[index].dist;
            }
        }
        Dijkistra(t[index].visited, ed,t,edgeNum,unvisitedSize,size,visitedNum);
    }
}

int main()
{
    FILE *in;
    in = fopen("Cities.txt","r");
    char line[MAX_SIZE];
    int i = 0, unvisitedNum = 0,visitedNum = 0, size = 0, choice = 0;
    int edgesNumber;
    char km[10];
    Edge e[MAX_SIZE];
    City cities[100];
    in==NULL ? printf("Cities file does not exist\n") : printf("taking data from courses file .... \n");
    while(choice != 4)
    {
        printf("\n\n               MENU                \n\n");
        printf("1. load cities \n");
        printf("2. Enter source city \n");
        printf("3. Enter destination city \n");
        printf("4. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if (choice == 1)
        {
            while(fgets(line,MAX_SIZE,in))
            {
                char *word = strtok(line,"\t");
                strcpy(e[i].from,word);
                word = strtok(NULL,"\t");
                strcpy(e[i].to,word);
                word = strtok(NULL,"\t\n");
                strcpy(km,word);
                km[strlen(km)-2]='\0';
                e[i].dist = atoi(km);
                i++;
            }
            fclose(in);
            edgesNumber = i;
            for (int i=0; i<edgesNumber; i++)
            {
                if(!isExists(e[i].from, unvisited, edgesNumber))
                {
                    strcpy(unvisited[unvisitedNum],e[i].from);
                    unvisitedNum++;
                }
                if(!isExists(e[i].to, unvisited, edgesNumber))
                {
                    strcpy(unvisited[unvisitedNum],e[i].to);
                    unvisitedNum++;
                }
            }
            size = unvisitedNum;
            for(int i=0; i<size; i++){
                strcpy(cities[i].name,unvisited[i]);
                cities[i].num = i;
            }
            for (int i=0;i<size;i++){
                printf("%s %d\n",cities[i].name, cities[i].num);
            }
        }
        if(choice == 2){
            Table minDist[100];
            char s_city[100];
            printf("Enter the source city: ");
            scanf("%*c%[^\n]", s_city);
            inisializeTable(minDist,s_city,size);
            Dijkistra(s_city,e,minDist,edgesNumber,unvisitedNum,size,visitedNum);

        }
    }
}
