// Theme: Sistema de cadastro em um loteamento, voltado para corretores.
// Developed by Juliano Vieira Goulart, Letícia Cristhinie Alexandre, Pedro Henrique de Oliveira Silva Xavier.
// Class: 14B - BSI 2025/1

#include <iostream>
#include <fstream>

using namespace std;

struct bd {
    char nome[100];
    int idade;
    char estadoCivil[50];
    char cidade[100];
    char finalidade[100];
    char telefone[50];
    char email[50];

    void imprime() {
        cout << endl << "NOME: " << nome << endl
        << "IDADE: " << idade << endl
        << "ESTADO CIVIL: " << estadoCivil << endl
    	<< "CIDADE QUE RESIDE: " << cidade << endl
        << "MOTIVO PARA A COMPRA DO LOTE: " << finalidade << endl
        << "TELEFONE DE CONTATO: " << telefone << endl
        << "EMAIL: " << email << endl << endl;
    }
};

bd* captarDados(int& tamanho, int& capacidade) {
    ifstream arquivoCSV("dados.csv");
    if (!arquivoCSV){
        cout << endl << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO, SERA REDIRECIONADO AO MENU PRINCIPAL." << endl;
    return nullptr;
    }

    char linhaCabecalho[500];
    arquivoCSV.getline(linhaCabecalho, 500);
    
    int numRegistros;
    arquivoCSV >> numRegistros;
    arquivoCSV.ignore();
    
    capacidade=40;
    tamanho=0;
    bd* dadosBD = new bd[capacidade];

    bd dados;
    char lixo;
    
    for(int i=0; i < numRegistros; i++){
        if (tamanho >= capacidade) {
            int acrescimo=10;
            int novaCapacidade = capacidade+acrescimo;
            bd* novoBD = new bd[novaCapacidade];

            for (int j=0; j < tamanho; j++) {
                novoBD[j] = dadosBD[j];
            }
            delete[] dadosBD;
            dadosBD = novoBD;
            capacidade = novaCapacidade;
        }

        arquivoCSV.getline(dados.nome, 100, ',');
        arquivoCSV >> dados.idade;
        arquivoCSV >> lixo;
        arquivoCSV.getline(dados.estadoCivil, 50, ',');
        arquivoCSV.getline(dados.cidade, 100, ',');
        arquivoCSV.getline(dados.finalidade, 100, ',');
        arquivoCSV.getline(dados.telefone, 50, ',');
        arquivoCSV.getline(dados.email, 50);
        
        dadosBD[tamanho] = dados;
        tamanho++;
    }
    arquivoCSV.close();
	return dadosBD;
}

