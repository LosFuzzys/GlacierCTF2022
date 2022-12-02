#!/bin/bash
chown pilot:pilot /app/old
chmod +x /app/old
while true; do
	su pilot -c 'timeout -k 30 1d socat TCP-LISTEN:13377,nodelay,reuseaddr,fork EXEC:"stdbuf -i0 -o0 -e0 ./old"'
done
