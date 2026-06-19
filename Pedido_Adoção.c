#include <stdio.h>

struct PedidoAdocao {
    char nome[100];
    char cpf[15];
    char telefone[20];
    char desejaAdotar;
    char possuiCondicoes;
};

int main() {
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

    return 0;
}
