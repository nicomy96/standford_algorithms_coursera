#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(int* p, size_t arrsize){
    for(size_t i = 0; i < arrsize; i++){
        if(i == 0){
            printf("[ ");
        }
        printf("%2d ", *(p + i));
        if(i == arrsize - 1){
            printf("]\n");
        }
    }
}

void merge(int *p, int *l, int *r, size_t mid, size_t end){
    size_t k = 0;
    size_t i = 0;
    size_t j = 0;

    while(i < mid && j < (end - mid)){
        if(*(l + i) <= *(r + j)){
            *(p + k) = *(l + i);
            i++;
        }else if(*(r + j) < *(l +i)){
            *(p + k) = *(r + j);
            j++;
        }
        k++;
    }

    while(i < mid){
        *(p + k) = *(l + i);
        k++;
        i++;
    }
    while(j < (end-mid)){
        *(p + k) = *(r + j);
        k++;
        j++;
    }
}

void merge_sort(int *p, size_t arrsize)
{
    if(arrsize < 2) return;
    size_t mid = (arrsize) / 2;
    int *l = malloc(sizeof(int) * mid);
    int *r = malloc(sizeof(int) * (arrsize - mid));
    if(l == NULL){
        printf("Can't allocate memory");
        exit(1);
    } 
    if(r == NULL){
        printf("Can't allocate memory");
        exit(1);
    } 
    size_t k = 0;
    for(size_t i = 0; i < mid; i++){
        *(l + i) = *(p + k);
        k++; 
    }
    for(size_t j = 0; j < (arrsize - mid); j++){
        *(r + j) = *(p + k);
        k++;
    }
    merge_sort(l, mid);
    merge_sort(r, arrsize - mid);
    merge(p, l, r, mid, arrsize);
    free(l);
    free(r);
};

int main(){
    srand((unsigned) time(NULL));
    const int range_max  = 100;
    const int range_min = 1;
    const size_t array_size = 50;
    int* p = malloc(sizeof(int) * array_size);
    if(p == NULL){
        printf("Can't allocate memory");
        exit(1);
    }  
    for(size_t i = 0; i < array_size; i++){
        *(p + i) = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    }

    print_array(p, array_size);
    merge_sort(p, array_size);
    print_array(p, array_size);

    free(p);
    return 0;
}