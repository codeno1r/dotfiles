#!/bin/sh

networkstatus=$(nmcli -t -f STATE g)

if [ "$networkstatus" = "connected" ]; then
  interface=$(nmcli -t -f DEVICE,TYPE connection show --active | awk -F: '$2=="wifi" {print $1; exit}')

  if [ -n "$interface" ]; then
    ssid=$(nmcli -t -f SSID device wifi show "$interface" | sed 's/SSID://')
    echo " $ssid"
  else
    echo "ETH"
  fi
else
  echo "Disconnected"
fi
