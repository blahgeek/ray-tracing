TARGET = test

OBJ_DIR = obj
INCLUDE_DIR = -I. -I/usr/include/opencv
CXXFLAGS = $(INCLUDE_DIR) -O2 -std=c++11
LINKOPENCV =  -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
LINKFLAGS = -lpng -std=c++11

CXX = g++
CXXSOURCES = $(shell find . -name "*.cpp")
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
