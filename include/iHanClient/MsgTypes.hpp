#ifndef MSGTYPES_H
#define MSGTYPES_H

#include "ZBLocations.hpp"
#include "ZBHAProfiles.hpp"
#include "DeviceTypes.hpp"




enum MSG_WHAT {
MSG_WHAT_DISCOVER = 1,
MSG_WHAT_CLNCAP,
MSG_WHAT_SRVCAP,
MSG_WHAT_AUTH,
MSG_WHAT_SENSOR,
MSG_WHAT_ENDPNT,
MSG_WHAT_SCRN,
MSG_WHAT_RESET,
MSG_WHAT_NEWENDPT,
MSG_WHAT_DELENDPT,
MSG_WHAT_VERSION,
MSG_WHAT_ENDPTVARDESCRIPTOR,
MSG_WHAT_ENDPTCONFIGDESCRIPTOR,
MSG_WHAT_ENDPTCONFIGVALS,
MSG_WHAT_BOOTLOAD = 0xA5,
MSG_WHAT_PONG = 0xFE,
MSG_WHAT_PING,
};

typedef MSG_WHAT MsgType;

/* discover messages */
#define MSG_STR_CTRLPORT "CtrlPort"
#define MSG_STR_CAPDEVICE "CapDvc"
#define MSG_STR_CAPDISPLAY "CapDsp"
#define MSG_STR_CAPCONTROL "CapCtr"
#define MSG_STR_CAPREPORT "CapRpt"
#define MSG_STR_CAPENDPT "CapEpt"
#define MSG_STR_HOSTID "HostID"

#define MSG_STR_AUTHKEY "AuthKey"

/* CAPDEVICE variables */
enum DEVICE_TYPES {
DEVICE_INVALID = 0,
DEVICE_MULN,
DEVICE_CONTROLLER,
DEVICE_CONTROLPAD,
DEVICE_LCD_ALPHA20X4,
DEVICE_LCD_ALPHA20X2,
DEVICE_LCD_MTXORB19264,
DEVICE_BLINKM,
DEVICE_SHT15,
DEVICE_LIGHTSEN,
DEVICE_MOVESEN,
DEVICE_GPIO_INPUT,
DEVICE_GPIO_OUTPUT,
DEVICE_GPIO_ADC,
PSEUDO_SCENE,
DEVICE_CONTROLPANEL,
PLUGIN_WEATHER,
DEVICE_ZWAVENODE,
DEVICE_PIC32,
DEVICE_SWITCHDEVICE,
DEVICE_SCP1000,
DEVICE_ZWAVECONTROLLER,
DEVICE_SENSORMULTILEVEL,
DEVICE_METER,
END_DEVICE_TYPES
};
/* No SUB Type */

#ifdef __18F2520
#define FWFUNC_LOCATION 0x7FF0
#endif

enum FIRMWARE_FUNC {
FWFUNC_MULN_STANDARD = 1,
FWFUNC_MULN_BLINKLED
};

/* CAPDISPLAY variables */
#define CAP_PANEL 0x01;
/* NO SUB Type */


#define XBEP_LCDSCRN 0x01
#define XBEP_LIGHT 0x02
#define XBEP_TEMP 0x10
#define XBEP_LIGHTSEN 0x11
#define XBEP_MOVESEN 0x12


enum BLINKM_CMDS {
BLINKM_SETFADESPEED = 1,
BLINKM_SETTIMEADJ,
BLINKM_FADETORGB,
BLINKM_FADETOHSB,
BLINKM_SETRGB,
BLINKM_FADETORNDRGB,
BLINKM_FADETORNDHSB,
BLINKM_GETRGB,
BLINKM_PLAYSCRPT,
BLINKM_STOPSCRPT,
BLINKM_SETSCPTLENREPS,
BLINKM_GETSCPTLINE,
BLINKM_SETSCPTLINE,
BLINKM_SETSCPT,
BLINKM_SETSTARTUP,
BLINKM_GETINPUT,
BLINKM_GETINPUTS,
BLINKM_GETVERSION
};

enum MULN_CMDS {
MULN_DEVICE_RESET = 0xA5,
MULN_DEVICE_CONFREAD = 0x01,
MULN_DEVICE_CONFWRITE
};


#define SRVCAP_PARENT_NAME "ParentName"
#define	SRVCAP_PARENT_SERIAL "ParentSerial"
#define	SRVCAP_ENDPT_TYPE "EndPtType"
#define	SRVCAP_ENDPT_SERIAL "EndPtSerial"
#define	SRVCAP_ENDPT_NAME "EndPtName"
#define SRVCAP_ENDPT_CONFIG_DESC "EndPtConfigDesc"
#define SRVCAP_ENDPT_CONFIG "EndPtConfig"
#define SRVCAP_ENDPT_VARS_DESC "EndPtVarDesc"
#define SRVCAP_ENDPT_VARS "EndPtVar"
#define SRVCAP_ENDPT_DELETEARRAYENTRY "__DELARRAYENTRY"


/* Config and Value Descriptors */
#define CFGD_NAME "Name"
#define CFGD_TYPE "Type"
#define CFGD_FRIENDLYNAME "FriendlyName"
#define CFGD_DESCRIPTION "Description"
#define CFGD_MIN "Min"
#define CFGD_MAX "Max"
#define CFGD_SIZE "Size"
#define CFGD_ENUMOPTIONS "EnumOptions"
#define CFGD_FLAGS "Flags"
#define CFGD_GROUP "Group"

/* CFGD_TYPE field types */
typedef enum t_ConfigType {
				TC_NULL = -1,
				TC_INT = 1,
				TC_LONG,
				TC_LONGLONG,
				TC_FLOAT,
				TC_STRING,
				TC_ENUM,
				TC_IPADDR,
				TC_BOOL,
				TC_HASH,
				TC_DATETIME,
				TC_VARSTORAGE
} t_ConfigType;

/* CFGD_TYPE field types */
typedef enum t_ConfigFlags {
				TCF_NONE = 0x00,
				TCF_READONLY = 0x01,
				TCF_FIXEDSIZE = 0x02
} t_ConfigFlags;

/* CFGD_GROUP Field Enums */
typedef enum t_ConfigGroups {
	TCG_NOGROUP = 0
} t_ConfigGroups;


typedef enum VarType_t {
    VAR_INVALID = 0,
    VAR_CONFIG,
    VAR_VARIABLE
} VarType_t;

/* MessageBus Fields */



#define MSGB_FROM "MSBFROM"
#define MSGB_TO "MSBTO"
#define MSGB_MSG_TYPE "MSGTYPE"
#define MSGB_MSG_SUBTYPE "MSGSUBTYPE"

enum MSG_BUS_TYPES {
	MSB_TYPE_CONTROL,
	MSB_TYPE_UPDATE,
	MSB_TYPE_STATECHANGE,
	MSB_TYPE_CONFIG
};
enum MSB_BUS_SUBTYPE {
	SHT15_RPT_TEMPANDHUMID,
	LIGHTSEN_RPT_LIGHT,
	MOVESEN_RPT_MOVE,
	GPIO_INPUT_RPT_STATE
};
enum PROTOCOL_TYPES {
	PROTOCOL_ZWAVE,
	PROTOCOL_DYNAMXCONNECT
};
#endif
