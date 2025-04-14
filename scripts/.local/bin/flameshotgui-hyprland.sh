#!/bin/sh

# Disable Hyprland animations
hyprctl --batch 'keyword animations:enabled false'

# flameshot gui --path=/home/codenoir/Pictures/FlameShot/ && xclip -selection clipboard -t image/png <$(ls -t /home/codenoir/Pictures/FlameShot/* | head -n 1) &
flameshot gui -r | tee ~/Pictures/FlameShot/$(date +'%Y-%m-%d_%H-%M-%S').png | wl-copy

# Enable Hyprland animations
hyprctl --batch 'keyword animations:enabled true'
