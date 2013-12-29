/*
 * Copyright 2013, epixoip.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that redistribution of source
 * retains the above copyright.
 */

#pragma once

#define LINUX
#define MAX_DEVS 16

#include "../ADL_SDK/include/adl_sdk.h"

typedef struct
{
	int id;
	int real_id;
	char name[1024];

	int fan_min_rpm;
	int fan_max_rpm;
	int fan_min_percent;
	int fan_max_percent;
	int fan_rpm_current;
	int fan_percent_current;

	float temp;

	int core_clock_min;
	int core_clock_max;
	int core_clock_step;
	int core_clock_default_range_min;
	int core_clock_default_range_max;
	int core_clock_custom_range_min;
	int core_clock_custom_range_max;
	int core_clock_current;

	int mem_clock_min;
	int mem_clock_max;
	int mem_clock_step;
	int mem_clock_default_range_min;
	int mem_clock_default_range_max;
	int mem_clock_custom_range_min;
	int mem_clock_custom_range_max;
	int mem_clock_current;

	int utilization;

	int pt_min;
	int pt_max;
	int pt_step;
	int pt_default;
	int pt_current;
} device_t;

