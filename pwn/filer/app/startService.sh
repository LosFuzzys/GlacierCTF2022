#!/bin/bash
while true; do
	timeout -k 30 1d socat TCP-LISTEN:1337,nodelay,reuseaddr,fork EXEC:"stdbuf -i0 -o0 -e0 ./FILE-er"
done
