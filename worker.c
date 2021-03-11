#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// compile using gcc:
// gcc worker.c -Wall -lm -Ofast -o worker && ./worker

#define RANDSIZE 3000
#define RANDMIN 1
#define RANDMAX 150
#define RANDSEED 1615011838
// #define MODSIZE 20
#define MODSIZE 4

#ifdef _MSC_BUILD
#define MY_SSCANF sscanf_s
#define MY_FOPEN(fp, filename, mode) fopen_s(&fp, filename, mode)
#else
#define MY_SSCANF sscanf
#define MY_FOPEN(fp, filename, mode) fp = fopen(filename, mode)
#endif

// randoms for min=1, max=150, size=3000, seed=1615011838
// int randoms[RANDSIZE] = { 69,75,121,75,130,121,43,29,116,13,35,106,107,42,145,6,49,109,150,8,120,79,10,80,79,75,83,115,89,145,141,7,121,13,133,100,133,77,31,98,90,65,105,98,107,2,103,57,110,5,64,79,83,125,61,63,49,45,28,40,91,18,46,62,31,81,63,65,7,93,65,148,8,19,95,16,72,100,124,31,104,37,12,36,12,72,98,112,116,27,1,56,97,99,117,29,29,82,93,87,24,7,137,83,78,81,98,149,30,123,30,133,10,41,70,73,14,70,86,31,148,139,86,94,139,105,122,69,36,65,5,111,123,141,44,50,124,43,101,55,16,32,90,77,124,61,51,137,130,38,17,128,26,4,123,14,10,95,82,97,61,139,58,85,129,101,135,4,45,137,59,60,18,50,38,141,110,88,29,90,126,97,119,53,100,91,119,110,87,50,56,147,38,15,82,69,17,118,124,62,6,84,23,23,133,113,65,93,102,93,84,77,39,104,32,40,44,150,51,33,101,9,81,139,23,64,109,40,31,134,3,36,68,25,110,50,137,24,142,89,18,127,67,108,80,150,50,26,149,100,58,100,108,138,140,33,52,150,72,134,133,126,72,50,150,83,100,39,9,143,29,26,120,147,36,101,147,85,126,47,34,85,146,44,125,37,76,78,36,49,61,19,24,34,68,75,117,69,113,125,114,43,52,135,40,87,85,36,73,113,82,9,47,130,52,73,16,29,150,52,77,61,122,2,146,39,76,112,10,91,138,123,133,92,107,74,80,41,109,3,3,93,11,102,124,114,24,41,142,24,92,68,136,115,69,33,4,46,145,65,136,34,37,119,125,143,42,55,85,53,57,88,47,119,91,72,82,16,112,125,91,106,42,76,70,12,109,125,109,5,39,95,90,75,115,65,67,58,119,2,12,77,141,110,45,133,31,28,148,143,2,141,98,95,118,69,8,128,44,116,132,82,112,72,59,76,38,27,36,58,28,47,134,70,7,80,104,37,107,4,81,10,144,80,104,111,149,13,89,94,128,122,25,142,95,135,67,132,12,102,39,91,149,74,63,57,3,16,93,11,19,76,20,64,5,25,25,3,89,15,96,67,136,23,110,81,59,26,114,70,30,55,11,80,128,73,136,33,140,130,43,61,55,115,124,60,41,148,114,130,12,112,98,50,36,57,32,94,134,145,14,13,49,76,92,79,50,129,111,39,109,55,1,13,19,125,124,112,122,88,91,36,101,90,85,136,146,116,79,31,12,144,44,113,121,37,41,72,16,1,13,26,107,13,90,126,137,64,139,11,53,79,46,3,70,32,40,117,147,20,147,60,14,92,22,36,129,62,108,46,114,120,71,71,132,62,98,21,125,86,31,79,66,76,81,37,107,120,3,5,140,149,64,55,91,86,142,121,49,99,68,65,120,40,135,4,101,134,24,76,121,54,56,88,31,39,124,39,8,126,95,49,26,8,5,116,145,147,138,44,147,55,108,19,94,144,22,45,29,97,22,149,52,77,86,82,115,59,22,25,86,116,125,111,123,32,129,20,80,116,115,128,73,124,146,16,117,69,112,47,15,35,45,66,112,32,49,128,90,70,54,25,35,81,135,60,112,113,79,93,131,95,70,53,68,66,120,86,36,82,132,51,116,78,18,129,109,119,9,48,90,114,124,125,44,10,86,57,25,14,149,5,108,121,109,77,88,78,12,123,9,143,75,27,122,145,5,80,113,13,29,52,127,2,78,72,63,13,129,87,78,29,143,87,149,3,13,86,81,76,111,141,120,35,69,91,29,74,20,43,138,48,147,16,101,74,88,66,139,118,2,118,48,47,55,47,101,119,34,83,97,46,74,66,81,142,59,11,117,78,54,105,28,50,22,30,25,109,95,13,128,149,33,26,97,139,124,47,107,59,130,105,105,105,73,35,148,131,45,115,110,150,121,39,101,142,69,126,3,13,40,130,63,72,5,9,60,30,56,69,89,87,23,43,41,95,129,38,127,75,54,87,75,76,125,25,120,95,52,122,10,92,3,72,65,60,81,27,89,38,95,27,124,19,121,66,16,99,5,44,24,111,130,150,36,7,24,5,101,128,28,110,121,31,32,35,142,14,113,80,103,57,9,76,128,31,43,45,32,47,88,55,59,120,54,95,126,129,1,128,106,81,88,76,13,21,13,4,34,125,135,38,84,45,113,113,76,57,59,107,5,146,63,64,115,18,60,142,146,60,120,4,42,109,131,54,129,45,57,64,20,94,101,5,138,115,117,63,21,77,71,25,72,133,140,89,150,49,132,48,11,101,51,52,59,83,106,89,128,64,2,49,7,4,53,145,118,71,109,40,147,30,117,120,64,106,110,64,57,92,13,67,94,115,118,3,47,125,143,24,91,145,124,97,50,78,143,18,50,4,109,98,33,75,68,148,83,79,113,139,20,125,55,114,89,74,18,136,49,10,61,139,56,35,137,106,14,32,25,64,35,133,11,119,110,130,116,42,59,79,82,78,53,136,93,142,59,12,29,9,22,89,49,129,25,88,136,91,119,10,4,55,45,66,23,56,46,138,149,6,118,80,135,73,65,78,116,25,89,144,86,12,134,36,43,61,25,28,1,143,90,56,99,36,121,121,91,68,11,89,73,128,70,58,102,134,135,67,60,125,60,47,39,44,83,81,6,107,108,6,2,47,61,100,82,83,123,74,1,133,64,73,12,133,130,114,18,16,30,130,141,142,26,29,87,10,109,92,19,118,97,72,15,59,21,148,141,45,124,141,27,37,116,91,72,95,54,141,111,135,120,3,126,48,83,62,57,41,3,127,8,1,48,74,111,69,124,4,113,149,46,42,87,11,132,8,106,87,51,118,71,20,120,99,67,52,62,26,144,65,2,53,117,50,29,78,20,54,133,34,52,28,127,138,39,108,48,46,96,98,65,69,19,86,17,138,39,78,13,84,44,66,38,63,115,66,42,36,21,24,70,72,51,46,112,141,56,61,88,53,60,2,121,130,139,39,117,27,117,31,110,62,97,148,124,113,115,15,51,136,38,120,109,141,67,122,33,24,84,121,77,143,122,99,25,13,138,141,39,6,74,51,67,72,100,93,34,64,107,84,101,47,105,112,89,74,83,121,149,17,91,75,61,115,76,85,127,63,128,67,120,51,19,36,122,118,128,57,84,137,43,86,85,147,47,23,122,32,45,121,100,38,97,62,2,22,49,30,136,26,148,105,128,17,43,1,134,72,57,119,58,1,55,44,148,101,118,21,34,13,141,133,50,88,45,103,11,93,132,49,20,129,3,147,47,45,147,31,117,105,149,76,106,53,120,5,56,139,25,89,1,68,124,102,57,18,54,67,12,87,17,31,118,20,79,14,116,127,96,134,133,147,60,88,101,81,144,6,69,71,147,122,138,22,125,44,39,81,12,102,17,29,34,36,100,112,102,65,88,47,101,122,43,10,112,144,142,105,51,112,25,99,83,64,120,58,9,60,138,73,11,56,3,44,144,102,57,95,68,144,43,18,18,86,79,129,131,70,83,83,32,10,32,16,73,53,125,134,113,14,56,25,70,58,69,115,61,125,59,30,21,3,100,38,88,28,16,120,150,150,105,31,9,136,98,134,90,73,19,52,86,126,77,57,85,47,21,145,73,131,76,145,134,25,84,123,53,99,145,52,1,99,134,61,136,133,44,75,55,114,29,43,89,105,99,23,53,22,69,125,54,145,22,89,19,105,62,123,106,108,76,106,56,111,16,41,94,112,17,148,75,45,92,14,51,93,88,103,16,7,130,69,1,53,8,71,7,121,44,112,78,119,67,35,132,135,127,75,96,143,124,72,38,66,137,88,8,75,93,23,81,124,143,133,26,52,53,32,74,96,46,53,117,14,87,98,148,115,74,145,108,47,67,47,112,105,36,21,29,128,95,11,3,140,45,28,41,98,112,115,95,7,69,113,72,58,112,70,22,35,64,129,82,32,25,95,39,113,18,119,142,112,130,145,101,76,74,44,23,87,60,20,93,128,34,67,35,146,136,57,30,101,87,13,35,14,10,73,126,27,41,19,138,72,13,141,148,87,86,72,75,145,143,70,24,27,136,111,22,121,69,103,123,5,18,7,70,27,79,97,53,22,116,92,93,30,134,142,116,69,64,93,115,56,12,139,134,147,99,57,117,17,10,141,73,27,148,45,53,128,141,7,51,8,98,144,38,82,135,55,52,100,147,17,58,8,5,41,4,5,98,22,73,9,13,47,87,62,91,41,91,82,47,142,89,46,135,126,127,21,31,81,23,79,97,80,87,3,120,90,59,119,112,131,127,26,27,63,87,20,103,27,3,51,18,143,97,54,21,125,127,103,55,149,31,1,130,117,55,1,57,113,120,70,145,148,147,74,61,83,93,65,11,147,116,81,139,62,36,9,36,12,111,143,62,142,45,41,10,100,94,66,114,63,37,11,60,33,84,22,17,78,139,80,74,104,10,114,67,45,123,4,109,135,48,72,126,93,15,136,94,108,103,57,72,42,67,33,126,52,55,143,31,95,124,104,100,133,68,16,79,92,71,37,76,119,11,104,113,25,141,56,132,93,112,105,36,81,137,64,34,93,108,65,37,81,70,136,63,39,53,141,130,124,80,56,144,90,61,106,16,51,11,49,45,24,3,81,6,139,144,40,82,101,104,20,31,23,6,145,114,58,37,93,83,116,50,76,107,110,83,24,10,93,72,55,19,74,37,24,115,30,63,98,32,68,117,114,91,24,108,54,82,144,48,14,12,98,142,20,109,74,44,119,69,115,75,87,91,111,110,107,140,75,106,73,142,72,36,134,148,45,37,79,38,137,144,101,136,37,121,94,111,14,62,81,30,136,17,120,148,28,128,137,102,83,111,94,57,146,77,54,40,16,34,130,2,79,80,39,116,50,132,128,115,96,58,145,133,126,16,131,3,144,117,105,128,130,100,34,27,26,139,119,41,74,98,94,3,79,132,118,129,16,147,93,111,54,139,93,29,5,73,83,148,92,89,125,71,38,61,97,64,101,65,6,25,64,2,27,143,35,46,23,50,42,17,10,147,6,5,77,10,77,9,59,70,98,85,140,37,145,139,100,96,105,8,120,71,9,48,63,43,93,137,145,36,3,4,84,8,60,10,69,137,70,127,56,69,62,98,106,108,138,107,105,144,114,74,116,24,23,28,119,17,66,113,52,69,18,37,128,78,98,99,116,70,75,73,138,38,72,145,146,111,4,100,7,19,76,122,43,98,52,63,115,117,77,68,87,94,105,65,73,52,65,90,23,139,13,11,79,136,57,74,97,112,75,103,131,150,126,75,150,27,137,16,144,63,135,80,58,89,46,33,43,110,122,65,1,36,127,79,74,86,54,72,47,128,76,79,30,51,55,81,78,93,96,71,5,80,52,115,71,150,147,15,109,20,131,11,108,10,89,31,95,44,102,43,22,27,24,103,77,78,33,4,21,30,126,77,11,28,41,133,79,89,147,37,11,128,100,118,39,38,148,133,82,1,77,5,27,100,9,5,28,41,61,100,122,36,26,132,115,119,115,43,109,13,132,119,42,81,138,80,20,37,62,3,37,41,59,115,42,67,120,121,107,30,70,130,117,96,112,134,116,128,78,74,140,59,95,32,41,134,111,61,21,75,115,109,17,24,74,58,90,95,29,99,26,98,78,44,95,39,27,60,68,105,36,58,65,32,89,106,15,101,68,87,77,32,46,93,107,21,1,47,17,29,47,42,28,124,85,123,65,14,84,132,118,21,39,84,52,29,39,119,32,8,107,108,40,54,51,48,74,51,94,90,131,140,33,8,16,118,32,80,131,18,113,150,38,2,83,142,82,24,12,113,31,118,123,122,22,23,20,147,125,15,139,105,57,21,14,72,138,98,53,20,115,15,71,54,68,56,45,150,131,108,14,63,76,136,35,149,60,106,47,34,22,35,40,130,56,106,103,95,53,5,17,17,72,87,70,139,44,17,40,24,124,106,87,101,143,23,1,53,30,48,138,103,134,28,83,39,133,35,134,87,92,52,103,13,40,74,53,84,142,93,9,18,100,147,20,92,19,21,144,100,120,132,53,103,61,37,44,43,123,79,129,64,130,133,128,19,108,83,4,100,25,65,19,26,61,38,117,132,110,111,81,131,144,35,136,54,123,29,148,96,107,126,61,138,10,91,58,117,23,62,118,99,126,136,124,88,76,90,69,35,102,52,68,95,138,53,148,111,81,145,56,89,22,18,76,83,108,133,102,130,44,69,130,71,107,103,61,32,95,129,118,46,82,35,141,70,87,40,30,69,87,137,7,10,4,82,93,14,65,44,45,10,14,25,133,120,29,43,53,123,73,21,19,57,107,61,126,96,100,57,14,88,43,21,98,98,4,92,13,68,135,58,130,148,134,14,118,12,108,72,37,30,144,55,86,101,17,113,46,18,19,111,106,113,33,105,113,37,46,125,6,30,84,135,79,119,50,98,33,7,20,69,89,13,25,76,15,41,39,60,58,109,73,65,72,105,19,34,141,116,60,49,47,144,85,126,112,135,73,144,141,144,114,79,59,138,5,73,28,95,35,138,53,107,104,26,61,25,59,104,140,21,2,37,66,86,64,79,70,38,73,113,32,88,93,142,76,149,64,5,93,98,44,146,54,148,21,17,22,132,22,63,2,23,1,119,10,116,47,132,4,21,146,87,109,88,78,34,87,141,90,29,141,134,76,96,33,149,112,106,32,133,18,85,57,71,53,119,36,99,100,91,120,147,27,78,84,6,13,20,49 };

