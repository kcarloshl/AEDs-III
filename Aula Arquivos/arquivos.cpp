#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    /*
    ofstream arq;

    arq.open("arquivo.txt", ios::app);
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    arq << "Exemplo de texto para arquivo" << endl;
    arq.put('P');
    //arq.flush();
    arq.close();
*/
/*
    ifstream arq;

    arq.open("arquivo.txt");

    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    string linha;
    char letra;

    while (!arq.eof())
    {
        getline(arq, linha);
        arq.get(letra);
        arq.ignore();

        cout << "Linha: " << linha << endl;
        cout << "Caractere: " << letra << endl;
    }
*/

    int tmemoria, fitas, i;
    char c;
    vector <char> mem;

    fstream arq("dados.in", ios::in);

    arq >> tmemoria >> fitas;
    arq.ignore();

    cout << "Fitas: " << fitas << endl;
    cout << "T. Memoria: " << tmemoria << endl;

    while (!arq.eof())
    {
        i = 0;
        while (i < tmemoria && !arq.eof())
        {
            arq.get(c);
            mem.push_back(c);
            i++;
            arq >> ws;
        }
        
        sort(mem.begin(), mem.end());
        cout << string(mem.begin(), mem.end()) << endl;
        mem.clear();
    }
    
    arq.close();

    return 0;
}