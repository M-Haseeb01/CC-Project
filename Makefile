# Compiler and Flags
CC = cc # Or gcc, or clang
# Get LLVM CFLAGS and LDFLAGS using llvm-config
LLVM_CONFIG = llvm-config
LLVM_CFLAGS = $(shell $(LLVM_CONFIG) --cflags)
LLVM_LDFLAGS_CORE = $(shell $(LLVM_CONFIG) --ldflags --system-libs --libs core)
# REMOVED 'scalar' from the list below
LLVM_LDFLAGS_COMPONENTS = $(shell $(LLVM_CONFIG) --libs analysis target native asmparser bitwriter executionengine)

CFLAGS_COMMON = -g -Wall -Wno-unused-function $(LLVM_CFLAGS)

# Target executable
TARGET = flow_compiler # Assuming your main C file is flow_compiler.c

# Source files (C files) - Assuming your main C file is flow_compiler.c
SRCS = ast.c lex.yy.c flowscript.tab.c llvm_generator.c flow_compiler.c
OBJS = $(SRCS:.c=.o)

# Flex and Bison generated files
FLEX_C_OUT = lex.yy.c
BISON_C_OUT = flowscript.tab.c
BISON_H_OUT = flowscript.tab.h

.PHONY: all clean test run_test test_file

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS_COMMON) -o $(TARGET) $(OBJS) $(LLVM_LDFLAGS_CORE) $(LLVM_LDFLAGS_COMPONENTS)

# Compile C source files to object files
# This general rule handles all .c -> .o compilation
# It depends on key headers to trigger recompilation if they change.
%.o: %.c ast.h llvm_generator.h $(BISON_H_OUT)
	$(CC) $(CFLAGS_COMMON) -c $< -o $@

# Bison: .y -> .c and .h
$(BISON_C_OUT) $(BISON_H_OUT): flowscript.y ast.h
	bison -d -v flowscript.y -o $(BISON_C_OUT)

# Flex: .l -> .c
$(FLEX_C_OUT): flowscript.l $(BISON_H_OUT) ast.h
	flex -o $(FLEX_C_OUT) flowscript.l

# Explicit dependencies for generated files to ensure they recompile if ast.h changes
lex.yy.o: $(FLEX_C_OUT) $(BISON_H_OUT) ast.h
flowscript.tab.o: $(BISON_C_OUT) ast.h

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)
	rm -f $(FLEX_C_OUT) $(BISON_C_OUT) $(BISON_H_OUT) flowscript.output
	rm -f *.ll *.bc # Remove LLVM IR and bitcode files
	rm -f test_program test.flow # Remove test artifacts from default test

# Rule to create a very basic default test.flow file
# You should replace this with your actual test.flow content for comprehensive testing.
test.flow:
	@echo "// test.flow - Basic placeholder" > test.flow
	@echo "5 |> print();" >> test.flow
	@echo "result = 10 + 2;" >> test.flow
	@echo "result |> print();" >> test.flow


# Comprehensive test target: clean, build, ensure test.flow exists, compile test file, run it
test: clean all test.flow
	@echo ""
	@echo "=== Compiling test.flow with $(TARGET) ==="
	./$(TARGET) test.flow
	@echo ""
	@echo "=== Running test.flow.ll with lli ==="
	lli test.flow.ll
	@echo ""
	@echo "=== (Optional) Compiling test.flow.ll to native 'test_program' ==="
	$(CC) test.flow.ll -o test_program $(LLVM_LDFLAGS_CORE) $(LLVM_LDFLAGS_COMPONENTS)
	@echo "=== Running native 'test_program' ==="
	./test_program
	@echo ""
	@echo "=== Default Test Complete ==="

# Target to compile and run a specific .flow file
# Usage: make test_file FILE=my_script.flow
test_file: all
	@if [ -z "$(FILE)" ]; then \
	    echo "Usage: make test_file FILE=<your_flow_script.flow>"; \
	    exit 1; \
	fi
	@echo ""
	@echo "=== Compiling $(FILE) with $(TARGET) ==="
	./$(TARGET) $(FILE)
	@echo ""
	@echo "=== Running $(FILE).ll with lli ==="
	lli $(FILE).ll
	@echo ""
	@echo "=== (Optional) Compiling $(FILE).ll to native '$(subst .flow,,$(FILE))_program' ==="
	$(CC) $(FILE).ll -o $(subst .flow,,$(FILE))_program $(LLVM_LDFLAGS_CORE) $(LLVM_LDFLAGS_COMPONENTS)
	@echo "=== Running native '$(subst .flow,,$(FILE))_program' ==="
	./$(subst .flow,,$(FILE))_program
	@echo ""
	@echo "=== Test for $(FILE) Complete ==="

# Simple target to just run the compiler on test.flow and then lli
run_test: all test.flow
	./$(TARGET) test.flow
	lli test.flow.ll
