#!/bin/sh
set -eu

readkey() {
	while test -t 0; do
		stty_state=$(stty -g)
		stty raw
		stty -echo
		keycode=$(dd bs=8 conv=sync count=1 </dev/tty 2>/dev/null)
		stty "${stty_state}"

		keycode_b64=$(printf "%s" "${keycode}" | base64)
		case "${keycode_b64}" in
		G1tB) echo up ;;
		G1tC) echo down ;;
		G1tE) echo left ;;
		G1tD) echo right ;;
		DQ==) echo enter ;;
		Aw==) echo "C-c" && exit ;;
		*) printf "keycode_b64=%s\n" "${keycode_b64}" ;;
		esac
		exit
	done
}

main() {
	FILE="$1"

	while true; do
		FILE=$(rclone lsf "${FILE}" | gum filter)
		key=$(readkey)
		case "${key}" in
		left) FILE="$1" ;;
		right) ;;
		C-c)
			echo C-c ok
			exit
			;;
		esac
		echo "${key}"
	done
}

# main "$@"

print_selection() {
	select_index="$1"
	shift

	argc=$#
	argi=1

	for opt in "$@"; do
		if test argi -eq ${select_index}; then
			printf ">"
		else
			printf " "
		fi

		printf " %s\n" "${opt}"
		argi=$((argi + 1))
	done
}

choose() {
	index=1
	print_selection ${index} "$@"

	while true; do
		key=$(readkey)
		case "${key}" in
		up)
			if test "${index}" -eq 1; then
				index=$#
			else
				index=$((index - 1))
			fi
			;;
		down)
			if test "${index}" -eq $#; then
				index=1
			else
				index=$((index + 1))
			fi
			;;
		enter)
			echo ${index}
			exit
			;;
		esac

		reset
		print_selection ${index} "$@"
	done
}

choose a b c
