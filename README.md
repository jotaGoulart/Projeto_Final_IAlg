Projeto Prático: Cadastro para loteamento.

Este é um projeto feito na linguagem C++, que visa manipular uma base de dados, proporcionando ao usuário uma interface intuitiva e clara. Além de, propiciar algumas ações para o mesmo, como: inserir, excluir, editar, ordenar, visualizar, buscar e copiar a base de dados para um arquivo do tipo binário.

Este programa foi desenvolvido pelos alunos: Juliano Vieira Goulart,  Letícia Cristhinie Alexandre e Pedro Henrique de Oliveira Silva Xavier. Todos, integrantes da turma 14B, da disciplina Introdução aos Algoritmos, lecionada pela professora PhD Elaine Cecília Gatto, do Departamento de Ciência da Computação - DCC, na Universidade Federal de Lavras - UFLA.

Descrição do Projeto:

O código funciona mediante a um arquivo .csv, que contém uma base de dados, contendo os campos: Nome, Idade, Estado Civil, Cidade, Finalidade, Telefone de contato e E-mail. Todos os dados presentes, são para fins de uso no código e não para corresponder com a realidade. Essa composição de dados, se deu por uma pesquisa feita com um corretor real, que nos direcionou a tais campos.

O programa se inicia com o ‘Menu Principal’, criado para dar a devida mobilidade ao usuário dentro da execução do programa. Ele apresenta as funcionalidades disponíveis ao cliente, solicitando que ele insira o número correspondente a ação em que deseja realizar.

Cada ação, se permeia a uma gama de funções implementadas no código-fonte, buscando a otimização da manipulação dos dados. Durante a execução, é pedido ao usuário a confirmação de cada ação que ele deseja realizar,  reproduzindo uma interface intuitiva e focada na compreensão por parte do mesmo. Com recomendações úteis e validações de e-mail, telefone, idade e outros campos para manter um padrão dentro do arquivo .csv

Todas as funcionalidades presentes no programa, estão dentro de um ‘switch’ na função ‘Int Main’. Optamos por esse formato, visando a facilidade na manutenção do código, já que o mesmo é dividido em várias funções, deixando assim, o fluxo bem claro, limpo e objetivo.





Descrição das funções presentes no código-fonte:

struct bd: é o registro que contém os campos da base de dados do arquivo .csv.

void imprime: dentro da struct, ele imprime os clientes quando solicitado, mantendo um formato base para essa impressão.

bool validarEmail: verifica se o e-mail inserido pelo usuário está na formatação correta.

bool validarIdade: verifica se a idade inserida está de acordo com a realidade.

bool validarTelefone: verifica se o telefone inserido está no formato brasileiro de escrita padrão.

bool validarCampoTexto: verifica se o texto inserido está não está vazio.

void lerEmailComValidacao: procedimento que lê (quando solicitado) o e-mail escrito pelo usuário e aplica a validação presente na função “validarEmail”.

void lerIdadeComValidacao: procedimento que lê (quando solicitado) a idade escrita pelo usuário e aplica a validação presente na função “validarIdade”.

void lerCampoComValidacao: procedimento que lê (quando solicitado) o texto escrito pelo usuário e aplica a validação presente na função “validarCampoTexto”.

void lerEmailComValidacao: procedimento que lê (quando solicitado) o telefone escrito pelo usuário e aplica a validação presente na função “validarTelefone”.

bd* captarDados: capta os dados presente no arquivo .csv, tornando-a uma função crucial dentro do programa. Ignora o cabeçalho, coleta o número de registros e por fim, os dados de todos os clientes presentes no arquivo .csv.

int visualizarESelecionarCliente: é a função que quando solicitada recebe um valor entre 1 e 2, vindos das funções “inserirCliente” e “excluirCliente”, para que possa gerar a opção do usuário realizar tais ações com a interface correta e do modo preferido pelo mesmo. Além de dar a opção da visualização particionada ou completa dos dados.

void inserirCliente: é a função que permite a inserção de novos clientes à base de dados, solicitando a inserção dos dados em sequência e realizando a reescrita do arquivo .csv atualizado.

void editarDados: é a função que permite a edição dos dados de algum cliente presente no arquivo .csv, nela, o usuário pode editar um campo, ou todos eles. De acordo com sua preferência.

