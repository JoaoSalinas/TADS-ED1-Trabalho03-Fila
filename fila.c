#include"fila.h"

//* Funções da ordem do exercicio*/
//mostrar os acessos armazenados na fila de acessos.
void showQueue(Queue* queue){
    if(queue->length == 0){
        printf("Fila Vazia!\n\n");
        pause();
        return;
    }
    
    int position = 0;

    if(queue->length == 1){
        printf("Posicao do log na fila: %d\n\n", position);
        printUserLog(queue->first);
        pause();
        return;
    }

    UserLog* userTmp = queue->first;

    while(position < queue->length){   
        printf("*****************************************\n\n");
        printf("Posicao do log na fila: %d\n\n", position);
        printUserLog(userTmp);
        printf("*****************************************\n\n");
        userTmp = userTmp->next;
        position++;
    }
    pause();
}

//visualizar na tela todos os nomes de usuários que fizeram login, 
//desprezando repetições de nomes de login
void showUsers(Queue* queue){
    UserLog* userTmp = NULL;

    char* allUsersInSystem[30];
    char* distinctUsersLogins[30];
    int positionOfTransfer = 0;

    if(queue->length == 0){
        printf("Lista Vazia!");
        pause();
        return;
    }

    if(queue->length == 1){
        showQueue(queue);
        return;
    }

    while(positionOfTransfer < queue->length){        
        userTmp = getUser(queue, positionOfTransfer);
        allUsersInSystem[positionOfTransfer] = userTmp->login;                
        positionOfTransfer++;                         
    }                

    int repeatLogin = 0, lengthOfDistinct = 0, i = 0, j = 0;
    for (i = 0; i < positionOfTransfer; i++) {
        if (i == 0) {            
            distinctUsersLogins[i] = allUsersInSystem[i];
            lengthOfDistinct++;            
        } else {
            repeatLogin = 0;
            //percorre o vetor distinto verificando se o valor allUsersInSystem[i] já existe
            for (j = 0; j < lengthOfDistinct; j++) {
                if(strcmp(allUsersInSystem[i], distinctUsersLogins[j]) == 0) {
                    repeatLogin++;
                }
            }
            //se o valor allUsersInSystem[i] não foi encontrado no vetor distinto, então adiciona
            if (repeatLogin == 0) {
                distinctUsersLogins[lengthOfDistinct] = allUsersInSystem[i];
                lengthOfDistinct++;
            }
        }
    }

    int k;
    printf("Lista de usuarios cadastrados: \n\n");
    for (k = 0; k < lengthOfDistinct; k++) {
        printf("%s \n\n", distinctUsersLogins[k]);
    }
    pause();

}

//visualizar na tela todos os nomes que efetuaram login após um horário indicado pelo administrador.
void showAfterHour(Queue* queue, Time* time){
    
    if(queue->length == 0){
        printf("Lista Vazia!\n\n");
        pause();
        return;
    }
    
    int position = 0;

    if(queue->length == 1){
        if(timeCompare(time, queue->first->loginAt) == -1){
            printf("Posicao do log na fila: %d\n\n", position);
            printUserLog(queue->first);
        }        
    }

    UserLog* userTmp = queue->first;

    while(position < queue->length){   
        if(timeCompare(time, userTmp->loginAt) == -1){
            printf("*****************************************\n\n");
            printf("Posicao do log na fila: %d\n\n", position);
            printUserLog(userTmp);
            printf("*****************************************\n\n");
        }
        userTmp = userTmp->next;
        position++;
    }
    pause();
}

//visualiza todos os acesso feitos por um determinado nome indicado pelo administrador.
void showUserAcessAttempts(Queue* queue, UserLog* user){
     if(emptyQueue(queue) == 0){
        return;
    }

    UserLog* userTmp = queue->first;

    while(userTmp->next != NULL){
        if(strcmp(userTmp->login, user->login) == 0){
            printUserLog(userTmp);
        }
        userTmp = userTmp->next;
    }
}

