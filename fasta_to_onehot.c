/* Copyright (c) 2017 Yun William Yu
 * Released under CC0 1.0 Universal. */
/* fasta_to_onehot.c */
/* Takes a fasta file in stdin.
 * Ignores title lines beginning with ">"
 * Encode the sequence line in one-hot tab-separated format
 * i.e. A = "0 1 0 0 0"
 *      C = "0 0 1 0 0"
 *      G = "0 0 0 1 0"
 *      T = "0 0 0 0 1"
 *      ? = "1 0 0 0 0"
 * Outputs to stdout
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int c = 0;
    int skipline = 0;
    int linebegin = 1;
    while (c != EOF)
    {
        c = getchar();
        switch (c) {
            case '>':
                skipline = 1; // Skip header line
                break;
            case '\n':
                if (skipline) {
                    skipline = 0;
                } else {
                    printf("\n");
                }
                break;
            case '\r': case EOF:
                // Don't do anything for carriage return
                break;
            case 'A': case 'a':
                if (!skipline) {
                    if (!linebegin) {
                        printf("\t");
                    }
                    printf("0\t1\t0\t0\t0");
                }
                break;
            case 'C': case 'c':
                if (!skipline) {
                    if (!linebegin) {
                        printf("\t");
                    }
                    printf("0\t0\t1\t0\t0");
                }
                break;
            case 'G': case 'g':
                if (!skipline) {
                    if (!linebegin) {
                        printf("\t");
                    }
                    printf("0\t0\t0\t1\t0");
                }
                break;
            case 'T': case 't':
                if (!skipline) {
                    if (!linebegin) {
                        printf("\t");
                    }
                    printf("0\t0\t0\t0\t1");
                }
                break;
            case 'N': case '.': case '-':
            default:
                if (!skipline) {
                    if (!linebegin) {
                        printf("\t");
                    }
                    printf("1\t0\t0\t0\t0");
                }
                break;
        }
        if ((c == '\n') || (c == '\r')) {
            linebegin = 1;
        } else {
            linebegin = 0;
        }
    }
}
