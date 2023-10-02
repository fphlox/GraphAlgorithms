# Make configuration

.RECIPEPREFIX = >

ifndef MANAGED_BUILD
	$(error This Makefile is not supposed to be called directly, use main Makefile to build the project)
endif

# Executable: s21_graph_cli

NAME = $(notdir $(CURDIR))

SOURCE_DIRECTORY = src
INCLUDE_DIRECTORIES = include $(SOURCE_ROOT)/s21_graph/include $(SOURCE_ROOT)/s21_graph_algorithms/include

BUILD_DIRECTORY = $(BUILD_ROOT)/$(NAME)
BINARY_DIRECTORY = $(BINARY_ROOT)/$(NAME)

SOURCES != find $(SOURCE_DIRECTORY) -name "*.cpp"
OBJECTS = $(SOURCES:$(SOURCE_DIRECTORY)/%.cpp=$(BUILD_DIRECTORY)/obj/%.o)

TARGET = $(BINARY_DIRECTORY)/$(NAME)

DEPENDENCIES = $(OBJECTS:.o=.d)

OBJECT_DIRECTORIES = $(sort $(dir $(OBJECTS)))

CPPFLAGS += $(addprefix -I,$(INCLUDE_DIRECTORIES))

LDLIBS += $(BINARY_ROOT)/s21_graph/s21_graph.a $(BINARY_ROOT)/s21_graph_algorithms/s21_graph_algorithms.a

# Build targets

$(TARGET): .EXTRA_PREREQS = $(BINARY_ROOT)/s21_graph/s21_graph.a $(BINARY_ROOT)/s21_graph_algorithms/s21_graph_algorithms.a
$(TARGET): $(OBJECTS) | $(BINARY_DIRECTORY)
>	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIRECTORY)/obj/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORIES)
>	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJECT_DIRECTORIES) $(BINARY_DIRECTORY):
>	mkdir -p $@

# Utility targets

mostlyclean:
>	$(RM) -r $(BUILD_DIRECTORY)

clean: mostlyclean
>	$(RM) -r $(BINARY_DIRECTORY)

# Include dependencies

-include $(DEPENDENCIES)