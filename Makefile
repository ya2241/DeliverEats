CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra

SRCS = main.cpp \
       delivery_rider.cpp \
       moped_rider.cpp \
       bicycle_rider.cpp \
       day_summary.cpp \
       file_handler.cpp \
       simulation.cpp

OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = tests.cpp \
            delivery_rider.cpp \
            moped_rider.cpp \
            bicycle_rider.cpp \
            day_summary.cpp \
            file_handler.cpp

TEST_OBJS = $(TEST_SRCS:.cpp=.o)

TARGET = deliver_eats
TEST_TARGET = run_tests

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

check: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

.PHONY: all check clean
