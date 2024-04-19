chash: src/* include/*
	cc src/* -o chash -std=c17 -Iinclude -Wcast-qual -Werror -pthread

check:
	clang-tidy src/* -checks='*,-llvm-header-guard,-llvmlibc-restrict-system-libc-headers' -- -std=c17 -Iinclude -Wcast-qual
	clang-format src/* --style=llVM --dry-run -Werror

fix:
	clang-tidy src/* -checks='*,-llvm-header-guard,-llvmlibc-restrict-system-libc-headers' --fix -- -std=c17 -Iinclude -Wcast-qual
	clang-format src/* --style=LLVM -i
