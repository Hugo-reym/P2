/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Hugo Rey Montoliu LOGIN 1: hugo.reym@udc.es
 * AUTHOR 2:Daniel Alaimo Garcia LOGIN 2: d.alaimo@udc.es
 * GROUP: 6.1
 * DATE: ** / ** / **
 */

#include "bid_stack.h"

bool push(tItemS d, tStack *stack) {
    if (stack->top==(SMax-1)) {
        return false;
    }
    else {
        stack->top++;
        stack->data[stack->top] = d;
        return true;
    }
}
void pop(tStack *stack) {
    stack->top--;
}
tItemS peek(tStack stack) {
    return stack.data[stack.top];
}
void createEmptyStack(tStack *stack) {
    stack->top= SNULL;
}
bool isEmptyStack(tStack stack) {
    return (stack.top == SNULL);
}