int visualizarESelecionarCliente(int* acao) {
    int numRegistros, capacidade;
    bd* dadosBD = captarDados(numRegistros, capacidade);
    
    if (dadosBD== nullptr || numRegistros== 0) {
        cout << "NENHUM CLIENTE ENCONTRADO!" << endl;
        return -1;
    }
    
    cout << "--------------------------------------------------------------------------------" << endl;
	cout << "COMO DESEJA VISUALIZAR OS CLIENTES?" << endl;
    cout << endl << "1. VER TODOS OS -> " << numRegistros << " CLIENTES" << endl;
    cout << "2. VER CLIENTES EM INTERVALO ESPECIFICO (Como do 90 ao 100)" << endl;
    cout << endl << "ESCOLHA UMA OPCAO: ";
    int opcaoVisualizacao;
    cin >> opcaoVisualizacao;
    cin.ignore();
    
    int inicioListagem=0;
    int fimListagem= numRegistros-1;
    
    if (opcaoVisualizacao == 2){
        cout << endl << "DIGITE A POSICAO INICIAL (1 A " << numRegistros << "): ";
        int posicaoInicial;
        cin >> posicaoInicial;
        cin.ignore();
        
        cout << endl << "DIGITE A POSICAO FINAL (1 A " << numRegistros << "): ";
        int posicaoFinal;
        cin >> posicaoFinal;
        cin.ignore();

        if (posicaoInicial < 1 || posicaoInicial > numRegistros || 
            posicaoFinal < 1 || posicaoFinal > numRegistros || 
            posicaoInicial > posicaoFinal) {
            cout << endl << "INTERVALO INVALIDO!" << endl;
            delete[] dadosBD;
            return -1;
        }
        inicioListagem= posicaoInicial-1;
        fimListagem= posicaoFinal-1;
    } else if (opcaoVisualizacao != 1) {
        cout << endl << "OPCAO INVALIDA!" << endl;
        delete[] dadosBD;
        return -1;
    }
    
    if(*acao ==1) {
		cout << endl << "-----------------------> LISTA DE CLIENTES PARA EDITAR <------------------------" << endl;
	} else if (*acao ==2) {
		cout << endl << "-----------------------> LISTA DE CLIENTES PARA EXCLUIR <-----------------------" << endl;
	}
    cout << "--------------------------------------------------------------------------------" << endl;

    for (int i = inicioListagem; i <= fimListagem; i++) {
        // esse if é apenas para manter a formatação da interface, pois, acima de 3 digitos, os '=', saem do alinhamento.
		if(i < 99) {
            cout << "CLIENTE " << i + 1 << ": =========================================" << endl;
        } else {
            cout << "CLIENTE " << i + 1 << ": ========================================" << endl;
        }
        dadosBD[i].imprime();
    }
    
    cout << "--------------------------------------------------------------------------------" << endl;
    if (*acao ==1) {
		cout << endl << "DIGITE O NUMERO DO CLIENTE QUE DESEJA EDITAR (" << inicioListagem+1 << " AO " << fimListagem+1 << "): ";
	} else if(*acao ==2) {
		cout << endl << "DIGITE O NUMERO DO CLIENTE QUE DESEJA EXCLUIR (" << inicioListagem+1 << " AO " << fimListagem+1 << "): ";
	}
    int clienteEscolhido;
    cin >> clienteEscolhido;
    cin.ignore();
    
    if (clienteEscolhido < 1 || clienteEscolhido > numRegistros) {
        cout << endl << "CLIENTE INVALIDO!" << endl;
        delete[] dadosBD;
        return -1;
    }
    
    delete[] dadosBD;
    return clienteEscolhido-1;
}

