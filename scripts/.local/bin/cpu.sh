#!/bin/bash

# Function to get current CPU stats
get_cpu_usage() {
  read cpu user nice system idle iowait irq softirq steal guest guest_nice < /proc/stat
  total=$((user + nice + system + idle + iowait + irq + softirq + steal))
  idle_all=$((idle + iowait))
  echo "$total $idle_all"
}

# Temp file to store previous CPU values
CACHE="/tmp/.cpu_stat_cache"

# First-time run: initialize cache and output placeholder
if [ ! -f "$CACHE" ]; then
  get_cpu_usage > "$CACHE"
  echo "CPU: 0%"
  exit 0
fi

# Read previous and current CPU stats
read -r prev_total prev_idle < "$CACHE"
read -r curr_total curr_idle < <(get_cpu_usage)

# Save current stats for next call
echo "$curr_total $curr_idle" > "$CACHE"

# Calculate deltas
delta_total=$((curr_total - prev_total))
delta_idle=$((curr_idle - prev_idle))

# Compute CPU usage
if [ "$delta_total" -ne 0 ]; then
  usage=$(( (100 * (delta_total - delta_idle)) / delta_total ))
else
  usage=0
fi

# Output for dwmblocks
echo "  $usage%"
