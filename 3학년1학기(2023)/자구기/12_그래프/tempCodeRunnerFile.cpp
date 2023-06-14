    for (i = 0; i < 3; i++)
        insertVertex(G4, i);// G4의 정점 0~2 삽입
    insertEdge(G4, 0, 2);
    insertEdge(G4, 0, 1);
    insertEdge(G4, 1, 2);
    insertEdge(G4, 1, 0);
    printf("\n\n G4의 인접 리스트");
    print_adjList(G4);