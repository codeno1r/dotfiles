#!/bin/sh

# current brightness
curr_brightness=$(brightnessctl g)

# max_brightness
max_brightness=$(brightnessctl m)

# brightness percentage
brightness_per=$((100 * curr_brightness / max_brightness))

case $BLOCK_BUTTON in
    1) 
        ;;
    3) 
        notify-send "󰃞 Brightness module" "\- Shows current brightness level ☀️." 
        ;;
    6) 
        setsid -f "$TERMINAL" -e "$EDITOR" "$0"
        ;;
esac

echo "󰃞 ${brightness_per}%"
