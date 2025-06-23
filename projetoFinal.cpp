// Theme: Sistema de cadastro em um loteamento, voltado para corretores.
// Developed by Juliano Vieira Goulart, Letícia Cristhinie Alexandre, Pedro Henrique de Oliveira Silva Xavier.
// Class: 14B - BSI 2025/1

#include <iostream>
#include <fstream>
#include <cstring>

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

bool validarEmail(const char* email) {
    int tamanho= strlen(email);
    
    // Verifica se está vazio
    if (tamanho == 0) {
        return false;
    }
    
    // Verifica se tem pelo menos 5 caracteres (a@b.c)
    if(tamanho < 5) {
        return false;
    }
    
    // Verifica se contém exatamente um @
    int countArroba=0;
    int posicaoArroba=-1;
    for (int i=0; i < tamanho; i++) {
        if (email[i] == '@') {
            countArroba++;
            posicaoArroba=i;
        }
    }
    
    if (countArroba != 1) {
        return false;
    }
    
    // Verifica se @ não está no início nem no final
    if (posicaoArroba== 0 || posicaoArroba == tamanho-1) {
        return false;
    }
    
    // Verifica se há pelo menos um ponto após o @
    bool temPontoAposArroba= false;
    for (int i=posicaoArroba + 1; i < tamanho; i++){
        if (email[i] == '.') {
            temPontoAposArroba = true;
            // Verifica se o ponto não está no final
            if (i == tamanho - 1) {
                return false;
            }
            break;
        }
    }
    
    if (!temPontoAposArroba) {
        return false;
    }
    
    // Verifica caracteres válidos (letras, números, @, ., _, -)
    for (int i=0; i < tamanho; i++) {
        char c= email[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')|| 
              (c >= '0' && c <= '9') || c == '@' || c == '.' || 
              c == '_' || c == '-')) {
            return false;
        }
    }
    
    return true;
}

bool validarIdade(int idade) {
    return(idade >= 18 && idade <= 110);
}

bool validarTelefone(const char* telefone) {
    int tamanho = strlen(telefone);
    
    // Verifica se está vazio
    if (tamanho == 0) {
        return false;
    }
    
    // Verifica se tem exatamente 15 caracteres: (xx) xxxxx-xxxx
    if (tamanho != 15) {
        return false;
    }
    
    // Verifica formato específico: (xx) xxxxx-xxxx
    // Posição 0: deve ser '('
    if (telefone[0] != '(') {
        return false;
    }
    
    // Posições 1-2: devem ser dígitos (código de área)
    for (int i=1; i <= 2; i++) {
        if (telefone[i] < '0' || telefone[i] > '9') {
            return false;
        }
    }
    
    // Posição 3: deve ser ')'
    if (telefone[3] != ')') {
        return false;
    }
    
    // Posição 4: deve ser espaço
    if (telefone[4] != ' ') {
        return false;
    }
    
    // Posições 5-9: devem ser dígitos (primeiro bloco do número)
    for (int i=5; i <= 9; i++) {
        if (telefone[i] < '0' || telefone[i] > '9') {
            return false;
        }
    }
    
    // Posição 10: deve ser '-'
    if (telefone[10] != '-') {
        return false;
    }
    
    // Posições 11-14: devem ser dígitos (último bloco do número)
    for (int i=11; i <= 14; i++) {
        if (telefone[i] < '0' || telefone[i] > '9') {
            return false;
        }
    }
    
    // Validações adicionais para números válidos no Brasil
    
    // Verifica se o código de área é válido (11-99)
    int DDD=(telefone[1] - '0')*10 +(telefone[2] - '0');
    if (DDD < 11 || DDD > 99) {
        return false;
    }
    
    // Verifica se o primeiro dígito do número é válido (deve ser 9)
    char primeiroDigito= telefone[5];
    if(primeiroDigito != '9') {
        return false;
    }
    
    // Se for celular (começa com 9), verifica se o segundo dígito está correto
    if (primeiroDigito== '9') {
        char segundoDigito = telefone[6];
        if (segundoDigito < '6' || segundoDigito > '9') {
            return false;
        }
    }
    
    return true;
}

