#ifdef sjdhgisdhfiusrhui

/*  SCE CONFIDENTIAL
 *  PlayStation(R)3 Programmer Tool Runtime Library 400.001
 *  Copyright (C) 2008 Sony Computer Entertainment Inc.
 *  All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sysutil/sysutil_sysparam.h>

#include "padutil.h"

static CellPadData  sPadData[CELL_UTIL_PAD_MAX];
static CellPadInfo2  sPadInfo2;

static bool sPadPressMode = false;
static bool sPadSensorMode = false;
static bool sPadActuatorMode = false;
static bool sIsPadModeChanged = false;

static int32_t sFilterCutoff = -1;
static CellPadFilterIIRSos sFilterSos[CELL_UTIL_PAD_MAX][4];
static bool sButtonAssignCircle = false;

// for inline
uint32_t gCellPadUtilDigitalButtonData[CELL_UTIL_PAD_MAX];
uint32_t gCellPadUtilDigitalButtonDataOld[CELL_UTIL_PAD_MAX];


//------------------------------------------------------------------------------
// INTERNAL

static bool updatePadInfo()
{
	CellPadInfo2 pad_info2;
	int32_t cr = cellPadGetInfo2(&pad_info2);
	if(cr != CELL_PAD_OK) return false;

	sPadInfo2 = pad_info2;

	return true;
}

static bool isConnected(uint8_t pad)
{
	if(pad >= CELL_UTIL_PAD_MAX) return false;
	if(pad >= sPadInfo2.max_connect) return false;

	return (sPadInfo2.port_status[pad] & CELL_PAD_STATUS_CONNECTED);
}

static void initSensorFilter(uint8_t pad, int32_t filter_cutoff)
{
	cellPadFilterIIRInit(&sFilterSos[pad][0], filter_cutoff);
	cellPadFilterIIRInit(&sFilterSos[pad][1], filter_cutoff);
	cellPadFilterIIRInit(&sFilterSos[pad][2], filter_cutoff);
	cellPadFilterIIRInit(&sFilterSos[pad][3], filter_cutoff);
}

//------------------------------------------------------------------------------
// EXTERNAL

bool cellPadUtilPadInit() 
{
	int ret = cellPadInit(CELL_UTIL_PAD_MAX);

	// check button assign
	int button_assign = 0;
	int cr = cellSysutilGetSystemParamInt(CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN, &button_assign);
	
	if(cr == CELL_OK && button_assign == CELL_SYSUTIL_ENTER_BUTTON_ASSIGN_CIRCLE){
		sButtonAssignCircle = true;
	}

	for(int pad = 0; pad < CELL_UTIL_PAD_MAX; ++pad){
		// set default value
		memset(&sPadData[pad], 0, sizeof(CellPadData));
		
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X] = 0x0080;
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y] = 0x0080;
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X] = 0x0080;
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y] = 0x0080;
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_X] = 0x0200;
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_Y] = 0x0200;
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_Z] = 0x0200;
		sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_G] = 0x0200;
	}

	return (ret == CELL_OK || ret == CELL_PAD_ERROR_ALREADY_INITIALIZED);
}

void cellPadUtilPadEnd()
{
	cellPadEnd();
}

bool cellPadUtilIsConnected(uint8_t pad)
{
	if(!updatePadInfo()){
		return false;
	}
	return isConnected(pad);
}

int16_t cellPadUtilGetFirstConnectedPad()
{
	int16_t first_active_pad = -1;

	for(int i = 0; i < CELL_UTIL_PAD_MAX; ++i){
		if(!isConnected(i)) continue;
		first_active_pad = i;
		break;
	}
	
	return first_active_pad;
}

uint32_t cellPadUtilGetEnterButton()
{
	return (sButtonAssignCircle? CELL_UTIL_BUTTON_CIRCLE: CELL_UTIL_BUTTON_CROSS);
}

uint32_t cellPadUtilGetBackButton()
{
	return (sButtonAssignCircle? CELL_UTIL_BUTTON_CROSS: CELL_UTIL_BUTTON_CIRCLE);
}

bool cellPadUtilUpdate() 
{
	if(!updatePadInfo()){
		return false;
	}
	
	if(sPadInfo2.system_info & CELL_PAD_INFO_INTERCEPTED){

		// clear pad data for inline
		for(int i = 0; i < CELL_UTIL_PAD_MAX; ++i){
			gCellPadUtilDigitalButtonData[i] = 0;
			gCellPadUtilDigitalButtonDataOld[i] = 0;

			cellPadUtilSetActDirect(i, 0, 0);
		}

		sIsPadModeChanged = true;

		return false;
	}

	for(int pad = 0; pad < CELL_UTIL_PAD_MAX; ++pad){

		if(!isConnected(pad)){
			gCellPadUtilDigitalButtonData[pad] = 0;
			gCellPadUtilDigitalButtonDataOld[pad] = 0;
			continue;
		}

		if((sPadInfo2.port_status[pad] & CELL_PAD_STATUS_ASSIGN_CHANGES) || sIsPadModeChanged){
			uint32_t device_mode = 0;
			device_mode |= (sPadPressMode  ? CELL_PAD_SETTING_PRESS_ON  : 0);
			device_mode |= (sPadSensorMode ? CELL_PAD_SETTING_SENSOR_ON : 0);

			// mask cap
			device_mode &= sPadInfo2.device_capability[pad];

			cellPadSetPortSetting(pad, device_mode);

			if(device_mode & CELL_PAD_SETTING_PRESS_ON){
				initSensorFilter(pad, sFilterCutoff);
			}
		}

		gCellPadUtilDigitalButtonDataOld[pad] = gCellPadUtilDigitalButtonData[pad];

		CellPadData paddata;
		int32_t ret = cellPadGetData(pad, &paddata);

		if(ret == CELL_PAD_OK && paddata.len != 0){		
			sPadData[pad] = paddata;
			uint16_t digit1 = 0x00FF & paddata.button[CELL_PAD_BTN_OFFSET_DIGITAL1];
			uint16_t digit2 = 0x00FF & paddata.button[CELL_PAD_BTN_OFFSET_DIGITAL2];

			gCellPadUtilDigitalButtonData[pad] = (digit2 << 8) | digit1;
		}
	}

	sIsPadModeChanged = false;

	return true;
}

void cellPadUtilClearBuffer()
{
	for(int i = 0; i < CELL_UTIL_PAD_MAX; ++i){
		gCellPadUtilDigitalButtonData[i] = 0;
		gCellPadUtilDigitalButtonDataOld[i] = 0;
	}
}

// axis
CellPadUtilAxis cellPadUtilGetAxisValue(uint8_t pad, uint32_t axis)
{
	CellPadUtilAxis ret = {0x80, 0x80};

	if(!isConnected(pad)) return ret;

	if(axis != CELL_UTIL_ANALOG_RIGHT && axis != CELL_UTIL_ANALOG_LEFT) return ret;

	if(sPadInfo2.system_info & CELL_PAD_INFO_INTERCEPTED) return ret;
	
	uint32_t offset = (axis >> 16) & 0x00FF;
	ret.x = sPadData[pad].button[offset];
	ret.y = sPadData[pad].button[offset + 1];

	return ret;
}

// sensor
void cellPadUtilSetSensorMode(bool bModeOn)
{
	sPadSensorMode = bModeOn;
	sIsPadModeChanged = true;
}
bool cellPadUtilGetSensorMode()
{
	return sPadSensorMode;
}
bool cellPadUtilSetSensorFilter(int32_t filter_cutoff)
{
	sFilterCutoff = filter_cutoff;
	for(int pad = 0; pad < CELL_UTIL_PAD_MAX; ++pad){
		initSensorFilter(pad, filter_cutoff);
	}

	return true;
}
CellPadUtilSensor cellPadUtilGetSensorValue(uint8_t pad)
{
	CellPadUtilSensor ret = {0x0200, 0x0200, 0x0200, 0x0200};

	if(!sPadSensorMode) return ret;
	if(!isConnected(pad)) return ret;

	if(sPadInfo2.system_info & CELL_PAD_INFO_INTERCEPTED) return ret;

	if(!cellPadUtilIsSupportedSensorMode(pad)) return ret;

	ret.x = sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_X];
	ret.y = sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_Y];
	ret.z = sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_Z];
	ret.g = sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_G];

	return ret;
}
CellPadUtilSensor cellPadUtilGetFilterdSensorValue(uint8_t pad)
{
	CellPadUtilSensor ret = {0x0200, 0x0200, 0x0200, 0x0200};

	if(!sPadSensorMode) return ret;
	if(!isConnected(pad)) return ret;

	if(sPadInfo2.system_info & CELL_PAD_INFO_INTERCEPTED) return ret;

	if(!cellPadUtilIsSupportedSensorMode(pad)) return ret;

	if(sFilterCutoff < 0) return ret;

	ret.x = cellPadFilterIIRFilter(&sFilterSos[pad][0], sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_X]);
	ret.y = cellPadFilterIIRFilter(&sFilterSos[pad][1], sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_Y]);
	ret.z = cellPadFilterIIRFilter(&sFilterSos[pad][2], sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_Z]);
	ret.g = cellPadFilterIIRFilter(&sFilterSos[pad][3], sPadData[pad].button[CELL_PAD_BTN_OFFSET_SENSOR_G]);

	return ret;
}

// press
void cellPadUtilSetPressMode(bool bModeOn)
{
	sPadPressMode = bModeOn;
	sIsPadModeChanged = true;
}
bool cellPadUtilGetPressMode()
{
	return sPadPressMode;
}
uint8_t cellPadUtilGetButtonPressValue(uint8_t pad, uint32_t button)
{
	if(!sPadPressMode) return 0;
	if(!isConnected(pad)) return 0;
	if(sPadInfo2.system_info & CELL_PAD_INFO_INTERCEPTED) return 0;

	if(!cellPadUtilIsSupportedPressMode(pad)) return 0;

	uint8_t offset = 0;
	switch(button){
	case CELL_UTIL_BUTTON_UP:       offset = CELL_PAD_BTN_OFFSET_PRESS_UP;    break;
	case CELL_UTIL_BUTTON_RIGHT:    offset = CELL_PAD_BTN_OFFSET_PRESS_RIGHT; break;
	case CELL_UTIL_BUTTON_DOWN:     offset = CELL_PAD_BTN_OFFSET_PRESS_DOWN;  break;
	case CELL_UTIL_BUTTON_LEFT:     offset = CELL_PAD_BTN_OFFSET_PRESS_LEFT;  break;
	case CELL_UTIL_BUTTON_L2:       offset = CELL_PAD_BTN_OFFSET_PRESS_L2;    break;
	case CELL_UTIL_BUTTON_R2:       offset = CELL_PAD_BTN_OFFSET_PRESS_R2;    break;
	case CELL_UTIL_BUTTON_L1:       offset = CELL_PAD_BTN_OFFSET_PRESS_L1;    break;
	case CELL_UTIL_BUTTON_R1:       offset = CELL_PAD_BTN_OFFSET_PRESS_R1;    break;
	case CELL_UTIL_BUTTON_TRIANGLE: offset = CELL_PAD_BTN_OFFSET_PRESS_TRIANGLE;  break;
	case CELL_UTIL_BUTTON_CIRCLE:   offset = CELL_PAD_BTN_OFFSET_PRESS_CIRCLE;    break;
	case CELL_UTIL_BUTTON_CROSS:    offset = CELL_PAD_BTN_OFFSET_PRESS_CROSS;     break;
	case CELL_UTIL_BUTTON_SQUARE:   offset = CELL_PAD_BTN_OFFSET_PRESS_SQUARE;    break;
	default:
		offset = 0;
	}

	if(offset == 0) return 0;

	return sPadData[pad].button[offset];
}

CellPadUtilPress cellPadUtilGetPressValue(uint8_t pad)
{
	CellPadUtilPress ret = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	if(!sPadPressMode) return ret;
	if(!isConnected(pad)) return ret;
	if(sPadInfo2.system_info & CELL_PAD_INFO_INTERCEPTED) return ret;

	if(!cellPadUtilIsSupportedPressMode(pad)) return ret;

	ret.up		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_UP];
	ret.right	= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_RIGHT];
	ret.down	= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_DOWN];
	ret.left	= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_LEFT];
	//ret.L3 = sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_L3];
	//ret.R3 = sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_R3];
	ret.L2		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_L2];
	ret.R2		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_R2];
	ret.L1		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_L1];
	ret.R1		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_R1];
	ret.triangle	= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_TRIANGLE];
	ret.circle		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_CIRCLE];
	ret.cross		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_CROSS];
	ret.square		= sPadData[pad].button[CELL_PAD_BTN_OFFSET_PRESS_SQUARE];

	return ret;
}

// pad data
const CellPadData* cellPadUtilGetPadData(uint8_t pad)
{
	if(pad >= CELL_UTIL_PAD_MAX) return 0;
	
	return &sPadData[pad];
}
const CellPadInfo2* cellPadUtilGetPadInfo2()
{
	return &sPadInfo2;
}

// check caps
bool cellPadUtilIsPs3Conformity(uint8_t pad)
{
	if(CELL_PAD_MAX_PORT_NUM <= pad) return false;
    if(!updatePadInfo()) return false;
	return sPadInfo2.device_capability[pad] & CELL_PAD_CAPABILITY_PS3_CONFORMITY;
}
bool cellPadUtilIsSupportedPressMode(uint8_t pad)
{
	if(CELL_PAD_MAX_PORT_NUM <= pad) return false;
	if(!updatePadInfo()) return false;
	return sPadInfo2.device_capability[pad] & CELL_PAD_CAPABILITY_PRESS_MODE;
}
bool cellPadUtilIsSupportedSensorMode(uint8_t pad)
{
	if(CELL_PAD_MAX_PORT_NUM <= pad) return false;
	if(!updatePadInfo()) return false;
	return sPadInfo2.device_capability[pad] & CELL_PAD_CAPABILITY_SENSOR_MODE;
}
bool cellPadUtilIsSupportedHpAnalogStick(uint8_t pad)
{
	if(CELL_PAD_MAX_PORT_NUM <= pad) return false;
	if(!updatePadInfo()) return false;
	return sPadInfo2.device_capability[pad] & CELL_PAD_CAPABILITY_HP_ANALOG_STICK;
}
bool cellPadUtilIsSupportedActuator(uint8_t pad)
{
	if(CELL_PAD_MAX_PORT_NUM <= pad) return false;
	if(!updatePadInfo()) return false;
	return sPadInfo2.device_capability[pad] & CELL_PAD_CAPABILITY_ACTUATOR;
}

// actuator
void cellPadUtilSetActuatorMode(bool bModeOn)
{
	sPadActuatorMode = bModeOn;
	sIsPadModeChanged = true;
}
bool cellPadUtilGetActuatorMode()
{
	return sPadActuatorMode;
}
bool cellPadUtilSetActDirect(uint8_t pad, uint8_t motor1, uint8_t motor2)
{
	if(!cellPadUtilIsSupportedActuator(pad)) return false;
	
	CellPadActParam actp;
	memset(&actp, 0x00, sizeof(CellPadActParam));

	if(sPadActuatorMode){
		actp.motor[0] = motor1; // 0 or 1
		actp.motor[1] = motor2; // 0x00 - 0xFF
	}
	
	cellPadSetActDirect(pad, &actp);
	
	return true;
}


#endif