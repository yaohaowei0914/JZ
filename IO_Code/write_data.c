#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_MATRICES 20 
#define BATCH 10
#define HEAD 8
#define TOKEN 64
#define DIM 512

int main() {
    srand(time(NULL));
    
    FILE *file = fopen("./data/input_matrix.bin", "wb");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }
    
    float *matrix = (float *)malloc(BATCH * HEAD * TOKEN * DIM * sizeof(float));
    if (matrix == NULL) {
        perror("内存分配失败");
        fclose(file);
        return 1;
    }

    for (int n = 0; n < NUM_MATRICES; n++) {
        for (int d = 0; d < BATCH; d++) {
            for (int h = 0; h < HEAD; h++) {
                for (int w = 0; w < TOKEN; w++) {
                    for (int dim = 0; dim < DIM; dim++) {
                        matrix[((d * HEAD + h) * TOKEN + w) * DIM + dim] = rand() % 101;  // 生成0-100之间的随机数
                    }
                }
            }
        }
        fwrite(matrix, sizeof(float), BATCH * HEAD * TOKEN * DIM, file);
    }
    
    free(matrix);
    
    fclose(file);
    
    return 0;
}
