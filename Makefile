chash: src/* include/*
	cc src/chash.c -o chash -std=c17 -Iinclude

check:
	clang-tidy src/* -checks='*,-llvm-header-guard' -- -std=c17 -Iinclude
	clang-format src/* --style=LLVM --dry-run -Werror

fix:
	clang-tidy src/* -checks='*,-llvm-header-guard' --fix -- -std=c17 -Iinclude
	clang-format src/* --style=LLVM -i
