#!/bin/sh

flameshot gui --path=/home/noir/Pictures/FlameShot/ && xclip -selection clipboard -t image/png < $(ls -t /home/noir/Pictures/FlameShot/* | head -n 1)
