#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

unsigned int p = 7;

int N = 16;
int *input_block_in_elements_original;
int *input_block_in_elements_modified;
//int IV[8] = {43, 49, 65, 5, 57, 107, 2, 13, 47, 109, 31, 29, 5, 51, 53, 7};

typedef struct{
    int *array;
    int array_size;
}Array_object;


int IV[16] = {43, 49, 65, 5, 57, 107, 2, 13, 47, 109, 31, 29, 5, 51, 53, 7};

//int IV[8] = {43, 49, 65, 5, 57, 107, 2, 13, 47, 109, 31, 29, 5, 51, 53, 7};

//NMNT matrix for p = 7 and N = 16

//FUNCTION SIGNATURE TO CALCULATE NMNT
int *calculate_NMNT(int *plaintext, int N, int M_p);

//FUNCTION SIGNATURE TO CALCULATE ONMNT
int *calculate_ONMNT(int *plaintext, int N, int M_p);

//FUNCTION SIGNATURE TO CALCULATE O2NMNT
int *calculate_O2NMNT(int *plaintext, int N, int M_p);

//FUNCTION SIGNATURE TO CALCULATE FNT
int *calculate_FNT(char **plaintext, int t);

//FUNCTION SIGNATURE TO ALLOCATE 2D ARRAY
int **memory_allocation_for_2D_array_int(int row_numbers, int column_numbers);

//FUNCTION SIGNATURE OF FREE 2D ARRAY POINTER
void free_2D_array_int(int** array_2D, int x_length);

//FUNCTION SIGNATURE TO ALLOCATE 2D ARRAY
char **memory_allocation_for_2D_array_char(char row_numbers, int column_numbers);

//FUNCTION SIGNATURE OF FREE 2D ARRAY POINTER
void free_2D_array_char(char** array_2D, int x_length);
int mod(int input, int Mp);
int* transform_block(int* input_block, int Mp);
char* string_to_binary(char* s);
int * shifted_array(int *input, int shift_amount);
int binary_to_hexadecimal(long long int binary_value);
int* xor_operation(int* hash_input_1, int* hash_input_2);
int* add_elements(int* first_element, int* second_element);
int* shuffling_array(int* input);

