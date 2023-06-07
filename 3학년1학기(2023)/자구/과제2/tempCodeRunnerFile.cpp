// ! 8.그래프 BFS 기능 출력
void BFS(Graph G1, int startNode) {
    int V = G1->V;
    int* visited = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }
    
    // Create a queue for BFS
    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;
    
    // Enqueue the start node and mark it as visited
    queue[rear++] = startNode;
    visited[startNode] = 1;
    
    printf("BFS result: ");
    
    while (front != rear) {
        // Dequeue a node from the queue
        int currentNode = queue[front++];
        printf("%d -> ", currentNode+1);
        
        AdjListNode adjacentNode = G1->Adj[currentNode]->Next;
        while (adjacentNode) {
            if (visited[adjacentNode->NodeNum] == 0) {
                // Enqueue the adjacent node and mark it as visited
                queue[rear++] = adjacentNode->NodeNum;
                visited[adjacentNode->NodeNum] = 1;
            }
            adjacentNode = adjacentNode->Next;
        }
    }
    
    printf("NULL\n");
    
    free(visited);
    free(queue);
}