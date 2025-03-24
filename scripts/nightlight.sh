#!/bin/bash

STATE_FILE="/tmp/nightlight_state"
MONITOR="eDP-1"

# Check if state file exists; if not, create it with default "off"
if [ ! -f "$STATE_FILE" ]; then
  echo "off" >"$STATE_FILE"
fi

# Read the current state
STATE=$(cat "$STATE_FILE")

if [ "$STATE" = "off" ]; then
  # Turn night light ON
  xrandr --output "$MONITOR" --gamma 1.0:0.6:0.6
  echo "on" >"$STATE_FILE"
  echo ""
else
  # Turn night light OFF
  xrandr --output "$MONITOR" --gamma 1:1:1
  echo "off" >"$STATE_FILE"
  echo ""
fi
