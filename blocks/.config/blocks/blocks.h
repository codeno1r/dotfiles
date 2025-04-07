// Modify this file to change what commands output to your statusbar, and
// recompile using the make command.
static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/
    {"", "cpu_plus_temp.sh", 5, 0},
    {"", "memory.sh", 5, 0},
    {"", "volume.sh", 0, 10},
    {"", "nlstatus.sh", 5, 17},
    {"", "network.sh", 5, 16},
    {"", "date '+%a %x %I:%M%p '", 60, 0},
};

// sets delimiter between status commands. NULL character ('\0') means no
// delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
