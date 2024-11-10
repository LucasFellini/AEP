#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>

int senhasIguais(char *senha, char *senha2);
bool validaSenha(char *senha);
void mensagemCentro(const char *message);
void tabela();
void mensagemAviso(const char *message);
void mostraMenu();
void limpaTela();
void criptografar(char *texto);
void descriptografar(char *texto);

struct novoCadastro {
    char nome[20];
    char senha[15];
};

typedef struct novoCadastro novoCadastro;

int main() {
    setlocale(LC_ALL, "Portuguese");

    int p = 1;
    int tecla;
    novoCadastro cadastro, cadastros[100];
    int totalCadastros = 0;
    int i, j;
    char nomeBusca[20];
    FILE *pont_arq;
    bool confirma;
    bool executando = true;
    int continuar;
    bool encontrado;

    do {
        limpaTela();
        mostraMenu();

        switch (p) {
            case 1: printf("\t\t> Cadastrar       <\n"); break;
            case 2: printf("\t\t> Exibir Cadastros<\n"); break;
            case 3: printf("\t\t> Alterar Cadastro<\n"); break;
            case 4: printf("\t\t> Excluir Cadastro<\n"); break;
            case 5: printf("\t\t> Sair            <\n"); break;
        }

        tecla = getch();
        if (tecla == 224 || tecla == 0)
            tecla = getch();

        switch (tecla) {
            case 72:
                p--;
                if (p < 1) p = 5;
                break;
            case 80:
                p++;
                if (p > 5) p = 1;
                break;
            case 13:
                switch (p) {
                    case 1:
                        do {
                            pont_arq = fopen("Dados_cadastrais.txt", "a");
                            if (pont_arq == NULL) {
                                mensagemAviso("Não foi possível abrir o arquivo");
                                return 1;
                            }

                            limpaTela();
                            mensagemCentro("Cadastro");
                            printf("\t\t+-------------------------------+\n");
                            printf("\t\t| Nome: ");
                            scanf(" %[^\n]", cadastro.nome);
                            printf("\t\t+-------------------------------+\n");

                            do {
                                printf("\t\t| Digite a senha: ");
                                scanf("%s", cadastro.senha);
                                printf("\t\t+-------------------------------+\n");

                                printf("\t\t| Digite a senha novamente: ");
                                char senha2[15];
                                scanf("%s", senha2);
                                printf("\t\t+-------------------------------+\n");

                                confirma = senhasIguais(cadastro.senha, senha2);
                                if (!confirma) {
                                    mensagemAviso("\nAs senhas não são iguais. Tente novamente.\n");
                                } else if (!validaSenha(cadastro.senha)) {
                                    mensagemAviso("\nA senha deve ter entre 6 e 14 caracteres, incluindo letras maiúsculas, minúsculas, números e caracteres especiais.\n");
                                }
                            } while (!confirma || !validaSenha(cadastro.senha));

                            criptografar(cadastro.nome);
                            criptografar(cadastro.senha);
                            fprintf(pont_arq, "%s\n%s\n\n", cadastro.nome, cadastro.senha);
                            mensagemAviso("\nCadastro realizado com sucesso!");
                            fclose(pont_arq);

                            printf("\nDeseja cadastrar outro? (1-Sim / 2-Não): ");
                            scanf("%d", &continuar);
                        } while (continuar == 1);
                        break;

                    case 2:
                        limpaTela();
                        pont_arq = fopen("Dados_cadastrais.txt", "r");
                        if (pont_arq == NULL) {
                            mensagemAviso("Não foi possível abrir o arquivo");
                            return 1;
                        }

                        printf("\n\t\t+-----------------+\n");
                        printf("\t\t|   Cadastros     |\n");
                        printf("\t\t+-----------------+\n");

                        while (fscanf(pont_arq, "%[^\n]\n%[^\n]\n\n", cadastro.nome, cadastro.senha) == 2) {
                            descriptografar(cadastro.nome);
                            descriptografar(cadastro.senha);
                            printf("\t\t| Nome: %s\n", cadastro.nome);
                            printf("\t\t| Senha: %s\n", cadastro.senha);
                            printf("\t\t+-----------------+\n");
                        }

                        fclose(pont_arq);
                        printf("\nPressione Enter para retornar ao menu principal...");
                        getchar(); getchar();
                        break;

                    case 3:
                        limpaTela();
                        pont_arq = fopen("Dados_cadastrais.txt", "r");
                        if (pont_arq == NULL) {
                            mensagemAviso("Não foi possível abrir o arquivo");
                            return 1;
                        }

                        totalCadastros = 0;
                        while (fscanf(pont_arq, "%[^\n]\n%[^\n]\n\n", cadastros[totalCadastros].nome, cadastros[totalCadastros].senha) == 2) {
                            descriptografar(cadastros[totalCadastros].nome);
                            descriptografar(cadastros[totalCadastros].senha);
                            totalCadastros++;
                        }
                        fclose(pont_arq);

                        printf("\nDigite o nome do cadastro que deseja alterar: ");
                        scanf(" %[^\n]", nomeBusca);

                        encontrado = false;
                        for (i = 0; i < totalCadastros; i++) {
                            if (strcmp(cadastros[i].nome, nomeBusca) == 0) {
                                encontrado = true;
                                printf("\n\t\t+-------------------------------+\n");
                                printf("\t\t| Nome atual: %s\n", cadastros[i].nome);
                                printf("\t\t| Senha atual: %s\n", cadastros[i].senha);
                                printf("\t\t+-------------------------------+\n");

                                printf("\t\t| Digite o novo nome: ");
                                scanf(" %[^\n]", cadastros[i].nome);
                                do {
                                    printf("\t\t| Digite a nova senha: ");
                                    scanf("%s", cadastro.senha);
                                    printf("\t\t+-------------------------------+\n");

                                    printf("\t\t| Digite a nova senha novamente: ");
                                    char senha2[15];
                                    scanf("%s", senha2);
                                    printf("\t\t+-------------------------------+\n");

                                    confirma = senhasIguais(cadastro.senha, senha2);
                                    if (!confirma) {
                                        mensagemAviso("\nAs senhas não são iguais. Tente novamente.\n");
                                    } else if (!validaSenha(cadastro.senha)) {
                                        mensagemAviso("\nA senha deve ter entre 6 e 14 caracteres, incluindo letras maiúsculas, minúsculas, números e caracteres especiais.\n");
                                    }
                                } while (!confirma || !validaSenha(cadastro.senha));

                                criptografar(cadastros[i].senha);
                                strcpy(cadastros[i].senha, cadastro.senha);

                                pont_arq = fopen("Dados_cadastrais.txt", "w");
                                if (pont_arq == NULL) {
                                    mensagemAviso("Não foi possível abrir o arquivo para gravação");
                                    return 1;
                                }

                                for (j = 0; j < totalCadastros; j++) {
                                    criptografar(cadastros[j].nome);
                                    criptografar(cadastros[j].senha);
                                    fprintf(pont_arq, "%s\n%s\n\n", cadastros[j].nome, cadastros[j].senha);
                                }

                                fclose(pont_arq);
                                mensagemAviso("\nCadastro alterado com sucesso!");
                                break;
                            }
                        }

                        if (!encontrado) {
                            printf("\nCadastro com o nome '%s' não encontrado.\n", nomeBusca);
                        }

                        printf("\nPressione Enter para retornar ao menu principal...");
                        getchar(); getchar();
                        break;

                    case 4:
                        limpaTela();
                        pont_arq = fopen("Dados_cadastrais.txt", "r");
                        if (pont_arq == NULL) {
                            mensagemAviso("Não foi possível abrir o arquivo");
                            return 1;
                        }

                        totalCadastros = 0;
                        while (fscanf(pont_arq, "%[^\n]\n%[^\n]\n\n", cadastros[totalCadastros].nome, cadastros[totalCadastros].senha) == 2) {
                            descriptografar(cadastros[totalCadastros].nome);
                            descriptografar(cadastros[totalCadastros].senha);
                            totalCadastros++;
                        }
                        fclose(pont_arq);

                        printf("\nDigite o nome do cadastro que deseja excluir: ");
                        scanf(" %[^\n]", nomeBusca);

                        encontrado = false;
                        for (i = 0; i < totalCadastros; i++) {
                            if (strcmp(cadastros[i].nome, nomeBusca) == 0) {
                                encontrado = true;
                                printf("\nDigite a senha para confirmar a exclusão: ");
                                char senha[15];
                                scanf("%s", senha);

                                if (strcmp(cadastros[i].senha, senha) == 0) {
                                    for (j = i; j < totalCadastros - 1; j++) {
                                        cadastros[j] = cadastros[j + 1];
                                    }
                                    totalCadastros--;
                                    pont_arq = fopen("Dados_cadastrais.txt", "w");
                                    if (pont_arq == NULL) {
                                        mensagemAviso("Não foi possível abrir o arquivo para gravação");
                                        return 1;
                                    }

                                    for (j = 0; j < totalCadastros; j++) {
                                        criptografar(cadastros[j].nome);
                                        criptografar(cadastros[j].senha);
                                        fprintf(pont_arq, "%s\n%s\n\n", cadastros[j].nome, cadastros[j].senha);
                                    }

                                    fclose(pont_arq);
                                    mensagemAviso("\nCadastro excluído com sucesso!");
                                } else {
                                    mensagemAviso("\nSenha incorreta. Excluindo o cadastro.");
                                }
                                break;
                            }
                        }

                        if (!encontrado) {
                            printf("\nCadastro com o nome '%s' não encontrado.\n", nomeBusca);
                        }

                        printf("\nPressione Enter para retornar ao menu principal...");
                        getchar(); getchar();
                        break;

                    case 5:
                        executando = false;
                        break;
                }
                break;
        }
    } while (executando);
    
	mensagemAviso("\nPrograma encerrado.\n");
    return 0;
}


