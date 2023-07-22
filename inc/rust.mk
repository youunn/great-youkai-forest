MAKEFLAGS   += -rR

ifndef problems
problems    = a
endif

rustc       = rustc
ifndef rustc_flags
rustc_flags = -g --edition 2021 --cfg sdm
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
	@../../bin/receive -o $(name)

.PHONY: $(problems)-test
case = 1
$(problems)-test: %-test: $(build_dir)/%
	@cat ./$(test_dir)/$*_$(case).in.txt |\
	  $< |\
	  diff - -auN ./$(test_dir)/$*_$(case).out.txt
	@echo $*_$(case) passed

.PHONY: $(problems)-copy $(problems)-copy-cmp
$(problems)-copy: %-copy: %.rs
	@(cat $<; \
	  echo ""; \
	  echo "#[cfg(not(sdm))]"; \
	  echo "#[allow(dead_code)]"; \
	  echo "mod cp {"; \
	  echo "pub mod io {"; \
	  cat ../../lib/cp/io.rs; \
	  echo "}"; \
	  echo "}"; \
	) | wl-copy
	@echo added $< to clipboard
$(problems)-copy-cmp: %-copy-cmp: %.rs
	@(cat $<; \
	  echo ""; \
	  echo "#[cfg(not(sdm))]"; \
	  echo "#[allow(dead_code)]"; \
	  echo "mod cp {"; \
	  echo "pub mod io {"; \
	  cat ../../lib/cp/io.rs; \
	  echo "}"; \
	  echo ""; \
	  echo "pub mod cmp {"; \
	  cat ../../lib/cp/cmp.rs; \
	  echo "}"; \
	  echo "}"; \
	) | wl-copy
	@echo added $< to clipboard
