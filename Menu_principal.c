// sistema.c

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

// protótipos
void menuAnimais();
void menuAdotantes();
void inicializarsistema();
void iniciarAdotantes();

int main()
{
    int opcao;

    inicializarsistema();
    iniciarAdotantes();

    do
    {
        printf("\n=================================\n");
        printf("       SISTEMA ADOTAPET\n");
        printf("=================================\n");
        printf("1. Modulo de Animais\n");
        printf("2. Modulo de Adotantes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao)
        {
            case 1:
                menuAnimais();
                break;

            case 2:
                menuAdotantes();
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}



void menuAnimais()
{
    int opcao = 0;

    do {
        printf("\n=== MENU ANIMAIS ===\n");
        printf("1. Cadastrar Animal\n");
        printf("2. Consultar Animal\n");
        printf("3. Listar Animais\n");
        printf("4. Alterar Dados\n");
        printf("5. Alterar Status\n");
        printf("0. Voltar\n");

        scanf("%d", &opcao);
        getchar();

        switch(opcao)
        {
            case 1: registrarAnimal(); break;
            case 2: consultarAnimal(); break;
            case 3: listarTodosAnimais(); break;
            case 4: atualizarDadosAnimal(); break;
            case 5: alterarStatusAnimal(); break;
        }

    } while(opcao != 0);
}




//============ Estruturas ==============

typedef struct {
    int id_animal;          
    char nome_animal[50];   
    char especie[30];       
    char raca[30];          
    int idade;              
    char sexo[2];          
    char status[30];        
    char porte[20];         
    float peso;             
    char cor[30];           
    char descricao[200];    
    char data_hora_cadastro[20]; 
} Animal;

// Vetor global limitado a 500 animais conforme a métrica M01
Animal registros[500]; 

// Variável para controlar quantos registros já foram preenchidos
int contador_registro = 0;

//========== Funções Auxiliares ===============

void limpartela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}




//====== Sistema ========

void inicializarsistema() {
int i ;
contador_registro = 0;

for(i=0; i<100; i++) {
registros [i].id_animal = 0; }

printf("Dados do animal inicializado com sucesso!");
    }


void registrarAnimal() {
    if (contador_registro >= 500) { 
        printf("Limite do sistema atingido (Max: 500 animais)!\n"); 
        return;
    }

    Animal a;
    char confirmar;

    a.id_animal = contador_registro + 1; 

//id automatico



    printf("\n----- ??CADASTRAR NOVO ANIMAL (ID: %d)?? -----\n", a.id_animal);

    printf("Digite o nome do animal (Se nao tiver digite sem nome): ");
    fgets(a.nome_animal, 50, stdin);
    a.nome_animal[strcspn(a.nome_animal, "\n")] = 0;

    printf("Digite a especie (Ex: Cachorro, Gato) (Obrigatorio): ");
    fgets(a.especie, 30, stdin);
    a.especie[strcspn(a.especie, "\n")] = 0;

    int sexo_valido = 0;
    do {
        printf("Digite o sexo (M ou F): ");
        fgets(a.sexo, 2, stdin);
        a.sexo[strcspn(a.sexo, "\n")] = 0;
        
        if (strcasecmp(a.sexo, "M") == 0 || strcasecmp(a.sexo, "F") == 0) { 
            sexo_valido = 1;
        } else {
            printf("\033[1;31mErro: O sexo deve ser apenas 'M' ou 'F'.\033[0m\n"); 
        }
    } while (!sexo_valido);

    printf("Digite a raca: ");
    fgets(a.raca, 30, stdin);
    a.raca[strcspn(a.raca, "\n")] = 0;

    printf("Digite a idade: ");
    scanf("%d", &a.idade);
    while (getchar() != '\n'); 

    printf("Digite o porte (Pequeno/Medio/Grande): ");
    fgets(a.porte, 20, stdin);
    a.porte[strcspn(a.porte, "\n")] = 0;

    printf("Digite o peso (em kg): ");
    scanf("%f", &a.peso);
    while (getchar() != '\n');

    printf("Digite a cor predominante: ");
    fgets(a.cor, 30, stdin);
    a.cor[strcspn(a.cor, "\n")] = 0;

    printf("Digite uma breve descricao/historico: ");
    fgets(a.descricao, 200, stdin);
    a.descricao[strcspn(a.descricao, "\n")] = 0;

    printf("Digite a data do cadastro (Ex: 16/06/2026): ");
    fgets(a.data_hora_cadastro, 20, stdin);
    a.data_hora_cadastro[strcspn(a.data_hora_cadastro, "\n")] = 0;

    strcpy(a.status, "Disponivel para Adocao"); 

    printf("\nDeseja confirmar o cadastro deste animal? (S/N): "); 
    scanf("%c", &confirmar);
    getchar();

    if (confirmar == 's' || confirmar == 'S') {
        registros[contador_registro] = a;
        contador_registro++;
        printf("\n\033[1;32mSucesso: Cadastro concluido com sucesso!\033[0m\n"); 
    } else {
        printf("\n\033[1;31mCadastro cancelado pelo usuario.\033[0m\n");
    }
}

void consultarAnimal() {
    char busca[50];
    int achou = 0;
    int i; // i declarada aqui em cima para o modo C89
    limpartela();

    printf("\n========== ??CONSULTAR ANIMAL?? ==========\n");
    printf("Buscar por nome, especie ou raca: ");
    fgets(busca, 50, stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (i = 0; i < contador_registro; i++) {
        if (strcasecmp(registros[i].nome_animal, busca) == 0 || 
            strcasecmp(registros[i].especie, busca) == 0 || 
            strcasecmp(registros[i].raca, busca) == 0) {
            
            printf("\n------------------------------------");
            printf("\n[Animal Encontrado]");
            printf("\nID:          %d", registros[i].id_animal);
            printf("\nNome:        %s", registros[i].nome_animal);
            printf("\nEspecie:     %s", registros[i].especie);
            printf("\nRaca:        %s", registros[i].raca);
            printf("\nIdade:       %d anos", registros[i].idade);
            printf("\nSexo:        %s", registros[i].sexo);
            printf("\nStatus:      [%s]", registros[i].status); 
            printf("\nCadastrado:  %s", registros[i].data_hora_cadastro); 
            printf("\n------------------------------------\n");
            achou = 1;
        }
    }
    
    if (!achou) {
        printf("\nNenhum animal localizado com o termo informado.\n"); 
    }
}

void listarTodosAnimais() {
    int i; // i declarada aqui em cima para o modo C89
    limpartela();
    printf("\n===== ??LISTA DE ANIMAIS CADASTRADOS ??=====\n");

    if (contador_registro == 0) {
        printf("Nenhum animal cadastrado no abrigo ate o momento.\n"); 
        return;
    }

    printf("%-4s | %-12s | %-10s | %-5s | %-7s | %-15s | %-16s\n", "ID", "Nome", "Especie", "Idade", "Sexo", "Status", "Data Cadastro");
    printf("-------------------------------------------------------------------------------------------------\n");
    
    for (i = 0; i < contador_registro; i++) {
        printf("%03d  | %-12s | %-10s | %-5d | %-7s | %-15s | %-16s\n", 
               registros[i].id_animal, 
               registros[i].nome_animal, 
               registros[i].especie, 
               registros[i].idade, 
               registros[i].sexo, 
               registros[i].status,
               registros[i].data_hora_cadastro); 
    }
    printf("-------------------------------------------------------------------------------------------------\n");
}

void atualizarDadosAnimal() {
    int id_busca;
    int achou = 0;
    int i; // i declarada aqui em cima para o modo C89
    limpartela();

    printf("========== ??ALTERAR DADOS DO ANIMAL?? ==========\n"); 
    printf("Digite o ID do animal que deseja alterar: ");
    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n');
        return;
    }
    getchar();

    for (i = 0; i < contador_registro; i++) {
        if (registros[i].id_animal == id_busca) {
            printf("\nAnimal selecionado: %s (%s)\n", registros[i].nome_animal, registros[i].especie);
            
            printf("Digite o novo nome para o animal: ");
            fgets(registros[i].nome_animal, 50, stdin);
            registros[i].nome_animal[strcspn(registros[i].nome_animal, "\n")] = 0;

            printf("Digite a nova idade: ");
            scanf("%d", &registros[i].idade);
            while (getchar() != '\n');

            printf("\n\033[1;32mSucesso: Dados do animal atualizados!\033[0m\n"); 
            achou = 1;
            break;
        }
    }
    if (!achou) {
        printf("\nID de animal invalido ou nao encontrado.\n");
    }
}

void alterarStatusAnimal() {
    int id_busca, opcao_status;
    int achou = 0;
    int i; // i declarada aqui em cima para o modo C89
    limpartela();

    printf("========== ??ALTERAR STATUS DO ANIMAL?? ==========\n"); 
    printf("Informe o ID do Animal: ");
    scanf("%d", &id_busca);
    getchar();

    for (i = 0; i < contador_registro; i++) {
        if (registros[i].id_animal == id_busca) {
            achou = 1;
            printf("\nStatus atual de %s: %s\n", registros[i].nome_animal, registros[i].status);
            printf("Selecione o novo Status:\n");
            printf("1. Disponivel para Adocao\n"); 
            printf("2. Em Processo de Adocao\n");  
            printf("3. Adotado\n");                
            printf("4. Em Tratamento\n");           
            printf("5. Indisponivel\n");            
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao_status);
            getchar();

            switch (opcao_status) {
                case 1: strcpy(registros[i].status, "Disponivel para Adocao"); break; 
                case 2: strcpy(registros[i].status, "Em Processo de Adocao"); break; 
                case 3: strcpy(registros[i].status, "Adotado"); break; 
                case 4: strcpy(registros[i].status, "Em Tratamento"); break; 
                case 5: strcpy(registros[i].status, "Indisponivel"); break; 
                default: printf("Opcao invalida. Status nao alterado.\n"); return;
            }
            printf("\n\033[1;32mSucesso: Status do Animal ID %d atualizado para '%s'!\033[0m\n", id_busca, registros[i].status); 
            break;
        }
    }

    if (!achou) {
        printf("\nAnimal com o ID %d nao foi encontrado.\n", id_busca);
    }
}

struct PedidoAdocao {
    char nome[100];
    char cpf[15];
    char telefone[20];
    char desejaAdotar;
    char possuiCondicoes;
}; 
    void menuPedidoAdocao()
	
	{
		
    struct PedidoAdocao pedido;

    printf("=== SISTEMA DE ADOCAO DE ANIMAIS ===\n\n");

    printf("Digite seu nome: ");
    fgets(pedido.nome, sizeof(pedido.nome), stdin);

    printf("Digite seu CPF: ");
    fgets(pedido.cpf, sizeof(pedido.cpf), stdin);

    printf("Digite seu telefone: ");
    fgets(pedido.telefone, sizeof(pedido.telefone), stdin);

    printf("Voce deseja adotar um animal? (S/N): ");
    scanf(" %c", &pedido.desejaAdotar);

    printf("Voce possui condicoes financeiras e espaco adequado para cuidar do animal? (S/N): ");
    scanf(" %c", &pedido.possuiCondicoes);

    printf("\n=== PEDIDO CADASTRADo E EM ANALISE ===\n");
    printf("Nome: %s", pedido.nome);
    printf("CPF: %s", pedido.cpf);
    printf("Telefone: %s", pedido.telefone);
    printf("Deseja adotar: %c\n", pedido.desejaAdotar);
    printf("Possui condicoes: %c\n", pedido.possuiCondicoes);

    if (pedido.desejaAdotar == 'S' || pedido.desejaAdotar == 's') {
        if (pedido.possuiCondicoes == 'S' || pedido.possuiCondicoes == 's') {
            printf("Pedido aprovado para analise.\n");
        } else {
            printf("Pedido nao pode prosseguir por falta de condicoes adequadas.\n");
        }
    } else {
        printf("Pedido cancelado.\n");
    }

    return;
    } 

/* =====================================================
   ADOTANTES
   ===================================================== */

   /*  CONSTANTES   */

#define MAX_ADOTANTES 100
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_TELEFONE 20
#define TAM_ENDERECO 200
#define TAM_EMAIL 100
#define ARQUIVO_ADOTANTES "adotantes.txt"

      /* STRUCT: representa um adotante  */

   typedef struct
   {
       int id;
       char nome[TAM_NOME];
       char cpf[TAM_CPF];
       char telefone[TAM_TELEFONE];
       char endereco[TAM_ENDERECO];
       char email[TAM_EMAIL];
       int ativo; /* 1 = cadastrado, 0 = removido */
   } Adotante;

/*  VARIÁVEIS GLOBAIS */
Adotante listaAdotantes[MAX_ADOTANTES];
int totalAdotantes = 0;

/* =====================================================
   DECLARAÇÃO DAS FUNÇÕES
   ===================================================== */
void menuAdotantes();
void cadastrarAdotante();
void listarAdotantes();
void buscarAdotantePorCPF();
void editarAdotante();
void removerAdotante();
int cpfJaCadastrado(char *cpf);
int gerarIdAdotante();
void limparBuffer();
void pausar();

/* Funções de arquivo — implementadas pela Pessoa 5,
   declaradas aqui para integração */

void salvarAdotantes();
void carregarAdotantes();

/* =====================================================
   FUNÇÃO PRINCIPAL DO MÓDULO
   (chame menuAdotantes() a partir do menu geral)
   ===================================================== */

void iniciarAdotantes()
{
    carregarAdotantes();
}


/* =====================================================
   MENU DE ADOTANTES
   ===================================================== */
void menuAdotantes()
{
    int opcao;

    do
    {
        printf("\n========================================\n");
        printf("     CADASTRO DE ADOTANTES\n");
        printf("========================================\n");
        printf("1. Cadastrar novo adotante\n");
        printf("2. Listar adotantes\n");
        printf("3. Buscar adotante por CPF\n");
        printf("4. Editar adotante\n");
        printf("5. Remover adotante\n");
        printf("0. Voltar ao menu principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            cadastrarAdotante();
            break;
        case 2:
            listarAdotantes();
            break;
        case 3:
            buscarAdotantePorCPF();
            break;
        case 4:
            editarAdotante();
            break;
        case 5:
            removerAdotante();
            break;
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}

/* =====================================================
   CADASTRAR ADOTANTE
   ===================================================== */
void cadastrarAdotante()
{
    if (totalAdotantes >= MAX_ADOTANTES)
    {
        printf("\nLimite de adotantes atingido!\n");
        pausar();
        return;
    }

    Adotante novo;

    printf("\n--- CADASTRO DE NOVO ADOTANTE ---\n");

    /* Nome */
    printf("Nome completo: ");
    fgets(novo.nome, TAM_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; /* remove o \n do final */

    /* CPF */
    printf("CPF (somente numeros): ");
    fgets(novo.cpf, TAM_CPF, stdin);
    novo.cpf[strcspn(novo.cpf, "\n")] = '\0';

    if (cpfJaCadastrado(novo.cpf))
    {
        printf("\nEsse CPF ja esta cadastrado!\n");
        pausar();
        return;
    }

    /* Telefone */
    printf("Telefone: ");
    fgets(novo.telefone, TAM_TELEFONE, stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = '\0';

    /* Endereço */
    printf("Endereco: ");
    fgets(novo.endereco, TAM_ENDERECO, stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = '\0';

    /* E-mail */
    printf("E-mail: ");
    fgets(novo.email, TAM_EMAIL, stdin);
    novo.email[strcspn(novo.email, "\n")] = '\0';

    /* Define ID e status */
    novo.id = gerarIdAdotante();
    novo.ativo = 1;

    /* Adiciona na lista */
    listaAdotantes[totalAdotantes] = novo;
    totalAdotantes++;

    salvarAdotantes(); /* salva no arquivo após cadastrar */

    printf("\nAdotante cadastrado com sucesso! ID: %d\n", novo.id);
    pausar();
}

/* =====================================================
   LISTAR ADOTANTES
   ===================================================== */
void listarAdotantes()
{
    int i;
    int encontrou = 0;

    printf("\n--- LISTA DE ADOTANTES ---\n");

    for (i = 0; i < totalAdotantes; i++)
    {
        if (listaAdotantes[i].ativo == 1)
        {
            printf("\n[ID: %d]\n", listaAdotantes[i].id);
            printf("  Nome:     %s\n", listaAdotantes[i].nome);
            printf("  CPF:      %s\n", listaAdotantes[i].cpf);
            printf("  Telefone: %s\n", listaAdotantes[i].telefone);
            printf("  Endereco: %s\n", listaAdotantes[i].endereco);
            printf("  E-mail:   %s\n", listaAdotantes[i].email);
            printf("  ----------\n");
            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Nenhum adotante cadastrado.\n");
    }

    pausar();
}

/* =====================================================
   BUSCAR ADOTANTE POR CPF
   ===================================================== */
void buscarAdotantePorCPF()
{
    char cpf[TAM_CPF];
    int i;

    printf("\n--- BUSCAR ADOTANTE POR CPF ---\n");
    printf("Digite o CPF: ");
    fgets(cpf, TAM_CPF, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    for (i = 0; i < totalAdotantes; i++)
    {
        if (listaAdotantes[i].ativo == 1 &&
            strcmp(listaAdotantes[i].cpf, cpf) == 0)
        {

            printf("\nAdotante encontrado:\n");
            printf("  ID:       %d\n", listaAdotantes[i].id);
            printf("  Nome:     %s\n", listaAdotantes[i].nome);
            printf("  CPF:      %s\n", listaAdotantes[i].cpf);
            printf("  Telefone: %s\n", listaAdotantes[i].telefone);
            printf("  Endereco: %s\n", listaAdotantes[i].endereco);
            printf("  E-mail:   %s\n", listaAdotantes[i].email);
            pausar();
            return;
        }
    }

    printf("Adotante com CPF '%s' nao encontrado.\n", cpf);
    pausar();
}

/* =====================================================
   EDITAR ADOTANTE
   ===================================================== */
void editarAdotante()
{
    int id, i;

    printf("\n--- EDITAR ADOTANTE ---\n");
    printf("Digite o ID do adotante: ");
    scanf("%d", &id);
    limparBuffer();

    for (i = 0; i < totalAdotantes; i++)
    {
        if (listaAdotantes[i].id == id && listaAdotantes[i].ativo == 1)
        {

            printf("Deixe em branco para manter o valor atual.\n\n");

            char temp[TAM_NOME];

            printf("Nome atual [%s]: ", listaAdotantes[i].nome);
            fgets(temp, TAM_NOME, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0)
                strcpy(listaAdotantes[i].nome, temp);

            printf("Telefone atual [%s]: ", listaAdotantes[i].telefone);
            fgets(temp, TAM_TELEFONE, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0)
                strcpy(listaAdotantes[i].telefone, temp);

            printf("Endereco atual [%s]: ", listaAdotantes[i].endereco);
            fgets(temp, TAM_ENDERECO, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0)
                strcpy(listaAdotantes[i].endereco, temp);

            printf("E-mail atual [%s]: ", listaAdotantes[i].email);
            fgets(temp, TAM_EMAIL, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0)
                strcpy(listaAdotantes[i].email, temp);

            salvarAdotantes();
            printf("\nDados atualizados com sucesso!\n");
            pausar();
            return;
        }
    }

    printf("Adotante com ID %d nao encontrado.\n", id);
    pausar();
}

/* =====================================================
   REMOVER ADOTANTE (remoção lógica)
   ===================================================== */
void removerAdotante()
{
    int id, i;
    char confirmacao;

    printf("\n--- REMOVER ADOTANTE ---\n");
    printf("Digite o ID do adotante: ");
    scanf("%d", &id);
    limparBuffer();

    for (i = 0; i < totalAdotantes; i++)
    {
        if (listaAdotantes[i].id == id && listaAdotantes[i].ativo == 1)
        {

            printf("Tem certeza que deseja remover '%s'? (s/n): ",
                   listaAdotantes[i].nome);
            scanf("%c", &confirmacao);
            limparBuffer();

            if (confirmacao == 's' || confirmacao == 'S')
            {
                listaAdotantes[i].ativo = 0; /* marca como inativo */
                salvarAdotantes();
                printf("Adotante removido com sucesso!\n");
            }
            else
            {
                printf("Operacao cancelada.\n");
            }

            pausar();
            return;
        }
    }

    printf("Adotante com ID %d nao encontrado.\n", id);
    pausar();
}

/* =====================================================
   VERIFICA SE CPF JÁ ESTÁ CADASTRADO
   ===================================================== */
int cpfJaCadastrado(char *cpf)
{
    int i;
    for (i = 0; i < totalAdotantes; i++)
    {
        if (listaAdotantes[i].ativo == 1 &&
            strcmp(listaAdotantes[i].cpf, cpf) == 0)
        {
            return 1; /* encontrou */
        }
    }
    return 0; /* não encontrou */
}

/* =====================================================
   GERA UM ID ÚNICO PARA O ADOTANTE
   ===================================================== */
int gerarIdAdotante()
{
    int maiorId = 0;
    int i;
    for (i = 0; i < totalAdotantes; i++)
    {
        if (listaAdotantes[i].id > maiorId)
        {
            maiorId = listaAdotantes[i].id;
        }
    }
    return maiorId + 1;
}

/* =====================================================
   LIMPA O BUFFER DO TECLADO
   ===================================================== */
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* =====================================================
   PAUSA ATÉ O USUÁRIO PRESSIONAR ENTER
   ===================================================== */
void pausar()
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/* =====================================================
   SALVAR ADOTANTES EM ARQUIVO
   (implementação provisória — Pessoa 5 pode substituir)
   ===================================================== */
void salvarAdotantes()
{
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO_ADOTANTES, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao salvar arquivo de adotantes!\n");
        return;
    }

    for (i = 0; i < totalAdotantes; i++)
    {
        fprintf(arquivo, "%d|%s|%s|%s|%s|%s|%d\n",
                listaAdotantes[i].id,
                listaAdotantes[i].nome,
                listaAdotantes[i].cpf,
                listaAdotantes[i].telefone,
                listaAdotantes[i].endereco,
                listaAdotantes[i].email,
                listaAdotantes[i].ativo);
    }

    fclose(arquivo);
}

/* =====================================================
   CARREGAR ADOTANTES DO ARQUIVO
   (implementação provisória — Pessoa 5 pode substituir)
   ===================================================== */
void carregarAdotantes()
{
    FILE *arquivo;

    arquivo = fopen(ARQUIVO_ADOTANTES, "r");
    if (arquivo == NULL)
    {
        /* arquivo ainda não existe — tudo bem, começa vazio */
        return;
    }

    totalAdotantes = 0;

    while (totalAdotantes < MAX_ADOTANTES)
    {
        Adotante a;
        int lidos = fscanf(arquivo, "%d|%99[^|]|%14[^|]|%19[^|]|%199[^|]|%99[^|]|%d\n",
                           &a.id,
                           a.nome,
                           a.cpf,
                           a.telefone,
                           a.endereco,
                           a.email,
                           &a.ativo);
        if (lidos != 7)
            break; /* chegou ao fim do arquivo */
        listaAdotantes[totalAdotantes] = a;
        totalAdotantes++;
    }

    fclose(arquivo);
}
