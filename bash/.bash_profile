# ~/.bash_profile

export XDG_CONFIG_HOME="$HOME/.config"
export QT_QPA_PLATFORMTHEME=qt5ct
export QT_QPA_PLATFORMTHEME=qt6ct
export PATH=$HOME/.local/bin:$PATH
export PATH="$HOME/depot_tools:$PATH"
export PATH=/opt/WebWork\ Tracker:$PATH
# export GDK_BACKEND=x11

startx

# if uwsm check may-start; then
#   exec uwsm start hyprland.desktop
# fi

# # Start Hyprland automatically on TTY1
# if [[ -z $DISPLAY ]] && [[ $(tty) == /dev/tty1 ]]; then
#   exec Hyprland
# fi

# # Start Hyprland automatically on TTY1
# if [[ -z $DISPLAY ]] && [[ $(tty) == /dev/tty1 ]]; then
#   # Ensure a D-Bus session is running for user services like xdg-desktop-portal
#   exec dbus-run-session Hyprland
# fi
