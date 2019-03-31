#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_DATA
{
    int index;
    struct NODE_DATA* next;
} NODE;

int main()
{
    //init data
    int n, m, u, v;
    int i,a,b;
    int can_go[101][101];
    int prev[101];
    memset(can_go,0,sizeof(can_go));
    memset(prev,0,sizeof(prev));


    //read data
    freopen("input.txt","r",stdin);
    scanf("%d %d %d %d", &n, &m, &u, &v);
    for (i=0; i<m; i++)
    {
        scanf("%d %d",&a,&b);
        can_go[a][b] = 1;
    }
    fclose(stdin);

    //BFS init
    NODE* this_node = malloc(sizeof(NODE));
    this_node->next = 0;
    this_node->index = v;
    prev[v] = -1;
    NODE* last_node = this_node;

    //BFS
    while (this_node)
    {
        for (i=1; i<101; i++)
            if (can_go[i][this_node->index] && !prev[i])
            {
                //Make new node
                prev[i] = this_node->index;
                last_node->next = malloc(sizeof(NODE));
                last_node = last_node->next;
                //set data
                last_node->index = i;
                last_node->next = 0;
            }
        this_node = this_node->next;
    }

    //output
    freopen("output.txt","w",stdout);
    if (!prev[u])
        printf(0);
    else
        while (u>0)
        {
            printf("%d ",u);
            u = prev[u];
        }
    fclose(stdout);
    return 0;
}
