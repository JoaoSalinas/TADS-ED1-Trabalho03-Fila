#include"date.h"

typedef struct user{
    char login[30];
    Date* dateLogin;
    Time* loginAt;
    Date* dateLogout;
    Time* logoutAt;
    struct user* next;
}UserLog;

typedef struct queue {
    UserLog* first;
    UserLog* last;
    int length;
} Queue;


//insere na fila
void insertLog(Queue* queue, UserLog* user);

//verifica se a lista esta vazia
int emptyQueue(Queue* queue);

//mostrar todos elementos da fila, começando pelo inicio da fila e indo até o fim
void showQueue(Queue* queue);

//visualizar na tela todos os nomes de usuários que fizeram login, desprezando repetições de nomes de login
void showUsers();

//visualizar na tela todos os nomes que efetuaram login após um horário indicado pelo administrador.
void showAfterHour(Queue* queue, Time* time);

//visualiza todos os acesso feitos por um determinado nome indicado pelo administrador.
void showUserAcessAttempts(Queue* queue, UserLog* user);

//Remover uma quantidade de acessos(número) estipulada pelo administrador, não esqueça de liberar a memória. 
//Mostrar os acessos removidos;
void freeUserAcess(Queue* queue, int quantity);

//** utils **/
UserLog* createUserLog();
Queue* createQueue();
UserLog* popQueue(Queue* queue);
void insertLog(Queue* queue, UserLog* user);
int indexLog(Queue* queue, char login[]);
UserLog* getUser(Queue* queue, int index);
int emptyQueue(Queue* queue);
void printUserLog(UserLog* user);
void createTestBase(Queue* queue);
void pause();
