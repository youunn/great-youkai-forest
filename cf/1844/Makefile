rustc       = rustc
rustc_flags = -g --edition 2021
name        = main
case        = 1

.PHONY: default
default:
	@echo do nothing

%.o: %.rs
	$(rustc) $(rustc_flags) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.in.txt *.out.txt

.PHONY: new
new:
	cp ../../tpl/a.rs $(name).rs

.PHONY: test
test: $(name).o
	cat ./$(name)_$(case).in.txt | ./$(name).o | diff - -auN ./$(name)_$(case).out.txt
