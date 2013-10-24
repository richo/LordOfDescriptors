CC = clang
OBJS = src/alameda.o

all: LoD

LoD: src/main.c $(OBJS)
	$(CC) -o $@ $(CFLAGS) $< $(OBJS)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<
