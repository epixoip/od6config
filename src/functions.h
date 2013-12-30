/*
 * Copyright 2013, epixoip.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that redistribution of source
 * retains the above copyright.
 */

#pragma once

extern void print_fanspeed (device_t *adapter);
extern void print_temp (device_t *adapter);
extern void print_clocks (device_t *adapter);
extern void print_info (device_t *adapter);
extern void set_fanspeed (device_t *adapter, int speed);
extern void set_clocks (device_t *adapter, int core, int mem);
extern void set_powertune (device_t *adapter, int threshold);
extern void set_targettemp (device_t *adapter, int target);
