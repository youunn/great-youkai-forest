rustc       = rustc
rustc_flags = -g
name        = main

.PHONY: default
default:
	@echo do nothing

%.o: %.rs
	$(rustc) $(rustc_flags) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.ti *.to

.PHONY: new
new:
	cp ../../tpl/a.rs $(name).rs