//Remover uma quantidade de acessos(número) estipulada pelo administrador, não esqueça de liberar a memória. 
//Mostrar os acessos removidos;
void freeUserAcess(Queue* queue, int quantity){

    if(queue->length == 0){
        printf("Impossivel remover item. Fila Vazia!\n\n");
        pause();
        return;
    }

    if(quantity > queue->length){
        printf("Quantidade de itens a remover precisam ser menores ou iguais a quantidade de itens na fila (limite atual de %d itens na fila)", queue->length);
        pause();
        return;
    }

    for(int i = 0; i < quantity; i++){     
        popQueue(queue);
    }

    printf("%d ite%c%c removido%c com sucesso", 
            quantity, 
            quantity == 1 ? 'm' : 'n',
            quantity == 1 ? ' ' : 's',
            quantity == 1 ? ' ' : 's');
    pause();
}

//* Funções Extras para auxiliar no manuseio da lista e outras utilidades para o sistema*/

UserLog* createUserLog(Queue* queue){

    UserLog* user = (UserLog*) malloc(sizeof(UserLog));    

    printf("Informe o login do usuario que deseja criar um registro:\n");
    scanf("%s", user->login);    
    pause();

    printf("Data em que quer entrou no sistema: \n");
    Date* dateStart = createDate();    
    if(validateDate(dateStart) == 1) {
        user->dateLogin = dateStart;
    } else{
        printf("\n\n **Data de login inválida!\n Voce sera direcionado ao inicio do processo.\nPreencha os campos com atencao!\n\n");
        pause();
        createUserLog(queue);
    }
    pause();

    printf("horario em que entrou no sistema: \n");
    Time* timeLogin = createTime();    
    if(validateTime(timeLogin) == 1) {
        user->loginAt = timeLogin;
    } else{
        printf("\n\n **Horario de login inválido! \nVoce sera direcionado ao inicio do processo.\nPreencha os campos com atencao!\n\n");
        pause();
        createUserLog(queue);    }    
    pause();

    printf("Data em que saiu do sistema: \n");
    Date* dateEnd = createDate();
     if(validateDate(dateEnd) == 1){
        user->dateLogout = dateEnd;
    } else{
        printf("\n\n **Data de logout inválida\n! Voce sera direcionado ao inicio do processo.\nPreencha os campos com atencao!\n\n");
        pause();
        createUserLog(queue);
    }

    if(dateCompare(dateStart, dateEnd) == 1){
        printf("\n\n **Data de logout precisa ser maior ou igual a data de login\n! Voce sera direcionado ao inicio do processo.\nPreencha os campos com atencao!\n\n");
        pause();
        createUserLog(queue);
    }
    pause();

    printf("Horario em que saiu do sistema: \n");
    Time* timeLogout = createTime();
    if(validateTime(timeLogout) == 1) {
        user->logoutAt = timeLogout;
    } else{
        printf("\n\n **Horario de logout inválido!\n Voce sera direcionado ao inicio do processo.\nPreencha os campos com atencao!\n\n");
        pause();
        createUserLog(queue);    
    }

    if(dateCompare(dateStart, dateEnd) == 0 && timeCompare(timeLogin, timeLogout) < 0) {
        user->logoutAt = timeLogout;
    } else{
        printf("\n\n **Em datas iguais o horario de logout precisa ser depois do horario de login!\n Voce sera direcionado ao inicio do processo.\nPreencha os campos com atencao!\n\n");
        pause();
        createUserLog(queue);    
    }
    pause();

    return user;                
}

