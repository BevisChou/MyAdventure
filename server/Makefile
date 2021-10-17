# Ref: https://stackoverflow.com/questions/50501388/how-to-update-g-compiler-on-osx

CPP11 = g++-11 -std=c++11
OPT = -pthread

BASEDIR = src

OUT = main

.PHONY: default, clean

default: ${BASEDIR}/*
	${CPP11} ${OPT} $^ -o ${OUT}

clean:
	$(shell rm ${OUT})