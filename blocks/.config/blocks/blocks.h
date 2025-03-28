//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"  ", 		"cpu.sh",		5,			0},
	{" ", "memory.sh",	5,		0},
	{"", 		"nlstatus.sh",		5,			17},
	{"", 		"network.sh",		5,			16},
	{"", 		"nightlight.sh",		0,			15},
	{"", 		"brightness.sh",		0,			14},
	{"", 		"volume.sh",		0,			10},
	{"", 		"battery.sh",		5,			3},
	{"", "date '+%b %d (%a) %I:%M%p '",					1,		0},
};

// Define StatusCMD
// static char *getcmds[] = {
// 	"volume.sh",       // Click action for Volume
// 	"brightness.sh",   // Click action for Brightness
// };
// static int getsigcmds = LENGTH(getcmds);

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;


