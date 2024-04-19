#!/bin/sh

while read -rsn1 input; do
	case "$input" in
	"$(printf '\x1B')") # ESC ASCII code (https://dirask.com/posts/ASCII-Table-pJ3Y0j)
		read -rsn1 -t 0.1 input
		if [ "$input" = "[" ]; then
			read -rsn1 -t 0.1 input
			case "$input" in
			A) echo '[Arrow Up]' ;;
			B) echo '[Arrow Down]' ;;
			C) echo '[Arrow Righ]' ;;
			D) echo '[Arrow Left]' ;;
			esac
		fi
		read -rsn5 -t 0.1 # flushing stdin
		;;
	q) # q letter
		break
		;;
	*) # other letters
		echo "$input"
		;;
	esac
done