Queue* createQueue(){
   Queue* queue = (Queue*) malloc(sizeof(Queue));

     if(!queue){
         printf("Problema com a criacao da fila de processos de log!\n");
         exit(0);
     }

     queue->first = NULL;
     queue->last = NULL;   

     return queue;
 }

 UserLog* popQueue(Queue* queue){
    UserLog* tmp = NULL;

    if(queue->first != NULL){      
      tmp = queue->first;            
      queue->first = queue->first->next;
      queue->length--;
    }else{
      printf("Fila vazia!\n\n");
    }
 } 

//insere no final da fila
void insertLog(Queue* queue, UserLog* user){
    if(queue->length == 0){
      queue->first = user;
      queue->last = user;
      queue->length = 1;
      return;
    } 

    queue->last->next = user;    
    queue->last = user;
    queue->last->next = NULL;
    queue->length++;

    printf("Registro criado com sucesso! \n\n");
    pause();
}

//pega a posicao de uma ocorrencia na fila
int indexLog(Queue* queue, char login[]){
     if(emptyQueue(queue) == 0){
        printf("Impossivel encontrar usuario em lista vazia! \n\n");
        pause();
        return -1;
    }

    UserLog* userTmp = queue->first;
    int indexOfUser = 0;

    while(userTmp->next != NULL){
        if(strcmp(userTmp->login, login) == 0){
            printf("usuario %s encontrado com sucesso na posicao %d da fila.\n\n", login, indexOfUser);
            return indexOfUser;
        }
        userTmp = userTmp->next;
        indexOfUser++;
    }

    return -1;
}

UserLog* getUser(Queue* queue, int index){

    if(queue->length == 0){
        return NULL;
    }

    if(index == 0 && queue->length == 1){
        return queue->first;        
    }

    UserLog* userTmp = queue->first;
    

    int position = 0;

    while(position <  queue->length){
        if(position == index){
            return userTmp;
        }
        position++;
        userTmp = userTmp->next;
    }

    printf("Usuario nao encontrado na fila!\n\n");
    return NULL;

}

//verifica se a lista esta vazia
int emptyQueue(Queue* queue){
    if(queue->length == 0) {
        printf("Fila Vazia!\n\n");        
        pause();
        return 0;
    } 
    printf("Fila com %d elemento%c...\n\n", queue->length, queue->length == 1 ? '.':'s'); 
    pause();   
    return 1;
}

 void printUserLog(UserLog* user){        
    printf("Login do usuario: %s\n\n", user->login);
    printf("Data e hora do Login: %d/%d/%d - %d:%d:%d;\n\n", 
            user->dateLogin->day, user->dateLogin->month, user->dateLogin->year, 
            user->loginAt->hours, user->loginAt->minutes, user->loginAt->seconds
    );
    printf("Data e hora do Logout: %d/%d/%d - %d:%d:%d;\n\n", 
            user->dateLogout->day, user->dateLogout->month, user->dateLogout->year, 
            user->logoutAt->hours,user->logoutAt->minutes, user->logoutAt->seconds
    );    
 }

void pause(){
    printf("\nAperte qualquer tecla para prosseguir...\n");
    getchar();
    scanf("c\n");
    fflush(stdin);
	printf("\33[H\33[2J");
}

