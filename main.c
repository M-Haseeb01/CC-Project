// main.c
#include <stdio.h>
#include "llvm_generator.c"

int main() {
    FILE* out = fopen("output.ll", "w");
    if (!out) {
        perror("output.ll");
        return 1;
    }

    generate_llvm_header(out);
    generate_main_start(out);
    generate_print(out, 42); // Pretend this came from FlowScript
    generate_main_end(out);

    fclose(out);
    printf("LLVM IR written to output.ll\n");
    return 0;
}

