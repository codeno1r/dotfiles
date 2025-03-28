#
# ~/.bash_profile
#

export XDG_CONFIG_HOME="$HOME/.config"
export QT_QPA_PLATFORMTHEME=qt5ct
export QT_QPA_PLATFORMTHEME=qt6ct
export PATH=$HOME/.local/bin:$PATH
[[ -f ~/.bashrc ]] && . ~/.bashrc

startx
