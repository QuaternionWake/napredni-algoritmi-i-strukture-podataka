#include <stdio.h>
#include <stdlib.h>

// BEGIN LIST
    struct List_ {
        int x;
        struct List_ *next;
    };

    typedef struct List_ List;
// END LIST

// BEGIN STACK
    #define MAXSIZE 1000

    struct Stack_ {
        int SP;
        int data[MAXSIZE];
    };
    typedef struct Stack_ Stack;

    void Clear(Stack *s) {
        s->SP = 0;
    }

    void Push(Stack *s, int x) {
        if (s->SP==MAXSIZE) {
            puts("Stack overflow... Aborting...");
            exit(1);
        }
        s->data[s->SP] = x;
        s->SP++;
    }

    int Pop(Stack *s) {
        if (s->SP==0) {
            puts("Illegal pop... Aborting...");
            exit(2);
        }
        s->SP--;
        return s->data[s->SP];
    }

    int Top(Stack *s) {
        if (s->SP==0) {
            puts("Illegal top... Aborting...");
            exit(2);
        }
        return s->data[s->SP-1];
    }

    int Is_empty(Stack s) {
        if (s.SP==0) return 1;
        return 0;
    }
// END STACK

// BEGIN QUEUE
    #define MAXSIZE 1000

    struct Queue_ {
        int In, Out, Count;
        int data[MAXSIZE];
    };
    typedef struct Queue_ Queue;

    void ClearQ(Queue *q) {
        q->In = 0;
        q->Out = 0;
        q->Count = 0;
    }

    void PushQ(Queue *q, int x) {
        if (q->Count==MAXSIZE) {
            puts("Queue overflow... Aborting...");
            exit(1);
        }
        q->data[q->In] = x;
        q->In = (q->In+1)%MAXSIZE;
        q->Count++;
    }

    int PopQ(Queue *q) {
        if (q->Count==0) {
            puts("Illegal pop... Aborting...");
            exit(2);
        }
        int x = q->data[q->Out];
        q->Out = (q->Out+1)%MAXSIZE;
        q->Count--;
        return x;
    }

    int Is_emptyQ(Queue q) {
        if (q.Count==0) return 1;
        return 0;
    }
// END QUEUE


#define NMAX 100

// Helping procedures for SCC

void DFS1(char G[][NMAX],int N,int v, Stack *L, char *visited) {
    visited[v] = 1;
    for (int u=0; u<N; u++ )
        if (G[v][u]==1 && visited[u]==0) DFS1(G,N,u,L,visited);
    Push(L,v);
}

char gt[NMAX][NMAX];  // staticly resreved space for transponed matrix

void GraphTransposeAM(char G[][NMAX],int N) {
    int i,j;
        for (i=0; i<N; i++)
            for (j=0; j<N; j++)
        	    gt[i][j] = G[j][i];
}

void DFS2(char G[][NMAX], int N, int v, char visited[] ) {
    visited[v] = 1;
    printf("%d ",v+1);
    for (int u=0; u<N; u++ )
        if (G[v][u]==1 && visited[u]==0) DFS2(G,N,u,visited);
}


// Output Strongly Connected Components - SCC of a graph G

void SCC( char G[][NMAX], int N ) {
    Stack L; int v; char **Gt; int count = 1;
    char *visited = (char *)malloc(N);
    Clear(&L);
    for (v=0; v<N; v++) visited[v] = 0;
    for (v=0; v<N; v++) 
        if (!visited[v]) DFS1(G,N,v,&L,visited);
    GraphTransposeAM(G,N);
    for (v=0; v<N; v++) visited[v] = 0;
    while (!Is_empty(L)) {
        v = Pop(&L);
        if (!visited[v]) {
            printf("SCC #%d: ",count++);
            DFS2(gt,N,v,visited);
            printf("\n");
        }
    }
}

#define NMAX 100

// Helping procedure for SCC
int min(int a, int b) {
    if (a<b) return a;
    return b;
}

int node_count;

void SCCUtil(char G[][NMAX], int N, int u, int disc[], int low[], Stack *L, int stackMember[]) {
    int v;
    static int time = 0;
    disc[u] = low[u] = ++time;
    Push(L,u);
    stackMember[u] = 1;
    
    for (v=0; v<N; v++) {
        if (G[u][v]==1 && disc[v]==-1) {
            SCCUtil( G, N, v, disc, low, L, stackMember);
            low[u] = min(low[u], low[v]);
        }
        else if (stackMember[v] == 1)
            low[u] = min(low[u], disc[v]);
    }
    int w = 0;
    if (low[u] == disc[u]) {
        printf("SCC #%d: ",node_count++);
        while (Top(L) != u) {
            w = Top(L);
            printf( "%d ", w+1 );
            stackMember[w] = 0;
            Pop(L);
        }
        w = Top(L);
        printf( "%d\n", w+1);;
        stackMember[w] = 0;
        Pop(L);
    }
}

// Output Strongly Connected Components - SCC of a graph G
void SCC_Tarjan( char G[][NMAX], int N ) {
    int v;
    int *disc = (int *)malloc(sizeof(int)*N);
    int *low = (int *)malloc(sizeof(int)*N);
    int* stackMember = (int *)malloc(N);
    Stack L;
    Clear(&L);
    for (v = 0; v < N; v++) {
        disc[v] = -1;
        low[v] = -1;
        stackMember[v] = 0;
    }
    node_count = 1;
    for (v = 0; v < N; v++)
        if (disc[v] == -1)
            SCCUtil( G, N, v, disc, low, &L, stackMember );
}



int main() {
    char G1[6][NMAX] =
        #include "lv2-graf.c"
    int N1 = 6;
  
    printf("---------- TARJAN'S SCC ALGORITHM ---------\n");
    printf("---------------- SMALL GRAPH --------------\n");

    SCC_Tarjan(G1,N1);

    printf("----------------- BIG GRAPH ---------------\n");

    char G2[NMAX][NMAX] = {0};
    int N2 = 25;
    for (int i=0; i<1.25*N2; i++) {
        int u,v;
        u = rand()%N2;
        v = rand()%N2;
        G2[u][v] = 1;
        G2[v][u] = 1;
    }

    SCC_Tarjan(G2,N2);

    return 0;
}
