od6config
==============

Configuration tool for AMD Overdrive6 devices.

##Status##
Hastily developed, but mostly feature-complete.

##Install##
Download the AMD Display Library SDK 6.0 or newer, and extract the archive into the _ADL_SDK_ directory. Then, issue the typical ``make && sudo make install'' to build and install.

##Usage##
```
Usage: od6config [OPTIONS] [SUBOPTIONS] ...

--list

    Lists all detected and supported display adapters.

--adapter=ADAPTERLIST

    Selects which adapters returned by --list should be affected.
    ADAPTERLIST contains a comma-separated list of adapter index
    numbers. If ADAPTERLIST is omitted, all adapters will be affected.

--autofix

    Sets minclock equal to maxclock, PowerTune to +50, and fan speed to 100%.

--get=SUBOPTS

    Display various information as read from the device. SUBOPTS contains a
    comma-separated list of which information to display.
    Valid SUBOPTS values:
        clocks                  Current core and memory clock values
        fan                     Current fan speed
        temp                    Current temperature in Celsius

--set=SUBOPTS

    Write the specified configuration values to the device. SUBOPTS contains a
    comma-separated list of config key-value pairs.
    Valid SUBOPTS values:
        core=<value>            Set the core clock frequency
        mem=<value>             Set the memor clock frequency
        fan=<value>             Set the fan speed percentage
        power=<value>           Set the PowerTune value
```

##Examples##

List all Overdrive6 devices:

    od6config --list

Show temperature and fan speed of all devices:

    od6config --get temp,fan

Show clock rates for devices 2 & 3 only:

    od6config --adapter 2,3 --get clocks

Automatically set all devices in an optimal configuration:

    od6config --autofix

Manually set the core and memory clocks on all devices to 1050 Mhz core, 1375 Mhz memory:

    od6config --set core=1050,mem=1375

Set the core clock to 1100 Mhz, the memory clock to 1250 Mhz, the fan speed to 90%, and PowerTune to +40 on the first device only:

    od6config --adapter 0 --set core=1100,mem=1250,fan=90,power=+40

... So on and so forth.
