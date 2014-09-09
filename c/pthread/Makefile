CC			= g++
CFLAGS		= -c -Wall
LDFLAGS		= -lpthread
SOURCES		= $(wildcard *.cpp)
INCLUDES	= -I.
OBJS		= $(patsubst %.cpp, %.o, $(SOURCES))
TARGET		= target

all: $(TARGET)

$(TARGET): $(OBJS) 
		$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o : %.cpp
		$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY : clean
clean:
		rm -rf $(OBJS) $(TARGET)
