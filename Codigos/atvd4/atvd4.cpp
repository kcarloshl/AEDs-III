#include <iostream>
#include <vector>

using namespace std;

struct Item
{
    char chave;
};

void troca(Item &a, Item &b)
{
    Item temp = a;
    a = b;
    b = temp;
}

void refaz_cima_baixo(vector<Item> &v, int k, int N)
{
    while (2 * k <= N)
    {
        int j = 2 * k;

        // encontra o maior filho
        if (j < N && v[j].chave < v[j + 1].chave)
            j++;

        // testa se pai é maior que filho
        if (v[k].chave >= v[j].chave)
            break;

        // troca pai e maior filho, repete
        troca(v[k], v[j]);
        k = j;
    }
}

void refaz_baixo_cima(vector<Item> &v, int k)
{
    while (k > 1 && v[k / 2].chave < v[k].chave)
    {
        troca(v[k], v[k / 2]);
        k = k / 2;
    }
}

void heap_constroi(vector<Item> &v, int n)
{
    for (int k = n / 2; k >= 1; k--)
    {
        refaz_cima_baixo(v, k, n);
    }
}

void heap_insere(vector<Item> &v, int &n, Item novo)
{
    n += 1;
    v[n] = novo;
    refaz_baixo_cima(v, n);
}

Item heap_remove_maximo(vector<Item> &v, int &n)
{
    troca(v[1], v[n]);
    n -= 1;
    refaz_cima_baixo(v, 1, n);
    return v[n + 1];
}

void heapsort(vector<Item> &v, int n)
{
    heap_constroi(v, n);
    int k = n;
    while (k >= 1)
    {
        troca(v[k], v[1]);
        k--;
        refaz_cima_baixo(v, 1, k);
    }
}

void imprime(const vector<Item> &v, int n)
{
    for (int i = 1; i <= n; i++)
        cout << v[i].chave << " ";
    cout << endl;
}

int main()
{
    vector<Item> v(11);
    int n = 10;
    int valores[] = {' ','A', 'L', 'G', 'O', 'R', 'I', 'T', 'M', 'O', 'S'};

    for (int i = 1; i <= n; i++)
        v[i].chave = valores[i];

    cout << "Vetor original:\n";
    imprime(v, n);

    heapsort(v, n);

    cout << "Vetor ordenado:\n";
    imprime(v, n);

    return 0;
}
