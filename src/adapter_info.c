/*
 * Copyright 2013, epixoip.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that redistribution of source
 * retains the above copyright.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "od6config.h"
#include "adl.h"
#include "adapter_info.h"


/* not one shred of error checking in this function.
 * could probably stand to add some, but meh, fuck it.
 */

void get_adapter_info (device_t *adapter)
{
	int temp = 0;
	int pt_caps = 0;
	int bufsize = 0;

	ADLOD6StateInfo *default_state;
	ADLOD6StateInfo *custom_state;

	ADLOD6Capabilities caps = {0};
	ADLOD6CurrentStatus current = {0};
	ADLOD6FanSpeedInfo fan_info = {0};
	ADLOD6ThermalControllerCaps fan_caps = {0};
	ADLOD6PowerControlInfo powertune = {0};

	ADL_Overdrive6_Capabilities_Get (adapter->real_id, &caps);

	adapter->core_clock_min  = caps.sEngineClockRange.iMin  / 100;
	adapter->core_clock_max  = caps.sEngineClockRange.iMax  / 100;
	adapter->core_clock_step = caps.sEngineClockRange.iStep / 100;
	adapter->mem_clock_min   = caps.sMemoryClockRange.iMin  / 100;
	adapter->mem_clock_max   = caps.sMemoryClockRange.iMax  / 100;
	adapter->mem_clock_step  = caps.sMemoryClockRange.iStep / 100;

	ADL_Overdrive6_ThermalController_Caps (adapter->real_id, &fan_caps);

	adapter->fan_min_rpm     = fan_caps.iFanMinRPM;
	adapter->fan_max_rpm     = fan_caps.iFanMaxRPM;
	adapter->fan_min_percent = fan_caps.iFanMinPercent;
	adapter->fan_max_percent = fan_caps.iFanMaxPercent;

	ADL_Overdrive6_FanSpeed_Get (adapter->real_id, &fan_info);

	adapter->fan_rpm_current     = fan_info.iFanSpeedRPM;
	adapter->fan_percent_current = fan_info.iFanSpeedPercent;

	ADL_Overdrive6_TargetTemperatureData_Get (adapter->real_id, &adapter->target_temp_current, &adapter->target_temp_default);
	ADL_Overdrive6_Temperature_Get (adapter->real_id, &temp);
	adapter->temp = (int)(temp / 1000);

	bufsize = sizeof (ADLOD6StateInfo) + sizeof (ADLOD6PerformanceLevel);

	default_state = (ADLOD6StateInfo *) calloc (1, bufsize);
	default_state->iNumberOfPerformanceLevels = 2;

	ADL_Overdrive6_StateInfo_Get (adapter->real_id, ADL_OD6_GETSTATEINFO_DEFAULT_PERFORMANCE, default_state);

	adapter->core_clock_default_range_min = default_state->aLevels[0].iEngineClock / 100;
	adapter->core_clock_default_range_max = default_state->aLevels[1].iEngineClock / 100;
	adapter->mem_clock_default_range_min  = default_state->aLevels[0].iMemoryClock / 100;
	adapter->mem_clock_default_range_max  = default_state->aLevels[1].iMemoryClock / 100;

	free (default_state);

	custom_state  = (ADLOD6StateInfo *) calloc (1, bufsize);
	custom_state->iNumberOfPerformanceLevels = 2;

	ADL_Overdrive6_StateInfo_Get (adapter->real_id, ADL_OD6_GETSTATEINFO_CUSTOM_PERFORMANCE, custom_state);

	adapter->core_clock_custom_range_min = custom_state->aLevels[0].iEngineClock / 100;
	adapter->core_clock_custom_range_max = custom_state->aLevels[1].iEngineClock / 100;
	adapter->mem_clock_custom_range_min  = custom_state->aLevels[0].iMemoryClock / 100;
	adapter->mem_clock_custom_range_max  = custom_state->aLevels[1].iMemoryClock / 100;

	free (custom_state);

	ADL_Overdrive6_CurrentStatus_Get (adapter->real_id, &current);

	adapter->core_clock_current = current.iEngineClock/ 100;
	adapter->mem_clock_current  = current.iMemoryClock/ 100;
	adapter->utilization	    = current.iActivityPercent;

	ADL_Overdrive6_PowerControl_Caps (adapter->real_id, &pt_caps);

	if (!pt_caps) return;

	ADL_Overdrive6_PowerControlInfo_Get (adapter->real_id, &powertune);
	ADL_Overdrive6_PowerControl_Get (adapter->real_id, &adapter->pt_current, &adapter->pt_default);

	adapter->pt_min  = powertune.iMinValue;
	adapter->pt_max  = powertune.iMaxValue;
	adapter->pt_step = powertune.iStepValue;
}