void excluirDados: é a função que permite a exclusão de algum cliente presente no arquivo .csv. Solicita a confirmação de exclusão e após confirmada, reescreve todo o arquivo .csv atualizado.

void imprimirTodosDados: é a função que imprime todos os dados quando solicitada, mantendo um formato padrão.

void menuSimples: é menu extra, acionado apenas quando solicitada a opção ‘1’ no menu principal, permite a manipulação dos dados já exibidos. Mantido por uma estrutura de repetição ‘while’, desligada apenas quando selecionada a opção ‘5’ no próprio menu simples.

void shellSortPorNome: é a ordenação por nome em ordem alfabética, para possibilitar a busca binária pelo campo ‘nome’. Utilizando os ‘gaps ciura’, para otimização.

void shellSortPorCidade: é a ordenação por cidade em ordem alfabética, para possibilitar a busca binária pelo campo ‘cidade’. Utilizando os ‘gaps ciura’, para otimização.

int buscaBinariaNomeRecursiva: é a função que possibilita a busca utilizando o campo ‘nome’, de forma recursiva, preferida no caso, para mostrar domínio da ambas maneiras (recursiva e iterativa).

int buscaBinariaCidadeIterativa: é a função que possibilita a busca utilizando o campo ‘cidade’, de forma iterativa, preferida no caso, para mostrar domínio da ambas maneiras (recursiva e iterativa).

void buscarTodosComCidade: busca todos os clientes com a mesma cidade recebida da função “buscaBinariaCidadeIterativa”.

void buscarTodosComNome: busca todos os clientes com o mesmo nome recebido da função “buscaBinariaNomeRecursiva”.

void menuOrdenacao: é um menu extra, básico e fundamental para a escolha do tipo de ordenação preferido.

void ordenarDados: função que ordena os dados de acordo com a preferência do usuário, reescrevendo de forma ordenada no arquivo .csv.

void menuBusca: mais um dos menus extras, que novamente é básico e fundamental para a escolha do tipo de busca.

void csvParaBinario: é a função que permite gravar os dados atualizados durante o programa em um arquivo binário “.bin”, permitindo assim, a criptografia da base de dados, desde que, o usuário faça o procedimento durante a execução do programa.


void buscarDados: é a função principal de busca, nela estão os menus, interfaces e chamadas das outras funções de busca, ela gere as opções dadas ao usuário e permite que as outras funções possam ser executadas corretamente.

void todosOsDados: é uma função criada para suportar e gerir o menu simples dentro do ‘case 1’ na main. Além disso, ela é fundamental para manter a main limpa e clara.

void menuPrincipal: o menu principal é uma interface intuitiva criada para mostrar ao usuário todas as funcionalidades do programa e como executá-las, sendo gerido na main.

bool sairDespedida: é a função de encerramento do programa, com uma mensagem de despedida e a confirmação de saída.

int main: nossa main é gerida por uma estrutura de repetição que mantêm o usuário no menu principal, a menos que deseje sair. Optamos por deixar a main o mais claro possível, para facilitar a manutenção e a compreensão da mesma.

Conclusão, erros, acertos e relatos de desenvolvimento:

Durante a construção deste projeto, tivemos alguns empecilhos, algumas dúvidas sobre sintaxe, muitas falhas de compilação, e principalmente falhas no fluxo de algumas operações, que causavam erros no código todo. Para reverter esses erros e as dúvidas, utilizamos do material disponibilizado no Campus da disciplina, alguns relatos e recomendações de estudantes antigos, e pesquisas na internet, principalmente no Stack Overflow, (tentamos reduzir a utilização de inteligências artificiais, elas foram usadas apenas em casos onde não encontramos outra solução, mesmo assim, de modo à sanar dúvidas, e não na escrita do código em si). Optamos pelo uso de Shell Sort, exclusivamente, devido a data em que nos foi ensinado, não tivemos aula de Quick e Merge Sort no período de desenvolvimento, além de utilizarmos dos ‘Gaps Ciura’ para melhorar sua otimização. Sobretudo, buscamos neste projeto, explorar de nossos conhecimentos adquiridos ao decorrer da disciplina, evitando o uso de funções externas e funcionalidades não vistas antes. Além de priorizar a compreensão do código, trazendo os procedimentos, confirmações e validações para as funções externas à função main.
