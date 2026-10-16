#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int op;
    string nome, idade, altura;
    fstream arq;

    do
    {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "0 - Sair." << endl;
        cout << "1 - Cadastrar." << endl;
        cout << "2 - Listar." << endl;
        cout << endl;

        cin >> op;
        cin.ignore();

        switch (op)
        {
        case 0:
        {
            cout << "PROGRAMA ENCERRADO!" << endl;
            break;
        }
        case 1:
        {
            arq.open("dadosatv3.in", ios::app);
            if (!arq.is_open())
            {
                cout << "Erro ao abrir o arquivo!" << endl;
                return 1;
            }

            cout << "Digite o nome: " << endl;
            cin >> nome;
            cout << "Digite a idade: " << endl;
            cin >> idade;
            cout << "Digite a altura: " << endl;
            cin >> altura;

            arq << nome << endl;
            arq << idade << endl;
            arq << altura << endl;
            // arq.flush(); o flush é uma função para não precisar fechar o programa para
            arq.close(); // que os dados inseridos seja salvo nos arquivos.
            break;
        }
        case 2:
        {
            fstream arq("dadosatv3.in", ios::in);

            while (!arq.eof())
            {
                getline(arq, nome);
                getline(arq, idade);
                getline(arq, altura);

                cout << "Nome: " << nome << endl;
                cout << "Idade: " << idade << endl;
                cout << "Altura: " << altura << endl;
                cout << endl;
                arq >> ws;
            }
            arq.close();
            break;
        }

        default:
        {
            cout << "Opção Inválida! Escolha Outra." << endl;
            break;
        }
        }
    } while (op != 0);

    return (0);
}