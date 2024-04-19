#!/bin/sh
set -eu

printf "%s" "Language: "
read -r lang

case $lang in
sh)
	sh sh/demo.sh --help
	;;
c)
	zig run -target aarch64-linux-musl -lc -static c/demo.c -- a b c
	;;
go)
	# tinygo build -no-debug go/demo.go
	tinygo run go/demo.go -- -f1 aa -f2 bb -f3 cc
	;;
rust) ;;
zig)
	zig run zig/src/main.zig
	;;
esac
