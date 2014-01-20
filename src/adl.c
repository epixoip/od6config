/*
 * Copyright 2013, epixoip.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that redistribution of source
 * retains the above copyright.
 */

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "od6config.h"
#include "adl.h"

ADL_MAIN_CONTROL_CREATE ADL_Main_Control_Create;
ADL_MAIN_CONTROL_DESTROY ADL_Main_Control_Destroy;
ADL_ADAPTER_NUMBEROFADAPTERS_GET ADL_Adapter_NumberOfAdapters_Get;
ADL_ADAPTER_ADAPTERINFO_GET ADL_Adapter_AdapterInfo_Get;
ADL_ADAPTER_ACTIVE_GET ADL_Adapter_Active_Get;
ADL_OVERDRIVE_CAPS ADL_Overdrive_Caps;
ADL_OVERDRIVE6_FANSPEED_GET ADL_Overdrive6_FanSpeed_Get;
ADL_OVERDRIVE6_THERMALCONTROLLER_CAPS ADL_Overdrive6_ThermalController_Caps;
ADL_OVERDRIVE6_TEMPERATURE_GET ADL_Overdrive6_Temperature_Get;
ADL_OVERDRIVE6_CAPABILITIES_GET ADL_Overdrive6_Capabilities_Get;
ADL_OVERDRIVE6_STATEINFO_GET ADL_Overdrive6_StateInfo_Get;
ADL_OVERDRIVE6_CURRENTSTATUS_GET ADL_Overdrive6_CurrentStatus_Get;
ADL_OVERDRIVE6_POWERCONTROL_CAPS ADL_Overdrive6_PowerControl_Caps;
ADL_OVERDRIVE6_POWERCONTROLINFO_GET ADL_Overdrive6_PowerControlInfo_Get;
ADL_OVERDRIVE6_POWERCONTROL_GET ADL_Overdrive6_PowerControl_Get;
ADL_OVERDRIVE6_FANSPEED_SET ADL_Overdrive6_FanSpeed_Set;
ADL_OVERDRIVE6_STATE_SET ADL_Overdrive6_State_Set;
ADL_OVERDRIVE6_POWERCONTROL_SET ADL_Overdrive6_PowerControl_Set;
ADL_OVERDRIVE6_TARGETTEMPERATUREDATA_GET ADL_Overdrive6_TargetTemperatureData_Get;
ADL_OVERDRIVE6_TARGETTEMPERATUREDATA_SET ADL_Overdrive6_TargetTemperatureData_Set;

void *adl_alloc (int size)
{
	void *buf = (void *) malloc (size);
	return buf;
}

void adl_free (void **buf)
{
	if (*buf != NULL)
		free (*buf);

	*buf = NULL;
}

void *get_func_addr (void *dll, const char *name)
{
	void *ptr = dlsym (dll, name);

	if (ptr == NULL && !strstr(name, "ADL_Overdrive6_TargetTemperatureData_"))
	{
		fprintf (stderr, "Error: function '%s' does not exist in ADL library.\n", name);
		exit (-1);
	}

	return ptr;
}

