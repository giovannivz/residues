OUTPUT=worker

ifeq ($(OS),Windows_NT)
	OUTPUT=worker.exe
endif

all: $(OUTPUT)

clean:
	rm -f $(OUTPUT)

$(OUTPUT): worker.c
	gcc worker.c -Wall -lm -lz -Ofast -o $(OUTPUT)