int main() {
    int Mp = (1 << p)-1;
    int *hash_output_modified = malloc(sizeof(int) * N);
    char *hash_output_binary_original =  malloc(sizeof(char)*N);
    char *hash_output_binary_temp =  malloc(sizeof(char)*N);
    char *hash_output_binary_modified =  malloc(sizeof(hash_output_modified)*N);
    char *pOutputbit_probability = malloc(sizeof (char) * 128);
    char pCounts = malloc(sizeof (char) * 128);
    char *pBinary_outout_hex = malloc(sizeof(char)*16);
    long long int binary_output_input;
    long long int binary_output_hexadecimal;
    int total_changed_bit = 0;

    // printf("Enter your message: ");
    //pInput_message = fgets(pInput_message, 2000, stdin);
    //char message[]  = "Two different input messages producing the same hash value is called a collision. In general, a property for a good hash function must possess is collision resistance";
//STEP # 1: GENERATE INPUT MESSAGE
    char char1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/,.-+=~`<>:";
    int message_size = sizeof (char1) - 1;
    //int message_size = sizeof(message) - 1;
    // int message_size_2 = sizeof (char1) - 1;
    char * pInput_message = malloc(sizeof(message_size));
    //Number of iterations
    int total_iterations = 1000 ;
    int * changed_bits = malloc(sizeof(int) * total_iterations);
    srand(time(0));
    int hit_number;
    int hit_number_0 = 0;
    int hit_number_1 = 0;
    int hit_number_2 = 0;
    int hit_number_3 = 0;
    int hit_number_4 = 0;
    int hit_number_5 = 0;
    int hit_number_6 = 0;
    int hit_number_7 = 0;
    int hit_number_8 = 0;
    int hit_number_9 = 0;
    int hit_number_10 = 0;
    int hit_number_11 = 0;
    int hit_number_12= 0;
    int hit_number_13 = 0;
    int hit_number_14 = 0;
    int hit_number_15 = 0;
    int hit_number_16 = 0;
    FILE *pFile;
    pFile = fopen("Result_diffusion_NMNT128.csv", "w+");
    fprintf(pFile,"Iteration_number, Changed_bit\n");

    for(int iteration_number = 1; iteration_number <= total_iterations; iteration_number++){
        hit_number = 0;
        printf("Iteration number = %d\n", iteration_number);
        for(int index = 0; index < message_size; index++)
        {
            pInput_message[index] = char1[rand() % message_size];
            //pInput_message[index] = message[index];
        }
//pInput_message = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
        //printf("message = %s\n", pInput_message);
        //pInput_message = "H:6XreOhe,,>0488W-lVEn6Jbugza23b>~Bzyclj3Q-I0~hJ";
        char *pOutput_message_binary_original =  malloc(sizeof(pInput_message) * N);
        char *pOutput_message_binary_modified =  malloc(sizeof(pInput_message) * N);
// STEP # 2: CONVERTED INTO BINARY STREAM
        pOutput_message_binary_original = string_to_binary(pInput_message);
        pOutput_message_binary_modified = string_to_binary(pInput_message);
        // printf("*pOutput_message_binary_original = %s\n", pOutput_message_binary_original);
        // printf("*pOutput_message_binary_modified = %s\n", pOutput_message_binary_modified);
        unsigned int binary_message_length_original = strlen(pOutput_message_binary_original) - 8;
        unsigned int binary_message_length_modified = strlen(pOutput_message_binary_modified) - 8;
        // printf("binary_message_length_original = %d\n", binary_message_length_original);
        // printf("binary_message_length_modified = %d\n", binary_message_length_modified);
        int message_bit_index = rand() % binary_message_length_modified-1;
        // printf("Binary message before change [%d] = %c\n", message_bit_index, pOutput_message_binary_modified[message_bit_index]);
// Changing a random bit in the input
         pOutput_message_binary_modified[message_bit_index] = pOutput_message_binary_modified[message_bit_index] == '1' ? '0' : '1';
        // pOutput_message_binary_modified[message_bit_index] = pOutput_message_binary_modified[message_bit_index];
        // printf("Message bit index = %d\n", message_bit_index);
        // printf("Binary message after change [%d] = %c\n", message_bit_index, pOutput_message_binary_modified[message_bit_index]);
        // printf("Message in binary = %s\n", pOutput_message_binary_modified);
        // printf("Number of binary bits = %d\n", binary_message_length_modified);
// STEP # 3: BINARY STREAM DIVIDED INTO BLOCKS BY p
        //Divide input message into blocks
        int number_of_blocks = binary_message_length_original/p;
        int reminder_of_last_block = binary_message_length_original % p;
        if( reminder_of_last_block != 0){
            int number_of_padding_required = p - (reminder_of_last_block);
            // printf("Number of padding required = %d\n", number_of_padding_required);
            number_of_blocks = number_of_blocks + 1;
            // printf("Number of blocks: %d\n", number_of_blocks);
        }
        int block_size = 0;
        // int IV[16] = {43, 49, 65, 5, 57, 107, 2, 13, 47, 109, 31, 29, 5, 51, 53, 7};
        // Dividing into blocks
        char *input_block_original = malloc(sizeof(char)*p);
        char *input_block_modified = malloc(sizeof(char) * p);
        input_block_in_elements_original = malloc(number_of_blocks * sizeof(int));
        input_block_in_elements_modified = malloc(number_of_blocks * sizeof(int));
        char * probability_output_bit = malloc(sizeof(char) * 128);
        int input_binary_in_decimal_original;
        int input_binary_in_decimal_modified;
        for(int i = 0; i < number_of_blocks; i++) {
            //printf("Block number: %d\n", i + 1);
            int binary_to_decimal_value_original = 0;
            int binary_to_decimal_value_modified = 0;
            int input_block_in_decimal_original = 0;
            int input_block_in_decimal_modified = 0;
            int binary_position = p - 1;
            if(i != number_of_blocks-1){ // NOT LAST BLOCK
                for (int j = 0; j < p; j++) {
                    input_block_original[j] = pOutput_message_binary_original[j + block_size];
                    input_block_modified[j] = pOutput_message_binary_modified[j + block_size];
                    // printf("input_block_original[%d] = %c\n", j, input_block_original[j]);
                    // printf("input_block_modified[%d] = %c\n", j, input_block_modified[j]);
// STEP 4: EACH BINARY BLOCK IS CONVERTED INTO DECIMAL ELEMENT
                    input_binary_in_decimal_original = (input_block_original[j] == '0') ?  0 : 1;
                    input_binary_in_decimal_modified = (input_block_modified[j] == '0') ?  0 : 1;
                    // printf("input_binary_in_decimal = %d\n", input_binary_in_decimal);
                    binary_to_decimal_value_original = (1 << (binary_position)) * input_binary_in_decimal_original;
                    binary_to_decimal_value_modified = (1 << (binary_position)) * input_binary_in_decimal_modified;
                    input_block_in_decimal_original = input_block_in_decimal_original + binary_to_decimal_value_original;
                    input_block_in_decimal_modified = input_block_in_decimal_modified + binary_to_decimal_value_modified;
                    binary_position--;
                }
            }else {
                for (int j = 0; j < p; j++) {
                    if(j < reminder_of_last_block){
                        input_block_original[j] = pOutput_message_binary_original[j + block_size];
                        input_block_modified[j] = pOutput_message_binary_modified[j + block_size];
                    }else{
                        input_block_original[j] = '0';
                        input_block_modified[j] = '0';
                    }
                    // printf("input_block_original[%d] = %c\n", j, input_block_original[j]);
                    // printf("input_block_modified[%d] = %c\n", j, input_block_modified[j]);
// STEP 4: EACH BINARY BLOCK IS CONVERTED INTO DECIMAL ELEMENT
                    input_binary_in_decimal_original = (input_block_original[j] == '0') ?  0 : 1;
                    input_binary_in_decimal_modified = (input_block_modified[j] == '0') ?  0 : 1;
                    // printf("input_binary_in_decimal = %d\n", input_binary_in_decimal);
                    binary_to_decimal_value_original = (1 << (binary_position)) * input_binary_in_decimal_original;
                    binary_to_decimal_value_modified = (1 << (binary_position)) * input_binary_in_decimal_modified;
                    input_block_in_decimal_original = input_block_in_decimal_original + binary_to_decimal_value_original;
                    input_block_in_decimal_modified = input_block_in_decimal_modified + binary_to_decimal_value_modified;
                    binary_position--;
                }
            }
            input_block_in_elements_original[i] = input_block_in_decimal_original;
            input_block_in_elements_modified[i] = input_block_in_decimal_modified;
            //printf("input_block_in_elements_original[%d]: %d\n",i, input_block_in_elements_original[i]);
            //printf("input_block_in_elements_modified[%d]: %d\n",i, input_block_in_elements_modified[i]);
            // printf("Binary to decimal value: %d\n",input_block_in_decimal);
            block_size = block_size + p;
        }
        // for(int i = 0;i < N;i++){
        //      printf("input_block_in_elements[%d]: %d\n",i, input_block_in_elements[i]);
        // }
        // printf("Number of blocks = %d\n", number_of_blocks);
// STEP # 5: DIVIDE THE DECIMAL ELEMENTS INTO BLOCKS OF N SIZE
        int number_of_element_blocks = number_of_blocks/N;
        int number_of_padding_required;
        if((number_of_blocks % N) > 0){
            number_of_padding_required = N - (number_of_blocks % N);
            // printf("Number padding required = %d\n", number_of_padding_required);
        }
        number_of_element_blocks = (number_of_element_blocks == 0 ) ? 1: ((number_of_blocks % N) == 0) ? number_of_element_blocks : (number_of_element_blocks + 1);
        // printf("number_of_element_blocks = %d\n", number_of_element_blocks);
        int element_block_size = 0;
        int* each_input_block_in_elements_original = malloc(sizeof (int)*N);
        int* each_input_block_in_elements_modified = malloc(sizeof (int)*N);
        int* hash_input_original = malloc(sizeof(int) * N);
        int* hash_input_modified = malloc(sizeof(int) * N);
        int* hash_output_original = malloc(sizeof(int) * N);
        int* hash_output_shifting = malloc(sizeof(int) * N);
        int* initial_vector = malloc(sizeof(int) * N);
        int* hash_intermediate_block_original = malloc(sizeof(int) * N);
        int* hash_intermediate_block_modified = malloc(sizeof(int) * N);
        char* hash_output_original_char = malloc(sizeof(int) * 128);
        char* hash_output_modified_char = malloc(sizeof(int) * 128);

        // Assign IV
        for(int i = 0; i < N; i++) {
            hash_output_original[i] = IV[i];
            hash_output_modified[i] = IV[i];
//             printf(" hash_output_original[%d] = %d\n", i, hash_output_original[i]);
//             printf(" hash_output_modified[%d] = %d\n", i, hash_output_modified[i]);
        }

        for(int hash_block_number = 0; hash_block_number < number_of_element_blocks; hash_block_number++){
            printf("Block number = %d\n",hash_block_number+1 );
            if (hash_block_number != number_of_element_blocks-1){
                for (int j = 0; j < N; j++){
                    each_input_block_in_elements_original[j] = input_block_in_elements_original[j + element_block_size];
                    each_input_block_in_elements_modified[j] = input_block_in_elements_modified[j + element_block_size];
                    //printf("each_input_block_in_elements_original[%d]= %d\n",j, each_input_block_in_elements_original[j] );
                    //printf("each_input_block_in_elements_modified[%d]= %d\n",j, each_input_block_in_elements_modified[j] );
                }
            }else{
                // Add padding
                for (int j = 0; j < N; j++){
                    if(j < N-number_of_padding_required){
                        each_input_block_in_elements_original[j] = input_block_in_elements_original[j + element_block_size];
                        each_input_block_in_elements_modified[j] = input_block_in_elements_modified[j + element_block_size];
                    }else {
                        each_input_block_in_elements_original[j] = 32;
                        each_input_block_in_elements_modified[j] = 32;
                    }
                }
            }
//            for(int i = 0; i < N; i++){
//                printf("NMNT input block before shuffling[%d] = %d\n", i, each_input_block_in_elements_original[i]);
//            }

// Shuffling block **** before **** the transformation
//            each_input_block_in_elements_original = shuffling_array(each_input_block_in_elements_original);
//            each_input_block_in_elements_modified = shuffling_array(each_input_block_in_elements_modified);
//            for(int i = 0; i < N; i++){
//                printf("NMNT input original block after shuffling[%d] = %d\n", i, each_input_block_in_elements_original[i]);
//                printf("NMNT input modified after shuffling[%d] = %d\n", i, each_input_block_in_elements_modified[i]);
//            }
// STEP # 6: APPLY THE TRANSFORM OPERATION: GNMNT Block
//            hash_input_original = transform_block(each_input_block_in_elements_original, Mp);
//            hash_input_modified = transform_block(each_input_block_in_elements_modified, Mp);
//
//            // Shuffling block **** after **** the transformation
//            //hash_input_original = shuffling_array(hash_input_original);
//            //hash_input_modified = shuffling_array(hash_input_modified);
//
//            for(int i = 0; i < N; i++){
//                //printf("hash_input_original_before_shifting[%d]= %d\n",i,  hash_input_original[i]);
//            }
//
//            //Shifting operations on the input of the NMNT elements
//           hash_input_original = shifted_array( hash_input_original,1);
//            hash_input_modified = shifted_array( hash_input_modified,1);
//
//            for(int i = 0; i < N; i++){
//                //printf("hash_input_original_after_shifting[%d]= %d\n",i,   hash_input_original[i]);
//            }
//            //Printing output of the GNMNT transformation
//            for(int i = 0; i < N; i++){
//                 printf("hash_input_original[%d]= %d\n",i,  hash_input_original[i]);
//                 printf("hash_input_modified[%d]= %d\n",i,  hash_input_modified[i]);
//            }
//
//            for(int i = 0; i < N; i++){
//                printf("hash_output_original_input[%d]= %d\n",i,  hash_output_original[i]);
//                printf("hash_output_modified_input[%d]= %d\n",i,  hash_output_modified[i]);
//            }
//
//            hash_output_original = xor_operation(hash_output_original, hash_input_original);
//            hash_output_modified = xor_operation(hash_output_modified,  hash_input_modified);

// STEP # 6: APPLY THE TRANSFORM OPERATION: GNMNT Block
#if 0
            //NMNT OPERATION
            hash_input_original = calculate_NMNT(each_input_block_in_elements_original, N, Mp);
            hash_input_modified = calculate_NMNT(each_input_block_in_elements_modified, N, Mp);
#endif

#if 0
            //ONMNT OPERATION
            hash_input_original = calculate_ONMNT(each_input_block_in_elements_original, N, Mp);
            hash_input_modified = calculate_ONMNT(each_input_block_in_elements_modified, N, Mp);
#endif

#if 0
            //O2NMNT OPERATION
            hash_input_original = calculate_O2NMNT(each_input_block_in_elements_original, N, Mp);
            hash_input_modified = calculate_O2NMNT(each_input_block_in_elements_modified, N, Mp);
#endif

#if 1
            //FNT OPERATION
            char** test_each_input_block_in_elements_original;
            char** test_each_input_block_in_elements_modified;
            test_each_input_block_in_elements_original = (char**) memory_allocation_for_2D_array_char(N,N);
            test_each_input_block_in_elements_modified = (char**) memory_allocation_for_2D_array_char(N,N);

            for(int index = 0; index < N; index++){
                sprintf(test_each_input_block_in_elements_original[index],"%d", each_input_block_in_elements_original[index]);
                sprintf(test_each_input_block_in_elements_modified[index],"%d", each_input_block_in_elements_modified[index]);
            }

            //TEST: PRINTING INPUT BLOCK OF FNT AFTER CONVERTING FROM INTEGER TO CHARACTERS
            for(int i = 0; i < N ; i++){
                for(int j = 0; j < 3; j++){
//                    printf("each_input_block_in_elements_original[%d][%d] = %c\n", i, j, test_each_input_block_in_elements_original[i][j]);
//                    printf("each_input_block_in_elements_modified[%d][%d] = %c\n", i, j, test_each_input_block_in_elements_modified[i][j]);
                }
//            printf("\n");
            }

            //FNT OPERATION
            if(hash_input_original == NULL){
                printf("Memory allocation error for Hash input original\n");
                exit(1);
            }else{
                hash_input_original = calculate_FNT(test_each_input_block_in_elements_original, 3);
            }

            if(hash_output_modified == NULL){
                printf("Memory allocation error for Hash input modified\n");
                exit(1);
            }else{
                hash_input_modified = calculate_FNT(test_each_input_block_in_elements_modified, 3);
            }

            //SUCCESSFULLY FREED 4 ALLOCATIONS
            free_2D_array_char(test_each_input_block_in_elements_original, N);
            free_2D_array_char(test_each_input_block_in_elements_modified, N);
#endif
            for(int i = 0; i < N; i++){
//                printf("hash_output_original_input[%d]= %d\n",i,  hash_output_original[i]);
//                printf("hash_input_original[%d]= %d\n",i,  hash_input_original[i]);
//                printf("hash_input_modified[%d]= %d\n",i,  hash_input_modified[i]);
            }
//
//            for(int i = 0; i < N; i++){
//                printf("hash_input_modified[%d]= %d\n",i,  hash_input_modified[i]);
//                printf("hash_output_modified_input[%d]= %d\n",i,  hash_output_modified[i]);
//            }

            //USING NEW HASH FUNCTION
//            int *calculate_NMNT(int *plaintext, int N, int M_p);

            //Shifting operations on the input of the NMNT elements
//           hash_input_original = shifted_array( hash_input_original,1);
//           hash_input_modified = shifted_array( hash_input_modified,1);
            if(hash_output_original == NULL){
                printf("Memory allocation error for hash output original\n");
                exit(1);
            }else{
                hash_output_original = xor_operation(hash_output_original, hash_input_original);
            }

            if(hash_output_modified == NULL){
                printf("Memory allocation error for hash input modified");
                exit(1);
            }else {
                hash_output_modified = xor_operation(hash_output_modified,  hash_input_modified);
            }
            for(int i = 0; i < N; i++){
                hash_input_original[i] = hash_output_original[i];
                hash_input_modified[i] = hash_output_modified[i];
            }
// STEP 7: APPLY KEY(IV) ON THE FIRST BLOCK AND APPLY XOR BETWEEN INTERMEDIATE BLOCKS

            for(int i = 0; i < N; i++){
//                printf("hash_output_original[%d]= %d\n",i,  hash_output_original[i]);
//                printf("hash_output_modified[%d]= %d\n",i,  hash_output_modified[i]);
            }

            for(int i = 0; i < N; i++){
                hash_output_original_char[i] = (char)hash_output_original[i];
                hash_output_modified_char[i] = (char)hash_output_modified[i];
//                printf("hash_output_original_char_[%d] = %d\n",i, hash_output_original[i]);
//                printf("hash_output_modified_char[%d] = %d\n",i, hash_output_modified[i]);
            }

            element_block_size = element_block_size + N;
        }



        for(int i = 0; i < N; i++){
            //printf("hash_output_original[%d] = %X\n",i, hash_output_original[i]);
            //printf("hash_output_modified[%d] = %X\n",i, hash_output_modified[i]);
            hit_number = hash_output_original[i] == hash_output_modified[i] ? hit_number + 1: hit_number;
        }


        // printf("hit_number = %d\n", hit_number);
        hash_output_binary_original = string_to_binary(hash_output_original_char);
        hash_output_binary_modified = string_to_binary(hash_output_modified_char);

        int number_of_changed_bit = 0;
        for(int i = 0; i < 128; i++){
           // printf("hash_output_binary_original[%d] = %c\n", i,hash_output_binary_original[i]);
           //printf("hash_output_binary_modified[%d] = %c\n", i,hash_output_binary_modified[i]);
            if(hash_output_binary_original[i] == hash_output_binary_modified[i]){
                number_of_changed_bit = number_of_changed_bit;
            }else {
                number_of_changed_bit++;
            }
        }

        printf("Number of changed bit = %d\n", number_of_changed_bit);
//        fprintf(pFile, "%d, %d\n", iteration_number, number_of_changed_bit);
        fprintf(pFile, "%d\n", number_of_changed_bit);

        // printf("hit_number_other = %d\n", hit_number_others);
//Uniform Distribution
        int block_adder = 0;
        int hexadecimal_block;
        for (int i = 0; i < strlen(hash_output_binary_original) / 4; i++){
            //printf("Hexadecimal block number = %d\n", i+1);
            for (int j = 0; j < 4; j++) {
                pBinary_outout_hex[j] = hash_output_binary_original[j + block_adder];
            }
            //printf("binary_output_binary = %s\n", pBinary_output_hex);
            block_adder = block_adder + 4;
        }

        if(hit_number == 16){
            //printf("Iterations with 16 character matched = %d\n", iteration_number);
        }
        switch (hit_number) {
            case 0:
                hit_number_0++;
                break;
            case 1:
                hit_number_1++;
                break;
            case 2:
                hit_number_2++;
                break;
            case 3:
                hit_number_3++;
                break;
            case 4:
                hit_number_4++;
                break;
            case 5:
                hit_number_5++;
                break;
            case 6:
                hit_number_6++;
                break;
            case 7:
                hit_number_7++;
                break;
            case 8:
                hit_number_8++;
                break;
            case 9:
                hit_number_9++;
                break;
            case 10:
                hit_number_10++;
                break;
            case 11:
                hit_number_11++;
                break;
            case 12:
                hit_number_12++;
                break;
            case 13:
                hit_number_13++;
                break;
            case 14:
                hit_number_14++;
                break;
            case 15:
                hit_number_15++;
                break;
            default:
                hit_number_16++;
                break;
        }
        total_changed_bit =  total_changed_bit + number_of_changed_bit;
    }
    double average_changed_bit = (total_changed_bit/total_iterations) ;
    double diffusion_percentage = (average_changed_bit/128) * 100;
   // printf("total changed bits = %d\n", total_changed_bit);
//    printf("Diffusion percentage = %f\n", diffusion_percentage);

//    printf("hit_number_0 = %d\n", hit_number_0);
//    printf("hit_number_1 = %d\n", hit_number_1);
//    printf("hit_number_2 = %d\n", hit_number_2);
//    printf("hit_number_3 = %d\n", hit_number_3);
//    printf("hit_number_4 = %d\n", hit_number_4);
//    printf("hit_number_5 = %d\n", hit_number_5);
//    printf("hit_number_6 = %d\n", hit_number_6);
//    printf("hit_number_7 = %d\n", hit_number_7);
//    printf("hit_number_8 = %d\n", hit_number_8);
//    printf("hit_number_9 = %d\n", hit_number_9);
//    printf("hit_number_10 = %d\n", hit_number_10);
//    printf("hit_number_11 = %d\n", hit_number_11);
//    printf("hit_number_12= %d\n", hit_number_12);
//    printf("hit_number_13 = %d\n", hit_number_13);
//    printf("hit_number_14= %d\n", hit_number_14);
//    printf("hit_number_15 = %d\n", hit_number_15);
//    printf("hit_number_16= %d\n", hit_number_16);
    fclose(pFile);

//    free(input_block_in_elements_original);
//    free(input_block_in_elements_modified);
//    free(transfrom_block);
//    free(string_to_binary);
//    free(shifted_array);
//    free(hash_output_modified);
//    free(hash_output_binary_original);
//    free(hash_output_binary_temp);
//    free(hash_output_binary_modified);
//    free(pOutputbit_probability);
//    free(pCounts);
//    free(pBinary_outout_hex);
//    free(pInput_message);
//    free(changed_bits);

    return 0;
}
char* string_to_binary(char* s) {
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}
int binary_to_hexadecimal(long long int binary_value){
    long long int hexadecimal_value = 0;
    char i = 1;
    char reminder;
    while(binary_value != 0){ //17
        reminder = binary_value % 10;  // 7
        hexadecimal_value = hexadecimal_value + reminder * i; //0 + 7
        i = i * 2;
        binary_value = binary_value/10;
    }
    return hexadecimal_value;
}
int* shifted_array(int* input, int shift_amount){
    int temp;
    for(int i = 0; i < shift_amount; i++){
        temp = input[0];
    }
    for(char index = 0; index < N - shift_amount; index++){
        input[index] = input[index + shift_amount];
    }
    input[N-1] = temp;
    return input;
}

int* transfrom_block(int* input_block, int Mp) {
    int* transformed_output = (int*) malloc(sizeof(int) * N);
    int sum = 0;
    int result = 0;

    if(transformed_output == NULL){
        printf("Memory allocation error for transformed_output\n");
        exit(1);
    }else{
        for (int row = 0; row < N; row++) {
            signed long long result_original = 0;
            signed long long result_modified = 0;
            signed long long sum_original = 0;
            signed long long sum_modified = 0;
            // int encryptedBlock[c] = mod(result, Mp);
            transformed_output[row] = result % Mp;
        }
    }
    return transformed_output;
}

int* xor_operation(int* hash_input_1, int* hash_input_2) {
    int *hash_output = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
//        printf("hash_input_1[%d] = %d\n", i, hash_input_1[i]);
//        printf("hash_input_2[%d] = %d\n", i, hash_input_2[i]);
        hash_output[i] = hash_input_1[i] ^ hash_input_2[i];
        //hash_output[i] = (char) hash_output[i];
        //printf("hash_output[%d] = %d\n",i, hash_output[i]);
        if(hash_output[i] == 0){
            hash_output[i] = 7; // 0 value is mapped to 7 to avoid null value
        }
    }
    return hash_output;
}

int* add_elements(int* first_element, int* second_element){
    int* output = malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++){
        output[i] =  first_element[i] + second_element[i];
    }
    return output;
}
int* shuffling_array(int* input){
    int temp;
    srand(time(NULL));

    for(int index = 0; index < N; index++){
        int new_index = (rand() % 16)-2;
        new_index = 16;  // 5
        temp = input[new_index]; // temp = input[5] // 60 //
        input[new_index] = input[index]; // input[5] = 10
        input[index] = temp;//input[0] = 60
    }
//    for(int index = 0; index < N; index++){
//        int new_index = (rand() % 16) - 2 ; //new_index = 5  // 5
//        //int new_index = 17; //new_index = 5  // 5
//        //printf("new_index = %d\n", new_index);
//        temp = input[new_index]; // temp = input[5] // 60 //
//        input[new_index] = input[index]; // input[5] = 10
//        input[index] = temp;//input[0] = 60
//    }

    return input;
}

//FUNCTION DECLARATIONS

//------------------------ FUNCTION DECLARATIONS -----------------------------------------------------------------------
//THIS FUNCTION CONVERTS STRING OR CHARACTER ARRAY INTO BINARY STRINGS
//char* string_to_binary(char* s) {
//    if(s == NULL){
//        return 0; /* no input string */
//    }
//    size_t len = strlen(s)-1; //Length of the string
//    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
//    binary[0] = '\0';
//
//    for(size_t i = 0; i < len; ++i) {
//        char ch = s[i];
//        for(int j = 7; j >= 0; --j){
//            if(ch & (1 << j)) {
//                strcat(binary,"1");
//            } else {
//                strcat(binary,"0");
//            }
//        }
//    }
//    return binary;
//}

int *convert_from_integer_to_binary(int *array, int array_size){
    int *output = (int *)calloc(8 * array_size, sizeof(int));
    int bit_offset = 0;

    if(output == NULL){
        printf("Memory allocation error for output\n");
        exit(1);
    }else{
        for(int i = 0; i < array_size; i++){
            for(int j = 0; j < 8; j++){
//                printf("array[%d] = %d\n", i, array[i]);
                output[j+bit_offset] = ((array[i] >> j) % 2) > 0 ? 1 : 0;
//                printf("output[%d] = %d\n",j+bit_offset,output[j+bit_offset]) ;
            }
            bit_offset = bit_offset + 8;
        }
    }
    return output;
}

int *convert_from_char_to_int(char *char_array, int array_size){
    int i;
    int *int_array = (int*)calloc(array_size, sizeof(int));
    if(int_array == NULL){
        printf("Memory allocation error for int_array\n");
        exit(1);
    }else{
        for (i = 0; i < array_size; i++){
            int_array[i] = char_array[i] - '0';
            int_array[i] = char_array[i];
        }
    }
    return int_array;
}

//FUNCTION DECLARATION TO ALLOCATE MEMORY FOR 2D ARRAY
int** memory_allocation_for_2D_array_int(int row_numbers, int column_numbers){
    int **ptr_2D_array;
    ptr_2D_array = (int **) calloc(row_numbers, sizeof(int *));
    for(int i = 0; i < row_numbers; i++){
        ptr_2D_array[i] = (int *) calloc(column_numbers, sizeof(int));
    }
    return ptr_2D_array;
}

//FUNCTION DECLARATION OF FREE 2D ARRAY POINTER
void free_2D_array_int(int** array_2D, int x_length){
    size_t i;
    for(i = 0; i < x_length; i++){
        if(array_2D != NULL){
            free(array_2D[i]);
            array_2D[i] = NULL;
        }
    }
    free(array_2D);
}

//FUNCTION DECLARATION TO ALLOCATE MEMORY FOR 2D ARRAY
char** memory_allocation_for_2D_array_char(char row_numbers, int column_numbers){
    char **ptr_2D_array = (char **) calloc(row_numbers, sizeof(int *));
    for(int i = 0; i < row_numbers; i++){
        ptr_2D_array[i] = (char *) calloc(column_numbers, sizeof(int));
    }
    return ptr_2D_array;
}

//FUNCTION DECLARATION OF FREE 2D ARRAY POINTER
void free_2D_array_char(char** array_2D, int x_length){
    size_t i;
    for(i = 0; i < x_length; i++){
        if(array_2D != NULL){
            free(array_2D[i]);
            array_2D[i] = NULL;
        }
    }
    free(array_2D);
}


int *calculate_NMNT(int *plaintext, int transform_length, int M_p) {
    int *output = (int *) calloc(transform_length, sizeof(int));
    int **ptr_NMNT = memory_allocation_for_2D_array_int(N,N);
    if(transform_length == 8) {
        int NMNT[8][8] = {
                {1, 1,   1,   1,   1,   1,   1,   1},
                {1, 111, 1,   0,   126, 16,  126, 0},
                {1, 1,   126, 126, 1,   1,   126, 126},
                {1, 0,   126, 111, 126, 0,   1,   16},
                {1, 126, 1,   126, 1,   126, 1,   126},
                {1, 16,  1,   0,   126, 111, 126, 0},
                {1, 126, 126, 1,   1,   126, 126, 1},
                {1, 0,   126, 16,  126, 0,   1,   111}
        };
        for(int i = 0; i < transform_length; i++){
            for(int j = 0; j < transform_length; j++){
                ptr_NMNT[i][j] = NMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
            }
        }
    }else if(transform_length == 16) {
//ONMNT matrix for p = 7 and N = 16
        int NMNT[16][16] = {
                {1, 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1},
                {1, 82,  111, 82,  1,   3,   0,   124, 126, 45,  16,  45,  126, 124, 0,   3},
                {1, 111, 1,   0,   126, 16,  126, 0,   1,   111, 1,   0,   126, 16,  126, 0},
                {1, 82,  0,   45,  126, 3,   111, 3,   126, 45,  0,   82,  1,   124, 16,  124},
                {1, 1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126},
                {1, 3,   16,  3,   1,   45,  0,   82,  126, 124, 111, 124, 126, 82,  0,   45},
                {1, 0,   126, 111, 126, 0,   1,   16,  1,   0,   126, 111, 126, 0,   1,   16},
                {1, 124, 0,   3,   126, 82,  16,  82,  126, 3,   0,   124, 1,   45,  111, 45},
                {1, 126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126},
                {1, 45,  111, 45,  1,   124, 0,   3,   126, 82,  16,  82,  126, 3,   0,   124},
                {1, 16,  1,   0,   126, 111, 126, 0,   1,   16,  1,   0,   126, 111, 126, 0},
                {1, 45,  0,   82,  126, 124, 111, 124, 126, 82,  0,   45,  1,   3,   16,  3},
                {1, 126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1},
                {1, 124, 16,  124, 1,   82,  0,   45,  126, 3,   111, 3,   126, 45,  0,   82},
                {1, 0,   126, 16,  126, 0,   1,   111, 1,   0,   126, 16,  126, 0,   1,   111},
                {1, 3,   0,   124, 126, 45,  16,  45,  126, 124, 0,   3,   1,   82,  111, 82}
        };
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_NMNT[i][j] = NMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_NMNT[i][j]);
            }
        }
    }

    if(output == NULL){
        printf("Memory allocation error\n");
        exit(1);
    }else{
        for (int row = 0; row < N; row++) {
            signed long long result = 0;
            signed long long sum = 0;
            for (int col = 0; col < N; col++) {
                sum = plaintext[col] * ptr_NMNT[row][col];
                result = result + sum;
            }
            output[row] = mod(result, M_p);
        }
    }
    free_2D_array_int(ptr_NMNT, N);
    return output;
}

//CALCULATING ONMNT
int *calculate_ONMNT(int *plaintext, int N, int M_p) {
    int *output = (int *) calloc(N, sizeof(int));
    int **ptr_ONMNT = memory_allocation_for_2D_array_int(N,N);

    //ONMNT matrix for p = 7 and N = 8
    if(N == 8) {
        int ONMNT[8][8] = {
                {1, 1, 1, 1, 1, 1, 1, 1},
                {72, 19, 19, 72, 5, 99, 28, 122},
                {82, 82, 3, 124, 45, 45, 124, 3},
                {19, 5, 122, 108, 28, 72, 72, 28},
                {111, 0, 16, 0, 111, 0, 16, 0},
                {19, 122, 122, 19, 28, 55, 72, 99},
                {82, 45, 3, 3, 45, 82, 124, 124},
                {72, 108, 19, 55, 5, 28, 28, 5}
        };
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_ONMNT[i][j] = ONMNT[i][j];
//                    printf("ptr_NMNT[%d][%d] = %d\n", i,j,ptr_ONMNT[i][j]);
            }
        }
    }else if(N == 16) {
        int ONMNT[16][16] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {72, 19, 19, 72, 5, 99, 28, 122, 55, 108, 108, 55, 122, 28, 99, 5},
                {82, 82, 3, 124, 45, 45, 124, 3, 82, 82, 3, 124, 45, 45, 124, 3},
                {19, 5, 122, 108, 28, 72, 72, 28, 108, 122, 5, 19, 99, 55, 55, 99},
                {111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0},
                {19, 122, 122, 19, 28, 55, 72, 99, 108, 5, 5, 108, 99, 72, 55, 28},
                {82, 45, 3, 3, 45, 82, 124, 124, 82, 45, 3, 3, 45, 82, 124, 124},
                {72, 108, 19, 55, 5, 28, 28, 5, 55, 19, 108, 72, 122, 99, 99, 122},
                {1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126},
                {5, 28, 28, 5, 55, 19, 108, 72, 122, 99, 99, 122, 72, 108, 19, 55},
                {3, 3, 45, 82, 124, 124, 82, 45, 3, 3, 45, 82, 124, 124, 82, 45},
                {99, 72, 55, 28, 19, 122, 122, 19, 28, 55, 72, 99, 108, 5, 5, 108},
                {0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16},
                {28, 72, 72, 28, 108, 122, 5, 19, 99, 55, 55, 99, 19, 5, 122, 108},
                {124, 3, 82, 82, 3, 124, 45, 45, 124, 3, 82, 82, 3, 124, 45, 45},
                {122, 28, 99, 5, 72, 19, 19, 72, 5, 99, 28, 122, 55, 108, 108, 55}
        };


        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_ONMNT[i][j] = ONMNT[i][j];
//                    printf("ptr_ONMNT[%d][%d] = %d\n", i,j,ptr_ONMNT[i][j]);
            }
        }
    }
    for (int row = 0; row < N; row++) {
        signed long long result = 0;
        signed long long sum = 0;
        for (int col = 0; col < N; col++) {
//        printf("plaintext[%d] = %d\n", row, plaintext[col]);
//                 printf("ptr_NMNT[%d][%d] = %d\n", row, col, ptr_NMNT[row][col]);
            sum = plaintext[col] * ptr_ONMNT[row][col];
            result = result + sum;
//                printf("result = %d\n", result);
        }
        output[row] = mod(result, M_p);
//        output[row] = result % 127;
    }
    free_2D_array_int(ptr_ONMNT, N);
    return output;
}

//CALCULATING ONMNT
int *calculate_O2NMNT(int *plaintext, int N, int M_p) {
    int *output = (int *) calloc(N, sizeof(int));
    int **ptr_O2NMNT = memory_allocation_for_2D_array_int(N,N);

    //ONMNT matrix for p = 7 and N = 8
    if(N == 8) {
        int O2NMNT[8][8] =
                {
                        {72, 19, 19, 72, 5, 99, 28, 122},
                        {19, 5, 122, 108, 28, 72, 72, 28},
                        {19, 122, 122, 19, 28, 55, 72, 99},
                        {72, 108, 19, 55, 5, 28, 28, 5},
                        {5, 28, 28, 5, 55, 19, 108, 72},
                        {99, 72, 55, 28, 19, 122, 122, 19},
                        {28, 72, 72, 28, 108, 122, 5, 19},
                        {122, 28, 99, 5, 72, 19, 19, 72}
                };
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_O2NMNT[i][j] = O2NMNT[i][j];
//                    printf("ptr_O2NMNT[%d][%d] = %d\n", i,j,ptr_O2NMNT[i][j]);
            }
        }

    }else if(N == 16) {
//O2NMNT matrix for p = 7 and N = 16
        int O2NMNT[16][16] = {
                {15, 56, 106, 105, 105, 106, 56, 15, 83, 26, 14, 36, 91, 113, 101, 44},
                {56, 105, 15, 14, 113, 112, 22, 71, 101, 36, 83, 106, 106, 83, 36, 101},
                {106, 15, 91, 71, 71, 91, 15, 106, 14, 44, 22, 101, 26, 105, 83, 113},
                {105, 14, 71, 44, 83, 56, 113, 22, 91, 106, 26, 112, 112, 26, 106, 91},
                {105, 113, 71, 83, 83, 71, 113, 105, 91, 21, 26, 15, 112, 101, 106, 36},
                {106, 112, 91, 56, 71, 36, 15, 21, 14, 83, 22, 26, 26, 22, 83, 14},
                {56, 22, 15, 113, 113, 15, 22, 56, 101, 91, 83, 21, 106, 44, 36, 26},
                {15, 71, 106, 22, 105, 21, 56, 112, 83, 101, 14, 91, 91, 14, 101, 83},
                {83, 101, 14, 91, 91, 14, 101, 83, 112, 56, 21, 105, 22, 106, 71, 15},
                {26, 36, 44, 106, 21, 83, 91, 101, 56, 22, 15, 113, 113, 15, 22, 56},
                {14, 83, 22, 26, 26, 22, 83, 14, 21, 15, 36, 71, 56, 91, 112, 106},
                {36, 106, 101, 112, 15, 26, 21, 91, 105, 113, 71, 83, 83, 71, 113, 105},
                {91, 106, 26, 112, 112, 26, 106, 91, 22, 113, 56, 83, 44, 71, 14, 105},
                {113, 83, 105, 26, 101, 22, 44, 14, 106, 15, 91, 71, 71, 91, 15, 106},
                {101, 36, 83, 106, 106, 83, 36, 101, 71, 22, 112, 113, 14, 15, 105, 56},
                {44, 101, 113, 91, 36, 14, 26, 83, 15, 56, 106, 105, 105, 106, 56, 15}
        };

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                ptr_O2NMNT[i][j] = O2NMNT[i][j];
//                    printf("ptr_O2NMNT[%d][%d] = %d\n", i,j,ptr_O2NMNT[i][j]);
            }
        }
    }

    if(output == NULL){
        printf("Memory allocation error for outout\n");
        exit(1);
    }else{
        for (int row = 0; row < N; row++) {
            signed long long result = 0;
            signed long long sum = 0;
            for (int col = 0; col < N; col++) {
//         printf("plaintext[%d] = %d\n", row, plaintext[col]);
//         printf("ptr_NMNT[%d][%d] = %d\n", row, col, ptr_NMNT[row][col]);
                sum = plaintext[col] * ptr_O2NMNT[row][col];
                result = result + sum;
//                printf("result = %d\n", result);
            }
            output[row] = mod(result, M_p);
//        output[row] = result % 127;
        }
    }

    free_2D_array_int(ptr_O2NMNT, N);

    return output;
}

int mod(int input, int Mp){
    int result = input % Mp;
    if (result < 0) {
        result += Mp;
    }
    return result;
}

//FNT FUNCTION DECLARATIONS
//Function of multiplying two arrays
Array_object multiply_two_arrays(int *a,int l1, char *plaintext){

    Array_object product_of_array;
    //        int a[100],b[100];
    int b[100];
    //        int ans[200] = {0};

    int i, j, tmp;
    int l2 = strlen(plaintext);

    for(i = l2-1,j = 0;i >= 0;i--,j++){
        b[j] = plaintext[i]-'0';
    }

    for(i = 0; i < l1; i++){
        //            printf("alpha_n_k[%d] = %d\n", i, a[i]);
    }

    for(i = 0; i < l2; i++){
        //            printf("x_n[%d] = %d\n", i, b[i]);
    }
    int* ans = (int*) calloc((l1 + l2)+1, sizeof (int));

    if(ans == NULL){
        printf("Memory allocation error for ans\n");
        exit(1);
    }else{
        for(i = 0;i < l2;i++){
            for(j = 0;j < l1;j++){
                ans[i+j] += b[i]*a[j];
            }
        }

        for(i = 0; i < l1+l2; i++){
            tmp = ans[i]/10;
            ans[i] = ans[i]%10;
            ans[i+1] = ans[i+1] + tmp;
        }

        for(i = l1+l2; i>= 0;i--){
            if(ans[i] > 0){
                break;
            }
        }
    }
    product_of_array.array = ans;
    product_of_array.array_size = l1+l2+1;

//    free(ans);
//    ans = NULL;
    return product_of_array;
}

// This function multiplies x with the number represented by res[].
// res_size is size of res[] or
// number of digits in the number
// represented by res[].
// This function uses simple school mathematics for multiplication.
// This function may value of res_size and returns the new value of res_size
int multiply(int x, int res[], int res_size){
    // Initialize carry
    int carry = 0;

    // One by one multiply n with
    // individual digits of res[]
    for (int i = 0; i < res_size; i++){
        int prod = res[i] * x + carry;

        // Store last digit of 'prod' in res[]
        res[i] = prod % 10;

        // Put rest in carry
        carry = prod / 10;
    }

    // Put carry in res and increase result size
    while (carry){
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}

//FUNCTION TO CALCULATE POWER OF A NUMBER x
Array_object power(int x, int n) {
    Array_object array_input;
    array_input.array = (int *) calloc(MAX, sizeof(int));
    array_input.array_size = 0;
    int *res = (int *) calloc(MAX, sizeof(int));
    int res_size = 0;
    int temp = x;

    // Initialize result
    while (temp != 0) {
        res[res_size++] = temp % 10;
        temp = temp / 10;
    }

    // printing value "1" for power = 0
    if (n == 0) {
        res[0] = 1;
    }
    // Multiply x n times (x^n = x*x*x....n times)
    // The loop start from 2 as i = 2, it means x^2 = x * x
    // i = 0: x^0 = 1
    // i = 1: x ^ 1 = x

    for (int i = 2; i <= n; i++) {
        res_size = multiply(x, res, res_size);
    }

    array_input.array = res;
    array_input.array_size = res_size;

//    free(res);
//    res = NULL;
    return array_input;
}
//FUNCTION DECLARATION TO REVERSE THE ARRAY
int* reverse_array(int *array, int array_size){
    int *temp_array = (int *) calloc(array_size, sizeof(int));

    if(temp_array == NULL){
        printf("Memory allocation error\n");
        exit(1);
    }else{
        for(int  i = 0; i < array_size; i++){
            temp_array[array_size-1-i] = array[i];
        }
        for(int  i = 0; i < array_size; i++){
            array[i] = temp_array[i];
        }
    }

//    free(temp_array);
//    temp_array = NULL;
    return array;
}

//FUNCTION DECLARATION TO ADD TWO DYNAMIC ARRAYS
Array_object add_two_arrays(int *array_1, int array_1_size, int *array_2, int array_2_size){
    int carry = 0;
    int temp_sum = 0;
    int sum_size;
    int index;
    int *sum = (int *) calloc(1000, sizeof(int));
    Array_object result;
    if(array_1_size <= array_2_size){
        //ADDING TWO ARRAYS WHEN SIZE OF FIRST ARRAY IS EQUAL OR SMALLER THAN SECOND ARRAY
        array_1 = reverse_array(array_1, array_1_size);
        array_2 = reverse_array(array_2, array_2_size);

        for(index = 0; index < array_1_size; index++){
            temp_sum = ((array_1[index] + array_2[index]) + carry);
            //            printf("%d + %d + %d = %d\n", array_1[index], array_2[index], carry, temp_sum);
            sum[index] = temp_sum % 10;
            //            printf("sum[%d] = %d\n", index, sum[index]);
            carry = (temp_sum >= 10)? 1:0;
            //            printf("carry = %d\n", carry);
        }

        for(index = array_1_size; index < array_2_size; index++){
            temp_sum = (array_2[index] + carry);
            //            printf("temp_sum = %d\n", temp_sum);
            sum[index] = temp_sum % 10;
            //            printf("sum[%d] = %d\n", index, sum[index]);
            carry = (temp_sum >= 10)? 1:0;
        }

        if(carry){
            sum[index] = carry;
            //            printf("sum[%d] = %d\n", index, sum[index]);
            result.array_size = index + 1;
        } else{
            result.array_size = index;
        }

    }else if(array_1_size > array_2_size){
        //ADDING TWO ARRAYS WHEN SIZE OF FIRST ARRAY IS SMALLER THAN SECOND ARRAY
        //        printf("Condition #2: array_1_size > array_2_size\n");//
        array_1 = reverse_array(array_1, array_1_size);
        array_2 = reverse_array(array_2, array_2_size);

        for(index = 0; index < array_2_size; index++){
            temp_sum = ((array_1[index] + array_2[index]) + carry);
            sum[index] = temp_sum % 10;
            carry = (temp_sum >= 10)? 1:0;
        }

        for(index = array_2_size; index < array_1_size; index++){ //i = 1, 2
            temp_sum = (array_1[index] + carry);
            sum[index] = temp_sum % 10;
            carry = (temp_sum >= 10)? 1:0;
        }

        if(carry){
            //            printf("carry = %d\n", carry);
            sum[index] = carry;
            //            printf("sum[%d] = %d\n", index, sum[index]);
            result.array_size = index + 1;
        } else{
            result.array_size = index;
        }

    }

//    free(array_1);
//    array_1 = NULL;
//
//    free(array_2);
//    array_2 = NULL;
    for(int i = 0; i < result.array_size; i++){
        //        printf("sum[%d] = %d\n", i, sum[i]);
    }
    result.array = reverse_array(sum, result.array_size);
    result.array = sum;
//    free(sum);
//    sum = NULL;
    return result;
}

//FUNCTION DECLARATION OF CALCULATING MOD Ft
int calculate_module(int *X_k, int array_size, int F_t){
    long long int temp = 0;
    for(int i = 0; i < array_size; i++){
        temp = (10 * temp) + X_k[i];
        //printf("%d = 10 * %d + %d\n", temp, temp, X_k[i]);
        temp %= F_t;
    }
    return  temp;
}

Array_object divide_arrays(int *dividend, int dividend_size, int divisor){
    Array_object result_array;
    int *result = (int *)calloc(dividend_size, sizeof(int));
    int index = 0;
    for(int i = 0; i < dividend_size; i++){
        result[index] = dividend[i]/divisor;
        dividend[i+1] = dividend[i+1] + ((dividend[i] % divisor) * 10);
        index++;
    }
    result_array.array_size = index;
    result_array.array = result;

//    free(result);
//    result = NULL;
    return result_array;
}

int* calculate_FNT(char **plaintext, int t){
    int F_t = (1 << (1 << t)) + 1;// Ft = 2^(2^t)
    int *X_k = (int *) calloc(N, sizeof(int));
    //    printf("F_t = %d\n", F_t);
//    int *alpha_n_k;
//    int *temp_X;
    int temp_X_size;
    int alpha = 4;

    Array_object sum_result;
    int alpha_nk_size;
    int product_size;
    Array_object output_from_function;
    Array_object output_of_product;
    Array_object temp_sum;
    //---------------------

    if(X_k == NULL){
        printf("Memory allocation error for X_k\n");
        exit(1);
    }else{
        for (int k = 0; k < N; k++) {
            //        printf("k = %d\n", k);
            //ASSIGNMENT OF INITIAL VALUES FOR temp_sum FOR ADDING TWO ARRAYS
            temp_sum.array_size = 2;
            temp_sum.array = (int *) calloc(temp_sum.array_size, sizeof(int));

            if(temp_sum.array == NULL){
                printf("memory allocation of temp_sum.array is not possible\n");
                exit(-1);
            }else{
                for (int i = 0; i < temp_sum.array_size; i++) {
                    temp_sum.array[i] = 0;
                }
            }

            for (int n = 0; n < N; n++) {
                //CALCULATION OF alpha_n_k
                output_from_function = power(alpha, n * k);
                alpha_nk_size = output_from_function.array_size;
                int *alpha_n_k = (int *) calloc(alpha_nk_size, sizeof(int));

                if(alpha_n_k == NULL){
                    printf("Memory allocation error for alpha_n_k\n");
                    exit(1);
                }else {
                    alpha_n_k = output_from_function.array;
                    free(output_from_function.array);
                    output_from_function.array = NULL;
                }

                //CALCULATE THE MULTIPLICATION OF EACH PRODUCT TERM FOR X(k)]
                output_of_product = multiply_two_arrays(alpha_n_k, alpha_nk_size, plaintext[n]);

                temp_X_size = output_of_product.array_size;
                int* temp_X = (int *) calloc(temp_X_size, sizeof(int));

                if(temp_X == NULL){
                    printf("Memory allocation error for temp_X\n");
                    exit(1);
                } else{
                    temp_X = output_of_product.array;
                    //CALLING REVERSE FUNCTION TO REVERSE temp_X TO MATCH WITH PLAINTEXT ARRAY INDEXING e.g. MSB AT O ARRAY INDEX
                    temp_X = reverse_array(temp_X, temp_X_size);

//                    free(output_of_product.array);
//                    output_of_product.array = NULL;
                }

                //            printf("temp_X_size = %d\n", temp_X_size);
                for (int i = 0; i < temp_X_size; i++) {
                    //                printf("temp_X[%d] = %d\n", i, temp_X[i]);
                }

                //CALLING FUNCTION TO ADD TWO DYNAMIC ARRAYS
                temp_sum = add_two_arrays(temp_X, temp_X_size, temp_sum.array, temp_sum.array_size);
                free(temp_X);
                temp_X = NULL;
                temp_sum.array = temp_sum.array;
                temp_sum.array_size = temp_sum.array_size;

//                free(alpha_n_k);
//                alpha_n_k = NULL;
            }


            //        struct Array_object i_temp_sum;
            //        i_temp_sum = divide_arrays(temp_sum.array, temp_sum.array_size, N);
            X_k[k] = calculate_module(temp_sum.array, temp_sum.array_size, F_t);
            //        X_k = calculate_module( i_temp_sum.array,  i_temp_sum.array_size, F_t);

            free(temp_sum.array);
            temp_sum.array = NULL;
        }

    }
    return X_k;
}

void convert_to_hex(int* bits, int bits_size){
    int result = 0;
    for (int i = 0; i < bits_size; i++) {
        result |= bits[i];
        if(i != bits_size - 1){
            result <<= 1; //result = result/2;
        }
    }
    char hex[64];
    sprintf(hex, "0x%02X", result);
    printf("%s", hex);
    printf("\n");
    //return result;
}

void convert_array_to_hexadecimal(int *array_int, int array_size){
    char *array_char = (char *) calloc(array_size, sizeof(int));
    int offset = 0;
//    int hex_block;
    for(int i = 0; i < array_size >> 2; i++){
        printf("\nhex_block[%d] = ", i);
        for(int j = 0; j < 4; j++){
            array_char[i] = array_int[j + offset];
            printf("%d", array_char[i]);
        }
        offset = offset + 4;
    }
}