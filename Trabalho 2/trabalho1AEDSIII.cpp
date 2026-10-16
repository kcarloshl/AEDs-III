#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <cmath>

using namespace std;

class Grafo
{

private:
    bool direcionado;
    int numVertices;

    vector<vector<int>> matriz;
    vector<int> cordeX;
    vector<int> cordeY;

    vector<string> nome;

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
            arq >> ws;
            getline(arq, nome[v]);

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

        cout << "Importacao do grafico concluida!" << endl;
    }

    // criar um grafo preenchido com 0
    void criarGrafoVazio(int n, bool eDirecionado)
    {
        numVertices = n;
        direcionado = eDirecionado;

        matriz.assign(n, vector<int>(n, 0));
        cordeX.assign(n, 0);
        cordeY.assign(n, 0);
        nome.assign(n, "");
    }

    // exibir a matriz de adjacências
    void exibirMatrizAdjacencias()
    {
        cout << "----------Matriz de Adjacencias:----------" << endl;

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                cout << matriz[i][j] << "\t";
            }

            cout << endl;
        }
    }

    // exibir vertices e seus nomes
    void exibirVerticesNomes()
    {
        cout << "Vertices e Seus Nomes: " << endl;

        for (int i = 0; i < numVertices; i++)
        {
            cout << matriz[i][0] << "\t" << nome[i];
            cout << endl;
        }
    }

    // consultar se um vertice é adjacente ao outro
    bool consultarAdjacencias(int u, int v)
    {
        return matriz[u][v] != 0;
    }

    // inserir uma nova aresta e inserir em conjunto
    void inserirAresta(int u, int v, int peso)
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
            arq << i << " " << cordeX[i] << " " << cordeY[i] << " " << nome[i] << endl;
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

    // edição dos nomes dos vertices
    void editarNomeVertice(int v, const string &novoNome)
    {
        if (v < 0 || v >= numVertices)
        {
            cout << "Vertice inexistente/invalido!" << endl;
            return;
        }

        nome[v] = novoNome;
    }

    // exibir nomes dos vertices
    void exibirNomeVertice()
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << "Vertice: " << i << " Nome: " << nome[i] << endl;
        }
    }

    // Busca Em Profundidade
    void buscaEmProfundidade()
    {
        // Declarar vetores de descoberta, termino, antecessor e cor
        vector<int> descoberta;
        vector<int> termino;
        vector<int> antecessor;
        vector<char> cor;

        descoberta.resize(numVertices);
        termino.resize(numVertices);
        antecessor.resize(numVertices);
        cor.resize(numVertices);

        // Declarar e inicializar com zero a variável tempo;
        int tempo = 0;

        // Inicializar vetor de antecessor com -1 e inicializar vetor de cor com BRANCO
        for (int i = 0; i < numVertices; i++)
        {
            antecessor[i] = -1;
            cor[i] = 'B';
        }

        // Para cada vértice u branco
        // Executar visitaEmProfundidade para u
        for (int u = 0; u < numVertices; u++)
        {
            if (cor[u] == 'B')
            {
                visitaEmProfundidade(u, tempo, descoberta, termino, antecessor, cor);
            }
        }
    }

private:
    void visitaEmProfundidade(int u, int &tempo, vector<int> &descoberta, vector<int> &termino, vector<int> &antecessor, vector<char> &cor)
    {
        // Colorir vértice u de cinza, incrementar o tempo e registrar tempo de descoberta u
        cor[u] = 'C';
        tempo++;
        descoberta[u] = tempo;

        // Exibir informações de descoberta
        cout << "Vertice: " << u << " | Tempo de Descoberta: " << descoberta[u] << endl;
        cout << endl;

        // Para cada vértice v adjacente branco do vértice u
        // Registrar antecessor de v sendo u
        // Executar visitaEmProfundidade recursivamente para v
        for (int v = 0; v < numVertices; v++)
        {
            if (matriz[u][v] != 0 && cor[v] == 'B')
            {
                antecessor[v] = u;
                visitaEmProfundidade(v, tempo, descoberta, termino, antecessor, cor);
            }
        }

        // Colorir vértice u de preto, incrementar o tempo e registrar tempo de término para u
        cor[u] = 'P';
        tempo++;
        termino[u] = tempo;

        // Exibir informações de finalização do vértice
        cout << "Informacoes de Finalizacao: " << endl;
        cout << "Vertice: " << u << endl;
        cout << "Tempo de Descoberta: " << descoberta[u] << endl;
        cout << "Tempo de Termino: " << termino[u] << endl;
        cout << "Antecessor: " << antecessor[u] << endl;
        if (cor[u] == 'P')
        {
            cout << "Cor: " << "Preto" << endl;
        }
        cout << endl;
    }

    // Busca Em Largura
