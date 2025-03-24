#!/bin/sh

networkstatus=$(nmcli -t -f STATE g)

if [ "$networkstatus" = "connected" ]; then
   echo "󰖩" 
fi

