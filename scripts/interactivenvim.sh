#!/bin/bash

# Capture the selected files from fzf
selected_files=$(fzf -m --preview="bat --color=always {}")

# Check if fzf returned anything
if [[ -z "$selected_files" ]]; then
    exit 0  # Exit the script if nothing is selected
fi

# Open selected files in Neovim
nvim $selected_files

