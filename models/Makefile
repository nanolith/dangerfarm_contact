.PHONY: ALL

MODEL_MAKEFILES?= \
	$(foreach file,\
	    $(wildcard *.mk), $(notdir $(file)))

ALL:
	$(foreach n, $(MODEL_MAKEFILES), ($(MAKE) -f $(n)) &&) true
