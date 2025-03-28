#!/bin/bash

# Get clipboard content
CLIPBOARD_TEXT=$(xclip -selection clipboard -o)

# Format snippet
SNIPPET="$CLIPBOARD_TEXT"

# Type the snippet back to the active window
xdotool type "$SNIPPET"

