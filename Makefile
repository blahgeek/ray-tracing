TARGET = ray-tracing

OBJ_DIR = build
INCLUDE_DIR = -I. -I/usr/include/opencv
CXXFLAGS = $(INCLUDE_DIR) -std=c++11 -O2 -fopenmp
LINKOPENCV = -lopencv_core -lopencv_highgui
LINKFLAGS = -lpng -std=c++11 -fopenmp

CXX = g++
CXXSOURCES = $(shell find src -name "*.cpp")
OBJS = $(addprefix $(OBJ_DIR)/,$(CXXSOURCES:.cpp=.o))
DEPFILES = $(OBJS:.o=.d)

.PHONY: all clean
all: $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.d: %.cpp
	@mkdir -pv $(dir $@)
	$(CXX) $(INCLUDE_DIR) -std=c++11 -MM -MT "$(OBJ_DIR)/$(<:.cpp=.o) $(OBJ_DIR)/$(<:.cpp=.d)" "$<"  > "$@"

sinclude $(DEPFILES)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LINKFLAGS) $(LINKOPENCV)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
