#!/bin/sh
## [Shell Command Language] (https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
set -eu

SCRIPT_NAME=$(basename "$0")

msg() { printf '%s\n' "$@" >&2; }
err() { msg "${SCRIPT_NAME}:error:$@"; }

show_help() {
	msg "help info"
}

main() {
	if test $# -gt 0; then
		while test $# -gt 0; do
			case "$1" in
			--help)
				show_help
				shift
				;;
			*)
				err "Unknown argument: '$1'"
				exit 1
				;;
			esac
		done
	else
		show_help
	fi
}

main "$@"
