#!/bin/sh

nordstatus=$(nordlayer status --silent | grep VPN | sed s/"VPN: "//)

if [ "$nordstatus" = "Connected" ]; then
  echo '{"icon": "󰳌"}'
fi
