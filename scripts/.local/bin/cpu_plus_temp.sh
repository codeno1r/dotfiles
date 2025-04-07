#!/bin/bash

# --- CPU Usage ---
get_cpu_usage() {
  read cpu user nice system idle iowait irq softirq steal guest guest_nice </proc/stat
  total=$((user + nice + system + idle + iowait + irq + softirq + steal))
  idle_all=$((idle + iowait))
  echo "$total $idle_all"
}

# --- CPU Temp from sensors ---
get_cpu_temp() {
  # Try common identifiers in order
  temp=$(sensors | grep -m 1 -E 'Package id 0|Tctl|Tdie|Core 0|CPU Temperature' |
    grep -oE '[+-]?[0-9]+(\.[0-9]+)?°C' |
    head -n1 | tr -d '+°C')

  if [[ -z "$temp" ]]; then
    echo "N/A"
  else
    # Trim decimal if it's ".0"
    temp=${temp%.*}
    echo "$temp"
  fi
}

# --- Persistent cache for CPU usage tracking ---
CACHE="/tmp/.cpu_stat_cache"

if [ ! -f "$CACHE" ]; then
  get_cpu_usage >"$CACHE"
  echo "CPU: 0% | Temp: $(get_cpu_temp)°C"
  exit 0
fi

read -r prev_total prev_idle <"$CACHE"
read -r curr_total curr_idle < <(get_cpu_usage)
echo "$curr_total $curr_idle" >"$CACHE"

delta_total=$((curr_total - prev_total))
delta_idle=$((curr_idle - prev_idle))

if [ "$delta_total" -ne 0 ]; then
  usage=$(((100 * (delta_total - delta_idle)) / delta_total))
else
  usage=0
fi

temp="$(get_cpu_temp)"

echo "  ${usage}% |  ${temp}°C"
