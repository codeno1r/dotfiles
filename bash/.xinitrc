nm-applet &
blueman-applet &
noisetorch -i &
dwmblocks &
# xrandr --output eDP-1 --mode 1920x1080  --output HDMI-1 --mode 1920x1080 --above eDP-1 &
# xrandr --output DP-0 --mode 1920x1080 --rate 165 &
xrandr --output DP-0 --mode 3440x1440 --rate 180 &
picom --config .config/picom/picom.conf &
feh --bg-fill .config/dwm/moonlight.jpg &
dunst &
numlockx on &

xset s off
xset -dpms
xset s noblank

exec dwm
