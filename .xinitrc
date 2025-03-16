dwmblocks &
xrandr --output eDP-1 --mode 1920x1080 --output HDMI-1 --mode 1920x1080 --above eDP-1 &
picom --config ~/.config/picom/picom.conf &
feh --bg-scale .config/dwm/uwp4497347.jpeg &
dunst &
exec dwm
