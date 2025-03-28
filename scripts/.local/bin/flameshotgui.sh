#!/bin/sh

flameshot gui --path=/home/codenoir/Pictures/FlameShot/ && xclip -selection clipboard -t image/png < $(ls -t /home/codenoir/Pictures/FlameShot/* | head -n 1) &