void lerEmailComValidacao(char* email) {
    bool emailValido=false;
    while (!emailValido) {
        cin.getline(email, 50);
        if (validarEmail(email)) {
            emailValido=true;
        } else {
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "EMAIL INVALIDO! DIGITE UM EMAIL VALIDO (exemplo: usuario@dominio.com): " << endl;
        }
    }
}

void lerIdadeComValidacao(int* idade) {
    bool idadeValida=false;
    while (!idadeValida) {
        cin >> *idade;
        cin.ignore();
        if (validarIdade(*idade)) {
            idadeValida=true;
        } else {
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "IDADE INVALIDA! DIGITE UMA IDADE ENTRE 18 E 110 ANOS: " << endl;
        }
    }
}

void lerTelefoneComValidacao(char* telefone) {
    bool telefoneValido = false;
    while (!telefoneValido) {
        cin.getline(telefone, 50);
        if (validarTelefone(telefone)) {
            telefoneValido = true;
        } else {
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "TELEFONE INVALIDO! DIGITE UM TELEFONE VALIDO (formato: (xx) xxxxx-xxxx): " << endl;
        }
    }
}

bd* captarDados(int& tamanho, int& capacidade) {
    ifstream arquivoCSV("dados.csv");
    if (!arquivoCSV){
        cout << endl << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO, SERA REDIRECIONADO AO MENU PRINCIPAL." << endl;
    return nullptr;
    }

    // Ignora o cabeçalho.
    arquivoCSV.ignore(1000, '\n');
    
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
    lerIdadeComValidacao(&novoCliente.idade);
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
    lerTelefoneComValidacao(novoCliente.telefone);
    cout << "--------------------------------------------------------------------------------" << endl;
	cout << "INSIRA O EMAIL ABAIXO:" << endl;
    lerEmailComValidacao(novoCliente.email);

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
            lerIdadeComValidacao(&dadosBD[indice].idade);
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
            lerTelefoneComValidacao(dadosBD[indice].telefone);
            break;
        case 7:
            cout << endl << "INSIRA O NOVO EMAIL: ";
            lerEmailComValidacao(dadosBD[indice].email);
            break;
        case 8:
            cout << "-------------------------> EDICAO COMPLETA DOS DADOS <--------------------------" << endl << endl;
            cout << "INSIRA O NOVO NOME COMPLETO: ";
            cin.getline(dadosBD[indice].nome, 100);
            cout << "--------------------------------------------------------------------------------" << endl;
			cout << "INSIRA A NOVA IDADE: ";
            lerIdadeComValidacao(&dadosBD[indice].idade);
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
            lerTelefoneComValidacao(dadosBD[indice].telefone);
            cout << "--------------------------------------------------------------------------------" << endl;
			cout <<"INSIRA O NOVO EMAIL: ";
            lerEmailComValidacao(dadosBD[indice].email);
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
    cout << "1. SIM, excluir e salvar! | 2. NAO, desejo retornar ao Menu Principal." << endl;
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
    cout << "4. ORDENAR CLIENTES. (Recomendado apos a insercao ou edicao de algum cliente.)" << endl;
    cout << "5. RETORNAR AO MENU PRINCIPAL." << endl;
    cout <<  "--------------------------------------------------------------------------------" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
}

// Função Shell Sort por Nome usando gaps de Ciura.
void shellSortPorNome(bd* dados, int numRegistros) {
    int gaps[9] = {1750,701,301,132,57,23,10,4,1};
    int numGaps=9;
    int indiceGap=0;
    while (indiceGap < numGaps && gaps[indiceGap] >= numRegistros) {
        indiceGap++;
    }
    for (int g=indiceGap; g < numGaps; g++) {
        int gap = gaps[g];
        
        for(int i=gap; i < numRegistros; i++) {
            bd temp=dados[i];
            int j;
            for (j=i; j >= gap && strcmp(dados[j-gap].nome, temp.nome) > 0; j -= gap) {
                dados[j] = dados[j-gap];
            }
            dados[j] = temp;
        }
    }
}

