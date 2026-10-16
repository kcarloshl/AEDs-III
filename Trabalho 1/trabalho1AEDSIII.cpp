#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Grafo
{

private:
    bool direcionado;
    int numVertices;

    vector<vector<int>> matriz;
    vector<int> cordeX;
    vector<int> cordeY;

public:
    Grafo() : direcionado(false), numVertices(0) {}

    // importa o grafo de um arquivo
    void importarGrafo(const string &nomearquivo)
    {
        ifstream arq(nomearquivo);

        if (!arq.is_open())
        {
            cout << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        string getlinha;
        arq >> getlinha;
        direcionado = (getlinha == "direcionado=sim");

        arq >> numVertices;

        criarGrafoVazio(numVertices, direcionado);

        for (int i = 0; i < numVertices; i++)
        {
            int v, x, y;
            arq >> v >> x >> y;
            cordeX[v] = x;
            cordeY[v] = y;
        }

        int numArestas;
        arq >> numArestas;

        for (int i = 0; i < numArestas; i++)
        {
            int u, v, peso;
            arq >> u >> v >> peso;
            inserirAresta(u, v, peso);
        }

        cout << "Importacao do gráfico concluida!" << endl;
    }

    // criar um grafo preenchido com 0
    void criarGrafoVazio(int n, bool eDirecionado)
    {
        numVertices = n;
        direcionado = eDirecionado;

        matriz.assign(n, vector<int>(n, 0));
        cordeX.assign(n, 0);
        cordeY.assign(n, 0);
    }

    // exibir a matriz de adjacências
    void exibirMatrizAdjacencias()
    {
        cout << "-----Matriz de Adjacencias:-----" << endl;

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                cout << matriz[i][j] << "/t";
            }

            cout << endl;
        }
    }

    // consultar se um vertice é adjacente ao outro
    bool consultarAdjacencias(int u, int v)
    {
        return matriz[u][v] != 0;
    }

    // inserir uma nova aresta
    void inserirAresta(int u, int v, int peso)
    {
        matriz[u][v] = peso;
        if (!direcionado)
        {
            matriz[v][u] = peso;
        }
    }

    // inserir mais de uma arestas novas
    void inserirArestaConjunto(int u, int v, int peso)
    {
        matriz[u][v] = peso;
        if (!direcionado)
        {
            matriz[v][u] = peso;
        }
    }

    // remover uma aresta existente
    void removerAresta(int u, int v)
    {
        matriz[u][v] = 0;
        if (!direcionado)
        {
            matriz[v][u] = 0;
        }
    }

    // editar cordenadas existentes
    void editarCordenadas(int v, int x, int y)
    {
        cordeX[v] = x;
        cordeY[v] = y;
    }

    // consultar primeiro adjacente do vertice
    int consultarPrimeiroAdjacente(int v)
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (matriz[v][i] != 0)
            {
                return i;
            }
        }
        return -1;
    }

    // consultar proximo adjacente a partir de um
    int consultarProximoAdjacente(int v, int apartir)
    {
        for (int i = apartir + 1; i < numVertices; i++)
        {
            if (matriz[v][i] != 0)
            {
                return i;
            }
        }
        return -1;
    }

    // verificar lista total de adjacencias
    void consultarListaAdjacente(int v)
    {
        cout << "Adjacentes de " << v << endl;
        for (int i = 0; i < numVertices; i++)
        {
            if (matriz[v][i] != 0)
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    // exportar o grafo em um arquivo de texto
    void exportarGrafo(const string &nomearquivo)
    {
        ofstream arq(nomearquivo);

        if (!arq.is_open())
        {
            cout << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        if (direcionado)
        {
            arq << "direcionado=sim" << endl;
        }
        else
        {
            arq << "direcionado=nao" << endl;
        }

        arq << numVertices << endl;

        // gravação do vertice e cordenadas (X,Y)
        for (int i = 0; i < numVertices; i++)
        {
            arq << i << " " << cordeX[i] << " " << cordeY[i] << endl;
        }

        // gravação da quantidade de arestas
        int contAresta = 0;
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (matriz[i][j] != 0)
                {
                    if (!direcionado && j < i)
                    {
                        continue;
                    }
                    contAresta++;
                }
            }
        }

        arq << contAresta << endl;

        // gravação das arestas(vertice de origem, vertice de destino e peso)
        for (int u = 0; u < numVertices; u++)
        {
            for (int v = 0; v < numVertices; v++)
            {
                if (matriz[u][v] != 0)
                {
                    if (!direcionado && v < u)
                    {
                        continue;
                    }

                    arq << u << " " << v << " " << matriz[u][v] << endl;
                }
            }
        }

        cout << "Grafo exportado para " << nomearquivo << endl;
    }
};

