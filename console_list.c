/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Hugo Rey Montoliu LOGIN 1: hugo.reym@udc.es
 * AUTHOR 2: Daniel Alaimo Garcia LOGIN 2: d.alaimo@udc.es
 * GROUP: 6.1
 * DATE: ** / ** / **
 */

#include "console_list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool createNode(tPosL* p);
void createEmptyList(tList* l) {
    *l =LNULL;
}
bool createNode(tPosL* p) {
    *p=malloc(sizeof(struct tNode));
    return (*p!=LNULL);
}
tPosL findPosition(tList L, tItemL d) {
    tPosL p;
    p=L;
    while ((p->next)!=LNULL && (strcmp((p->next)->data.consoleId,d.consoleId)<0)) {
        p=p->next;
    }
    return p;
}
bool insertItem(tItemL d,tList* L) {
    tPosL q,p;
    if(!createNode(&q)) {
        return false;
    }
    else {
        q->data=d;
        q->next=LNULL;
        if(*L==LNULL) {
            *L=q; //The list now points to the first element
        } else if(strcmp((*L)->data.consoleId,d.consoleId)>0) {//insert at the begining
            q->next=*L;
            *L=q;
        } else {
            p=findPosition(*L,d);
            q->next=p->next;
            p->next=q;
        }
        return true;
    }
}

tPosL last(tList L) {
    tPosL p;
    for(p=L;p->next!=LNULL;p=p->next);
    return p;
}
tPosL first(tList L) {
    return L;
}
tPosL next(tPosL p, tList L) {
    return p->next;
}
tPosL previous(tPosL p, tList L) {
    tPosL q;
    if(p==L) {
        return LNULL;
    } else {
        for(q=L;q->next!=p;q=q->next);
        return q;
    }
}
tList deleteAtPosition(tPosL p,tList *l) {
    tPosL q;
    if(p==*l) {
        *l=(*l)->next;

    } else if(p->next==LNULL) {//delete the element in the last position
        for(q=*l;q->next!=p;q=q->next);
        q->next=LNULL;
    } else {
        //delete between two nodes
        q=p->next;
        p->data=q->data;
        p->next=q->next;
        p=q;
    }
    free(p);
    return (*l);
}
tPosL findItem(tConsoleId d, tList L) {
    tPosL p;
    for(p=L;(p!=LNULL);p=p->next) {
        if (strcmp(p->data.consoleId, d)==0) {
            return p;
        }
    }
    return LNULL;
}
void updateItem(tItemL d, tPosL p, tList* L) {
    p->data=d;
}
bool isEmptyList(tList L) {
    return (L==LNULL);
}
tItemL getItem(tPosL p, tList L) {
    return p->data;
}