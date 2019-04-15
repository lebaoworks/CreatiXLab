#include <stdio.h>
#include <stdlib.h>

#ifndef PATH_FINDING
#define PATH_FINDING
typedef struct NODE_DATA
{
    int index;
    struct NODE_DATA* next;
} NODE;

void path_finding()
{
    FILE * input = fopen("input.txt","r");
    //check and open file
    if (input)
    {
        printf("Reading data... ");
        //init data
        int n, m, u, v;
        int i,a,b;
        int can_go[101][101];
        int prev[101];
        memset(can_go,0,sizeof(can_go));
        memset(prev,0,sizeof(prev));

        //read data
        fscanf(input,"%d %d %d %d", &n, &m, &u, &v);
        for (i=0; i<m; i++)
        {
            fscanf(input,"%d %d",&a,&b);
            can_go[a][b] = 1;
        }
        fclose(input);
        printf("Done.\n");

        printf("Processing... ");
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
        printf("Done.\n");

        printf("Exporting...");
        //output
        FILE *output = fopen("output.txt","w");
        if (output)
        {
            if (!prev[u])
                fprintf(output,0);
            else
                while (u>0)
                {
                    if (prev[u]<0)
                        fprintf(output,"%d",u);
                    else
                        fprintf(output,"%d ",u);
                    u = prev[u];
                }
            fclose(output);
            printf("Done.\n");
        }
        else
            printf("Fail.\n");
    }
}
void path_finding_print_result()
{
    FILE *input = fopen("output.txt","r");
    if (input)
    {
        int x;
        printf("Path: ");
        while (!feof(input))
        {
            fscanf(input,"%d",&x);
            if (feof(input))
                printf("%d\n",x);
            else
                printf("%d -> ",x);
        }
        fclose(input);
    }
}
#endif // PATH_FINDING
