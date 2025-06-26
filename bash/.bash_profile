#
# ~/.bash_profile
#

export XDG_CONFIG_HOME="$HOME/.config"
# export QT_QPA_PLATFORMTHEME=qt5ct
export QT_QPA_PLATFORMTHEME=qt6ct
export PATH=$HOME/.local/bin:$PATH
export PATH=/opt/WebWork\ Tracker:$PATH

# startx

# Start Hyprland automatically on TTY1
if [[ -z $DISPLAY ]] && [[ $(tty) == /dev/tty1 ]]; then
  exec Hyprland
fi
