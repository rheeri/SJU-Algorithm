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
typedef struct IncidentEdge
{
	int edge_num;
	struct IncidentEdge* next;
}IncidentEdge;
typedef struct Vertex
{
	char name;
	struct IncidentEdge* incidentedge;
}Vertex;
typedef struct Graph
{
	struct Vertex vertex[6];
	struct Edge edge[22];
}Graph;
void insert_vertexlist(Graph* graph, int edge, int b);
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
void insert_vertexlist(Graph* graph, int edge, int b) {
	IncidentEdge* newEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	newEdge->edge_num = edge;
	newEdge->next = NULL;

	IncidentEdge* p = graph->vertex[b].incidentedge;
	while (p->next != NULL) p = p->next;
	p->next = newEdge;
}
void initi(Graph* graph)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		graph->vertex[i].name = i + '1';
		graph->vertex[i].incidentedge = (IncidentEdge*)malloc(sizeof(IncidentEdge));
		memset(graph->vertex[i].incidentedge, 0, sizeof(IncidentEdge));
		graph->vertex[i].incidentedge->edge_num = -1;
		graph->vertex[i].incidentedge->next = NULL; //추가
	}

	memset(graph->edge, -1, sizeof(graph->edge));

	graph->edge[0].endpoint = 1;
	graph->edge[0].vertex1 = graph->vertex[0].name;
	graph->edge[0].vertex2 = graph->vertex[1].name;
	insert_vertexlist(graph, 0, 0);
	insert_vertexlist(graph, 0, 1);

	graph->edge[1].endpoint = 1;
	graph->edge[1].vertex1 = graph->vertex[0].name;
	graph->edge[1].vertex2 = graph->vertex[2].name;
	insert_vertexlist(graph, 1, 0);
	insert_vertexlist(graph, 1, 2);

	graph->edge[2].endpoint = 1;
	graph->edge[2].vertex1 = graph->vertex[0].name;
	graph->edge[2].vertex2 = graph->vertex[3].name;
	insert_vertexlist(graph, 2, 0);
	insert_vertexlist(graph, 2, 3);

	graph->edge[3].endpoint = 2;
	graph->edge[3].vertex1 = graph->vertex[0].name;
	graph->edge[3].vertex2 = graph->vertex[5].name;
	insert_vertexlist(graph, 3, 0);
	insert_vertexlist(graph, 3, 5);

	graph->edge[4].endpoint = 1;
	graph->edge[4].vertex1 = graph->vertex[1].name;
	graph->edge[4].vertex2 = graph->vertex[2].name;
	insert_vertexlist(graph, 4, 1);
	insert_vertexlist(graph, 4, 2);

	graph->edge[5].endpoint = 4;
	graph->edge[5].vertex1 = graph->vertex[2].name;
	graph->edge[5].vertex2 = graph->vertex[4].name;
	insert_vertexlist(graph, 5, 2);
	insert_vertexlist(graph, 5, 4);

	graph->edge[6].endpoint = 4;
	graph->edge[6].vertex1 = graph->vertex[4].name;
	graph->edge[6].vertex2 = graph->vertex[4].name;
	insert_vertexlist(graph, 6, 4);

	graph->edge[7].endpoint = 3;
	graph->edge[7].vertex1 = graph->vertex[4].name;
	graph->edge[7].vertex2 = graph->vertex[5].name;
	insert_vertexlist(graph, 7, 4);
	insert_vertexlist(graph, 7, 5);
}
void cmmd_a(Graph* graph) {
	int node;
	scanf("%d", &node);
	getchar();

	//node가 존재하지 않는 경우
	if (node <= 0 || node > MAX) {
		printf("-1\n");
		return;
	}

	int p[100][2];
	int cnt = 0;

	Vertex v = graph->vertex[node - 1];
	IncidentEdge* i = v.incidentedge;

	while (i->next != NULL) {
		i = i->next;
		int w = graph->edge[i->edge_num].endpoint;

		char inode;
		if (graph->edge[i->edge_num].vertex1 == (char)(node + '0')) inode = graph->edge[i->edge_num].vertex2;
		else inode = graph->edge[i->edge_num].vertex1;

		p[cnt][0] = inode - '0';
		p[cnt][1] = w;
		cnt++;
	}

	for (int i = 0; i < cnt - 1; i++) {
		for (int j = i; j < cnt; j++) {
			if (p[i][0] > p[j][0]) {
				int tmp1 = p[i][0];
				int tmp2 = p[i][1];
				p[i][0] = p[j][0];
				p[i][1] = p[j][1];
				p[j][0] = tmp1;
				p[j][1] = tmp2;
			}
		}
	}
	for (int i = 0; i < cnt; i++) {
		printf(" %d %d", p[i][0], p[i][1]);
	}
	printf("\n");
	return;
}
void cmmd_b(Graph* graph) {
	int a, b, w;
	scanf("%d %d %d", &a, &b, &w);
	getchar();

	Vertex v = graph->vertex[a - 1];
	IncidentEdge *i = v.incidentedge;

	//그래프에 정점 a or b가 존재하지 않으면
	if (a > MAX || b > MAX || a <= 0 || b <= 0) {
		printf("-1\n");
		return;
	}

	//w=0이면 간선(a,b)를 삭제
	if (w == 0) {
		int removeE;
		for (int i = 0; i <= E; i++) {
			char v1 = (char)(a + '0');
			char v2 = (char)(b + '0');
			if ((graph->edge[i].vertex1 == v1 && graph->edge[i].vertex2 == v2) || (graph->edge[i].vertex1 == v2 && graph->edge[i].vertex2 == v1)) {
				removeE = i;
				break;
			}
		}

		//a == b인 경우
		IncidentEdge* ci = graph->vertex[a - 1].incidentedge;
		if (a == b) {
			while (ci->next != NULL) {
				if (ci->next->edge_num == removeE) {
					ci->next = ci->next->next;
					return;
				}
				ci = ci->next;
			}
		}

		//a!=b인 경우
		IncidentEdge* ai = graph->vertex[a - 1].incidentedge;
		while (ai->next != NULL) {
			if (ai->next->edge_num == removeE) {
				ai->next = ai->next->next;
				break;
			}
			ai = ai->next;
		}
		IncidentEdge* bi = graph->vertex[b - 1].incidentedge;
		while (bi->next != NULL) {
			if (bi->next->edge_num == removeE) {
				bi->next = bi->next->next;
				return;
			}
			bi = bi->next;
		}
	}

	//간선(a,b)의 가중치를 w로 변경, 간선이 존재하지 않으면 새로 생성
	while (i->next != NULL) {
		i = i->next;
		if (graph->edge[i->edge_num].vertex1 == (char)(a + '0') && graph->edge[i->edge_num].vertex2 == (char)(b + '0') || graph->edge[i->edge_num].vertex2 == (char)(a + '0') && graph->edge[i->edge_num].vertex1 == (char)(b + '0')) {
			graph->edge[i->edge_num].endpoint = w;
			return;
		}
	}

	graph->edge[E].endpoint = w;
	graph->edge[E].vertex1 = (char)(a + '0');
	graph->edge[E].vertex2 = (char)(b + '0');

	//a == b인 경우, 한 번만 insert해야 함
	insert_vertexlist(graph, E, a - 1);
	if (a != b) {
		insert_vertexlist(graph, E, b - 1);
	}
	E += 1;
	return;
}