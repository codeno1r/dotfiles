// Modify this file to change what commands output to your statusbar, and
// recompile using the make command.

static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/
    {"", "cpu.sh", 5, 0},
    {"", "memory.sh", 5, 0},
    // {"", "nlstatus.sh", 5, 17},
    {"", "network.sh", 5, 16},
    // {"", "brightness.sh", 0, 14},
    {"", "volume.sh", 0, 10},
    {"", "battery.sh", 5, 3},
    {"", "date '+%b %d (%a) %I:%M%p '", 5, 0},
};

// sets delimiter between status commands. NULL character ('\0') means no
// delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
