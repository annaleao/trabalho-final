#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Passageiro {
    char cpf[12];
    string nome;
    string endereco;
    string telefone;
    int numPassagem;
    int numPoltrona;
    string voo;
    string horario;
};

void exibirMenu(const string& voo) {
    cout << "EMPRESA AÉREA QUEDA LIVRE - "<< voo << "."  << endl;
    cout << "MENU DE OPÇÕES" << endl;
    cout << "[1] Mostrar Lista de Passageiros" << endl;
    cout << "[2] Pesquisar Passageiro por CPF" << endl;
    cout << "[3] Pesquisar Passageiro por Nome" << endl;
    cout << "[4] Cadastrar Passageiro" << endl;
    cout << "[5] Excluir Passageiro da Lista" << endl;
    cout << "[6] Mostrar Fila de Espera" << endl;
    cout << "[9] Sair" << endl;
    cout << "Digite sua opção: ";
}

bool arquivoExiste(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    return arquivo.good();
}

vector<Passageiro> carregarPassageiros(const string& voo) {
    vector<Passageiro> passageiros;
    string nomeArquivo = voo + ".txt";

    if (!arquivoExiste(nomeArquivo)) {
        return passageiros;
    }

    ifstream arquivo(nomeArquivo);
    string linha;
    while (getline(arquivo, linha)) {
        Passageiro passageiro;
        istringstream iss(linha);
        iss >> passageiro.cpf >> passageiro.nome >> passageiro.endereco >>     passageiro.telefone
            >> passageiro.numPassagem >> passageiro.numPoltrona >> passageiro.voo >> passageiro.horario;
        passageiros.push_back(passageiro);
    }
    arquivo.close();

    return passageiros;
}

void salvarPassageiros(const string& voo, const vector<Passageiro>& passageiros) {
    string nomeArquivo = voo + ".txt";
    ofstream arquivo(nomeArquivo);

    for (const Passageiro& passageiro : passageiros) {
        arquivo << passageiro.cpf << " " << passageiro.nome << " " << passageiro.endereco << " "
                << passageiro.telefone << " " << passageiro.numPassagem << " " << passageiro.numPoltrona
                << " " << passageiro.voo << " " << passageiro.horario << endl;
    }

    arquivo.close();
}

void mostrarListaPassageiros(const string& voo) {
    vector<Passageiro> passageiros = carregarPassageiros(voo);

    if (passageiros.empty()) {
        cout << "A lista de passageiros do voo " << voo << " está vazia." << endl;
        return;
    }

    cout << "Lista de passageiros do voo " << voo << ":" << endl;
    for (const Passageiro& passageiro : passageiros) {
        cout << "CPF: " << passageiro.cpf << ", Nome: " << passageiro.nome << ", Número da Passagem: "
            << passageiro.numPassagem << ", Número da Poltrona: " << passageiro.numPoltrona << endl;
    }
}

