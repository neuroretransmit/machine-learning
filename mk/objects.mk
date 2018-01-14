OBJECTS := $(shell echo $(SOURCES:.cc=.o) | sed 's/src/obj/g')
TESTOBJECTS := $(shell echo $(TESTSOURCES:.cc=.o) | sed 's/$(TESTSRCDIR)/$(OBJDIR)\/$(TESTSRCDIR)/g')