int senhasIguais(char *senha, char *senha2) {
    return strcmp(senha, senha2) == 0;
}

bool validaSenha(char *senha) {
    int x;
    bool a1 = false, a2 = false, a3 = false, a4 = false;

    if (strlen(senha) < 6 || strlen(senha) >= 15)
        return false;

    for (x = 0; x < strlen(senha); x++) {
        if (senha[x] >= 'A' && senha[x] <= 'Z')
            a1 = true;
        if (senha[x] >= 'a' && senha[x] <= 'z')
            a2 = true;
        if (senha[x] >= '0' && senha[x] <= '9')
            a3 = true;
        if ((senha[x] >= 33 && senha[x] <= 47) ||
            (senha[x] >= 58 && senha[x] <= 64) ||
            (senha[x] >= 91 && senha[x] <= 96) ||
            (senha[x] >= 123 && senha[x] <= 126))
            a4 = true;
    }

    return a1 && a2 && a3 && a4;
}

void criptografar(char *texto) {
    while (*texto) {
        *texto += 10;
        texto++;
    }
}

void descriptografar(char *texto) {
    while (*texto) {
        *texto -= 10;
        texto++;
    }
}

void mensagemCentro(const char *message) {
    int width = 60; 
    int padding = (width - strlen(message)) / 2;
    printf("%*s%s%*s\n", padding, "", message, padding, "");
}

void tabela() {
    printf("\n\n");
    printf("\n\t\t+-----------------+\n");
    printf("\t\t|      CRUD       |  ");
    printf("\n\t\t+-----------------+\n");
}

void mensagemAviso(const char *message) {
    printf("%s\n", message);
}

void mostraMenu() {
    tabela();
    printf("\t\t+-----------------+\n");
    printf("\t\t| Cadastrar       |\n");
    printf("\t\t| Exibir Cadastros|\n");
    printf("\t\t| Alterar Cadastro|\n");
    printf("\t\t| Excluir Cadastro|\n");
    printf("\t\t| Sair            |\n");
    printf("\t\t+-----------------+\n");
}

void limpaTela() {
    system("cls");
}
