#!/bin/sh

nordstatus=$(nordlayer status --silent | grep VPN | sed s/"VPN: "//)

echo $nordstatus

if [ "$nordstatus" = "Not Connected" ] || [ "$nordstatus" = "Disconnected" ] || [ "$nordstatus" = "Failed" ]; then
    mtrgateway=$(nordlayer gateways --silent | grep MTR | sed s/'         MTR │ '// | sed s/'│'//)
    nordlayer connect $mtrgateway --silent
else
    nordlayer disconnect --silent
fi
