/*
 * Copyright 2013, epixoip.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that redistribution of source
 * retains the above copyright.
 */

#pragma once

#define AMDVENDORID 0x1002
#define ADL_WARNING_NO_DATA -100

extern void *adl_alloc (int size);
extern void adl_free (void **buf);
extern int adl_init ();
extern int init_adapters (device_t *devices);

typedef int (*ADL_MAIN_CONTROL_CREATE) (ADL_MAIN_MALLOC_CALLBACK, int);
typedef int (*ADL_MAIN_CONTROL_DESTROY) ();
typedef int (*ADL_ADAPTER_NUMBEROFADAPTERS_GET) (int*);
typedef int (*ADL_ADAPTER_ADAPTERINFO_GET) (LPAdapterInfo, int);
typedef int (*ADL_ADAPTER_ACTIVE_GET) (int, int*);
typedef int (*ADL_OVERDRIVE_CAPS) (int iAdapterIndex, int *iSupported, int *iEnabled, int *iVersion);
typedef int (*ADL_OVERDRIVE6_FANSPEED_GET) (int iAdapterIndex, ADLOD6FanSpeedInfo *lpFanSpeedInfo);
typedef int (*ADL_OVERDRIVE6_THERMALCONTROLLER_CAPS) (int iAdapterIndex, ADLOD6ThermalControllerCaps *lpThermalControllerCaps);
typedef int (*ADL_OVERDRIVE6_TEMPERATURE_GET) (int iAdapterIndex, int *lpTemperature);
typedef int (*ADL_OVERDRIVE6_CAPABILITIES_GET) (int iAdapterIndex, ADLOD6Capabilities *lpODCapabilities);
typedef int (*ADL_OVERDRIVE6_STATEINFO_GET) (int iAdapterIndex, int iStateType, ADLOD6StateInfo *lpStateInfo);
typedef int (*ADL_OVERDRIVE6_CURRENTSTATUS_GET) (int iAdapterIndex, ADLOD6CurrentStatus *lpCurrentStatus);
typedef int (*ADL_OVERDRIVE6_POWERCONTROL_CAPS) (int iAdapterIndex, int *lpSupported);
typedef int (*ADL_OVERDRIVE6_POWERCONTROLINFO_GET) (int iAdapterIndex, ADLOD6PowerControlInfo *lpPowerControlInfo);
typedef int (*ADL_OVERDRIVE6_POWERCONTROL_GET) (int iAdapterIndex, int *lpCurrentValue, int *lpDefaultValue);
typedef int (*ADL_OVERDRIVE6_FANSPEED_SET) (int iAdapterIndex, ADLOD6FanSpeedValue *lpFanSpeedValue);
typedef int (*ADL_OVERDRIVE6_STATE_SET) (int iAdapterIndex, int iStateType, ADLOD6StateInfo *lpStateInfo);
typedef int (*ADL_OVERDRIVE6_POWERCONTROL_SET) (int iAdapterIndex, int iValue);

extern ADL_MAIN_CONTROL_CREATE ADL_Main_Control_Create;
extern ADL_MAIN_CONTROL_DESTROY ADL_Main_Control_Destroy;
extern ADL_ADAPTER_NUMBEROFADAPTERS_GET ADL_Adapter_NumberOfAdapters_Get;
extern ADL_ADAPTER_ADAPTERINFO_GET ADL_Adapter_AdapterInfo_Get;
extern ADL_ADAPTER_ACTIVE_GET ADL_Adapter_Active_Get;
extern ADL_OVERDRIVE_CAPS ADL_Overdrive_Caps;
extern ADL_OVERDRIVE6_FANSPEED_GET ADL_Overdrive6_FanSpeed_Get;
extern ADL_OVERDRIVE6_THERMALCONTROLLER_CAPS ADL_Overdrive6_ThermalController_Caps;
extern ADL_OVERDRIVE6_TEMPERATURE_GET ADL_Overdrive6_Temperature_Get;
extern ADL_OVERDRIVE6_CAPABILITIES_GET ADL_Overdrive6_Capabilities_Get;
extern ADL_OVERDRIVE6_STATEINFO_GET ADL_Overdrive6_StateInfo_Get;
extern ADL_OVERDRIVE6_CURRENTSTATUS_GET ADL_Overdrive6_CurrentStatus_Get;
extern ADL_OVERDRIVE6_POWERCONTROL_CAPS ADL_Overdrive6_PowerControl_Caps;
extern ADL_OVERDRIVE6_POWERCONTROLINFO_GET ADL_Overdrive6_PowerControlInfo_Get;
extern ADL_OVERDRIVE6_POWERCONTROL_GET ADL_Overdrive6_PowerControl_Get;
extern ADL_OVERDRIVE6_FANSPEED_SET ADL_Overdrive6_FanSpeed_Set;
extern ADL_OVERDRIVE6_STATE_SET ADL_Overdrive6_State_Set;
extern ADL_OVERDRIVE6_POWERCONTROL_SET ADL_Overdrive6_PowerControl_Set;

