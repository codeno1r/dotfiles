#!/bin/sh

export PATH="/usr/local/bin:/usr/bin:/bin"

case $BLOCK_BUTTON in
1)
  pavucontrol
  pkill -RTMIN+10 "${STATUSBAR:-dwmblocks}"
  ;;
2) wpctl set-mute @DEFAULT_SINK@ toggle ;;
3) notify-send " Volume module" "\- Shows volume ,  if muted.
- Middle click to mute.
- Scroll to change." ;;
4) wpctl set-volume @DEFAULT_SINK@ 1%+ ;;
5) wpctl set-volume @DEFAULT_SINK@ 1%- ;;
6) setsid -f "$TERMINAL" -e "$EDITOR" "$0" ;;
esac

vol="$(wpctl get-volume @DEFAULT_AUDIO_SINK@)"

# Check mute status
if printf '%s\n' "$vol" | grep -q '\[MUTED\]'; then
  echo ""
  exit
fi

# Extract numeric volume, e.g. "Volume: 0.50" → 50
vol="$(printf "%.0f" "$(echo "$vol" | awk '{ print $2 * 100 }')")"

# Pick icon based on volume level
if [ "$vol" -eq 0 ]; then
  icon=""
elif [ "$vol" -le 65 ]; then
  icon=""
else
  icon=""
fi

echo "$icon $vol%"
