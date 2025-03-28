dwmblocks &
xrandr --output eDP-1 --mode 1920x1080  --output HDMI-1 --mode 1920x1080 --above eDP-1 &
picom --config .config/picom/picom.conf &
feh --bg-scale dwm/isolated-house.jpg &
dunst &

# eval $(/usr/bin/gnome-keyring-daemon --start --components=pkcs11,secrets,ssh,gpg)
# export SSH_AUTH_SOCK
# eval $(dbus-launch --sh-syntax --exit-with-session)
# export XDG_SESSION_TYPE=x11
# export XDG_SESSION_DESKTOP=dwm

exec dwm
