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

int count_split_inv(int *p, int *l, int *r, size_t mid, size_t end){
    size_t k = 0;
    size_t i = 0;
    size_t j = 0;
    int inversions_count = 0;

    while(i < mid && j < (end - mid)){
        if(*(l + i) <= *(r + j)){
            *(p + k) = *(l + i);
            i++;
        }else if(*(r + j) < *(l +i)){
            *(p + k) = *(r + j);
            j++;
            inversions_count += (mid - i);
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

    return inversions_count;
}

int count_sort(int *p, size_t arrsize)
{
    if(arrsize < 2) return 0;
    int inversions_count = 0;   
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
    inversions_count += count_sort(l, mid);
    inversions_count += count_sort(r, arrsize - mid);
    inversions_count += count_split_inv(p, l, r, mid, arrsize);
    free(l);
    free(r);
    return inversions_count;
};

int main(){
    srand((unsigned) time(NULL));
    const int range_max  = 100;
    const int range_min = 1;
    int array_size;
    
    printf("Digit the size of the array\n");
    scanf("%d", &array_size);
    while(array_size < 1){
       printf("%d is not a valid size, the size of the array must be greater than 0\nDigit a new size:\n", array_size); 
       scanf("%d", &array_size);
    }

    int* p = malloc(sizeof(int) * array_size);
    int inversions_count;
    if(p == NULL){
        printf("Can't allocate memory");
        exit(1);
    }  
    for(size_t i = 0; i < array_size; i++){
        *(p + i) = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    }

    print_array(p, array_size);
    inversions_count = count_sort(p, array_size);
    printf("Inversions: %d\n", inversions_count);

    free(p);
    return 0;
}