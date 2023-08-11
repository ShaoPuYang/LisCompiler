# Copyright liserver. All rights reserved.

# Settings of compiler
TokenStream := token/TokenStream.o
TokenAnalysis := TokenAnalysis/TokenAnalysis.o

ApplicationCore := main.o
LibraryCore := library/console/prints.o library/system/rwfile.o
CompilerCore := ${TokenStream} ${TokenAnalysis} ${ApplicationCore} ${LibraryCore} core/Compiler.o

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
cur_makefile_path := $(patsubst %/, %, $(dir $(mkfile_path)))

CompilerNoUpdateARG = -I ${cur_makefile_path}
CompileARG = -O3 -Wno-deprecated ${CompilerNoUpdateARG}

TARGER := bin/LisCompiler
OBJ_DIR := bin/obj

DEBUG = FALSE
CC := g++

ifeq (${DEBUG}, TRUE)
	CompileARG = -Wall -O0 -Werror -D__DEBUG ${CompilerNoUpdateARG}
endif

# DO NOT EDIT UNDER HERE

all: ${TARGER}

${OBJ_DIR}/%.o: %.cpp
	${CC} -c $< -o ${OBJ_DIR}/$(notdir $@) ${CompileARG}

${TARGER}: $(addprefix ${OBJ_DIR}/, ${CompilerCore})
	${CC} -o $@ $(addprefix ${OBJ_DIR}/, $(notdir ${CompilerCore})) ${CompileARG}

clean:
	del *.o

.PHONY: ${TARGER} clean
