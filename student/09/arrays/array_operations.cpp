#include "array_operations.hh"
#include <iostream>

int greatest_v1(int *itemptr, int size){
    int greatest=0;

    while(*itemptr < size){
        if(*itemptr>greatest){
            greatest=*itemptr;
        }
        ++itemptr;
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr){
    int greatest=0;
    while(itemptr!=endptr){
        if(*itemptr>greatest){
            greatest =*itemptr;
        }
        ++itemptr;
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr){
    int it=0;
    while(itemptr!=endptr){
        *(targetptr + it) = *itemptr;
        ++itemptr;
        ++it;
    }
}

void reverse(int *leftptr, int *rightptr){

    while(leftptr!=rightptr){
        int r = *(rightptr-1);
        int l = *(leftptr);
        *(leftptr)=r;
        *(rightptr-1)=l;
        --rightptr;
        ++leftptr;
    }
}
