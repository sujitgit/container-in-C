/**********************************************************************************************
 *  CS 540 - Assignment 1
 *  Author : Sujit Kumar
 *  containers in C.
 * Issue with the code is : Sorting part not completed. I am providing my test code.
 * ********************************************************************************************/

#ifndef  _DEQUE_HPP_
#define  _DEQUE_HPP_

#include<string.h>
#include<stdlib.h>

#define Deque_DEFINE(data_type) \
	struct Deque_##data_type; \
                                   \
        struct Deque_##data_type##_Iterator { \
              int pos;\
              void (*inc)(Deque_##data_type##_Iterator*); \
              void (*dec)(Deque_##data_type##_Iterator*); \
              data_type& (*deref)(Deque_##data_type##_Iterator*);\
              Deque_##data_type* itercontnr;\
              };\
         struct Deque_##data_type { \
              data_type* Container; \
              int container_capacity; \
              int conatiner_curr_size; \
              int front_point; \
              int back_point; \
              char type_name[sizeof("Deque_" #data_type)]; \
              bool (*empty)(Deque_##data_type*); \
              int (*size)(Deque_##data_type*); \
              void (*push_front)(Deque_##data_type*, data_type); \
              void (*push_back)(Deque_##data_type*, data_type); \
              void (*pop_front)(Deque_##data_type*); \
              void (*pop_back)(Deque_##data_type*); \
              void (*dtor)(Deque_##data_type*) ; \
              void (*clear)(Deque_##data_type*); \
              data_type& (*front)(Deque_##data_type*); \
              data_type& (*back)(Deque_##data_type*); \
              data_type& (*at)(Deque_##data_type*, int); \
              Deque_##data_type##_Iterator (*begin)(Deque_##data_type*); \
              Deque_##data_type##_Iterator (*end)(Deque_##data_type*); \
              bool (*compare)(const data_type&, const data_type&); \
           }; \
\
\
void DequeClear(Deque_##data_type* contnr){\
              free(contnr->Container); contnr->front_point = 0; contnr->back_point =0; \
              contnr->container_capacity = 1 ; contnr->conatiner_curr_size = 0; \
              contnr->Container = (data_type*)malloc(sizeof(data_type)); \
}\
\
void DequeDtor(Deque_##data_type* contnr){\
              free(contnr->Container); \
}\
\
data_type& DequeAt(Deque_##data_type* contnr, int pos){\
              return contnr->Container[pos]; \
}\
\
int getsize(Deque_##data_type* contnr){\
               return contnr->conatiner_curr_size; \
}\
\
bool isempty(Deque_##data_type* contnr){\
            if (0==contnr->conatiner_curr_size ) \
                  return true; \
            else \
                  return false; \
}\
\
data_type& getfront(Deque_##data_type* contnr) {\
           return contnr->Container[contnr->front_point]; \
}\
\
data_type& getback(Deque_##data_type* contnr) {\
            return contnr->Container[contnr->back_point]; \
}\
void DequeResize(Deque_##data_type *contnr, int newSz){\
           data_type* temp = (data_type*)malloc(newSz*sizeof(data_type));\
           int start = contnr->conatiner_curr_size -1 ; int front= contnr->front_point; int i=0;\
           while(start>=0){\
                temp[i++]=contnr->Container[front]; front = (front + 1)%(contnr->container_capacity); start = start - 1; \
           }\
           free(contnr->Container); contnr->Container = temp; contnr->container_capacity = newSz; contnr->front_point = 0;\
           contnr->back_point = contnr->conatiner_curr_size - 1;\
}\
\
void DequePushFront(Deque_##data_type* contnr, data_type data){\
           if(contnr->conatiner_curr_size == contnr->container_capacity) {DequeResize(contnr, 2*(contnr->container_capacity));} \
            if (0 == contnr->front_point ) {contnr->front_point = contnr->container_capacity - 1; }\
            else {contnr->front_point = contnr->front_point -1 ;} \
            contnr->Container[contnr->front_point] = data; \
            contnr->conatiner_curr_size = contnr->conatiner_curr_size + 1; \
}\
\
void DequePopFront(Deque_##data_type* contnr){\
           if(0==contnr->conatiner_curr_size) return; \
           else {contnr->front_point = (contnr->front_point + 1)%(contnr->container_capacity);}\
           contnr->conatiner_curr_size = contnr->conatiner_curr_size -1 ; \
}\
\
void DequePopBack(Deque_##data_type* contnr){\
           if(0==contnr->conatiner_curr_size) return; \
           else if (0==contnr->back_point) {contnr->back_point = contnr->container_capacity -1 ;}\
           else {contnr->back_point = contnr->back_point - 1 ;}\
           contnr->conatiner_curr_size = contnr->conatiner_curr_size -1 ; \
}\
\
void DequePushBack(Deque_##data_type* contnr, data_type data){\
           if(contnr->conatiner_curr_size == contnr->container_capacity) {DequeResize(contnr, 2*(contnr->container_capacity));} \
           contnr->back_point = (contnr->back_point + 1)%(contnr->container_capacity);\
           contnr->Container[contnr->back_point] = data; \
           contnr->conatiner_curr_size = contnr->conatiner_curr_size + 1; \
}\
data_type& DequeDeref(Deque_##data_type##_Iterator* iter){ \
           int temp = iter->pos;\
           return iter->itercontnr->Container[temp];\
}\
void DequeInc(Deque_##data_type##_Iterator* itercont){\
           itercont->pos = (itercont->pos + 1) % itercont->itercontnr->container_capacity;\
}\
\
void DequeDec(Deque_##data_type##_Iterator* itercont){\
          if(0==itercont->pos ){ itercont->pos = itercont->itercontnr->container_capacity - 1; }\
          else { itercont->pos = itercont->pos -1 ; }\
}\
\
Deque_##data_type##_Iterator DequeBegin(Deque_##data_type* contnr){\
           Deque_##data_type##_Iterator tempiter;\
           tempiter.pos = contnr->front_point;\
           tempiter.itercontnr = contnr;\
           tempiter.inc = DequeInc; tempiter.dec = DequeDec; tempiter.deref=DequeDeref;\
           return tempiter;\
}\
\
Deque_##data_type##_Iterator DequeEnd(Deque_##data_type* contnr){\
           Deque_##data_type##_Iterator tempiter;\
           tempiter.pos = contnr->back_point + 1;\
           tempiter.itercontnr = contnr;\
           tempiter.inc = DequeInc; tempiter.dec = DequeDec; tempiter.deref=DequeDeref;\
           return tempiter;\
}\
bool Deque_##data_type##_equal(Deque_##data_type temp1, Deque_##data_type temp2){\
           int equal = 1;\
           if(temp1.conatiner_curr_size != temp2.conatiner_curr_size){ return false; }\
           int front1 = temp1.front_point; int front2 = temp2.front_point;\
           int back1 = temp1.back_point; int back2 = temp2.back_point;\
           while(true){\
                const data_type data1 = (temp1.Container[front1]); const data_type data2 = (temp2.Container[front2]); \
                if(!(0 == temp1.compare(data1,data2) && 0==temp1.compare(data2,data1))){ return false;}\
                if(front1 == back1) break;\
                if(front2 == back2) break;\
                front1 = (front1 + 1) % temp1.container_capacity;\
                front2 = (front2 + 1) % temp2.container_capacity;\
            };\
            \
           return true;\
}\
void Deque_##data_type##_ctor(Deque_##data_type* contnr, bool (*comp)(const data_type&, const data_type&)) { \
              contnr->container_capacity = 1; \
              contnr->conatiner_curr_size= 0;  \
              contnr->front_point        = 0;  \
              contnr->back_point         = 0;  \
              strcpy(contnr->type_name, "Deque_" #data_type); \
              data_type* pntr = (data_type*)malloc(sizeof(data_type)); \
              contnr->Container = (data_type*)malloc(sizeof(data_type));  \
              contnr->size =getsize ;  contnr->empty = isempty; contnr->front = getfront; \
              contnr->back = getback;  contnr->push_back = DequePushBack; contnr->push_front = DequePushFront; \
              contnr->pop_back = DequePopBack; contnr->pop_front = DequePopFront;   contnr->begin = DequeBegin;\
              contnr->end = DequeEnd; contnr->at= DequeAt; contnr->dtor=DequeDtor;  contnr->compare= comp; \
              contnr->clear = DequeClear; \
} \
bool Deque_##data_type##_Iterator_equal(Deque_##data_type##_Iterator iter1, Deque_##data_type##_Iterator iter2){\
            if((iter1.itercontnr == iter2.itercontnr) && (iter1.pos == iter2.pos)) return true;\
            return false;\
}\

#endif
