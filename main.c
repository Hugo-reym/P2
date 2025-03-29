/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Hugo Rey Montoliu LOGIN 1: hugo.reym@udc.es
 * AUTHOR 2: Daniel Alaimo García LOGIN 2: d.alaimo@udc.es
 * GROUP: 6.1
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "console_list.h"

#define MAX_BUFFER 255
tItemL createItem(tItemL d,char *id,  char *user, char *brand,char *price,tStack s){

    strcpy(d.consoleId,id);
    strcpy(d.seller,user);
    d.consoleBrand=(unsigned)*brand;
    d.consolePrice=atof(price);
    d.bidCounter=0;
    d.bidCounter=0;
    d.bidStack=s;
    return d;
}
void addNewConsole(tList *l,char *id, char *user, char *brand,char *price) {
    tItemL d;
    tStack s;
    createEmptyStack(&s);
    char y[9];
    d=createItem(d,id,user,brand,price,s);
    if((char)d.consoleBrand == 'n') {
        strcpy(y, "nintendo");
    }else {
        strcpy(y, "sega");
    }
    printf("console %s seller %s brand %s price %s\n",  id, user, brand, price);
    if (findItem(d.consoleId,*l)==LNULL) {
        if (insertItem(d,l)) {
            printf("*New: console %s seller %s brand %s price %.2f\n", d.consoleId,d.seller,y,d.consolePrice);
        } else {printf("+ Error: New not possible\n");}
    } else {printf("+ Error: New not possible\n");}
}
void showStats(tList l) {
    tPosL pos;
    char y[9];
    tItemL tmp,top_increase;
    int numb_sega,numb_nintendo,counter;
    numb_sega=numb_nintendo=counter=0;
    float sum_prices_sega,sum_prices_nintendo,avg_prices_sega,avg_prices_nintendo,increase,aux;
    sum_prices_sega=sum_prices_nintendo=avg_prices_nintendo=avg_prices_sega=aux=0.0;
    if (!isEmptyList(l)) {
        for(pos=first(l);pos!=next(last(l),l);pos = next(pos,l)) {

            tmp=getItem(pos,l);
            if((char)tmp.consoleBrand == 'n') {
                strcpy(y, "nintendo");
                numb_nintendo++;
                sum_prices_nintendo+=tmp.consolePrice;
                avg_prices_nintendo=((float)sum_prices_nintendo/(float)numb_nintendo);
            }else {
                strcpy(y, "sega");
                numb_sega++;
                sum_prices_sega+=tmp.consolePrice;
                avg_prices_sega=((float)sum_prices_sega/(float)numb_sega);
            }

            increase=((tmp.bidStack.data->consolePrice-tmp.consolePrice)/tmp.consolePrice)*100;
            if (increase>aux){aux=increase; top_increase=tmp;}
            if (tmp.bidCounter==0) {
                printf("Console %s seller %s brand %s price %.2f. No bids \n",tmp.consoleId,tmp.seller,y,tmp.consolePrice);
            } else {
                counter++;
                printf("Console %s seller %s brand %s price %.2f bids %d top bidder %s\n",tmp.consoleId,tmp.seller,y,tmp.consolePrice,tmp.bidCounter,tmp.bidStack.data->bidder);
            }
        }
        if((char)top_increase.consoleBrand == 'n') {
            strcpy(y, "nintendo");
        }else {
            strcpy(y, "sega");
        }
        printf("Brand    Consoles    Price    Average\nNintendo        %d    %.2f    %.2f\n",numb_nintendo,sum_prices_nintendo,avg_prices_nintendo);
        printf("Sega            %d   %.2f   %.2f\n", numb_sega, sum_prices_sega, avg_prices_sega);
        if (counter==0) {
            printf("Top bid not possible\n");
        } else {
            printf("Top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n",top_increase.consoleId,top_increase.seller,y,top_increase.consolePrice,top_increase.bidStack.data->bidder,top_increase.bidStack.data->consolePrice,aux);
        }
    } else{printf("+ Error: Stats not possible");}
}
void deleteConsole(tList *l,tConsoleId id) {
    tItemL temp;
    char y[9];

    if(!isEmptyList(*l)) {
        printf(" console %s\n",id);
        if(findItem(id,*l)==LNULL) {
            printf(" + Error: Delete not possible\n");
        } else {
            temp=getItem(findItem(id,*l),*l);
            deleteAtPosition(findItem(id,*l),l);
            if((char)temp.consoleBrand == 'n') {
                strcpy(y, "nintendo");
            }else {
                strcpy(y, "sega");
            }
            printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",temp.consoleId,temp.seller,y,temp.consolePrice,temp.bidCounter);
        }
    } else {
        printf("+ Error: Delete not possible");
    }
}
void Bid(tList *l,tConsoleId console,tUserId seller,tConsolePrice price) {
    char y[9];
    tItemS tempS;
    strcpy(tempS.bidder,seller);
    tempS.consolePrice=price;
    printf("console %s bidder %s price %.2f\n",console,seller,price);
    if (findItem(console,*l)==LNULL) {
        printf(" + Error: Bid not possible\n");
    }else {
        tItemL temp = getItem(findItem(console, *l), *l);
        if(price<=temp.consolePrice || (strcmp(seller,temp.seller)==0) || !push(tempS,&temp.bidStack)) {
            printf(" + Error: Bid not possible\n");
        }else {

            if((char)temp.consoleBrand == 'n') {
                strcpy(y, "nintendo");
            }else {
                strcpy(y, "sega");
            }
            temp.bidStack.data->consolePrice=price;
            strcpy(temp.bidStack.data->bidder,seller);
            temp.bidCounter++;

            push(tempS,&temp.bidStack);
            updateItem(temp,findItem(console,*l),l);
            printf("* Bid: console %s bidder %s brand %s price %.2f bids %d\n",temp.consoleId,temp.bidStack.data->bidder,y,temp.bidStack.data->consolePrice,temp.bidCounter);
        }
    }
}
void Award(tList *l,tConsoleId console) {
    char y[9];
    tItemL temp = getItem(findItem(console, *l), *l);
    if (findItem(console,*l)==LNULL || isEmptyStack(temp.bidStack)) {
        printf(" + Error: Award not possible\n");
    } else {
        if((char)temp.consoleBrand == 'n') {
            strcpy(y, "nintendo");
        }else {
            strcpy(y, "sega");
        }
        printf("* Award: console %s bidder %s brand %s price %.2f\n",temp.consoleId,temp.bidStack.data->bidder,y,temp.bidStack.data->consolePrice);
        deleteAtPosition(findItem(console,*l),l);
    }
}
void Invalidate(tList *l) {
    tPosL pos;
    tItemL temp;
    char y[9];
    int num_console,num_bids,aux;
    num_console=num_bids=aux=0;
    float avg_bids=0;
    for(pos=first(*l);pos!=next(last(*l),*l);pos = next(pos,*l)) {
        temp=getItem(pos,*l);
        num_bids+=temp.bidCounter;
        num_console++;
    }
    avg_bids=(float)num_bids/(float)num_console;
    if (isEmptyList(*l)) {
        printf(" + Error: Invalidate not possible\n");
    } else {
        for(pos=first(*l);pos!=next(last(*l),*l);pos = next(pos,*l)) {
            temp=getItem(pos,*l);
            if (temp.bidCounter>(2*avg_bids)) {

                if((char)temp.consoleBrand == 'n') {
                    strcpy(y, "nintendo");
                }else {
                    strcpy(y, "sega");
                }
                printf("* InvalidateBids: console %s seller %s brand %s price %.2f bids %d average bids %.2f\n",temp.consoleId,temp.seller,y,temp.consolePrice,temp.bidCounter,avg_bids);
                temp.bidCounter=0;
                updateItem(temp,findItem(temp.consoleId,*l),l);
            } else{aux++;}
        }
    } if(aux==num_console) {
        printf(" + Error: Invalidate not possible\n");
    }
}
void Remove(tList *l) {
    tPosL pos;
    tItemL temp;
    char y[9];
    for(pos=first(*l);pos!=next(last(*l),*l);pos = next(pos,*l)) {
        temp=getItem(pos,*l);
        if (temp.bidCounter==0) {
            if((char)temp.consoleBrand == 'n') {
                strcpy(y, "nintendo");
            }else {
                strcpy(y, "sega");
            }
            printf("Removing console %s seller %s brand %s price %.2f bids %d\n",temp.consoleId,temp.seller,y,temp.consolePrice,temp.bidCounter);
            deleteAtPosition(pos,l);
        }
    }
}
void processCommand(tList *l,char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4) {
    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: ",commandNumber,command);
            addNewConsole(l,param1,param2,param3,param4);
            break;
        case 'D':
            printf("%s %c: ",commandNumber,command);
            deleteConsole(l,param1);
            break;
        case 'B':
            printf("%s %c: ",commandNumber,command);
            Bid(l,param1,param2,atof(param3));
            break;
        case 'A':
            printf("%s %c: console %s\n",commandNumber,command, param1);
            Award(l,param1);
            break;
        case 'R':
            printf("%s %c\n",commandNumber,command);
            Remove(l);
            break;
        case 'S':
            printf("%s %c \n",commandNumber,command);
            showStats(*l);
            break;
        case 'I':
            printf("%s %c\n",commandNumber,command);
            Invalidate(l);
            break;
        default:
            printf("%s %c ",commandNumber,command);
            break;
    }
}


void readTasks(char *filename, tList l) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(&l,commandNumber, command[0], param1, param2, param3, param4);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tList l;
    createEmptyList(&l);
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name,l);

    return 0;
}