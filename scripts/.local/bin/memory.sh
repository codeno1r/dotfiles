#!/bin/sh

# Read memory info from /proc/meminfo, strip the "kB" suffix using awk
memtotal=$(grep MemTotal /proc/meminfo | awk '{print $2}')
memfree=$(grep MemAvailable /proc/meminfo | awk '{print $2}')
swaptotal=$(grep SwapTotal /proc/meminfo | awk '{print $2}')
swapfree=$(grep SwapFree /proc/meminfo | awk '{print $2}')

# Convert to MB (adding 512 ensures proper rounding)
mem_total=$(((memtotal + 512) / 1024))
mem_free=$(((memfree + 512) / 1024))
swap_total=$(((swaptotal + 512) / 1024))
swap_free=$(((swapfree + 512) / 1024))

# Calculate used memory and swap
mem_used=$((mem_total - mem_free))
swap_used=$((swap_total - swap_free))

# Combine total memory and swap usage
total_used=$((mem_used + swap_used))

# Format to two significant digits
if [ "$total_used" -ge 1000 ]; then
  total_used="$((total_used / 1000))GB" # Convert to GB if >= 1000MB
#elif [ "$total_used" -ge 100 ]; then
#    total_used="${total_used}MB"  # Keep three digits for 100-999 MB
else
  total_used="${total_used}MB" # Keep two digits for < 100 MB
fi

# Print output
echo " ${total_used}"
