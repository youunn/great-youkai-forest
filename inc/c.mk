MAKEFLAGS   += -rR

ifndef problems
problems    = a
endif

cc          = gcc
ifndef cflags
cflags      = --std=gnu11
endif
build_dir   = build
test_dir    = test

name        = main

.PHONY: default
default: clean

.PHONY: clean rm
clean:
	rm -rf $(build_dir)
rm:
	rm -rf $(build_dir) $(test_dir)

.PHONY: new
new: $(name).c
%.c:
	cp ../../tpl/a.c $@

.PHONY: $(problems)
$(problems): %: $(build_dir)/%
$(build_dir)/%: %.c | $(build_dir)
	$(cc) $(cflags) $< -o $@
$(build_dir):
	@mkdir -p $@

.PHONY: pre
pre: $(test_dir)/$(name)_1.in.txt
$(test_dir)/$(name)_1.in.txt:
	@../../bin/receive -o $(name)

.PHONY: $(problems)-test
case = 1
$(problems)-test: %-test: $(build_dir)/%
	@cat ./$(test_dir)/$*_$(case).in.txt |\
	  $< |\
	  diff - -auN ./$(test_dir)/$*_$(case).out.txt
	@echo $*_$(case) passed

.PHONY: $(problems)-copy
$(problems)-copy: %-copy: %.c
	cat $< | wl-copy