int moduli[MODSIZE] = {
   2,3,5,7
};

// modulo that returns positive numbers only
// https://stackoverflow.com/a/57544473
int modulo(int a, int b) {
    int m = a % b;

    if (m < 0) {
        m = (b < 0) ? m - b : m + b;
    }

    return m;
}

// parse command line arguments
void parse_args(int argc, char* argv[], char** filename, int* x_input, int* rand_min, int* rand_max, unsigned* rand_size, unsigned* rand_seed) {
    // check for correct number of args
    if (argc < 3) {
        printf("%s: <filename.csv> <x> [<random min> <random max> <random size> <random seed>]\n", argv[0]);
        exit(1);
    }

    if (argc >= 3) {
        *filename = argv[1];
        MY_SSCANF(argv[2], "%d", x_input);
    }

    // defaults
    *rand_min = RANDMIN;
    *rand_max = RANDMAX;
    *rand_size = RANDSIZE;
    *rand_seed = RANDSEED;

    if (argc >= 4) {
        MY_SSCANF(argv[3], "%d", rand_min);
    }

    if (argc >= 5) {
        MY_SSCANF(argv[4], "%d", rand_max);
    }

    if (argc >= 6) {
        MY_SSCANF(argv[5], "%u", rand_size);
    }

    if (argc >= 7) {
        MY_SSCANF(argv[6], "%u", rand_seed);
    }

    printf("Settings:\n");
    printf("- Filename: %s\n", *filename);
    printf("- X: %d\n", *x_input);
    printf("- Random Min-Max: %d-%d\n", *rand_min, *rand_max);
    printf("- Random Size: %u\n", *rand_size);
    printf("- Random Seed: %u\n", *rand_seed);
    printf("\n");
}