void pesquisarPorCPF(const string& voo, const string& cpf) {
    vector<Passageiro> passageiros = carregarPassageiros(voo);
    bool encontrado = false;

    for (const Passageiro& passageiro : passageiros) {
        if (passageiro.cpf == cpf) {
            encontrado = true;
            cout << "Passageiro encontrado:" << endl;
            cout << "CPF: " << passageiro.cpf << ", Nome: " << passageiro.nome << ", Endereço: "
                << passageiro.endereco << ", Telefone: " << passageiro.telefone << ", Número da Passagem: "
                << passageiro.numPassagem << ", Número da Poltrona: " << passageiro.numPoltrona
                << ", Voo: " << passageiro.voo << ", Horário: " << passageiro.horario << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Passageiro não consta neste voo." << endl;
    }
}


void pesquisarPorNome(const string& voo, const string& nome) {
    vector<Passageiro> passageiros = carregarPassageiros(voo);
    bool encontrado = false;

    for (const Passageiro& passageiro : passageiros) {
        if (passageiro.nome == nome) {
            encontrado = true;
            cout << "Passageiro encontrado:" << endl;
            cout << "CPF: " << passageiro.cpf << ", Nome: " << passageiro.nome << ", Endereço: "
                << passageiro.endereco << ", Telefone: " << passageiro.telefone << ", Número da Passagem: "
                << passageiro.numPassagem << ", Número da Poltrona: " << passageiro.numPoltrona
                << ", Voo: " << voo << ", Horário: " << passageiro.horario << endl;
        }
    }

    if (!encontrado) {
        cout << "Passageiro não consta neste voo." << endl;
    }
}

int contarPassageirosFilaEspera(const string& voo) {
    string nomeArquivoFila = voo + "_fila.txt";
    ifstream arquivoFila(nomeArquivoFila);

    if (!arquivoFila || arquivoFila.peek() == ifstream::traits_type::eof()) {
        return 0;
    }

    int contador = 0;
    string linha;

    while (getline(arquivoFila, linha)) {
        contador++;
    }

    arquivoFila.close();

    return contador;
}

void cadastrarPassageiroFilaEspera(const string& voo, const Passageiro& passageiro) {
    string nomeArquivoFila = voo + "_fila.txt";
    ofstream arquivoFila(nomeArquivoFila, ios::app);

    arquivoFila << passageiro.cpf << " " << passageiro.nome << " " << passageiro.endereco << " "
                << passageiro.telefone << " " << passageiro.numPassagem << " " << passageiro.numPoltrona
                << " " << passageiro.voo << " " << passageiro.horario << endl;

    arquivoFila.close();

    cout << "Passageiro cadastrado na fila de espera com sucesso." << endl;
}

void cadastrarPassageiro(const string& voo) {
    Passageiro novoPassageiro;

    cout << "CPF: ";
    cin >> novoPassageiro.cpf;
    cin.ignore();

    cout << "Nome: ";
    getline(cin, novoPassageiro.nome);

    cout << "Endereço: ";
    getline(cin, novoPassageiro.endereco);

    cout << "Telefone: ";
    getline(cin, novoPassageiro.telefone);

    cout << "Número da Passagem: ";
    cin >> novoPassageiro.numPassagem;

    cout << "Número da Poltrona: ";
    cin >> novoPassageiro.numPoltrona;

    novoPassageiro.voo = voo;

    cout << "Horário: ";
    cin.ignore();
    getline(cin, novoPassageiro.horario);

    vector<Passageiro> passageiros = carregarPassageiros(voo);

    if (passageiros.size() < 10) {
        passageiros.push_back(novoPassageiro);
        salvarPassageiros(voo, passageiros);
        cout <<"Passageiro cadastrado com sucesso." << endl;
    } else {
        string nomeArquivoFila = voo + "_fila.txt";
        ifstream arquivoFila(nomeArquivoFila);

        if (!arquivoFila || arquivoFila.peek() == ifstream::traits_type::eof()) {
            cadastrarPassageiroFilaEspera(voo, novoPassageiro);
        } else {
            int tamanhoFila = contarPassageirosFilaEspera(voo);
            if (tamanhoFila < 5) {
                cadastrarPassageiroFilaEspera(voo, novoPassageiro);
            } else {
                cout <<"!!A lista de passageiros está cheia e a fila de espera está completa!!" << endl;
                cout << "!!Não é possível cadastrar o passageiro!!" << endl;
            }
        }

        arquivoFila.close();
    }
}

void excluirPassageiro(const string& voo) {
    vector<Passageiro> passageiros = carregarPassageiros(voo);

    if (passageiros.empty()) {
        cout << "A lista de passageiros do voo " << voo << " está vazia." << endl;
        return;
    }

    string cpf;
    cout << "Digite o CPF do passageiro a ser excluído: ";
    cin >> cpf;

    bool encontrado = false;
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
        if ((*it).cpf == cpf) {
            passageiros.erase(it);
            cout << "Passageiro excluído com sucesso." << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Passageiro não consta neste voo." << endl;
        return;
    }

    if (passageiros.size() < 10) {
        string nomeArquivoFila = voo + "_fila.txt";
        if (arquivoExiste(nomeArquivoFila)) {
            ifstream arquivoFila(nomeArquivoFila);
            string linha;
            if (getline(arquivoFila, linha)) {
                Passageiro proximoPassageiro;
                istringstream iss(linha);
                iss >> proximoPassageiro.cpf >> proximoPassageiro.nome >> proximoPassageiro.endereco
                    >> proximoPassageiro.telefone >> proximoPassageiro.numPassagem >> proximoPassageiro.numPoltrona
                    >> proximoPassageiro.voo >> proximoPassageiro.horario;
                passageiros.push_back(proximoPassageiro);
                cout << "O passageiro " << proximoPassageiro.nome << " foi incluído na lista de passageiros." << endl;

                ofstream novaFila(nomeArquivoFila);
                string novaFilaConteudo;
                while (getline(arquivoFila, novaFilaConteudo)) {
                    novaFila << novaFilaConteudo << endl;
                }
                novaFila.close();
            }
            arquivoFila.close();
        }
    }

    salvarPassageiros(voo, passageiros);
}

void mostrarFilaEspera(const string& voo) {
    string nomeArquivoFila = voo + "_fila.txt";

    if (!arquivoExiste(nomeArquivoFila)) {
        cout << "A fila de espera do voo " << voo << " está vazia." << endl;
        return;
    }

    ifstream arquivoFila(nomeArquivoFila);
    string linha;
    cout << "Fila de espera do voo " << voo << ":" << endl;
    while (getline(arquivoFila, linha)) {
        Passageiro passageiro;
        istringstream iss(linha);
        iss >> passageiro.cpf >> passageiro.nome >> passageiro.endereco >> passageiro.telefone
            >> passageiro.numPassagem >> passageiro.numPoltrona >> passageiro.voo >> passageiro.horario;
        cout << "CPF: " << passageiro.cpf << ", Nome: " << passageiro.nome << ", Número da Passagem: "
            << passageiro.numPassagem << ", Número da Poltrona: " << passageiro.numPoltrona << endl;
    }
    arquivoFila.close();
}

int main() {
    int opcao;
    string voo;

    cout << "Digite o nome do voo (BH-RIO, BH-SP ou BH-BRASÍLIA): ";
    cin >> voo;

    while (true) {
        exibirMenu(voo);
        cin >> opcao;

        switch (opcao) {
            case 1:
                mostrarListaPassageiros(voo);
                break;
            case 2: {
                string cpf;
                cout << "Digite o CPF: ";
                cin >> cpf;
                pesquisarPorCPF(voo, cpf);
                break;
            }
            case 3: {
                string nome;
                cout << "Digite o nome: ";
                cin.ignore();
                getline(cin, nome);
                pesquisarPorNome(voo, nome);
                break;
            }
            case 4:
                cadastrarPassageiro(voo);
                break;
            case 5:
                excluirPassageiro(voo);
                break;
            case 6:
                mostrarFilaEspera(voo);
                break;
            case 9:
                cout << "Saindo do programa." << endl;
                return 0;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    }

    return 0;
}