void inserirCliente() {
    cout << endl << "DESEJA MESMO INSERIR UM CLIENTE? 1. SIM | 2. NAO (Retornara ao menu principal)." << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    int acaoInserir;
    cin >> acaoInserir;
    cin.ignore();
    
    if (acaoInserir != 1) {
        return;
    }
    
    bd novoCliente;
    cout << endl << "INSIRA O NOME COMPLETO ABAIXO: (Como no exemplo: 'Maria de Oliveira Alexandre')" << endl;
    cin.getline(novoCliente.nome, 100);
	cout << "--------------------------------------------------------------------------------" << endl;
    cout << "INSIRA A IDADE ABAIXO:" << endl;
    cin >> novoCliente.idade;
	cin.ignore();
	cout << "--------------------------------------------------------------------------------" << endl;
    cout << "INSIRA O ESTADO CIVIL ABAIXO: ('Solteiro', 'Casado'...)" << endl;
	cin.getline(novoCliente.estadoCivil, 50);
    cout << "--------------------------------------------------------------------------------" << endl;
	cout << "INSIRA A CIDADE ONDE RESIDE ABAIXO: (Apenas a cidade)" << endl;
    cin.getline(novoCliente.cidade, 100);
    cout << "--------------------------------------------------------------------------------" << endl;
	cout <<"DESEJA: 'Morar', 'Investir' ou 'Montar um Negocio'?" << endl;
    cin.getline(novoCliente.finalidade, 100);
    cout << "--------------------------------------------------------------------------------" << endl;
	cout << "INSIRA O TELEFONE DE CONTATO ABAIXO: (Conforme: (xx) xxxxx-xxxx)" << endl;
    cin.getline(novoCliente.telefone, 50);
    cout << "--------------------------------------------------------------------------------" << endl;
	cout << "INSIRA O EMAIL ABAIXO:" << endl;
    cin.getline(novoCliente.email, 50);

    int numRegistros=0;
    ifstream lerArquivo("dados.csv");
    char linhaCabecalho[500];
    lerArquivo.getline(linhaCabecalho, 500);
    lerArquivo >> numRegistros;
    lerArquivo.ignore();
    
    char linhas[1000][500];
    int numLinhas=0;
    char linha[500];
    
    while(lerArquivo.getline(linha, 500) && numLinhas < 1000){
        int i = 0;
        while(linha[i] != '\0') {
            linhas[numLinhas][i] = linha[i];
            i++;
        }
        linhas[numLinhas][i] = '\0';
        numLinhas++;
    }
    lerArquivo.close(); 
    numRegistros++;

    ofstream arquivoCSV("dados.csv");
    arquivoCSV << "NOME,IDADE,ESTADO CIVIL,CIDADE,FINALIDADE,TELEFONE,EMAIL" << endl;
    arquivoCSV << numRegistros << endl;
    for (int i=0; i < numLinhas; i++){
        arquivoCSV << linhas[i] << endl;
    }
    arquivoCSV << novoCliente.nome << "," << novoCliente.idade << "," << novoCliente.estadoCivil << "," 
    << novoCliente.cidade << "," << novoCliente.finalidade << "," << novoCliente.telefone << "," 
    << novoCliente.email << endl;
    arquivoCSV.close();
    
	cout << endl << "O(A) CLIENTE: " << novoCliente.nome << ", FOI INSERIDO COM SUCESSO!" << endl;
}