// generate <rand_size> random numbers between <rand_min> and <rand_max> using <rand_seed> as a seed
void generate_randoms(int* randoms, int rand_min, int rand_max, unsigned rand_size, unsigned rand_seed) {
   // seed random number generator
   srand(rand_seed);

   // generate random numbers from rand_min to rand_max (inclusive)
   for (int idx = 0; idx < rand_size; idx++) {
      randoms[idx] = (rand() % ((rand_max - rand_min) + 1)) + rand_min;
      // printf("random: %d\n", randoms[idx]);
   }
}

// precalculate all possible residues for the given moduli and random numbers
void precalc_moduli(int** precalc, int* moduli, int mod_size, int* randoms, int rand_size, int rand_max) {
    // calculate all possible positive and negative numbers
    for (int rand_num = -rand_max; rand_num <= rand_max; rand_num++) {
        int* mod_calcs = (int*) calloc(mod_size, sizeof(int));

        if (mod_calcs == NULL) {
            printf("Unable to allocate memory");
            exit(1);
        }

        for (int mi = 0; mi < mod_size; mi++) {
            mod_calcs[mi] = modulo(rand_num, moduli[mi]);
        }

        precalc[rand_num + rand_max] = mod_calcs;
    }
}

void alloc_residues(int** residues, int* moduli, int mod_size) {
    for (int mi = 0; mi < mod_size; mi++) {
        int* buf = (int*)calloc(moduli[mi], sizeof(int));

        if (buf == NULL) {
            printf("Unable to allocate memory");
            exit(1);
        }

        residues[mi] = buf;
    }
}

