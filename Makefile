# hemlock-codex: SFT dataset generation and verification.

HEMLOCK_REPO ?= $(HOME)/Projects/hemlock
HEMLOCK      := $(HEMLOCK_REPO)/hemlock
HEMLOCKC     := $(HEMLOCK_REPO)/hemlockc
STDLIB_DIR   := hemlock/stdlib
SEED_FILES   := $(shell find $(STDLIB_DIR) -name '*.hml' 2>/dev/null | sort)

.PHONY: all sft stdlib check-stdlib-seeds clean help

all: sft stdlib

sft:
	python3 generate_sft.py

stdlib: check-stdlib-seeds
	python3 generate_stdlib_sft.py

# Parity-first: every stdlib seed must produce byte-identical output under
# the interpreter and the compiled binary. Fails fast on the first mismatch.
check-stdlib-seeds:
	@if [ ! -x "$(HEMLOCK)" ] || [ ! -x "$(HEMLOCKC)" ]; then \
	  echo "error: $(HEMLOCK) or $(HEMLOCKC) not found or not executable."; \
	  echo "       Build them with: (cd $(HEMLOCK_REPO) && make all)"; \
	  exit 2; \
	fi
	@pass=0; fail=0; failed_files=""; \
	for f in $(SEED_FILES); do \
	  i=$$(timeout 15 $(HEMLOCK) $$f 2>&1); \
	  bin=$$(mktemp); \
	  timeout 20 $(HEMLOCKC) $$f -o $$bin >/dev/null 2>&1; \
	  if [ -x $$bin ]; then c=$$(timeout 15 $$bin 2>&1); else c="[compile failed]"; fi; \
	  rm -f $$bin; \
	  if [ "$$i" = "$$c" ]; then \
	    pass=$$((pass + 1)); \
	    printf "  [OK]       %s\n" "$$f"; \
	  else \
	    fail=$$((fail + 1)); \
	    failed_files="$$failed_files $$f"; \
	    printf "  [MISMATCH] %s\n" "$$f"; \
	    printf "    INTERP : %s\n" "$$(echo "$$i" | head -3 | tr '\n' '|')"; \
	    printf "    COMPILE: %s\n" "$$(echo "$$c" | head -3 | tr '\n' '|')"; \
	  fi; \
	done; \
	echo ""; \
	echo "  $$pass passed, $$fail failed"; \
	if [ $$fail -gt 0 ]; then exit 1; fi

clean:
	rm -f hemlock_codex_sft.jsonl hemlock_codex_stdlib_sft.jsonl

help:
	@echo "Targets:"
	@echo "  sft                 Generate hemlock_codex_sft.jsonl (translation + generation)"
	@echo "  stdlib              Verify stdlib seeds, then generate hemlock_codex_stdlib_sft.jsonl"
	@echo "  check-stdlib-seeds  Run every stdlib/**/*.hml through interpreter AND compiler,"
	@echo "                      fail on any interpreter/compiler output mismatch"
	@echo "  all                 sft + stdlib"
	@echo "  clean               Remove generated JSONL files"
	@echo ""
	@echo "Variables:"
	@echo "  HEMLOCK_REPO        Path to hemlock repo root (default: ~/Projects/hemlock)"
