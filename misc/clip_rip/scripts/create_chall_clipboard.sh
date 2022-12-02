#!/bin/bash

file=challenge_clipboard
cp_file=$HOME/chall/bart_chalkboard_gags.txt

pass glacierctf/flag1 | wlclipmgr store --page $file

for _ in {0..5}; do
    while read -r line; do
        echo -n "$line" | wlclipmgr store --page $file
    done < $cp_file
done

argv0="clipboard-password-redact"
exec -a "$argv0" bash <<<"trap 'kill %1' TERM; sleep 2 & wait" &
copy_secure_pid=$!

pass glacierctf/flag2 | \
    wlclipmgr store --page $file --block $argv0:2

kill $copy_secure_pid
