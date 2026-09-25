CC:= g++
CFLAGS:= -std=c++20 -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lSDL3

TARGET=build\GameOfLife.exe
SRC=*.cpp

$(TARGET) : $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	@$(TARGET) 

clean:
	@del  $(TARGET)


