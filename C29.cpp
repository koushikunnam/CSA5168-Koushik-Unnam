#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#define LANE_SIZE 64
#define BLOCK_SIZE 1024
#define RATE (BLOCK_SIZE / LANE_SIZE) 
#define CAPACITY (1600 - BLOCK_SIZE)  
#define STATE_SIZE 25               
void initialize_state(uint64_t state[STATE_SIZE]) {
    for (int i = 0; i < STATE_SIZE; i++) {
        state[i] = 0;
    }
}
void set_initial_message_block(uint64_t state[STATE_SIZE]) {
    for (int i = 0; i < RATE; i++) {
        state[i] = rand();
        if (state[i] == 0) {
            state[i] = 1; 
        }
    }
}
int all_capacity_lanes_nonzero(uint64_t state[STATE_SIZE]) {
    for (int i = RATE; i < STATE_SIZE; i++) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}
int main() {
    srand(time(NULL)); 
    uint64_t state[STATE_SIZE];
    int rounds = 0;
    initialize_state(state);
    set_initial_message_block(state);
    while (!all_capacity_lanes_nonzero(state)) {
        for (int i = 0; i < RATE; i++) {
            for (int j = RATE; j < STATE_SIZE; j++) {
                state[j] ^= state[i];
            }
        }
        rounds++;
    }
    printf("Number of rounds to fill capacity lanes with nonzero bits: %d\n", rounds);
    return 0;
}