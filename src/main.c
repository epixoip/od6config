/*
 * Copyright 2013, epixoip.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that redistribution of source
 * retains the above copyright.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "od6config.h"
#include "adl.h"
#include "adapter_info.h"
#include "functions.h"


int _get = 0;
int _set = 0;
int _fix = 0;
int _list = 0;
int _core = 0;
int _mem = 0;
int _get_fan = 0;
int _set_fan = 0;
int _temp = 0;
int _power = 0;
int _clocks = 0;
int core_clock = 0;
int mem_clock = 0;
int fanspeed = 0;
int power = 0;
int adapter_cnt = 0;
int device_list[MAX_DEVS];

enum
{
	GET_CLOCKS,
	GET_FAN,
	GET_TEMP,
};

enum
{
	SET_CORE,
	SET_MEM,
	SET_FAN,
	SET_POWER
};

char * const get_subopts[] =
{
	[GET_CLOCKS] = "clocks",
	[GET_FAN]    = "fan",
	[GET_TEMP]   = "temp",
	NULL
};

char * const set_subopts[] =
{
        [SET_CORE]   = "core",
        [SET_MEM]    = "mem",
        [SET_FAN]    = "fan",
        [SET_POWER]  = "power",
        NULL
};

char * const adapter_opts[] = {	NULL };

static struct option long_options[] =
{
	{ "help",    no_argument,       0,     'h' },
	{ "list",    no_argument,       &_list, 1  },
	{ "autofix", no_argument,       &_fix,  1  },
	{ "adapter", required_argument, 0,     'a' },
	{ "get",     required_argument, 0,     'g' },
	{ "set",     required_argument, 0,     's' },
	{ 0,         0,	                0,      0  }
};


void print_help ()
{
	puts ("\nod6config -- Configuration tool for AMD Overdrive6 devices.");
	puts ("Usage: od6config [OPTIONS] [SUBOPTIONS] ...\n");
	puts ("--list\n");
	puts ("    Lists all detected and supported display adapters.\n");
	puts ("--adapter=ADAPTERLIST\n");
        puts ("    Selects which adapters returned by --list should be affected.");
	puts ("    ADAPTERLIST contains a comma-separated list of adapter index");
	puts ("    numbers. If ADAPTERLIST is omitted, all adapters will be affected.\n");
	puts ("--autofix\n");
	puts ("    Sets minclock equal to maxclock, PowerTune to +50, and fan speed to 100%.\n");
	puts ("--get=SUBOPTS\n");
	puts ("    Display various information as read from the device. SUBOPTS contains a");
	puts ("    comma-separated list of which information to display.");
	puts ("    Valid SUBOPTS values:");
	puts ("	clocks			Current core and memory clock values");
	puts ("	fan			Current fan speed");
	puts ("	temp			Current temperature in Celsius\n");
	puts ("--set=SUBOPTS\n");
	puts ("    Write the specified configuration values to the device. SUBOPTS contains a");
	puts ("    comma-separated list of config key-value pairs.");
	puts ("    Valid SUBOPTS values:");
	puts ("	core=<value>		Set the core clock frequency");
	puts ("	mem=<value>		Set the memor clock frequency");
	puts ("	fan=<value>		Set the fan speed percentage");
	puts ("	power=<value>		Set the PowerTune value\n\n");
}


int main (int argc, char **argv)
{
	int i = 0;
	int num_devices = 0;
	int opts = 0;
	char *subopts, *value;
	device_t devices[MAX_DEVS] = {{0}};


	if (adl_init() < 0)
	{
		fprintf (stderr, "Failed to initialize the ADL library.\n");
		return (1);
	}

	if ((num_devices = init_adapters (devices)) < 1)
	{
		fprintf (stderr, "No Overdrive6 devices found!\n");
		return (2);
	}


	while (1)
	{
		int option_index = 0;

		if ((opts = getopt_long_only (argc, argv, "ha:", long_options, &option_index)) == -1)
			break;

		switch (opts)
		{
			case 0:
				if (long_options[option_index].flag != 0)
					break;
			case 'h':
				print_help ();
				return (0);
			case 'a':
				subopts = optarg;
				while (*subopts != '\0')
					switch (getsubopt (&subopts, adapter_opts, &value))
					{
						default:
							device_list[adapter_cnt++] = atoi (value);
					}
				break;
			case 'g':
				_get = 1;
				subopts = optarg;
				while (*subopts != '\0')
					switch (getsubopt (&subopts, get_subopts, &value))
					{
						case GET_CLOCKS:
							_clocks = 1;
							break;
						case GET_FAN:
							_get_fan = 1;
							break;
						case GET_TEMP:
							_temp = 1;
							break;
						default:
							fprintf (stderr, "Syntax error: Unknown suboption for --get: `%s'\n", value);
							return (5);
					}		
				break;
			case 's':
				_set = 1;
				subopts = optarg;
				while (*subopts != '\0')
					switch (getsubopt (&subopts, set_subopts, &value))
					{
						case SET_CORE:
							if (value == NULL)
							{
								fprintf (stderr, "Syntax error: `core' requires a value.\n");
								return (5);
							}
							_core = 1;
							core_clock = atoi (value);
							break;
						case SET_MEM:
							if (value == NULL)
							{
								fprintf (stderr, "Syntax error: `mem' requires a value.\n");
								return (5);
							}
							_mem = 1;
							mem_clock = atoi (value);
							break;
						case SET_FAN:
							if (value == NULL)
							{
								fprintf (stderr, "Syntax error: `fan' requires a value.\n");
								return (5);
							}
							_set_fan = 1;
							fanspeed = atoi (value);
							break;
						case SET_POWER:
							if (value == NULL)
							{
								fprintf (stderr, "Syntax error: `power' requires a value.\n");
								return (5);
							}
							_power = 1;
							power = atoi (value);
							break;
						default:
							fprintf (stderr, "Syntax error: Unknown suboption for --set: `%s'\n", value);
							return (5);
					}
				break;
			case '?':
				break;
			default:
				abort ();
		}
	}


	if (!_get && !_set && !_list && !_fix)
	{
		print_help ();
		return (3);
	}


	if (!adapter_cnt || _list)
	{
		adapter_cnt = num_devices;

		for (i = 0; i < num_devices; i++)
			device_list[i] = i;
	}
	else if (adapter_cnt > num_devices)
	{
		fprintf (stderr, "You have requested %d devices, but you only have %d Overdrive6 devices present.\n", adapter_cnt, num_devices);
		return (4);
	}


	for (i = 0; i < adapter_cnt; i++)
		if (device_list[i] > num_devices - 1)
		{
			fprintf (stderr, "Device %d does not exist!\n", device_list[i]);
			return (5);
		}


	printf ("\n");

	for (i = 0; i < adapter_cnt; i++)
	{
		get_adapter_info (&devices[device_list[i]]);

		printf ("Adapter %d: %s\n", devices[device_list[i]].id, devices[device_list[i]].name);

		if (_list)
			continue;

		if (_fix)
		{
			set_clocks (&devices[device_list[i]], devices[device_list[i]].core_clock_custom_range_max, devices[device_list[i]].mem_clock_custom_range_max);
			set_fanspeed (&devices[device_list[i]], devices[device_list[i]].fan_max_percent);
			set_powertune (&devices[device_list[i]], devices[device_list[i]].pt_max);
		}	
		else if (_set)
		{
			if (_core && _mem)
				set_clocks (&devices[device_list[i]], core_clock, mem_clock);
			else if (_core)
				set_clocks (&devices[device_list[i]], core_clock, devices[device_list[i]].mem_clock_current);
			else if (_mem)
				set_clocks (&devices[device_list[i]], devices[device_list[i]].core_clock_current, mem_clock);

			if (_set_fan)   set_fanspeed (&devices[device_list[i]], fanspeed);
			if (_power) set_powertune (&devices[device_list[i]], power);
		}

		if (_get)
		{
			if (_clocks) print_clocks (&devices[device_list[i]]);
			if (_get_fan)    print_fanspeed (&devices[device_list[i]]);
			if (_temp)   print_temp (&devices[device_list[i]]);
		}

		printf ("\n");
	}

	if (_list) printf ("\n");

	return (0);
}

