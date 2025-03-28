#!/bin/bash

# Get the list of connected sinks (audio output devices)
connected_sinks=$(wpctl status | grep "Sinks" -A 10)

# Check if the headset is plugged in
if echo "$connected_sinks" | grep -q "Poly Blackwire 3320 Series"; then
    # Switch to the headset output (replace "headset" with the exact device name of your headset)
    wpctl set-default sink "$(echo "$connected_sinks" | grep 'Poly Blackwire 3320 Series' | awk '{print $1}')"
else
    # If the headset is not plugged in, switch to the default speakers (replace "speakers" with the exact device name of your speakers)
    wpctl set-default sink "$(echo "$connected_sinks" | grep 'Family 17h/19h/1ah HD Audio Controller' | awk '{print $1}')"
fi

