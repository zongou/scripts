#!/bin/sh
## [Shell Command Language] (https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
set -eu

SCRIPT_NAME=$(basename "$0")

msg() { printf '%s\n' "$@" >&2; }
err() { msg "${SCRIPT_NAME}:error:$@"; }

run() {
	if test $# -gt 0; then
		file="$1"
		shift
		case "${file}" in
		*.c)
			if command -v cc >/dev/null; then
				cc "${file}" -o "${TMPDIR}/a.out" && "${TMPDIR}/a.out" "$@"
			else
				exec zig run -target $(uname -m)-linux-musl -lc -static "${file}" -- "$@"
			fi
			;;
		*.cpp)
			if command -v c++ >/dev/null; then
				c++ "${file}" -o "${TMPDIR}/a.out" && "${TMPDIR}/a.out" "$@"
			else
				exec zig run -target $(uname -m)-linux-musl -lc++ -static "${file}" -- "$@"
			fi
			;;
		*.zig)
			exec zig run "${file}" -- "$@"
			;;
		*.go)
			exec go run "${file}" -- "$@"
			;;
		*.r) ;;
		*) err "Unrecognized file '${file}'" ;;
		esac
	else
		show_help
		exit 1
	fi
}

show_help() {
	msg "help info"
}

main() {
	if test $# -gt 0; then
		while test $# -gt 0; do
			case "$1" in
			--help)
				show_help
				break
				;;
			*)
				run "$@"
				break
				;;
			esac
		done
	else
		show_help
	fi
}

main "$@"