public:
    void buscaEmLargura()
    {
        // Declarar vetores de antecessor, cor e distância
        vector<int> antecessor(numVertices);
        vector<char> cor(numVertices);
        vector<double> distancia(numVertices);

        // Inicializar vetor de antecessor com -1, o vetor de cor com BRANCO e o vetor de distância com INFINITO
        for (int i = 0; i < numVertices; i++)
        {
            antecessor[i] = -1;
            cor[i] = 'B';
            distancia[i] = INFINITY;
        }

        // Para cada vértice u branco:
        // Executar visitaEmLargura para u.
        for (int u = 0; u < numVertices; u++)
        {
            if (cor[u] == 'B')
            {
                visitaEmLargura(u, antecessor, cor, distancia);
            }
        }
    }

private:
    void visitaEmLargura(int u, vector<int> &antecessor, vector<char> &cor, vector<double> &distancia)
    {
        // Colorir vértice u de cinza
        cor[u] = 'C';

        // Definir a distância do vértice u como 0
        distancia[u] = 0;

        // Criar uma fila vazia f
        queue<int> fila;

        // Enfileirar o vértice u em f
        fila.push(u);

        // Exibir informações de descoberta
        cout << "Vertice: " << u << " | Distancia: " << distancia[u] << endl;
        cout << endl;

        // Enquanto houver vértice na fila f
        while (!fila.empty())
        {
            // Pega o proximo da fila
            int v = fila.front();
            // Desenfileirar o vértice v de fila f
            fila.pop();

            // Para cada vértice k adjacente branco de v
            for (int k = 0; k < numVertices; k++)
            {
                if (matriz[v][k] != 0 && cor[k] == 'B')
                {
                    // Colorir vértice k de cinza
                    cor[k] = 'C';

                    // Registrar antecessor de k sendo v
                    antecessor[k] = v;

                    // Registrar a distância de k como a distância de v somada de 1
                    distancia[k] = distancia[v] + 1;

                    // Enfileirar k na fila f
                    fila.push(k);
                }
            }

            // Colorir vértice v de preto
            cor[v] = 'P';

            // Exibir informações de finalização do vértice
            cout << "Vertice: " << v
                 << " | Distancia: " << distancia[v]
                 << " | Antecessor: " << antecessor[v];
            if (cor[v] == 'P')
            {
                cout << " | Cor: " << "Preto" << endl;
            }
            cout << endl;
        }
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
        cout << "2 - Criar um grafo vazio a partir de um numero de vertices informado pelo usuario." << endl;
        cout << "3 - Exibir matriz das adjacencias." << endl;
        cout << "4 - Consultar se um vertice e adjacente a outro." << endl;
        cout << "5 - Inserir uma nova aresta." << endl;
        cout << "6 - Inserir arestas em conjunto." << endl;
        cout << "7 - Remover arestas." << endl;
        cout << "8 - Editar a coordenada dos vertices." << endl;
        cout << "9 - Consultar o primeiro adjacente um vertice." << endl;
        cout << "10 - Consultar o proximo adjacente de um vertice a partir de um adjacente informado." << endl;
        cout << "11 - Consultar a lista completa de adjacentes de um vertice." << endl;
        cout << "12 - Exportar o grafo para um arquivo de texto." << endl;
        cout << "13 - Editar o nome de um vertice." << endl;
        cout << "14 - Exibir nome do vertice." << endl;
        cout << "15 - Busca Em Profundidade." << endl;
        cout << "16 - Busca Em Largura." << endl;
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
            cout << "Qual o nome do arquivo para importacao: " << endl;
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
            cout << "E direcionado (sim/nao): " << endl;
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

                g.inserirAresta(u, v, p);
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
            cout << "Qual o nome do arquivo para exportacao: " << endl;
            cin >> arquivo;
            g.exportarGrafo(arquivo);
            break;
        }

        case 13:
        {
            int v;
            string novoNome;

            cout << "Vertice: " << endl;
            cin >> v;
            cout << "Novo nome: " << endl;
            cin >> ws;
            getline(cin, novoNome);

            g.editarNomeVertice(v, novoNome);
            cout << "Nome editado com sucesso!" << endl;
            break;
        }

        case 14:
        {
            g.exibirNomeVertice();
            break;
        }

        case 15:
        {
            g.buscaEmProfundidade();
            break;
        }

        case 16:
        {
            g.buscaEmLargura();
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