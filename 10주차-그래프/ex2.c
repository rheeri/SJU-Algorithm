//인접리스트 구현
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX 6
int E = 8; //Edge number

typedef struct Edge
{
	int endpoint; // weight
	char vertex1, vertex2;
}Edge;
typedef struct Vertex
{
	char name;
	struct IncidentEdge* incidentedge;
}Vertex;
typedef struct Graph
{
	struct Vertex vertex[6];
	struct Edge edge[22];
	int adjacencyMatrix[8][8];
}Graph;
void initi(Graph* graph);
void cmmd_a(Graph* graph);
void cmmd_b(Graph* graph);

void main() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	initi(graph);

	char c;
	while (1) {
		scanf("%c", &c);
		getchar();

		if (c == 'a') {
			cmmd_a(graph);
		}
		else if (c == 'm') {
			cmmd_b(graph);
		}
		else {
			exit(0);
		}
	}
}
void initi(Graph* graph)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		graph->vertex[i].name = i + '1';
	}

	memset(graph->edge, -1, sizeof(graph->edge));
	memset(graph->adjacencyMatrix, -1, sizeof(graph->adjacencyMatrix));

	graph->edge[0].endpoint = 1;
	graph->edge[0].vertex1 = '1';
	graph->edge[0].vertex2 = '2';
	graph->adjacencyMatrix[0][1] = 0;
	graph->adjacencyMatrix[1][0] = 0;

	graph->edge[1].endpoint = 1;
	graph->edge[1].vertex1 = '1';
	graph->edge[1].vertex2 = '3';
	graph->adjacencyMatrix[0][2] = 1;
	graph->adjacencyMatrix[2][0] = 1;

	graph->edge[2].endpoint = 1;
	graph->edge[2].vertex1 = '1';
	graph->edge[2].vertex2 = '4';
	graph->adjacencyMatrix[0][3] = 2;
	graph->adjacencyMatrix[3][0] = 2;

	graph->edge[3].endpoint = 2;
	graph->edge[3].vertex1 = '1';
	graph->edge[3].vertex2 = '6';
	graph->adjacencyMatrix[0][5] = 3;
	graph->adjacencyMatrix[5][0] = 3;

	graph->edge[4].endpoint = 1;
	graph->edge[4].vertex1 = '2';
	graph->edge[4].vertex2 = '3';
	graph->adjacencyMatrix[1][2] = 4;
	graph->adjacencyMatrix[2][1] = 4;

	graph->edge[5].endpoint = 4;
	graph->edge[5].vertex1 = '3';
	graph->edge[5].vertex2 = '5';
	graph->adjacencyMatrix[2][4] = 5;
	graph->adjacencyMatrix[4][2] = 5;

	graph->edge[6].endpoint = 4;
	graph->edge[6].vertex1 = '5';
	graph->edge[6].vertex2 = '5';
	graph->adjacencyMatrix[4][4] = 6;

	graph->edge[7].endpoint = 3;
	graph->edge[7].vertex1 = '5';
	graph->edge[7].vertex2 = '6';
	graph->adjacencyMatrix[4][5] = 7;
	graph->adjacencyMatrix[5][4] = 7;
}
void cmmd_a(Graph* graph) {
	int node;
	scanf("%d", &node);
	getchar();

	int lst[100][2];
	int cnt = 0;
	char id;

	//node가 존재하지 않는 경우
	if (node <= 0 || node > MAX) {
		printf("-1\n");
		return;
	}

	for (int i = 0; i < MAX; i++) {
		if (graph->adjacencyMatrix[node - 1][i] != -1) {
			if (graph->edge[graph->adjacencyMatrix[node - 1][i]].vertex1 == (char)(node + '0'))
				id = graph->edge[graph->adjacencyMatrix[node - 1][i]].vertex2;
			else
				id = graph->edge[graph->adjacencyMatrix[node - 1][i]].vertex1;

			lst[cnt][0] = (int)(id - '0');
			lst[cnt][1] = graph->edge[graph->adjacencyMatrix[node - 1][i]].endpoint;
			cnt++;
		}
	}
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = i; j < cnt; j++) {
			if (lst[i][0] > lst[j][0]) {
				int tmp1 = lst[i][0];
				int tmp2 = lst[i][1];
				lst[i][0] = lst[j][0];
				lst[i][1] = lst[j][1];
				lst[j][0] = tmp1;
				lst[j][1] = tmp2;
			}
		}
	}
	for (int i = 0; i < cnt; i++) {
		printf(" %d %d", lst[i][0], lst[i][1]);
	}
	printf("\n");
	return;

}
void cmmd_b(Graph* graph) {
	int a, b, w;
	scanf("%d %d %d", &a, &b, &w);
	getchar();

	//그래프에 정점 a or b가 존재하지 않으면
	if (a > MAX || b > MAX || a <= 0 || b <= 0) {
		printf("-1\n");
		return;
	}

	//w=0이면 간선(a,b)를 삭제
	if (w == 0) {
		graph->adjacencyMatrix[a - 1][b - 1] = -1;
		graph->adjacencyMatrix[b - 1][a - 1] = -1;
		return;
	}

	//간선(a,b)의 가중치를 w로 변경, 간선이 존재하지 않으면 새로 생성
	if (graph->adjacencyMatrix[a - 1][b - 1] == -1) {
		graph->adjacencyMatrix[a - 1][b - 1] = E;
		graph->adjacencyMatrix[b - 1][a - 1] = E;
		graph->edge[E].vertex1 = (char)(a + '0');
		graph->edge[E].vertex2 = (char)(b + '0');
		graph->edge[E].endpoint = w;
		E++;
	}
	else {
		graph->edge[graph->adjacencyMatrix[a - 1][b - 1]].endpoint = w;
	}
	return;
}