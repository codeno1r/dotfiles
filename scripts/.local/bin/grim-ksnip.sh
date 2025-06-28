#!/bin/bash

img="/tmp/screenshot-$(date +%s).png"

grim -g "$(slurp)" "$img"

if [[ -f "$img" ]] && file "$img" | grep -q 'PNG image data'; then
  ksnip "$img" >/dev/null 2>&1

  # Copy image to clipboard explicitly as PNG
  wl-copy --type image/png <"$img"
  notify-send "Screenshot" "✅ Copied to clipboard"
else
  notify-send "Grim" "❌ Screenshot failed or invalid image"
fi
