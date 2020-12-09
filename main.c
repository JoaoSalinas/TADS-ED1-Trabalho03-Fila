#include"fila.h"
#include<stdlib.h>
#include<stdio.h>
int main(){

    int choice = -1;
    Queue* queue = createQueue();
    
    while(choice != 0){
        printf("Selecione uma opção para continuar:\n");

        printf("###################################################\n");
        printf("##########Sistema de controle de log##################\n");
        printf("######################################################\n");
        printf("# 1   -  Inserir uma tentativa de login(fim da fila).#\n");
        printf("# 2   -  Remove um log (inicio da fila).             #\n");
        printf("# 3   -  Verifica se a fila esta vazia.              #\n");        
        printf("# 4   -  Mostrar lista de acessos.                   #\n");
        printf("# 5   -  Mostrar usuarios (ignorando repetidos).     #\n");
        printf("# 6   -  Mostrar registros apos horario especifico.  #\n");
        printf("# 7   -  Mostrar registros de um usuario especifico. #\n");
        printf("# 8   -  Remover acessos:                            #\n");
        printf("# 0   -  Sair.                                       #\n");
        printf("# 999 -  Criar base de testes.                       #\n");
        printf("######################################################\n\n");

        printf("------------------------------------------------------\n");
        printf("Informe a opcao escolhida:");
        scanf("%d", &choice);
        printf("------------------------------------------------------\n");

        switch(choice){
            int position;
            int listOption;
            case -1:
            break;
            case 1: ;
                UserLog* user = createUserLog();
                insertLog(queue, user);
                break;
            case 2: ;                
                freeUserAcess(queue, 1);
                break;
            case 3: ;
                emptyQueue(queue);
                break;
            case 4: ;
                showQueue(queue);
                break;
            case 5: ;
                showUsers(queue);
                break;
            case 6: ;
                if(queue->length != 0){
                    Time* time = createTime();
                    showAfterHour(queue, time);
                } else{
                    emptyQueue(queue);
                }
                break;
            case 7: ;   
                int positionInQueue = 0;
                showQueue(queue);
                if(queue->length > 0){
                    printf("Selecione o usuario na fila comecando por 0 e indo ate %d\n", queue->length-1);             
                    scanf("%d", &positionInQueue);
                    fflush(stdin);
                    
                    UserLog* userToGet = getUser(queue, positionInQueue);
                    showUserAcessAttempts(queue, userToGet);
                }
                break;
            case 8: ;
                if(queue->length > 0){
                    int quantityOfDeleting = 0;

                    printf("Escolha uma quantidade de itens que deseja remover da fila:");
                    scanf("%d", &quantityOfDeleting);
                    fflush(stdin);

                    freeUserAcess(queue, quantityOfDeleting);
                } else{
                    emptyQueue(queue);
                }
                break;          
            case 0:
                printf("Volte sempre!\n");
                break;
            case 999:
                createTestBase(queue);
                break;
            default:
                printf("Opcao invalida! Escolha uma opcao entre as disponiveis na lista!\n\n");
                pause();
                break;
        }
    }

    return 0;
}