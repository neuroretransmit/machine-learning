PROJECT := ml

include mk/directories.mk
include mk/binaries.mk
include mk/sources.mk
include mk/objects.mk
include mk/libs.mk
include mk/compiler.mk

all: $(LIBRARY) tests 

tests: $(TESTBINARY)
	./$<

$(LIBRARY): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -shared $(LIBS) -o $@

$(OBJECTS): $(OBJDIR)%.o: $(SRCDIR)%.cc
	@mkdir -p $(@D)
	$(CXX) $< -c -o $@

$(TESTBINARY): $(OBJECTS) $(TESTOBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(TESTCFLAGS) $^ $(LIBS) $(TESTLIBS) -o $@

$(TESTOBJECTS): $(TESTOBJDIR)%.o: $(TESTSRCDIR)%.cc
	@mkdir -p $(@D)
	$(CXX) $< -c -o $@

run: $(TESTBINARY)
	./$<

run-valgrind: $(TESTBINARY)
	valgrind --leak-check=full ./$<

clean:
	rm -rf $(BINDIR) $(OBJDIR) $(LIBDIR)

# Use for debugging makefile variables
#   $ make print-SOME_VAR
print-%  : ; @echo $* = $($*)

