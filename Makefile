CC = g++
CFLAGS = -O3 -fomit-frame-pointer -fexpensive-optimizations -ffast-math
VFLAGS = --std=c++17
LDFLAGS = -pthread
CDFLAGS = -g -pg
TARGET = a.exe
DTARGET = d_a.exe
WARNINGS = -Wall -Weffc++ -Wextra -Winit-self -Wzero-as-null-pointer-constant -Wnon-virtual-dtor -Winline -Wmissing-declarations -Wmissing-include-dirs -Wundef -Wredundant-decls -Wfloat-equal -Wmain -Wunreachable-code -Wshadow -Wcast-align -Wswitch-default -Wswitch-enum
CPP = main.cpp

all:
	$(CC) $(WARNINGS) $(VFLAGS) $(CFLAGS) $(CPP) $(LDFLAGS) -o $(TARGET)

debug:
	$(CC) $(WARNINGS) $(VFLAGS) $(CDFLAGS) $(CPP) $(LDFLAGS) -o $(DTARGET)

clean:
	rm -rf $(TARGET) $(DTARGET)
