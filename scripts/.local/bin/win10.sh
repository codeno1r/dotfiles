#!/bin/sh

virsh --connect=qemu:///system start win10 && virt-manager --connect qemu:///system --show-domain-console win10
# virt-manager --connect qemu:///system --show-domain-console win10
