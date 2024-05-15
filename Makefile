.PHONY: ALL clean CHECKED_TARGETS RELEASE_TARGETS test test.contact
.PHONY: testreport testreport.contact model-checks docs

GCOV=gcov

COMMON_CFLAGS=-std=c18 $(COMMON_INCLUDES) -Wall -Werror -Wextra -Wpedantic

CHECKED_CC=$(CC)
CHECKED_CFLAGS=$(COMMON_CFLAGS) -fPIC -O0 --coverage

RELEASE_CC=$(CC)
RELEASE_CFLAGS=$(COMMON_CFLAGS) -fPIC -O2

BUILD_DIR=$(CURDIR)/build
CHECKED_BUILD_DIR=$(BUILD_DIR)/checked
RELEASE_BUILD_DIR=$(BUILD_DIR)/release

LIBCONTACT.CHECKED=$(CHECKED_BUILD_DIR)/libcontact.a
LIBCONTACT.RELEASE=$(RELEASE_BUILD_DIR)/libcontact.a
LIBCONTACT_CHECKED_BUILD_DIR=$(CHECKED_BUILD_DIR)/libcontact
LIBCONTACT_RELEASE_BUILD_DIR=$(RELEASE_BUILD_DIR)/libcontact

SRCDIR=$(CURDIR)/src
LIBCONTACT_SRCDIR=$(SRCDIR)/libcontact
LIBCONTACT_DIRS=$(LIBCONTACT_SRCDIR)
LIBCONTACT_SOURCES=$(foreach d,$(LIBCONTACT_DIRS),$(wildcard $(d)/*.c))
LIBCONTACT_STRIPPED_SOURCES=$(patsubst $(SRCDIR)/%,%,$(LIBCONTACT_SOURCES))
LIBCONTACT_CHECKED_DIRS=$(LIBCONTACT_CHECKED_BUILD_DIR)
LIBCONTACT_CHECKED_OBJECTS= \
    $(patsubst %.c,$(CHECKED_BUILD_DIR)/%.o,\
        $(LIBCONTACT_STRIPPED_SOURCES))
LIBCONTACT_RELEASE_DIRS=$(LIBCONTACT_RELEASE_BUILD_DIR)
LIBCONTACT_RELEASE_OBJECTS= \
    $(patsubst %.c,$(RELEASE_BUILD_DIR)/%.o,\
        $(LIBCONTACT_STRIPPED_SOURCES))

CHECKED_OBJECTS=$(LIBCONTACT_CHECKED_OBJECTS)

TESTDIR=$(CURDIR)/test
TESTDIRS=$(TESTDIR)/libcontact
TEST_BUILD_DIR=$(BUILD_DIR)/test
TEST_DIRS=$(patsubst $(TESTDIR)/%,$(TEST_BUILD_DIR)/%,$(TESTDIRS))
TEST_SOURCES=$(foreach d,$(TESTDIRS),$(wildcard $(d)/*.cpp))
STRIPPED_TEST_SOURCES=$(patsubst $(TESTDIR)/%,%,$(TEST_SOURCES))
TEST_OBJECTS=$(patsubst %.cpp,$(TEST_BUILD_DIR)/%.o,$(STRIPPED_TEST_SOURCES))
TESTCONTACT=$(TEST_BUILD_DIR)/testcontact

RELEASE_CXXFLAGS=-std=c++20 $(COMMON_CXXFLAGS) -O2
TEST_CXXFLAGS=$(RELEASE_CXXFLAGS) $(TEST_INCLUDES) $(COMMON_INCLUDES)

COVERAGE_REPORT_DIR=$(TEST_BUILD_DIR)/coverage-report
LIBCONTACT_REPORT_FILES=\
    $(patsubst %.c,$(COVERAGE_REPORT_DIR)/%.c.gcov,\
        $(LIBCONTACT_STRIPPED_SOURCES))
REPORT_FILES=$(LIBCONTACT_REPORT_FILES)

MINUNIT_PATH=$(HOME)/apps/minunit
MINUNIT_INCLUDE=-I $(MINUNIT_PATH)/include
MINUNIT_LINK=-L $(MINUNIT_PATH)/lib -lminunit

INCLUDE_DIR=$(PWD)/include
COMMON_INCLUDES=-I $(INCLUDE_DIR)
TEST_INCLUDES=$(MINUNIT_INCLUDE)

DOC_BUILD_DIR=$(BUILD_DIR)/docs
DOCDIR=$(CURDIR)/docs
PANDOC?=pandoc
XELATEX?=pdflatex

ALL: CHECKED_TARGETS RELEASE_TARGETS

clean:
	rm -rf $(BUILD_DIR)

model-checks:
	(cd models && $(MAKE))

test: $(TEST_DIRS) CHECKED_TARGETS test.contact

test.contact: CHECKED_TARGETS $(TESTCONTACT)
	find $(BUILD_DIR) -type f -name "*.gcda" -exec rm {} \; -print
	$(TESTCONTACT)

testreport: testreport.contact

testreport.contact: $(TEST_DIRS) test.contact $(REPORT_FILES)

$(COVERAGE_REPORT_DIR)/%.c.gcov: $(SRCDIR)/%.c test.contact
	mkdir -p $(dir $@)
	(cd $(dir $@) && \
		$(GCOV) -o $(dir $(CHECKED_BUILD_DIR)/$*.o) $<)

$(TESTCONTACT): $(CHECKED_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(TEST_CXXFLAGS) \
	    -o $@ $(TEST_OBJECTS) \
	    $(CHECKED_OBJECTS) -lpthread \
	    $(MINUNIT_LINK) \
	    --coverage

$(TEST_BUILD_DIR)/%.o: $(TESTDIR)/%.cpp $(INCLUDES)
	$(CXX) $(TEST_CXXFLAGS) -c -o $@ $<

CHECKED_TARGETS: $(LIBCONTACT_CHECKED_DIRS) $(LIBCONTACT.CHECKED)

RELEASE_TARGETS: $(LIBCONTACT_RELEASE_DIRS) $(LIBCONTACT.RELEASE)

$(CHECKED_BUILD_DIR) $(RELEASE_BUILD_DIR) $(TEST_DIRS):
	mkdir -p $@

$(LIBCONTACT.CHECKED) : $(LIBCONTACT_CHECKED_OBJECTS)
	$(AR) rcs $@ $(LIBCONTACT_CHECKED_OBJECTS)

$(LIBCONTACT_CHECKED_DIRS): $(CHECKED_BUILD_DIR)
	mkdir -p $@

$(CHECKED_BUILD_DIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(CHECKED_CC) $(CHECKED_CFLAGS) -c -o $@ $<

$(LIBCONTACT.RELEASE) : $(LIBCONTACT_RELEASE_OBJECTS)
	$(AR) rcs $@ $(LIBCONTACT_RELEASE_OBJECTS)

$(LIBCONTACT_RELEASE_DIRS): $(RELEASE_BUILD_DIR)
	mkdir -p $@

$(RELEASE_BUILD_DIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(RELEASE_CC) $(RELEASE_CFLAGS) -c -o $@ $<

docs: $(DOC_BUILD_DIR)/dangerform_contact_talk.pdf

$(DOC_BUILD_DIR)/dangerform_contact_talk.pdf: $(DOC_BUILD_DIR)
$(DOC_BUILD_DIR)/dangerform_contact_talk.pdf: $(DOCDIR)/dangerform_contact_talk.md
	$(PANDOC) -f "markdown_strict+yaml_metadata_block" -T beamer \
	    --slide-level 2 $< -o $(DOC_BUILD_DIR)/dangerform_contact_talk.tex
	(cd $(DOC_BUILD_DIR) && $(XELATEX) dangerform_contact_talk.tex)
	(cd $(DOC_BUILD_DIR) && $(XELATEX) dangerform_contact_talk.tex)

$(DOC_BUILD_DIR):
	mkdir -p $(DOC_BUILD_DIR)
