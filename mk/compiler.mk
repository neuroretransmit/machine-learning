CXXSTD := -std=c++14
WARNINGS := -Wall -Werror -Wextra
DEFINITIONS := 
CFLAGS := $(CXXSTD) $(WARNINGS) $(DEFINES) -fPIC -Iinclude
TESTCFLAGS := -pthread

ifneq (,$(findstring -DDEBUG, $(DEFINES)))
	CFLAGS += -g
endif

CXX += $(CFLAGS)
