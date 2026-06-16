#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//============ Estruturas ==============

typedef struct {
    int id_animal;          
    char nome_animal[50];   
    char especie[30];       
    char raca[30];          
    int idade;              
    char sexo[10];          
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

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

//====== Sistema ========

void registrarAnimal() {
    if (contador_registro >= 500) { 
        printf("Limite do sistema atingido (Max: 500 animais)!\n"); 
        return;
    }

    Animal a;
    char confirmar;

    a.id_animal = contador_registro + 1; 

    printf("\n----- CADASTRAR NOVO ANIMAL (ID: %d) -----\n", a.id_animal);

    printf("Digite o nome do animal (Obrigatorio): ");
    fgets(a.nome_animal, 50, stdin);
    a.nome_animal[strcspn(a.nome_animal, "\n")] = 0;

    printf("Digite a especie (Ex: Cachorro, Gato) (Obrigatorio): ");
    fgets(a.especie, 30, stdin);
    a.especie[strcspn(a.especie, "\n")] = 0;

    int sexo_valido = 0;
    do {
        printf("Digite o sexo (Macho ou Femea): ");
        fgets(a.sexo, 10, stdin);
        a.sexo[strcspn(a.sexo, "\n")] = 0;
        
        if (strcasecmp(a.sexo, "Macho") == 0 || strcasecmp(a.sexo, "Femea") == 0) { 
            sexo_valido = 1;
        } else {
            printf("\033[1;31mErro: O sexo deve ser apenas 'Macho' ou 'Femea'.\033[0m\n"); 
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

    printf("\n========== CONSULTAR ANIMAL ==========\n");
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
    printf("\n===== LISTA DE ANIMAIS CADASTRADOS =====\n");

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

    printf("========== ALTERAR DADOS DO ANIMAL ==========\n"); 
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

    printf("========== ALTERAR STATUS DO ANIMAL ==========\n"); 
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

int main() {
    int opcao = 0;

    do {
        limpartela();
        printf("\n\033[1;34m=========== ADOTAPET - MENU DE ANIMAIS ===========\033[0m\n");
        printf("1. Cadastrar Novo Animal\n");      
        printf("2. Consultar Animal\n");           
        printf("3. Listar Todos os Animais\n");    
        printf("4. Alterar Dados do Animal\n");    
        printf("5. Alterar Status do Animal\n");   
        printf("0. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: registrarAnimal(); break;
            case 2: consultarAnimal(); break;
            case 3: listarTodosAnimais(); break;
            case 4: atualizarDadosAnimal(); break;
            case 5: alterarStatusAnimal(); break;
            case 0: printf("\nSaindo do modulo de animais...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
        pausar();
    } while (opcao != 0);

    return 0;
}