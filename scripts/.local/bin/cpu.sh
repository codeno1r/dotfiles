#!/bin/sh

# Read the first line of /proc/stat
read cpu user nice system idle iowait irq softirq steal guest guest_nice </proc/stat

# Calculate total and idle CPU time
total=$((user + nice + system + idle + iowait + irq + softirq + steal))
used=$((total - idle))

# Ensure proper rounding up
cpu_usage=$(((100 * used + total - 1) / total))

# Prevent 0% from appearing, always show at least 1%
[ "$cpu_usage" -eq 0 ] && cpu_usage=1

# Print output
echo "  ${cpu_usage}%"
