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

void swap(int* p, size_t a, size_t b){
    int temp = *(p + a);
    *(p + a) = *(p + b);
    *(p + b) = temp;
}

size_t random_(size_t start, size_t end){
    return ((double)rand() / RAND_MAX) * (end - start) + start;
}

int partition(int *p, size_t start, size_t end){
    size_t pIndex = start;
    int pivot = *(p + end);
    for(size_t i = start; i < end; i++){
        if(*(p + i) <= pivot){
            swap(p, i, pIndex);
            pIndex++;
        }
    }
    if(pIndex < end)
        swap(p, pIndex, end);
    return pIndex;
}

int randomize_partition(int *p, size_t start, size_t end){
    size_t pIndex = random_(start, end);
    swap(p, pIndex, end);
    return partition(p, start, end);
}

void quick_sort(int *p, int start, int end){
    if(end - start < 1) return;
    int pIndex = randomize_partition(p, start, end);
    quick_sort(p, start, pIndex - 1);
    quick_sort(p, pIndex + 1, end);
}

size_t max_value(int * p, size_t arr_size){
    int max = *p;
    for(size_t i = 1; i < arr_size; i++){
        if(*(p + i) > max){
            max = *(p + i);
        }
    }
    return max;
}

size_t create_random_unimodal_array(int* r, size_t array_size){
    //Range for the values in the array
    const int range_max  = array_size < 100 ? 100 : array_size;
    const int range_min = 1;
    
    size_t mid_size = random_(1, array_size - 1);

    int* p = malloc(sizeof(int) * mid_size);
    int* q = malloc(sizeof(int) * array_size - mid_size);
    
    if(p == NULL || q == NULL){
        printf("Can't allocate memory");
        exit(1);
    }  
    for(size_t i = 0; i < array_size; i++){
        if(i < mid_size)
            *(p + i) = random_(range_min, range_max);
        else
            *(q + (i - mid_size )) = random_(range_min, range_max);
    }

    //creating a unimodal array in r
    int p_max_value = max_value(p, mid_size);
    int q_max_value = max_value(q, array_size - mid_size);
    //store the max_value_index for future validation
    int max_value_index = 0;
    quick_sort(p, 0, mid_size - 1);
    quick_sort(q, 0, array_size - mid_size - 1);
    if(p_max_value > q_max_value){
        for(size_t i = 0; i < array_size; i++){
            if(i < mid_size)
                *(r + i) = *(p + i);
            else
                *(r + i) = *(q + (array_size - i - 1));
        }
        max_value_index = mid_size - 1;
    }else{
        for(size_t i = 0; i < array_size; i++){
            if(i < mid_size)
                *(r + (array_size - i - 1)) = *(p + i);
            else
                *(r + i - mid_size) = *(q + i - mid_size);
        }
        max_value_index = array_size - mid_size - 1;
    }
    
    return max_value_index;
    free(p);
    free(q);
}

int get_array_size(int *array_size){
    char buf[6] = "";
    printf("Digit the size for the random unimodal array\n");
    
    if(!fgets(buf, sizeof buf, stdin)){
        exit(1);
    };
    *array_size = strtol(buf, NULL, 0);
    if(*array_size > 0){
        return 1;
    }
    printf("Invalid Input, the array size must be grater than 0\n"); 
    return 0;
}

size_t find_max_value_unimodal_array(int* p, int start, int end){
    if(end - start < 1) return start;
    int mid = (end + start) / 2;
    while(mid != start && *(p + mid) == *(p + mid + 1))
        mid--;
    if(*(p + mid) < *(p + mid + 1)){
        return find_max_value_unimodal_array(p, mid + 1, end);
    }else{
        return find_max_value_unimodal_array(p, start, mid);
    }
}
int main(){
    srand((unsigned) time(NULL));
    int array_size;
    while(!get_array_size(&array_size)){
    }

    int* r = malloc(sizeof(int) * array_size);
    
    if(r == NULL){
        printf("Can't allocate memory");
        exit(1);
    } 

    size_t max_value_index = create_random_unimodal_array(r, array_size);
    printf("This is the unimodal array: ");
    print_array(r, array_size);
    printf("max value %d\n", *(r + max_value_index));
    size_t max_value_index_alg = find_max_value_unimodal_array(r, 0, array_size - 1);
    printf("max value algorithm %d\n", *(r + max_value_index_alg));
    free(r);
}