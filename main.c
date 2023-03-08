#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

unsigned int p = 7;
time_t t;

int N = 16;
int *input_block_in_elements_original;
int *input_block_in_elements_modified;
//int IV[8] = {43, 49, 65, 5, 57, 107, 2, 13, 47, 109, 31, 29, 5, 51, 53, 7};

int IV[16] = {43, 49, 65, 5, 57, 107, 2, 13, 47, 109, 31, 29, 5, 51, 53, 7};

//NMNT
//NMNT matrix for p = 7 and N = 8
//int NMNT[8][8] = {
//        {1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 111, 1, 0, 126, 16, 126, 0},
//        {1, 1, 126, 126, 1, 1, 126, 126},
//        {1, 0, 126, 111, 126, 0, 1, 16},
//        {1, 126, 1, 126, 1, 126, 1, 126},
//        {1, 16, 1, 0, 126, 111, 126, 0},
//        {1, 126, 126, 1, 1, 126, 126, 1},
//        {1, 0, 126, 16, 126, 0, 1, 111}
//};

//NMNT matrix for p = 7 and N = 16
//int NMNT[16][16] =
//        {{1, 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1},
//         {1, 82,  111, 82,  1,   3,   0,   124, 126, 45,  16,  45,  126, 124, 0,   3},
//         {1, 111, 1,   0,   126, 16,  126, 0,   1,   111, 1,   0,   126, 16,  126, 0},
//         {1, 82,  0,   45,  126, 3,   111, 3,   126, 45,  0,   82,  1,   124, 16,  124},
//         {1, 1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126},
//         {1, 3,   16,  3,   1,   45,  0,   82,  126, 124, 111, 124, 126, 82,  0,   45},
//         {1, 0,   126, 111, 126, 0,   1,   16,  1,   0,   126, 111, 126, 0,   1,   16},
//         {1, 124, 0,   3,   126, 82,  16,  82,  126, 3,   0,   124, 1,   45,  111, 45},
//         {1, 126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126, 1,   126},
//         {1, 45,  111, 45,  1,   124, 0,   3,   126, 82,  16,  82,  126, 3,   0,   124},
//         {1, 16,  1,   0,   126, 111, 126, 0,   1,   16,  1,   0,   126, 111, 126, 0},
//         {1, 45,  0,   82,  126, 124, 111, 124, 126, 82,  0,   45,  1,   3,   16,  3},
//         {1, 126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1,   1,   126, 126, 1},
//         {1, 124, 16,  124, 1,   82,  0,   45,  126, 3,   111, 3,   126, 45,  0,   82},
//         {1, 0,   126, 16,  126, 0,   1,   111, 1,   0,   126, 16,  126, 0,   1,   111},
//         {1, 3,   0,   124, 126, 45,  16,  45,  126, 124, 0,   3,   1,   82,  111, 82}};

//ONMNT matrix for p = 7 and N = 8
//int NMNT[8][8] = {
//        {1, 1, 1, 1, 1, 1, 1, 1},
//        {72, 19, 19, 72, 5, 99, 28, 122},
//        {82, 82, 3, 124, 45, 45, 124, 3},
//        {19, 5, 122, 108, 28, 72, 72, 28},
//        {111, 0, 16, 0, 111, 0, 16, 0},
//        {19, 122, 122, 19, 28, 55, 72, 99},
//        {82, 45, 3, 3, 45, 82, 124, 124},
//        {72, 108, 19, 55, 5, 28, 28, 5}
//};

//ONMNT matrix for p = 7 and N = 16
//int NMNT[16][16] = {
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {72, 19, 19, 72, 5, 99, 28, 122, 55, 108, 108, 55, 122, 28, 99, 5},
//        {82, 82, 3, 124, 45, 45, 124, 3, 82, 82, 3, 124, 45, 45, 124, 3},
//        {19, 5, 122, 108, 28, 72, 72, 28, 108, 122, 5, 19, 99, 55, 55, 99},
//        {111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0},
//        {19, 122, 122, 19, 28, 55, 72, 99, 108, 5, 5, 108, 99, 72, 55, 28},
//        {82, 45, 3, 3, 45, 82, 124, 124, 82, 45, 3, 3, 45, 82, 124, 124},
//        {72, 108, 19, 55, 5, 28, 28, 5, 55, 19, 108, 72, 122, 99, 99, 122},
//        {1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126, 1, 126},
//        {5, 28, 28, 5, 55, 19, 108, 72, 122, 99, 99, 122, 72, 108, 19, 55},
//        {3, 3, 45, 82, 124, 124, 82, 45, 3, 3, 45, 82, 124, 124, 82, 45},
//        {99, 72, 55, 28, 19, 122, 122, 19, 28, 55, 72, 99, 108, 5, 5, 108},
//        {0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16, 0, 111, 0, 16},
//        {28, 72, 72, 28, 108, 122, 5, 19, 99, 55, 55, 99, 19, 5, 122, 108},
//        {124, 3, 82, 82, 3, 124, 45, 45, 124, 3, 82, 82, 3, 124, 45, 45},
//        {122, 28, 99, 5, 72, 19, 19, 72, 5, 99, 28, 122, 55, 108, 108, 55}
//};

