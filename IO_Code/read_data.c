#include <stdio.h>
#include <stdlib.h>

#define NUM_MATRICES 20
#define BATCH 10
#define HEAD 8
#define TOKEN 64
#define DIM 512

int main() {
    FILE *file = fopen("./data/input_matrix.bin", "rb");
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
        fread(matrix, sizeof(float), BATCH * HEAD * TOKEN * DIM, file);
        // 输出每个矩阵的第一个元素
        printf("矩阵 %d 的第一个元素: %f\n", n+1, matrix[0]);
    }
    
    // 释放矩阵内存
    free(matrix);
    
    // 关闭文件
    fclose(file);
    
    return 0;
}