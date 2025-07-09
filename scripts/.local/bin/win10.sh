#!/bin/sh

# virsh --connect=qemu:///system start win10 && virt-viewer --connect qemu:///system --full-screen win10
virsh --connect=qemu:///system start win11 && virt-manager --connect qemu:///system --show-domain-console win11
# virt-manager --connect qemu:///system --show-domain-console win10