// Função Shell Sort por Cidade usando gaps de Ciura.
void shellSortPorCidade(bd* dados, int numRegistros) {
    int gaps[9] = {1750,701,301,132,57,23,10,4,1};
    int numGaps=9;
    int indiceGap=0;
    while (indiceGap < numGaps && gaps[indiceGap] >= numRegistros) {
        indiceGap++;
    }

    for(int g=indiceGap; g < numGaps; g++) {
        int gap=gaps[g];
        
        for (int i=gap; i < numRegistros; i++){
            bd temp=dados[i];
            int j;
            
            for (j=i; j >= gap && strcmp(dados[j-gap].cidade, temp.cidade) > 0; j -= gap){
                dados[j]=dados[j-gap];
            }
            dados[j]=temp;
        }
    }
}

// Busca binária por nome (recursiva)
int buscaBinariaNomeRecursiva(bd* dados, int inicio, int fim, const char* nomeBusca) {
    if (inicio > fim) {
        return -1;
    }
    int meio=inicio + (fim - inicio)/2;
    int comparacao = strcmp(dados[meio].nome, nomeBusca);
    
    if(comparacao == 0) {
        return meio;
    } else if (comparacao > 0){
        return buscaBinariaNomeRecursiva(dados, inicio, meio - 1, nomeBusca);
    } else {
        return buscaBinariaNomeRecursiva(dados, meio + 1, fim, nomeBusca);
    }
}

// Busca binária por cidade (iterativa)
int buscaBinariaCidadeIterativa(bd* dados, int numRegistros, const char* cidadeBusca) {
    int inicio=0;
    int fim=numRegistros -1;
    
    while(inicio <= fim) {
        int meio = inicio + (fim - inicio)/2;
        int comparacao = strcmp(dados[meio].cidade, cidadeBusca);
        
        if (comparacao == 0){
            return meio;
        } else if (comparacao > 0){
            fim = meio-1;
        } else {
            inicio= meio+1;
        }
    }
    return -1;
}

// Função para encontrar todos os registros de uma cidade específica
void buscarTodosComCidade(bd* dados, int numRegistros, const char* cidadeBusca, int* indices, int& quantEncontrados) {
    quantEncontrados=0;
    
    // Primeiro, encontra um registro com a cidade
    int indiceBase = buscaBinariaCidadeIterativa(dados, numRegistros, cidadeBusca);
    if (indiceBase== -1) return;
    
    // Busca para trás
    int i=indiceBase;
    while (i >= 0 && strcmp(dados[i].cidade, cidadeBusca) == 0) {
        indices[quantEncontrados++] = i;
        i--;
    }
    
    // Busca para frente (começando do próximo elemento)
    i=indiceBase + 1;
    while (i < numRegistros && strcmp(dados[i].cidade, cidadeBusca) == 0) {
        indices[quantEncontrados++] = i;
        i++;
    }
    
    // Ordena os índices encontrados
    for (int j=0; j < quantEncontrados - 1; j++) {
        for (int k=j + 1; k < quantEncontrados; k++) {
            if (indices[j] > indices[k]){
                int temp = indices[j];
                indices[j] = indices[k];
                indices[k] = temp;
            }
        }
    }
}

// Função para encontrar todos os registros com um nome específico
void buscarTodosComNome(bd* dados, int numRegistros, const char* nomeBusca, int* indices, int& quantEncontrados) {
    quantEncontrados=0;
    
    // Primeiro, encontra um registro com o nome
    int indiceBase = buscaBinariaNomeRecursiva(dados,0, numRegistros-1, nomeBusca);
    if (indiceBase== -1) return;
    
    // Busca para trás
    int i = indiceBase;
    while(i >= 0 && strcmp(dados[i].nome, nomeBusca) == 0) {
        indices[quantEncontrados++] = i;
        i--;
    }
    
    // Busca para frente (começando do próximo elemento)
    i=indiceBase + 1;
    while (i < numRegistros && strcmp(dados[i].nome, nomeBusca) == 0) {
        indices[quantEncontrados++] = i;
        i++;
    }
    
    // Ordena os índices encontrados
    for (int j=0; j < quantEncontrados - 1; j++) {
        for (int k =j + 1; k < quantEncontrados; k++) {
            if (indices[j] > indices[k]) {
                int temp = indices[j];
                indices[j] = indices[k];
                indices[k] = temp;
            }
        }
    }
}

