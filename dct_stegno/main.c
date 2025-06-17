#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dct.h"

#define SIZE 256

unsigned char image[SIZE * SIZE];
unsigned char stego_image[SIZE * SIZE];
char message[1024];

void read_image(const char* filename, unsigned char* data) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Cannot open %s\n", filename);
        exit(1);
    }
    fseek(f, 1078, SEEK_SET);  // Skip BMP header for 8-bit grayscale (54+1024 palette)
    fread(data, 1, SIZE * SIZE, f);
    fclose(f);
}

void write_image(const char* filename, unsigned char* data) {
    FILE *f_in = fopen("lena_gray.bmp", "rb");
    FILE *f_out = fopen(filename, "wb");
    if (!f_in || !f_out) {
        printf("File error\n");
        exit(1);
    }
    unsigned char header[1078];
    fread(header, 1, 1078, f_in);
    fwrite(header, 1, 1078, f_out);
    fwrite(data, 1, SIZE * SIZE, f_out);
    fclose(f_in);
    fclose(f_out);
}

void encode(unsigned char* img, char* msg, unsigned char* stego) {
    memcpy(stego, img, SIZE * SIZE);
    int idx = 0, bit_pos = 0;
    char ch = msg[0];

    for (int i = 0; i < SIZE; i += 8) {
        for (int j = 0; j < SIZE; j += 8) {
            double block[8][8];
            for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++)
                    block[x][y] = (double) img[(i + x) * SIZE + (j + y)];

            dct(block);

            int bit = (ch >> bit_pos) & 1;
            block[4][3] = ((int)block[4][3] & ~1) | bit;

            bit_pos++;
            if (bit_pos == 8) {
                bit_pos = 0;
                idx++;
                ch = msg[idx];
                if (ch == '\0') goto done;
            }

            idct(block);

            for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++) {
                    int val = (int) block[x][y];
                    if (val < 0) val = 0;
                    if (val > 255) val = 255;
                    stego[(i + x) * SIZE + (j + y)] = (unsigned char) val;
                }
        }
    }
done:
    return;
}


void decode(unsigned char* stego, char* out) {
    int idx = 0;
    char ch = 0;
    int bit_pos = 0;

    for (int i = 0; i < SIZE; i += 8) {
        for (int j = 0; j < SIZE; j += 8) {
            double block[8][8];
            for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++)
                    block[x][y] = (double) stego[(i + x) * SIZE + (j + y)];
            
            dct(block);

            int bit = (int)block[4][3] & 1;
            ch |= (bit << bit_pos);
            bit_pos++;
            if (bit_pos == 8) {
                out[idx++] = ch;
                if (ch == '\0') {
                    out[idx] = '\0';
                    return;
                }
                ch = 0;
                bit_pos = 0;
            }
        }
    }
}

int main() {
    read_image("lena_gray.bmp", image);

    FILE* secret = fopen("secret.txt", "r");
    if (!secret) {
        printf("Cannot open secret.txt\n");
        return 1;
    }
    fgets(message, sizeof(message) - 1, secret);
    message[strcspn(message, "\n")] = '\0';
    fclose(secret);

    printf("Message to encode: %s\n", message);

    int msg_len = strlen(message) + 1;  // include null
    encode(image, message, stego_image);
    write_image("stego.bmp", stego_image);

    char decoded[1024];
    printf("Decoding from stego.bmp:\n");
    read_image("stego.bmp", stego_image);
    decode(stego_image, decoded);
    printf("Decoded Message: %s\n", decoded);

    return 0;
}