void clear_residues(int** residues, int* moduli, int mod_size) {
    // clear out existing residues
    for (int mi = 0; mi < mod_size; mi++) {
        int mod = moduli[mi];

        for (int ni = 0; ni < mod; ni++) {
            residues[mi][ni] = 0;
        }
    }
}

void write_csv_header(FILE* fp, int* moduli, int mod_size) {
    // write csv header
    fprintf(fp, "x,y,z");

    // write all moduli and residues
    for (int mi = 0; mi < mod_size; mi++) {
        int mod = moduli[mi];

        for (int ni = 0; ni < mod; ni++) {
            fprintf(fp, ",M%d_%d", mod, ni);
        }
    }

    fprintf(fp, "\n");
}

void write_csv_row(FILE* fp, double x_float, double y_float, double z_float, int* moduli, int mod_size, int** residues, int rand_size) {
    // write x,y,z position
    fprintf(fp, "%.3f,%.3f,%.3f", x_float, y_float, z_float);

    // write residues as percentages
    for (int mi = 0; mi < mod_size; mi++) {
        for (int ni = 0; ni < moduli[mi]; ni++) {
            fprintf(fp, ",%.2f", 100.0 * residues[mi][ni] / rand_size);
        }
    }

    fprintf(fp, "\n");
}

