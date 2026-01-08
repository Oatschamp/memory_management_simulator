CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Isrc -Isrc/allocator -Isrc/buddy -Isrc/cache -Isrc/virtual_memory

SRCS = \
	src/main.cpp \
	src/memory_manager.cpp \
	src/physical_memory.cpp \
	src/statistics.cpp \
	src/buddy/buddy_allocator.cpp \
	src/cache/cache_level.cpp \
	src/virtual_memory/virtual_memory_manager.cpp

TARGET = memsim

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
