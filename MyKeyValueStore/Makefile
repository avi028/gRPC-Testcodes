CC = g++  
TARGET = MyCache
INCLUDES = storage.h MyCache.h
OBJS = MyCache.o storage.o

all: $(OBJS) $(INCLUDES)
	$(CC) $(OBJS) -o $(TARGET) -lpthread
 
MyCache.o : MyCache.cpp $(INCLUDES)
	$(CC) -c MyCache.cpp -o $@

storage.o : storage.cc storage.h
	$(CC) -c storage.cc -o $@

clean:
	@rm -rf *.o $(TARGET)

run: 
	@./$(TARGET)