// command line: worker <filename> <x>
int main(int argc, char* argv[]) {
    char* filename;
    int x_input;
    int rand_min;
    int rand_max;
    unsigned rand_size;
    unsigned rand_seed;

    // parse args
    parse_args(argc, argv, &filename, &x_input, &rand_min, &rand_max, &rand_size, &rand_seed);

    // generate random numbers
    int randoms[rand_size];
    generate_randoms(randoms, rand_min, rand_max, rand_size, rand_seed);

    // precalculate all possible numbers against all possible moduli
    // and store in memory
    int* precalc[(rand_max * 2) + 1];
    precalc_moduli(precalc, moduli, MODSIZE, randoms, rand_size, rand_max);

    // allocate residues array
    int* residues[MODSIZE] = { 0 };
    alloc_residues(residues, moduli, MODSIZE);

    // open csv file for writing
    FILE* fp;
    MY_FOPEN(fp, filename, "wb");

    if (fp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    // print csv header
    write_csv_header(fp, moduli, MODSIZE);

    // precalculate x truncation
    double x_float = x_input / 1000.0;
    double x_truncs[rand_size];

    for (int ri = 0; ri < rand_size; ri++) { // 3000
        x_truncs[ri] = trunc(x_float * randoms[ri]);
    }

    // record keeping
    time_t timestamp_start, timestamp_end;
    unsigned records = 0;

    time(&timestamp_start); // starting timestamp

    // calculate residues
    for (int y = -1000; y <= 1000; y++) { // 2001
        double y_float = y / 1000.0;

        // precalculate y truncation
        double y_truncs[rand_size];

        for (int ri = 0; ri < rand_size; ri++) { // 3000
            y_truncs[ri] = trunc(y_float * x_truncs[ri]);
        }

        for (int z = -1000; z <= 1000; z++) { // 2001
            double z_float = z / 1000.0;

            // clear out existing residues
            clear_residues(residues, moduli, MODSIZE);

            // accumulate residues for this iteration
            for (int ri = 0; ri < rand_size; ri++) { // 3000
                // calculate z truncation
                int trc = (int)trunc(z_float * y_truncs[ri]);

                for (int mi = 0; mi < MODSIZE; mi++) { // 4
                    // lookup residue for trc against moduli[mi]
                    int pi = (trc + rand_max);
                    int residue = precalc[pi][mi];

                    // count the residue towards the total
                    residues[mi][residue]++;
                }
            }

            // write csv row to file
            write_csv_row(fp, x_float, y_float, z_float, moduli, MODSIZE, residues, rand_size);
            records++;
        }

        // ending timestamp
        time(&timestamp_end);

        unsigned duration = timestamp_end - timestamp_start;

        // status message
        printf(
            "x: %.3f, y: %.3f, z_count: %d, time: %d, z/s: %.0f, progress: %.2f%%\n",
            x_float,
            y_float,
            records,
            duration,
            1.0 * records / duration,
            100.0 * records / (2001 * 2001)
        );

        fflush(fp);
    }

    fclose(fp);
    exit(0);
}