void editarDados(){
    cout << endl << "DESEJA MESMO EDITAR UM CLIENTE? 1. SIM | 2. NAO (Retornara ao menu principal)" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    int acaoEditar;
    cin >> acaoEditar;
    cin.ignore();
    
    if (acaoEditar != 1) {
        return;
    }

	int ptrEditar=1;
    int indice= visualizarESelecionarCliente(&ptrEditar);
    
    // o -1 aqui é o retorno da função visualizarESelecionarCliente(), para qualquer erro presente nela.
	// é usado para imprimir a mensagem que informa o usuário sobre cancelamento do procedimento.
	if (indice == -1) { 
        cout << endl << "OPERACAO DE EDICAO CANCELADA! RETORNANDO AO MENU PRINCIPAL." << endl;
        return;
    }

    int numRegistros, capacidade;
    bd* dadosBD = captarDados(numRegistros, capacidade);
    
    if(dadosBD ==nullptr || numRegistros == 0 || indice >= numRegistros){
        cout << "ERRO AO CARREGAR DADOS PARA EDICAO!" << endl;
        if(dadosBD !=nullptr) delete[] dadosBD;
        return;
    }

    cout << endl << "--------------------------> DADOS ATUAIS DO CLIENTE <---------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    dadosBD[indice].imprime();
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl << "QUAL CAMPO DESEJA EDITAR?" << endl;
    cout << "1. NOME" << endl;
    cout << "2. IDADE" << endl;
    cout << "3. ESTADO CIVIL" << endl;
    cout << "4. CIDADE" << endl;
    cout << "5. FINALIDADE" << endl;
    cout << "6. TELEFONE" << endl;
    cout << "7. EMAIL" << endl;
    cout << "8. EDITAR TODOS OS CAMPOS" << endl << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    
    int campoEscolhido=0;
    cin >> campoEscolhido;
    cin.ignore();
    
    switch (campoEscolhido){
        case 1:
            cout << endl << "INSIRA O NOVO NOME COMPLETO: ";
            cin.getline(dadosBD[indice].nome, 100);
            break;
        case 2:
            cout << endl <<"INSIRA A NOVA IDADE: ";
            cin >> dadosBD[indice].idade;
            cin.ignore();
            break;
        case 3:
            cout << endl << "INSIRA O NOVO ESTADO CIVIL ('Casado', 'Solteiro', 'Divorciado'...): ";
            cin.getline(dadosBD[indice].estadoCivil, 50);
            break;
        case 4:
            cout << endl << "INSIRA A NOVA CIDADE (Conforme o exemplo: 'Lavras'): ";
            cin.getline(dadosBD[indice].cidade, 100);
            break;
        case 5:
            cout << endl <<"INSIRA A NOVA FINALIDADE ('Morar', 'Investir' ou 'Montar um Negocio'): ";
            cin.getline(dadosBD[indice].finalidade, 100);
            break;
        case 6:
            cout << endl << "INSIRA O NOVO TELEFONE (Conforme o exemplo: '(xx) xxxxx-xxxx)': ";
            cin.getline(dadosBD[indice].telefone, 50);
            break;
        case 7:
            cout << endl << "INSIRA O NOVO EMAIL: ";
            cin.getline(dadosBD[indice].email, 50);
            break;
        case 8:
            cout << "-------------------------> EDICAO COMPLETA DOS DADOS <--------------------------" << endl << endl;
            cout << "INSIRA O NOVO NOME COMPLETO: ";
            cin.getline(dadosBD[indice].nome, 100);
            cout << "--------------------------------------------------------------------------------" << endl;
			cout << "INSIRA A NOVA IDADE: ";
            cin >> dadosBD[indice].idade;
            cin.ignore();
            cout << "--------------------------------------------------------------------------------" << endl;
			cout <<"INSIRA O NOVO ESTADO CIVIL ('Casado', 'Solteiro', 'Divorciado'...): ";
            cin.getline(dadosBD[indice].estadoCivil, 50);
            cout << "--------------------------------------------------------------------------------" << endl;
			cout <<"INSIRA A NOVA CIDADE (Conforme o exemplo: 'Lavras'): ";
            cin.getline(dadosBD[indice].cidade, 100);
            cout << "--------------------------------------------------------------------------------" << endl;
			cout <<"INSIRA A NOVA FINALIDADE ('Morar', 'Investir' ou 'Montar um Negocio'): ";
            cin.getline(dadosBD[indice].finalidade, 100);
            cout << "--------------------------------------------------------------------------------" << endl;
			cout <<"INSIRA O NOVO TELEFONE (Conforme o exemplo: '(xx) xxxxx-xxxx)': ";
            cin.getline(dadosBD[indice].telefone, 50);
            cout << "--------------------------------------------------------------------------------" << endl;
			cout <<"INSIRA O NOVO EMAIL: ";
            cin.getline(dadosBD[indice].email, 50);
			cout << "--------------------------------------------------------------------------------" << endl;
            break;
        default:
            cout << endl << "OPCAO INVALIDA!" << endl;
            delete[] dadosBD;
            return;
    }
    
    ofstream arquivoCSV("dados.csv");
    arquivoCSV << "NOME,IDADE,ESTADO CIVIL,CIDADE,FINALIDADE,TELEFONE,EMAIL" << endl;
    arquivoCSV << numRegistros << endl;
    for (int i = 0; i < numRegistros; i++) {
        arquivoCSV << dadosBD[i].nome << "," 
                   << dadosBD[i].idade << "," 
                   << dadosBD[i].estadoCivil << "," 
                   << dadosBD[i].cidade << "," 
                   << dadosBD[i].finalidade << "," 
                   << dadosBD[i].telefone << "," 
                   << dadosBD[i].email << endl;
    }
    arquivoCSV.close();
    
    cout << endl <<  "--------------------------------------------------------------------------------"  << endl;
    cout << "O(A) CLIENTE: " << dadosBD[indice].nome << ", FOI EDITADO COM SUCESSO!" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    
    delete[] dadosBD;
}

