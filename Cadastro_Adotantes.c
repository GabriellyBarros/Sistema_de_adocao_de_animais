#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int main()
{
    carregarAdotantes(); /* carrega dados salvos ao iniciar */
    menuAdotantes();
    return 0;
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