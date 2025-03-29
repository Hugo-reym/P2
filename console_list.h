/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Hugo Rey Montoliu LOGIN 1: hugo.reym
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef CONSOLE_LIST_H
#define CONSOLE_LIST_H

#include "types.h"
#include "bid_stack.h"
#include <stdbool.h>
#define LNULL NULL

typedef struct tItemL {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;
typedef struct tNode *tPosL;
struct tNode {
    tItemL data;
    tPosL next;
};
typedef tPosL tList;
tPosL findPosition(tList L, tItemL d);
void createEmptyList(tList *L);
bool insertItem(tItemL d, tList *L);
tList deleteAtPosition(tPosL p, tList *L);
bool isEmptyList(tList L);
tPosL last(tList L);
tPosL first(tList L);
tPosL previous(tPosL p, tList L);
void updateItem(tItemL d, tPosL p, tList *L);
tPosL next(tPosL p, tList L);
tPosL findItem(tConsoleId d,tList L);
tItemL getItem(tPosL p, tList L);


#endif