// Menu de ordenação
void menuOrdenacao() {
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    cout << "-------------------------> OPCOES DE ORDENACAO <-------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "1. ORDENAR POR NOME (A-Z)" << endl;
    cout << "2. ORDENAR POR CIDADE (A-Z)" << endl;
    cout << "3. VOLTAR AO MENU PRINCIPAL" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
}

// Função para ordenar e salvar dados
void ordenarDados() {
    int numRegistros=0, capacidade=0;
    bd* dadosBD = captarDados(numRegistros, capacidade);
    
    if (dadosBD == nullptr || numRegistros == 0) {
        cout << "NENHUM DADO ENCONTRADO PARA ORDENAR!" << endl;
        return;
    }
    
    menuOrdenacao();
    int opcaoOrdenacao;
    cin >> opcaoOrdenacao;
    cin.ignore();
    
    switch (opcaoOrdenacao) {
        case 1:
            cout << endl << "ORDENANDO POR NOME..." << endl;
            shellSortPorNome(dadosBD, numRegistros);
            cout << "DADOS ORDENADOS POR NOME COM SUCESSO!" << endl;
            break;
        case 2:
            cout << endl << "ORDENANDO POR CIDADE..." << endl;
            shellSortPorCidade(dadosBD, numRegistros);
            cout << "DADOS ORDENADOS POR CIDADE COM SUCESSO!" << endl;
            break;
        case 3:
            delete[] dadosBD;
            return;
        default:
            cout << "OPCAO INVALIDA!" << endl;
            delete[] dadosBD;
            return;
    }
    
    // Exibir dados ordenados
    cout << endl << "----------------- DADOS ORDENADOS -----------------" << endl;
    imprimirTodosDados(dadosBD, numRegistros);
    cout << "--------------------------------------------------------------------------------" << endl;
    
    // Pergunta se deseja salvar
    cout << endl << "DESEJA SALVAR A ORDENACAO NO ARQUIVO?" << endl;
    cout << "1. SIM | 2. NAO" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    int salvarOpcao=0;
    cin >> salvarOpcao;
    cin.ignore();
    
    if (salvarOpcao == 1) {
        // Salvar dados ordenados no arquivo
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
        cout << endl << "DADOS ORDENADOS SALVOS COM SUCESSO!" << endl;
    }
    
    delete[] dadosBD;
}

// Menu de busca
void menuBusca() {
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    cout << "------------------------------> OPCOES DE BUSCA <-------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "1. BUSCAR CLIENTE POR NOME" << endl;
    cout << "2. BUSCAR CLIENTE POR CIDADE" << endl;
    cout << "3. VOLTAR AO MENU PRINCIPAL" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
}