int adl_init ()
{
	void *dll;

	if ((dll = dlopen("libatiadlxx.so", RTLD_LAZY | RTLD_GLOBAL)) == NULL)
	{
		fprintf (stderr, "Unable to open libatiadlxx.so. Please download the latest AMD Catalyst software.\n");
		return (-1);
	}

	ADL_Main_Control_Create = (ADL_MAIN_CONTROL_CREATE) get_func_addr (dll, "ADL_Main_Control_Create");
	ADL_Main_Control_Destroy = (ADL_MAIN_CONTROL_DESTROY) get_func_addr (dll, "ADL_Main_Control_Destroy");
	ADL_Adapter_NumberOfAdapters_Get = (ADL_ADAPTER_NUMBEROFADAPTERS_GET) get_func_addr (dll, "ADL_Adapter_NumberOfAdapters_Get");
	ADL_Adapter_AdapterInfo_Get = (ADL_ADAPTER_ADAPTERINFO_GET) get_func_addr (dll, "ADL_Adapter_AdapterInfo_Get");
	ADL_Adapter_Active_Get = (ADL_ADAPTER_ACTIVE_GET) get_func_addr (dll, "ADL_Adapter_Active_Get");
	ADL_Overdrive_Caps = (ADL_OVERDRIVE_CAPS) get_func_addr (dll, "ADL_Overdrive_Caps");
	ADL_Overdrive6_FanSpeed_Get = (ADL_OVERDRIVE6_FANSPEED_GET) get_func_addr (dll, "ADL_Overdrive6_FanSpeed_Get");
	ADL_Overdrive6_ThermalController_Caps = (ADL_OVERDRIVE6_THERMALCONTROLLER_CAPS) get_func_addr (dll, "ADL_Overdrive6_ThermalController_Caps");
	ADL_Overdrive6_Temperature_Get = (ADL_OVERDRIVE6_TEMPERATURE_GET) get_func_addr (dll, "ADL_Overdrive6_Temperature_Get");
	ADL_Overdrive6_Capabilities_Get = (ADL_OVERDRIVE6_CAPABILITIES_GET) get_func_addr (dll, "ADL_Overdrive6_Capabilities_Get");
	ADL_Overdrive6_StateInfo_Get = (ADL_OVERDRIVE6_STATEINFO_GET) get_func_addr (dll, "ADL_Overdrive6_StateInfo_Get");
	ADL_Overdrive6_CurrentStatus_Get = (ADL_OVERDRIVE6_CURRENTSTATUS_GET) get_func_addr (dll, "ADL_Overdrive6_CurrentStatus_Get");
	ADL_Overdrive6_PowerControl_Caps = (ADL_OVERDRIVE6_POWERCONTROL_CAPS) get_func_addr (dll, "ADL_Overdrive6_PowerControl_Caps");
	ADL_Overdrive6_PowerControlInfo_Get = (ADL_OVERDRIVE6_POWERCONTROLINFO_GET) get_func_addr (dll, "ADL_Overdrive6_PowerControlInfo_Get");
	ADL_Overdrive6_PowerControl_Get = (ADL_OVERDRIVE6_POWERCONTROL_GET) get_func_addr (dll, "ADL_Overdrive6_PowerControl_Get");
	ADL_Overdrive6_FanSpeed_Set  = (ADL_OVERDRIVE6_FANSPEED_SET) get_func_addr (dll, "ADL_Overdrive6_FanSpeed_Set");
	ADL_Overdrive6_State_Set = (ADL_OVERDRIVE6_STATE_SET) get_func_addr (dll, "ADL_Overdrive6_State_Set");
	ADL_Overdrive6_PowerControl_Set = (ADL_OVERDRIVE6_POWERCONTROL_SET) get_func_addr (dll, "ADL_Overdrive6_PowerControl_Set");
	ADL_Overdrive6_TargetTemperatureData_Get = (ADL_OVERDRIVE6_TARGETTEMPERATUREDATA_GET) get_func_addr (dll, "ADL_Overdrive6_TargetTemperatureData_Get");
	ADL_Overdrive6_TargetTemperatureData_Set = (ADL_OVERDRIVE6_TARGETTEMPERATUREDATA_SET) get_func_addr (dll, "ADL_Overdrive6_TargetTemperatureData_Set");

	return (0);
}

int init_adapters (device_t *devices)
{
	int i = 0;
	int active_cnt = 0;
	int od_supported = 0;
	int od_enabled = 0;
	int od_version = 0;
	int adl_num_adapters = 0;
	int active_devs[MAX_DEVS];
	LPAdapterInfo adapter_info;

	ADL_Main_Control_Create (adl_alloc, 1);
	ADL_Adapter_NumberOfAdapters_Get (&adl_num_adapters);

	if (adl_num_adapters < 1)
		return (-1);

	adapter_info = (AdapterInfo *) calloc (adl_num_adapters, sizeof (AdapterInfo));
	ADL_Adapter_AdapterInfo_Get (adapter_info, adl_num_adapters * sizeof (AdapterInfo));

	for (i = 0; i < adl_num_adapters; i++)
	{
		int is_active = 0;

		if (ADL_Adapter_Active_Get (adapter_info[i].iAdapterIndex, &is_active) != ADL_OK)
			continue;
		else
			if (is_active != ADL_TRUE)
				continue;

		if (ADL_Overdrive_Caps (adapter_info[i].iAdapterIndex, &od_supported, &od_enabled, &od_version) != ADL_OK)
			continue;

		if (od_version != 6)
			continue;

		active_devs[active_cnt++] = i;
	}

	for (i = 0; i < active_cnt; i++)
	{
		devices[i].id = i;
		devices[i].real_id = active_devs[i];
		memcpy (&devices[i].name, adapter_info[active_devs[i]].strAdapterName, strlen (adapter_info[active_devs[i]].strAdapterName) * sizeof (char));
	}

	free (adapter_info);

	return active_cnt;
}