void createTestBase(Queue* queue){
    UserLog* userTest1 = (UserLog*) malloc(sizeof(UserLog));
    Date* dateLogin1 = (Date*) malloc(sizeof(Date));
    Time* timeLogin1 = (Time*) malloc(sizeof(Time));
    Date* dateLogout1 = (Date*) malloc(sizeof(Date));
    Time* timeLogout1 = (Time*) malloc(sizeof(Time));

    UserLog* userTest2 = (UserLog*) malloc(sizeof(UserLog));
    Date* dateLogin2 = (Date*) malloc(sizeof(Date));
    Time* timeLogin2 = (Time*) malloc(sizeof(Time));
    Date* dateLogout2 = (Date*) malloc(sizeof(Date));
    Time* timeLogout2 = (Time*) malloc(sizeof(Time));

    UserLog* userTest3 = (UserLog*) malloc(sizeof(UserLog));
    Date* dateLogin3 = (Date*) malloc(sizeof(Date));
    Time* timeLogin3 = (Time*) malloc(sizeof(Time));
    Date* dateLogout3 = (Date*) malloc(sizeof(Date));
    Time* timeLogout3 = (Time*) malloc(sizeof(Time));


    UserLog* userTest3Again = (UserLog*) malloc(sizeof(UserLog));
    Date* dateLogin3Again = (Date*) malloc(sizeof(Date));
    Time* timeLogin3Again = (Time*) malloc(sizeof(Time));
    Date* dateLogout3Again = (Date*) malloc(sizeof(Date));
    Time* timeLogout3Again = (Time*) malloc(sizeof(Time));

    strcpy(userTest1->login,"usuarioDeTeste01");
    
    dateLogin1->day = 10;
    dateLogin1->month = 10;
    dateLogin1->year = 2020;
    userTest1->dateLogin = dateLogin1;

    timeLogin1->hours = 8;
    timeLogin1->minutes = 10;
    timeLogin1->seconds = 25;
    userTest1->loginAt = timeLogin1;

    dateLogout1->day = 10;
    dateLogout1->month = 10;
    dateLogout1->year = 2020;
    userTest1->dateLogout = dateLogout1;

    timeLogout1->hours = 17;
    timeLogout1->minutes = 15;
    timeLogout1->seconds = 45;
    userTest1->logoutAt = timeLogout1;
    insertLog(queue, userTest1);


    strcpy(userTest2->login,"usuarioDeTeste02");    
    dateLogin2->day = 10;
    dateLogin2->month = 10;
    dateLogin2->year = 2020;
    userTest2->dateLogin = dateLogin2;

    timeLogin2->hours = 7;
    timeLogin2->minutes = 59;
    timeLogin2->seconds = 55;
    userTest2->loginAt = timeLogin2;

    dateLogout2->day = 10;
    dateLogout2->month = 10;
    dateLogout2->year = 2020;
    userTest2->dateLogout = dateLogout2;

    timeLogout2->hours = 17;
    timeLogout2->minutes = 0;
    timeLogout2->seconds = 45;
    userTest2->logoutAt = timeLogout2;    
    insertLog(queue, userTest2);

    strcpy(userTest3->login,"usuarioDeTeste03");    
    dateLogin3->day = 10;
    dateLogin3->month = 10;
    dateLogin3->year = 2020;
    userTest3->dateLogin = dateLogin3;

    timeLogin3->hours = 8;
    timeLogin3->minutes = 59;
    timeLogin3->seconds = 50;
    userTest3->loginAt = timeLogin3;

    dateLogout3->day = 10;
    dateLogout3->month = 10;
    dateLogout3->year = 2020;
    userTest3->dateLogout = dateLogout3;

    timeLogout3->hours = 18;
    timeLogout3->minutes = 15;
    timeLogout3->seconds = 45;
    userTest3->logoutAt = timeLogout3;    
    insertLog(queue, userTest3);

    strcpy(userTest3Again->login,"usuarioDeTeste03");    
    dateLogin3Again->day = 11;
    dateLogin3Again->month = 10;
    dateLogin3Again->year = 2020;
    userTest3Again->dateLogin = dateLogin3Again;

    timeLogin3Again->hours = 8;
    timeLogin3Again->minutes = 59;
    timeLogin3Again->seconds = 55;
    userTest3Again->loginAt = timeLogin3Again;

    dateLogout3Again->day = 11;
    dateLogout3Again->month = 10;
    dateLogout3Again->year = 2020;
    userTest3Again->dateLogout = dateLogout3Again;

    timeLogout3Again->hours = 18;
    timeLogout3Again->minutes = 15;
    timeLogout3Again->seconds = 45;
    userTest3Again->logoutAt = timeLogout3Again;    
    insertLog(queue, userTest3Again);
}