void csvParaBinario() {
    int numRegistros=0, capacidade=0;
    bd* dadosBD=captarDados(numRegistros, capacidade);
    
    if (dadosBD== nullptr || numRegistros== 0){
        cout << "NENHUM DADO ENCONTRADO PARA CONVERTER!" << endl;
        return;
    }

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "DESEJA MESMO CONVERTER OS DADOS PARA UM ARQUIVO BINARIO?" << endl;
    cout << "1. SIM. (Recomendado, para a seguranca de seus clientes.) | 2. NAO." << endl;
    cout << "OS DADOS PRESENTES NO ARQUIVO CSV NAO SERAO PERDIDOS! APENAS COPIADOS." << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "ESCOLHA UMA OPCAO: ";

    int opcaoConversao=0;
    cin >> opcaoConversao;
    switch (opcaoConversao){
        case 1: 
        {
            ofstream arquivoBinario("dados.bin",ios::binary);
            if (!arquivoBinario){
                cout << endl << "ERRO AO CRIAR ARQUIVO BINARIO! TENTE NOVAMENTE." << endl;
                    delete[] dadosBD;
                return;
            }

            const char* cabecalho= "NOME,IDADE,ESTADO CIVIL,CIDADE,FINALIDADE,TELEFONE,EMAIL";
            int tamanhoCabecalho= strlen(cabecalho);
            
            arquivoBinario.write(reinterpret_cast<const char*>(&tamanhoCabecalho), sizeof(int));
                arquivoBinario.write(cabecalho, tamanhoCabecalho);
            arquivoBinario.write(reinterpret_cast<const char*>(&numRegistros), sizeof(int));
            for (int i=0; i < numRegistros; i++){
                arquivoBinario.write(dadosBD[i].nome, 100);
                arquivoBinario.write(reinterpret_cast<const char*>(&dadosBD[i].idade), sizeof(int));
                arquivoBinario.write(dadosBD[i].estadoCivil, 50);
                arquivoBinario.write(dadosBD[i].cidade, 100);
                arquivoBinario.write(dadosBD[i].finalidade, 100);
                arquivoBinario.write(dadosBD[i].telefone, 50);
                arquivoBinario.write(dadosBD[i].email, 50);
            }
            arquivoBinario.close();
            delete[] dadosBD;
            
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "----------------> DADOS CONVERTIDOS PARA BINARIO COM SUCESSO! <-----------------" << endl;
            cout << "-------------> ARQUIVO 'dados.bin' ATUALIZADO COM " << numRegistros << " REGISTROS. <--------------" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
        }
        break;
        case 2:
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "OK! RETORNANDO AO MENU PRINCIPAL..." << endl;
            delete[] dadosBD;
        break;
        default:
            cout << endl << "OPCAO INVALIDA! TENTE NOVAMENTE, INSERINDO UMA DAS OPCOES ABAIXO!" << endl;
            delete[] dadosBD;
            cin.clear();
            cin.ignore(1000, '\n');
            csvParaBinario();
        break;
    }
}

// Função principal de busca
void buscarDados() {
    int numRegistros=0, capacidade;
    bd* dadosBD = captarDados(numRegistros, capacidade);
    if(dadosBD== nullptr || numRegistros== 0) {
        cout << "NENHUM DADO ENCONTRADO PARA BUSCAR!" << endl;
        return;
    }
    
    menuBusca();
    int opcaoBusca=0;
    cin >> opcaoBusca;
    cin.ignore();
    
    switch(opcaoBusca) {
        case 1: {
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << endl << "PARA BUSCAR POR NOME, OS DADOS DEVEM ESTAR DEVIDAMENTE ORDENADOS." << endl;
            cout << "OS DADOS ESTAO SENDO ORDENADOS AUTOMATICAMENTE POR NOME EM ORDEM ALFABETICA..." << endl;
            
            shellSortPorNome(dadosBD, numRegistros);
            cout << endl << "DADOS ORDENADOS POR NOME! (Não afeta o arquivo, é apenas momentaneo)" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << endl << "DIGITE O NOME COMPLETO! PARA BUSCAR. (Exatamente como cadastrado): " << endl;
            char nomeBusca[100];
            cin.getline(nomeBusca, 100);
            
            int indices[1000];
            int quantEncontrados;
            buscarTodosComNome(dadosBD, numRegistros, nomeBusca, indices, quantEncontrados);
            
            if (quantEncontrados > 0) {
                cout << endl << "ENCONTRADOS " << quantEncontrados << " CLIENTE(S) COM NOME '" << nomeBusca << "':" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                for (int i = 0; i < quantEncontrados; i++) {
                    cout << "CLIENTE " << indices[i] + 1 << ":" << endl;
                    dadosBD[indices[i]].imprime();
                    cout << "--------------------------------------------------------------------------------" << endl;
                }
            } else {
                cout << endl << "CLIENTE NAO ENCONTRADO!" << endl;
                cout << "LEMBRE-SE: O nome deve ser digitado EXATAMENTE como foi cadastrado." << endl;
            }
        break;
        }
        case 2: {
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << endl << "PARA BUSCAR POR CIDADE, OS DADOS DEVEM ESTAR DEVIDAMENTE ORDENADOS." << endl;
            cout << "OS DADOS ESTAO SENDO ORDENADOS AUTOMATICAMENTE POR CIDADE EM ORDEM ALFABETICA..." << endl;
            
            shellSortPorCidade(dadosBD, numRegistros);
            cout << endl << "DADOS ORDENADOS POR CIDADE! (Não afeta o arquivo, é apenas momentaneo)" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << endl << "DIGITE A CIDADE PARA BUSCAR (Exatamente como cadastrada): " << endl;
            char cidadeBusca[100];
            cin.getline(cidadeBusca, 100);
            
            int indices[1000];
            int quantEncontrados;
            buscarTodosComCidade(dadosBD, numRegistros, cidadeBusca, indices, quantEncontrados);
            
            if(quantEncontrados > 0) {
                cout << endl << "ENCONTRADOS " << quantEncontrados << " CLIENTE(S) NA CIDADE '" << cidadeBusca << "':" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                for (int i = 0; i < quantEncontrados; i++) {
                    cout << "CLIENTE " << indices[i] + 1 << ":" << endl;
                    dadosBD[indices[i]].imprime();
                    cout << "--------------------------------------------------------------------------------" << endl;
                }
            } else {
                cout << endl << "NENHUM CLIENTE ENCONTRADO NA CIDADE: '" << cidadeBusca << "'!" << endl;
                cout << "LEMBRE-SE: A cidade deve ser digitada EXATAMENTE como foi cadastrada." << endl;
            }
        break;
        }
        case 3:
            delete[] dadosBD;
            return;
        break;
        default:
            cout << "OPCAO INVALIDA!" << endl;
            delete[] dadosBD;
            return;
        break;
    }
    
    delete[] dadosBD;
}

