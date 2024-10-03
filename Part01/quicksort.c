#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(int* p, size_t array_size){
    for(size_t i = 0; i < array_size; i++){
        if(i == 0){
            printf("[ ");
        }
        printf("%2d ", *(p + i));
        if(i == array_size - 1){
            printf("]\n");
        }
    }
}

void swap(int* array,int a, int b){
    int temp = *(array + a);
    *(array + a) = *(array + b);
    *(array + b) = temp;
}

size_t _random(size_t start, size_t end){
    return ((double)rand() / RAND_MAX) * (end - start) + start;
}

int get_non_negative_integer(int *number, char* message, char* error_message){
    char buf[6] = "";
    printf("%s\n", message);
    
    if(!fgets(buf, sizeof buf, stdin)){
        exit(1);
    };
    *number = strtol(buf, NULL, 0);
    if(*number> 0){
        return 1;
    }
    printf("%s\n", error_message);
    return 0;
}

void generate_random_distinct_array(int* array, int array_size){
    int aux_array_size = array_size * 10;
    int aux_array[aux_array_size];
    int random_index;
    int temp;
    for(size_t i = 0; i < aux_array_size; i++){
        aux_array[i] = i;
    }
    while(array_size > 0){
        random_index = _random(0, aux_array_size - 1);
        temp = aux_array[random_index];
        swap(aux_array, random_index, aux_array_size - 1);
        *(array + array_size - 1) = temp;
        aux_array_size--;
        array_size--;
    }
}
int partition(int* array, size_t start, size_t end){
    size_t p_index = start;
    int pivot = *(array + end);
    for(size_t i = start; i < end; i++){
        if(*(array + i) < pivot){
            swap(array,p_index, i);
            p_index++;
        }
    }
    swap(array, p_index, end);
    return p_index;
}

int randomize_partition(int* array, size_t start, size_t end){
    size_t p_index = _random(start, end);
    swap(array, p_index, end);
    return partition(array, start, end);
}

void quick_sort(int* array, int start, int end){
    if(end - start < 1) return;
    int p_index = randomize_partition(array, start, end);
    quick_sort(array, start, p_index - 1);
    quick_sort(array, p_index + 1, end);
}

int main(){
    srand((unsigned) time(NULL));
    int array_size;
    while(!get_non_negative_integer(&array_size,
        "Digit the size for the array", "Invalid Input, the value must be grater than 0")){
    }
    int* p = malloc(sizeof(int) * array_size);
    if(p==NULL){
        printf("Can't allocate memory");
        exit(1);
    }

    generate_random_distinct_array(p, array_size);
    print_array(p, array_size);
    quick_sort(p, 0, array_size - 1);
    print_array(p, array_size);
    return 0;
}