int main()
{
    Grafo g;

    int op;

    do
    {
        cout << endl;
        cout << "-----MENU-----" << endl;
        cout << endl;
        cout << "1 - Importar um grafo de um arquivo de texto." << endl;
        cout << "2 - Criar um grafo vazio a partir de um número de vértices informado pelo usuário." << endl;
        cout << "3 - Exibir matriz das adjacências." << endl;
        cout << "4 - Consultar se um vértice é adjacente a outro." << endl;
        cout << "5 - Inserir uma nova aresta." << endl;
        cout << "6 - Inserir arestas em conjunto." << endl;
        cout << "7 - Remover arestas." << endl;
        cout << "8 - Editar a coordenada dos vértices." << endl;
        cout << "9 - Consultar o primeiro adjacente um vértice." << endl;
        cout << "10 - Consultar o próximo adjacente de um vértice a partir de um adjacente informado." << endl;
        cout << "11 - Consultar a lista completa de adjacentes de um vértice." << endl;
        cout << "12 - Exportar o grafo para um arquivo de texto." << endl;
        cout << "0 - SAIR" << endl;
        cin >> op;

        switch (op)
        {
        case 0:
        {
            cout << "PROGRAMA ENCERRADO!" << endl;
            break;
        }

        case 1:
        {
            string arquivo;
            cout << "Qual o nome do arquivo para importação: " << endl;
            cin >> arquivo;
            g.importarGrafo(arquivo);
            break;
        }

        case 2:
        {
            int n;
            string d;
            cout << "Quantos vertices: " << endl;
            cin >> n;
            cout << "É direcionado (sim/nao): " << endl;
            cin >> d;
            g.criarGrafoVazio(n, d == "sim");
            break;
        }

        case 3:
        {
            g.exibirMatrizAdjacencias();
            break;
        }

        case 4:
        {
            int u, v;
            cout << "U: " << endl;
            cin >> u;
            cout << "V: " << endl;
            cin >> v;
            if (g.consultarAdjacencias(u, v))
            {
                cout << "Sim" << endl;
            }
            else
            {
                cout << "Nao" << endl;
            }
            break;
        }

        case 5:
        {
            int u, v, p;
            cout << "U: " << endl;
            cin >> u;
            cout << "V: " << endl;
            cin >> v;
            cout << "Peso: " << endl;
            cin >> p;
            g.inserirAresta(u, v, p);
            break;
        }

        case 6:
        {
            char sn = 's';
            int u, v, p;

            while (sn == 's' || sn == 'S')
            {
                cout << "Vertice de Origem: " << endl;
                cin >> u;
                cout << "Vertice de Destino: " << endl;
                cin >> v;
                cout << "Peso da Aresta: " << endl;
                cin >> p;

                g.inserirArestaConjunto(u, v, p);
                cout << "Aresta inserida!" << endl;

                cout << "Deseja inserir outra (s/n): " << endl;
                cin >> sn;
            }

            break;
        }

        case 7:
        {
            int u, v;
            cout << "U: " << endl;
            cin >> u;
            cout << "V: " << endl;
            cin >> v;
            g.removerAresta(u, v);
            break;
        }

        case 8:
        {
            int v, x, y;
            cout << "V: " << endl;
            cin >> v;
            cout << "X: " << endl;
            cin >> x;
            cout << "Y: " << endl;
            cin >> y;
            g.editarCordenadas(v, x, y);
            break;
        }

        case 9:
        {
            int v;
            cout << "V: " << endl;
            cin >> v;
            cout << "Primeiro Adjacente de " << v << ": " << g.consultarPrimeiroAdjacente(v);
            break;
        }

        case 10:
        {
            int v, a;
            cout << "V: " << endl;
            cin >> v;
            cout << "A partir de: " << endl;
            cin >> a;
            cout << "Proximo Adjacente de " << v << " a partir de" << a << ": " << g.consultarProximoAdjacente(v, a);
            break;
        }

        case 11:
        {
            int v;
            cout << "V: " << endl;
            cin >> v;
            g.consultarListaAdjacente(v);
            break;
        }

        case 12:
        {
            string arquivo;
            cout << "Qual o nome do arquivo para exportação: " << endl;
            cin >> arquivo;
            g.exportarGrafo(arquivo);
            break;
        }

        default:
        {
            cout << "Opcao Invalida!" << endl;
            cout << "Por Favor Escolha Outra:" << endl;
            break;
        }
        }

    } while (op != 0);
    return 0;
}