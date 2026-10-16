#include <iostream>
#include <vector>
#include <algorithm> //sort
using namespace std;

int main()
{

    int Tmemoria, Qfita;
    int tamanho = 0;

    
    cout << "Digite o tamanho do dado:" << endl;
    cin >> tamanho;

    vector<char> dado(tamanho);
    vector<char> memoria(Tmemoria);
    vector<char> fita1();
    vector<char> fita2();
    vector<char> fita3();
    vector<char> fita4();
    vector<char> fita5();
    vector<char> fita6();

    cout << "Digite o tamanho da memoria:" << endl;
    cin >> Tmemoria;

    cout << "Digite a quantidade de fitas:" << endl;
    cin >> Qfita;

    cout << "Digite o dado que deseja ordenar:" << endl;
    for (int i = 0; i < tamanho; i++)
    {
        cin >> dado[i];
    }

    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < Tmemoria; j++)
        {
            memoria[j] = dado[i];
        }
        sort(memoria.begin(), memoria.end());
        if (i <= 2 || i >= 9 && i <= 11 || i >= 18 && i <= 20 || i <= 27 && i <= 29)
        {
            for (int k = 0; k < i + 3; k++)
            {
                fita1[k] = 
            }
            
        }
        
        
    }
    

    for (int i = 0; i < tamanho; i++)
    {
        cout << dado[i];
    }

    return (0);
}