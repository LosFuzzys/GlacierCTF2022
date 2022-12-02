#! /bin/bash

uuid=$(cat /proc/sys/kernel/random/uuid)

cp $HOME/.local/share/wlclipmgr/challenge_clipboard.gpg \
   $HOME/.local/share/wlclipmgr/$uuid.gpg

exit() {
    rm $HOME/.local/share/wlclipmgr/$uuid.gpg
}
trap exit EXIT

wlclipmgr replr --page $uuid

