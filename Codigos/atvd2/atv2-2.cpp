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

    int tmemoria, fitas, i, numFita = 0;
    char c;
    vector <char> mem;

    fstream arq("dadosatv2.in", ios::in);

    arq >> tmemoria >> fitas;
    arq.ignore();

    cout << "Fitas: " << fitas << endl;
    cout << "T. Memoria: " << tmemoria << endl;

    // Geração de Blocos
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
        
        // Criação das Fitas
        numFita = (numFita % fitas) + 1;
        string nomeFita = "fita" + to_string(numFita) + ".txt";
        
        ofstream fitaOut(nomeFita, ios::app);
        fitaOut << string(mem.begin(), mem.end()) << endl;
        mem.clear();
    }
    
    arq.close();

    cout << "\nBlocos gravados nas fitas com sucesso!" << endl;

    return 0;
}