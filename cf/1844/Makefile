MAKEFLAGS   += -rR

problems    = a b c d e f1 f2 g h

rustc       = rustc
rustc_flags = -g --edition 2021
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
new: $(name).rs
%.rs:
	cp ../../tpl/a.rs $@

.PHONY: $(problems)
$(problems): %: $(build_dir)/%
$(build_dir)/%: %.rs | $(build_dir)
	$(rustc) $(rustc_flags) $< -o $@
$(build_dir):
	@mkdir -p $@

.PHONY: pre
pre: $(test_dir)/$(name)_1.in.txt
$(test_dir)/$(name)_1.in.txt:
	@receive -o $(name)

.PHONY: test
case = 1
test: $(build_dir)/$(name)
	@cat ./$(test_dir)/$(name)_$(case).in.txt \
	  | ./$(build_dir)/$(name) \
	  | diff - -auN ./$(test_dir)/$(name)_$(case).out.txt
