/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Hugo Rey Montoliu LOGIN 1: hugo.reym@udc.es
 * AUTHOR 2: Daniel Alaimo Garcia LOGIN 2: d.alaimo@udc.es
 * GROUP: 6.1
 * DATE: ** / ** / **
 */

#ifndef BID_STACK_H
#define BID_STACK_H
#define SMax 100
#define SNULL -1
#include <stdbool.h>
#include "types.h"

typedef struct {
    tUserId bidder;
    tConsolePrice consolePrice;
}tItemS;
typedef int tPosS;
typedef struct {
    tItemS data[SMax];
    tPosS top;
}tStack;
void createEmptyStack(tStack *stack);
bool push (tItemS item,tStack *stack);
void pop(tStack *stack);
tItemS peek(tStack stack);
bool isEmptyStack(tStack stack);
#endif