void todosOsDados() {
    bool sair= false;
    int numRegistros=0, capacidade=0;
    bd* dadosBD = captarDados(numRegistros, capacidade);
    
    cout << endl << "----------------- AQUI ESTAO OS DADOS DE TODOS SEUS CLIENTES! ------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl << endl;
    imprimirTodosDados(dadosBD, numRegistros);
    
    while(!sair) {
        
        if (dadosBD== nullptr){
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
                ordenarDados();
            break;
            
            case 5: 
                cout << endl << "RETORNANDO AO MENU PRINCIPAL..." << endl;
                sair=true;
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
    cout << "3. PARA EDITAR OS DADOS DE CLIENTES." << endl;
    cout << "4. PARA EXCLUIR OS DADOS DE CLIENTES." << endl;
    cout << "5. PARA BUSCAR CLIENTES ESPECIFICOS." << endl;
    cout << "6. PARA ORDENAR DADOS. (Recomendado apos a insercao ou edicao de algum cliente.)" << endl;
    cout << "7. PARA CONVERTER DADOS PARA CRIPTOGRAFIA BINARIA." << endl;
    cout << "8. PARA SAIR." << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
}

bool sairDespedida() {
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl << "DESEJA ENCERRAR O PROGRAMA?" << endl;
    cout << "1. SIM | 2. NAO (Retornara ao menu principal)." << endl << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    int acaoDespedida=0;
    cin >> acaoDespedida;
    
    if(acaoDespedida==1){
        cout << endl << "--------------------------------------------------------------------------------" << endl;
        cout << "----------------- OBRIGADO POR USAR NOSSO SISTEMA, ATE BREVE! ------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return true;
    } else if (acaoDespedida < 1 || acaoDespedida > 2){
        cout << endl <<  "--------------------------------------------------------------------------------" << endl;
        cout << "---------------------- ESCOLHA INVALIDA! TENTE NOVAMENTE. ----------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return sairDespedida();
    } else {
        return false;
    }
}

int main() {
    bool sair=false;
    while (!sair) {
        menuPrincipal();
        int acaoPrincipal=0;
        cin >> acaoPrincipal;
        cin.ignore();
        
        switch (acaoPrincipal) {
            case 1:
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
                buscarDados();
            break;
            
            case 6:
                ordenarDados();
            break;
            case 7:
                csvParaBinario();
            break;
            case 8:
                sair=sairDespedida();
            break;
                
            default:
                cout << endl <<  "--------------------------------------------------------------------------------" << endl;
                cout << "---------------------- ESCOLHA INVALIDA! TENTE NOVAMENTE. ----------------------" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
            break;
        }
    }
return 0;
}