void excluirDados() {
    cout << endl <<"DESEJA MESMO EXCLUIR UM CLIENTE? 1. SIM | 2. NAO (Retornara ao menu principal)" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    int acaoExcluir;
    cin >> acaoExcluir;
    cin.ignore();
    
    if (acaoExcluir != 1) {
        return;
    }

	int ptrExcluir=2;
    int indice = visualizarESelecionarCliente(&ptrExcluir);
    // aqui, utilizamos o mesmo método para a função de exclusão, pois as funções possuem o mesmo esqueleto.
	// o -1 aqui é o retorno da função visualizarESelecionarCliente(), para qualquer erro presente nela.
	// é usado para imprimir a mensagem que informa o usuário sobre cancelamento do procedimento.
    if (indice == -1) {
        cout << "OPERACAO DE EXCLUSAO CANCELADA! RETORNANDO AO MENU PRINCIPAL." << endl;
        return;
    }

    int numRegistros, capacidade;
    bd* dadosBD = captarDados(numRegistros, capacidade);
    
    if (dadosBD == nullptr || numRegistros == 0 || indice >= numRegistros) {
        cout << "ERRO AO CARREGAR DADOS PARA EXCLUSAO!" << endl;
        if (dadosBD != nullptr) delete[] dadosBD;
        return;
    }

    cout << endl << "----------------------> DADOS DO CLIENTE A SER EXCLUIDO <-----------------------" << endl;
    cout <<  "--------------------------------------------------------------------------------" << endl;
    dadosBD[indice].imprime();
    cout <<  "--------------------------------------------------------------------------------" << endl;
    
    cout << endl << "TEM CERTEZA QUE DESEJA EXCLUIR ESTE CLIENTE?" << endl;
    cout << "1. SIM, Excluir!. | 2. NAO, Desejo retornar ao Menu Principal." << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    int confirmarExclusao;
    cin >> confirmarExclusao;
    cin.ignore();
    
    if (confirmarExclusao != 1) {
        cout << endl << "EXCLUSAO CANCELADA!" << endl << endl;
        delete[] dadosBD;
        return;
    }

    for (int i=indice; i < numRegistros - 1; i++) {
        dadosBD[i] = dadosBD[i + 1];
    }
    numRegistros--;

    ofstream arquivoCSV("dados.csv");
    arquivoCSV << "NOME,IDADE,ESTADO CIVIL,CIDADE,FINALIDADE,TELEFONE,EMAIL" << endl;
    arquivoCSV << numRegistros << endl;
    for (int i=0; i < numRegistros; i++) {
        arquivoCSV << dadosBD[i].nome << "," 
                   << dadosBD[i].idade << "," 
                   << dadosBD[i].estadoCivil << "," 
                   << dadosBD[i].cidade << "," 
                   << dadosBD[i].finalidade << "," 
                   << dadosBD[i].telefone << "," 
                   << dadosBD[i].email << endl;
    }
    arquivoCSV.close();
    cout << endl <<  "--------------------------------------------------------------------------------" << endl;
    cout << "-----------------------> CLIENTE EXCLUIDO COM SUCESSO! <------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    delete[] dadosBD;
}

void imprimirTodosDados(bd* dadosBD, int tamanho) {
    for (int i=0; i < tamanho; i++) {
        if(i < 99) {
            cout << "CLIENTE " << i + 1 << ": =========================================" << endl;
            dadosBD[i].imprime();
        } else {
            cout << "CLIENTE " << i + 1 << ": ========================================" << endl;
            dadosBD[i].imprime();
        }
    }
}

