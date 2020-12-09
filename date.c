#include"date.h"

Date* createDate(){
    Date* date;
    printf("Digite o dia:");
    scanf("%d",&date->day);
    
    printf("Digite o mes:");
    scanf("%d",&date->month);
    
    printf("Digite o ano:");
    scanf("%d",&date->year);    
    
    return date;
}

Time* createTime(){

    Time* time = (Time*) malloc(sizeof(Time));

    printf("Informe o horario que quer criar o log (apenas horas):");
    scanf("%d", &time->hours);

    printf("Informe o horario que quer criar o log (apenas minutos):");
    scanf("%d", &time->minutes);

    printf("Informe o horario que quer criar o log (apenas segundos):");
    scanf("%d", &time->seconds);

    return time;

}

int validateTime(Time* time){        
    return (((time->hours >= 0 && time->hours < 24) && 
             (time->minutes >= 0 && time->minutes <= 59) &&
             (time->seconds >= 0 && time->seconds <= 59)) ? 1 : 0);
}

int validateDate(Date* date){        
    return (((validateYear(date->year) == 1) && 
             (validateMonth(date->month) == 1) &&
             (validateDay(date) == 1)) ? 1 : 0);
}

int validateYear(int year){
    return ((year >= 1500 && year <= 2100) ? 1 : 0);    
}

int validateMonth(int month){
    return ((month >= 1 && month <= 12) ? 1 : 0);    
}

int validateDay(Date* date){
    return ((date->day >= 1 && date->day <= lastDayOfMonth(date)) ? 1 : 0);    
}

int lastDayOfMonth(Date* date){  
    int lastDayOfMonth = 0;
    int month = date->month;
    
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        lastDayOfMonth = 31;        
    } else if(month == 4 || month == 6 || month == 9 || month == 11){
        lastDayOfMonth = 30;
    } else if(month == 2){
        lastDayOfMonth = leapYear(date->year) == 1 ? 29 : 28;      
    } 

    return lastDayOfMonth;       
}

int leapYear(int year){
    return ((year % 4) == 0) && (((year % 100 != 0) || ((year % 400) == 0)) ? 1 : 0);
}

int dayOfWeekString(Date* date){     
    int dayOfWeekInteger = (
        ((date->month-1) * lastDayOfMonth(date)) + 
        ((date->day)+4))
        % 7;

    char dayOfWeekString[50];

    switch(dayOfWeekInteger){
        case 0: 
            strcpy(dayOfWeekString, "Dia da semana : Domingo");
            break;            
        case 1: 
            strcpy(dayOfWeekString, "Dia da semana : Segunda-Feira");
            break;  
        case 2: 
            strcpy(dayOfWeekString, "Dia da semana : Terça-Feira");
            break;  
        case 3: 
            strcpy(dayOfWeekString, "Dia da semana : Quarta-Feira");
            break;  
        case 4: 
            strcpy(dayOfWeekString, "Dia da semana : Quinta-Feira");
            break;  
        case 5: 
            strcpy(dayOfWeekString, "Dia da semana : Sexta-Feira");
            break;  
        case 6: 
            strcpy(dayOfWeekString, "Dia da semana : Sábado");
            break;  
    }        
    printf("%s\n", dayOfWeekString);  
    return 0;      
}


int fullMonthString(int month){
    char result[15];
         switch(month){
            case 1: 
                strcpy(result, "Janeiro");
                break;            
            case 2: 
                strcpy(result, "Fevereiro");
                break;  
            case 3: 
                strcpy(result, "Março");
                break;  
            case 4: 
                strcpy(result, "Abril");
                break;  
            case 5: 
                strcpy(result, "Maio");
                break;  
            case 6: 
                strcpy(result, "Junho");
                break;  
            case 7: 
                strcpy(result, "Julho");
                break; 
            case 8: 
                strcpy(result, "Agosto");
                break;   
            case 9: 
                strcpy(result, "Setembro");
                break;   
            case 10: 
                strcpy(result, "Outubro");
                break;   
            case 11: 
                strcpy(result, "Novembro");
                break;   
            case 12: 
                strcpy(result, "Dezembro");
                break;   
        }

        printf("%s", result);
        return 0;   
}

int fullDateString(Date* date){                
    printf("Rio grande, %d de ", date->day);
    fullMonthString(date->month);
    printf(" de %d\n", date->year);
    return 0;           
}

//se as datas forem iguais retorna 0, 
//se a primeira data for maior retorna 1, 
//se a segunda data for maior retorna -1
int dateCompare(Date* firstDate, Date* secondDate){    
    if(firstDate->year > secondDate->year){
        return 1;
    } else if(firstDate->year < secondDate->year){
        return -1;
    }else{
        if(firstDate->month > secondDate->month){
            return 1;
        }else if(firstDate->month < secondDate->month){
            return -1;
        }else{
            if(firstDate->day > secondDate->day){
                return 1;
            }else if(firstDate->day > secondDate->day){
                return -1;
            }    
        }        
    }
    return 0;
}

//se as datas forem iguais retorna 0, 
//se a primeira data for maior retorna 1, 
//se a segunda data for maior retorna -1
int timeCompare(Time* firstTime, Time* secondTime){    
    if(firstTime->hours > secondTime->hours){
        return 1;
    } else if(firstTime->hours < secondTime->hours){
        return -1;
    }else{
        if(firstTime->minutes > secondTime->minutes){
            return 1;
        }else if(firstTime->minutes < secondTime->minutes){
            return -1;
        }else{
            if(firstTime->seconds > secondTime->seconds){
                return 1;
            }else if(firstTime->seconds > secondTime->seconds){
                return -1;
            }    
        }        
    }
    return 0;
}