CC			= g++
CFLAGS		= -c -Wall
LDFLAGS		=
OBJS     = event.o main.o net.o
all: server client

server: $(OBJS)
		$(CC) $(LDFLAGS) $(OBJS)  -o $@
client: client.o
		$(CC) $<  -o $@
%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean
clean:
		rm -rf  $(TARGET) $(OBJS)
