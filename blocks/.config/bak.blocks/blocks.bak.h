//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"󰖂 ", 		"nordlayer status | grep VPN | sed s/'VPN: '//",		15,			0},
	{" ", 		"top -bn1 | grep load | awk '/^top/ {print $11}' | sed s/,/%/",		3,			18},
	{" ", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	30,		0},
	{"", 		"brightness.sh",		0,			14},
	{"", 		"volume.sh",		0,			10},
	{"", 		"battery.sh",		5,			3},
	{"", "date '+%b %d (%a) %I:%M%p'",					1,		0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
