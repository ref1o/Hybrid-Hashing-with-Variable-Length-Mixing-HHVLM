/*********************************************************************
* Filename:   hhvlm.c
* Author:     Federico Fiorelli
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the Hybrid Hashing with Variable-Length 
              Mixing (HHVLM) algorithm. This algorithm combines non-linear 
              bitwise operations, dynamic memory allocation, and multi-round 
              compression to generate a 256-bit hash from arbitrary input data.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/****************************** MACROS ******************************/
#define ROTLEFT(a, b) (((a) << (b)) | ((a) >> (32 - (b))))

/**************************** VARIABLES *****************************/

/*********************** FUNCTION DEFINITIONS ***********************/

/*********************************************************************
* Function:  rotate_left
* Details:   Performs a left bitwise rotation on a 32-bit integer.
* Params:    value - the integer to rotate
*            shift - the number of bits to rotate by
* Returns:   The rotated value.
*********************************************************************/
uint32_t rotate_left(uint32_t value, int shift) {
    return ROTLEFT(value, shift);
}

/*********************************************************************
* Function:  generate_salt
* Details:   Generates a simple 16-byte salt. For a more secure 
             implementation, replace this with a cryptographically 
             secure random number generator.
* Params:    salt - a pointer to a 16-byte array where the salt will be stored
*********************************************************************/
void generate_salt(uint8_t salt[16]) {
    for (int i = 0; i < 16; i++) {
        salt[i] = (uint8_t)(i * 17);  // Simple pattern-based salt generation
    }
}

/*********************************************************************
* Function:  extend_state
* Details:   Extends a 32-bit state across a 32-byte output buffer by 
             copying the state and rotating it for each 4-byte segment.
* Params:    state  - the 32-bit state to extend
*            output - a pointer to a 32-byte buffer to store the extended state
*********************************************************************/
void extend_state(uint32_t state, uint8_t output[32]) {
    for (int i = 0; i < 32; i += 4) {
        memcpy(output + i, &state, 4);  // Copy the 4-byte state into each 4-byte segment of the output buffer
        state = ROTLEFT(state, 8);  // Rotate the state for diversity in each segment
    }
}

/*********************************************************************
* Function:  hybrid_hash
* Details:   The main hashing function that processes input data to 
             produce a 256-bit hash. This function uses dynamic memory 
             allocation for flexibility.
* Params:    input  - a pointer to the input data
*            length - the length of the input data
*            output - a pointer to a 32-byte buffer to store the resulting hash
*********************************************************************/
void hybrid_hash(const uint8_t *input, size_t length, uint8_t output[32]) {
    uint8_t salt[16];
    generate_salt(salt);

    // Calculate the length after padding
    size_t padded_length = ((length + 16 + 31) / 32) * 32;

    // Dynamically allocate memory for the buffer
    uint8_t *buffer = (uint8_t *)malloc(padded_length);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Preprocess: Append salt and input, then pad
    memcpy(buffer, salt, 16);
    memcpy(buffer + 16, input, length);
    if (length + 16 < padded_length) {
        memset(buffer + 16 + length, 0, padded_length - (16 + length));
    }

    uint32_t state = 0xdeadbeef; // Arbitrary initial state value
    for (size_t i = 0; i < padded_length; i += 32) {
        uint32_t *block = (uint32_t *)(buffer + i);
        for (int j = 0; j < 8; j++) {
            state ^= ROTLEFT(block[j], j + i % 32);
            state = (state * 0x5bd1e995) ^ ROTLEFT(state, 13);
        }
    }

    for (int round = 0; round < 5; ++round) {
        state ^= ROTLEFT(state, 17);
        state = (state * 0x5bd1e995) ^ ROTLEFT(state, 13);
    }

    extend_state(state, output);

    // Final XOR with salt for enhanced security
    for (int i = 0; i < 16; i++) {
        output[i] ^= salt[i];
    }

    // Free the dynamically allocated memory
    free(buffer);
}

/*********************************************************************
* Function:  main
* Details:   A sample main function to demonstrate the usage of the 
             hybrid_hash function. This function now takes input from 
             the command line and hashes it.
*********************************************************************/
int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"Your data here\"\n", argv[0]);
        return 1;
    }

    uint8_t hash[32];
    const char *data = argv[1];
    hybrid_hash((const uint8_t *)data, strlen(data), hash);

    // Print the resulting hash in hexadecimal format
    printf("Hash: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
