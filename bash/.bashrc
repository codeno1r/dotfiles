#!/usr/bin/env bash

export LIBVIRT_DEFAULT_URI="qemu:///session"

eval "$(starship init bash)"

fastfetch

alias ll="ls -la --color=auto"
alias ff="fastfetch"
alias yi="yazi"
alias inv='interactivenvim.sh'
alias deltemp='sudo pacman -Rns $(pacman -Qdtq)'
alias mdb="mongosh mongodb+srv://cluster0.xy0sq.mongodb.net/ptadmin --apiVersion 1 --username gvarrworks --password A1APwwOLA2Z2O5ks"