//O2NMNT
//O2NMNT matrix for p = 7 and N = 8
//int NMNT[8][8] =
//                    {
//                        {72, 19, 19, 72, 5, 99, 28, 122},
//                        {19, 5, 122, 108, 28, 72, 72, 28},
//                        {19, 122, 122, 19, 28, 55, 72, 99},
//                        {72, 108, 19, 55, 5, 28, 28, 5},
//                        {5, 28, 28, 5, 55, 19, 108, 72},
//                        {99, 72, 55, 28, 19, 122, 122, 19},
//                        {28, 72, 72, 28, 108, 122, 5, 19},
//                        {122, 28, 99, 5, 72, 19, 19, 72}
//                    };

//O2NMNT matrix for p = 7 and N = 16
int NMNT[16][16] = {
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
    int total_iterations = 100 ;
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
            each_input_block_in_elements_original = shuffling_array(each_input_block_in_elements_original);
            each_input_block_in_elements_modified = shuffling_array(each_input_block_in_elements_modified);
//            for(int i = 0; i < N; i++){
//                printf("NMNT input original block after shuffling[%d] = %d\n", i, each_input_block_in_elements_original[i]);
//                printf("NMNT input modified after shuffling[%d] = %d\n", i, each_input_block_in_elements_modified[i]);
//            }
// STEP # 6: APPLY THE TRANSFORM OPERATION: GNMNT Block
            hash_input_original = transform_block(each_input_block_in_elements_original, Mp);
            hash_input_modified = transform_block(each_input_block_in_elements_modified, Mp);

            // Shuffling block **** after **** the transformation
            //hash_input_original = shuffling_array(hash_input_original);
            //hash_input_modified = shuffling_array(hash_input_modified);

            for(int i = 0; i < N; i++){
                //printf("hash_input_original_before_shifting[%d]= %d\n",i,  hash_input_original[i]);
            }

            //Shifting operations on the input of the NMNT elements
//            hash_input_original = shifted_array( hash_input_original,1);
//            hash_input_modified = shifted_array( hash_input_modified,1);

            for(int i = 0; i < N; i++){
                //printf("hash_input_original_after_shifting[%d]= %d\n",i,   hash_input_original[i]);
            }
            //Printing output of the GNMNT transformation
            for(int i = 0; i < N; i++){
                 printf("hash_input_original[%d]= %d\n",i,  hash_input_original[i]);
                 printf("hash_input_modified[%d]= %d\n",i,  hash_input_modified[i]);
            }

            for(int i = 0; i < N; i++){
                printf("hash_output_original_input[%d]= %d\n",i,  hash_output_original[i]);
                printf("hash_output_modified_input[%d]= %d\n",i,  hash_output_modified[i]);
            }

            hash_output_original = xor_operation(hash_output_original, hash_input_original);
            hash_output_modified = xor_operation(hash_output_modified,  hash_input_modified);
// STEP 7: APPLY KEY(IV) ON THE FIRST BLOCK AND APPLY XOR BETWEEN INTERMEDIATE BLOCKS

            for(int i = 0; i < N; i++){
                printf("hash_output_original[%d]= %d\n",i,  hash_output_original[i]);
                printf("hash_output_modified[%d]= %d\n",i,  hash_output_modified[i]);
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
        fprintf(pFile, "%d, %d\n", iteration_number, number_of_changed_bit);

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

int* transform_block(int* input_block, int Mp) {
    int* transformed_output = malloc(sizeof(int) * N);
    int sum = 0;
    signed long long result_original = 0;
    signed long long result_modified = 0;
    signed long long sum_original = 0;
    signed long long sum_modified = 0;
    for (int row = 0; row < N; row++) {
        int result = 0;
        for (int col = 0; col < N; col++) {
            sum = input_block[col] * NMNT[col][row];
            result = result + sum;
            //printf("result = %d\n", result);
        }
        // int encryptedBlock[c] = mod(result, Mp);
        transformed_output[row] = result % Mp;
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