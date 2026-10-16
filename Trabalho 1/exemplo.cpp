#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Graph {
private:
    bool directed;
    int numVertices;

    vector<vector<int>> adj;    // matriz de adjacência
    vector<int> coordX;         // coordenada x de cada vértice
    vector<int> coordY;         // coordenada y de cada vértice

public:

    Graph() : directed(false), numVertices(0) {}

    // cria grafo vazio
    void createEmptyGraph(int n, bool isDirected) {
        numVertices = n;
        directed = isDirected;

        adj.assign(n, vector<int>(n, 0));
        coordX.assign(n, 0);
        coordY.assign(n, 0);
    }

    // importa
    void importFromFile(const string &filename) {
        ifstream arq(filename);

        if (!arq.is_open()) {
            cout << "Erro ao abrir arquivo!\n";
            return;
        }

        string dirLine;
        arq >> dirLine;
        directed = (dirLine == "direcionado=sim");

        arq >> numVertices;

        createEmptyGraph(numVertices, directed);

        // ler coordenadas
        for (int i = 0; i < numVertices; i++) {
            int id, x, y;
            arq >> id >> x >> y;
            coordX[id] = x;
            coordY[id] = y;
        }

        int numArestas;
        arq >> numArestas;

        for (int i = 0; i < numArestas; i++) {
            int u, v, peso;
            arq >> u >> v >> peso;
            insertEdge(u, v, peso);
        }

        cout << "Grafo importado com sucesso!\n";
    }

    // exportar
    void exportToFile(const string &filename) {
        ofstream arq(filename);

        if (!arq.is_open()) {
            cout << "Erro ao criar arquivo!\n";
            return;
        }

        arq << "direcionado=" << (directed ? "sim" : "nao") << "\n";
        arq << numVertices << "\n";

        for (int i = 0; i < numVertices; i++)
            arq << i << " " << coordX[i] << " " << coordY[i] << "\n";

        int cont = 0;
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                if (adj[i][j] != 0)
                    cont++;

        arq << cont << "\n";

        for (int u = 0; u < numVertices; u++)
            for (int v = 0; v < numVertices; v++)
                if (adj[u][v] != 0)
                    arq << u << " " << v << " " << adj[u][v] << "\n";

        cout << "Grafo exportado para " << filename << "!\n";
    }

    // exibir matriz
    void showAdjacencyMatrix() {
        cout << "\nMatriz de Adjacência:\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++)
                cout << adj[i][j] << " ";
            cout << "\n";
        }
    }

    // verifica adjacência
    bool isAdjacent(int u, int v) {
        return adj[u][v] != 0;
    }

    // inserir aresta
    void insertEdge(int u, int v, int peso) {
        adj[u][v] = peso;
        if (!directed)
            adj[v][u] = peso;
    }

    // remover aresta
    void removeEdge(int u, int v) {
        adj[u][v] = 0;
        if (!directed)
            adj[v][u] = 0;
    }

    // editar coordenada
    void editVertexCoord(int v, int x, int y) {
        coordX[v] = x;
        coordY[v] = y;
    }

    // primeiro adjacente
    int getFirstAdjacent(int v) {
        for (int j = 0; j < numVertices; j++)
            if (adj[v][j] != 0)
                return j;
        return -1;
    }

    // próximo adjacente após "after"
    int getNextAdjacent(int v, int after) {
        for (int j = after + 1; j < numVertices; j++)
            if (adj[v][j] != 0)
                return j;
        return -1;
    }

    // lista completa dos adjacentes
    void listAdjacents(int v) {
        cout << "Adjacentes de " << v << ": ";
        for (int j = 0; j < numVertices; j++)
            if (adj[v][j] != 0)
                cout << j << " ";
        cout << "\n";
    }
};


/* =================== MENU PRINCIPAL =================== */

int main() {
    Graph g;
    int op;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1 - Importar grafo\n";
        cout << "2 - Criar grafo vazio\n";
        cout << "3 - Exibir matriz\n";
        cout << "4 - Verificar adjacencia\n";
        cout << "5 - Inserir aresta\n";
        cout << "6 - Remover aresta\n";
        cout << "7 - Editar coordenada do vértice\n";
        cout << "8 - Primeira adjacencia\n";
        cout << "9 - Proxima adjacencia\n";
        cout << "10 - Listar adjacentes\n";
        cout << "11 - Exportar grafo\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";
        cin >> op;

        if (op == 1) {
            string arq;
            cout << "Nome do arquivo: ";
            cin >> arq;
            g.importFromFile(arq);
        }
        else if (op == 2) {
            int n; string d;
            cout << "Numero de vertices: ";
            cin >> n;
            cout << "Direcionado (sim/nao): ";
            cin >> d;
            g.createEmptyGraph(n, d == "sim");
        }
        else if (op == 3) {
            g.showAdjacencyMatrix();
        }
        else if (op == 4) {
            int u, v;
            cout << "U V: ";
            cin >> u >> v;
            cout << (g.isAdjacent(u, v) ? "Sim\n" : "Nao\n");
        }
        else if (op == 5) {
            int u, v, p;
            cout << "U V Peso: ";
            cin >> u >> v >> p;
            g.insertEdge(u, v, p);
        }
        else if (op == 6) {
            int u, v;
            cout << "U V: ";
            cin >> u >> v;
            g.removeEdge(u, v);
        }
        else if (op == 7) {
            int v, x, y;
            cout << "V X Y: ";
            cin >> v >> x >> y;
            g.editVertexCoord(v, x, y);
        }
        else if (op == 8) {
            int v;
            cout << "V: ";
            cin >> v;
            cout << "Primeiro adjacente: " << g.getFirstAdjacent(v) << "\n";
        }
        else if (op == 9) {
            int v, a;
            cout << "V After: ";
            cin >> v >> a;
            cout << "Proximo adjacente: " << g.getNextAdjacent(v, a) << "\n";
        }
        else if (op == 10) {
            int v;
            cout << "V: ";
            cin >> v;
            g.listAdjacents(v);
        }
        else if (op == 11) {
            string arq;
            cout << "Nome do arquivo: ";
            cin >> arq;
            g.exportToFile(arq);
        }

    } while (op != 0);

    return 0;
}