void menuSimples() {
    cout << endl << "----------------- INSIRA O NUMERO DA OPCAO QUE DESEJA, ABAIXO. -----------------" << endl;
    cout <<  "--------------------------------------------------------------------------------" << endl;
    cout << "1. EDITAR DADOS." << endl;
    cout << "2. ADICIONAR UM CLIENTE." << endl;
    cout << "3. EXCLUIR CLIENTE." << endl;
    cout << "4. RETORNAR AO MENU PRINCIPAL." << endl;
    cout <<  "--------------------------------------------------------------------------------" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
}

void todosOsDados() {
    bool continuarNaSecao = true;
    int tamanho, capacidade;
    bd* dadosBD = captarDados(tamanho, capacidade);
    imprimirTodosDados(dadosBD, tamanho);
    
    while(continuarNaSecao) {
        
        if (dadosBD == nullptr){
            return;
        }
        
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "------------------ QUAL ACAO DESEJA REALIZAR AGORA CORRETOR? -------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl << endl;
        menuSimples();
        int acaoSimples;
        cin >> acaoSimples;
        cin.ignore();
        
        switch(acaoSimples){
            case 1:
                editarDados();
            break;
                
            case 2:
                inserirCliente();
            break;
                
            case 3:
                excluirDados();
            break;
                
            case 4: 
                cout << endl << "RETORNANDO AO MENU PRINCIPAL..." << endl;
                continuarNaSecao = false;
            break;
                
            default:
                cout << endl << "OPCAO INVALIDA! TENTE NOVAMENTE." << endl << endl;
            break;
        }
    }
    delete[] dadosBD;
}

void menuPrincipal() {
   
    cout << endl <<  "--------------------------------------------------------------------------------" << endl;
    cout << "-------------------------------> MENU PRINCIPAL <-------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl << endl;
    cout << "---------------------> OLA CORRETOR, COMO POSSO AJUDA-LO? <---------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "1. PARA EXIBIR OS DADOS DE TODOS OS CLIENTES." << endl;
    cout << "2. PARA ADICIONAR UM CLIENTE AO BANCO DE DADOS." << endl;
    cout << "3. PARA EDITAR OS DADOS DE CLIENTES ESPECIFICOS." << endl;
    cout << "4. PARA EXCLUIR OS DADOS DE CLIENTES ESPECIFICOS." << endl;
    cout << "5. PARA SAIR." << endl;
    cout <<  "--------------------------------------------------------------------------------" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
}

bool sairDespedida() {
    cout << endl << "DESEJA MESMO ENCERRAR O PROGRAMA?" << endl;
    cout << "1. SIM  |  2. NAO (Retornara ao menu principal)." << endl << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    int acaoDespedida=0;
    cin >> acaoDespedida;
    
    if(acaoDespedida==1){
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "----------------- OBRIGADO POR USAR NOSSO SISTEMA, ATE BREVE! ------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return true;
    } else if (acaoDespedida < 1 || acaoDespedida > 2){
        cout << endl <<  "--------------------------------------------------------------------------------" << endl;
        cout << "---------------------- ESCOLHA INVALIDA! TENTE NOVAMENTE. ----------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl << endl;
        return sairDespedida();
    } else {
        return false;
    }
}

int main() {
    bool sair=false;
    while (!sair) {
        menuPrincipal();
        int acaoPrincipal, acaoSimples;
        cin >> acaoPrincipal;
        cin.ignore();
        
        switch(acaoPrincipal) {
            case 1:
                cout << endl << "----------------- AQUI ESTAO OS DADOS DE TODOS SEUS CLIENTES! ------------------" << endl;
                cout << "--------------------------------------------------------------------------------" << endl << endl;
                todosOsDados();
            break;
                
            case 2:
                inserirCliente();
            break;
                
            case 3:
                editarDados();
            break;
                
            case 4:
                excluirDados();
            break;
                
            case 5:
                sair=sairDespedida();
            break;
                
            default:
                cout << "OPCAO INVALIDA! Tente novamente." << endl;
            break;
        }
    }
    
return 0;
}