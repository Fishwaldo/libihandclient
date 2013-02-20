/* ControlPad - ZBLocations.cpp
** Copyright (c) 2010 Justin Hammond
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
**  USA
**
** ControlPad SVN Identification:
** $Rev$
*/

/** @file ZBLocations.cpp
 *  @brief
 */

#include "ZBLocations.hpp"
#include "ZBHAProfiles.hpp"

const char LocationStrings[][0x48] = {
		{ LOC_ATRIUM_TXT },
		{ LOC_BAR_TXT },
		{ LOC_COURTYARD_TXT },
		{ LOC_BATHROOM_TXT },
		{ LOC_BEDROOM_TXT },
		{ LOC_BILLIARD_TXT },
		{ LOC_UTILITY_TXT },
		{ LOC_CELLAR_TXT },
		{ LOC_CLOSET_TXT },
		{ LOC_THEATER_TXT },
		{ LOC_OFFICE_TXT },
		{ LOC_DECK_TXT },
		{ LOC_DEN_TXT },
		{ LOC_DINING_TXT },
		{ LOC_ELECTRICAL_TXT },
		{ LOC_ELEVATOR_TXT },
		{ LOC_ENTRY_TXT },
		{ LOC_FAMILY_TXT },
		{ LOC_MAIN_TXT },
		{ LOC_UPSTAIRS_TXT },
		{ LOC_DOWNSTAIRS_TXT },
		{ LOC_BASEMENT_TXT },
		{ LOC_GALLERY_TXT },
		{ LOC_GAME_TXT },
		{ LOC_GARAGE_TXT },
		{ LOC_GYM_TXT },
		{ LOC_HALLWAY_TXT },
		{ LOC_HOUSE_TXT },
		{ LOC_KITCHEN_TXT },
		{ LOC_LAUNDRY_TXT },
		{ LOC_LIBRARY_TXT },
		{ LOC_MASTERBED_TXT },
		{ LOC_MUD_TXT },
		{ LOC_NURSERY_TXT },
		{ LOC_PANTRY_TXT },
		{ LOC_OFFICE2_TXT },
		{ LOC_OUTSIDE_TXT },
		{ LOC_POOL_TXT },
		{ LOC_PORCH_TXT },
		{ LOC_SEWING_TXT },
		{ LOC_SITTING_TXT },
		{ LOC_STAIRWAY_TXT },
		{ LOC_YARD_TXT },
		{ LOC_ATTIC_TXT },
		{ LOC_HOTTUB_TXT },
		{ LOC_LIVING_TXT },
		{ LOC_SAUNA_TXT },
		{ LOC_SHOP_TXT },
		{ LOC_GUESTBED_TXT },
		{ LOC_GUESTBATH_TXT },
		{ LOC_POWDER_TXT },
		{ LOC_BACKYARD_TXT },
		{ LOC_FRONTYARD_TXT },
		{ LOC_PATIO_TXT },
		{ LOC_DRIVEWAY_TXT },
		{ LOC_SUN_TXT },
		{ LOC_LIVING2_TXT },
		{ LOC_SPA_TXT },
		{ LOC_WHIRLPOOL_TXT },
		{ LOC_SHED_TXT },
		{ LOC_EQUIPMENT_TXT },
		{ LOC_HOBBY_TXT },
		{ LOC_FOUNTAIN_TXT },
		{ LOC_POND_TXT },
		{ LOC_RECEPTION_TXT },
		{ LOC_BREAKFAST_TXT },
		{ LOC_NOOK_TXT },
		{ LOC_GARDEN_TXT },
		{ LOC_BALCONY_TXT },
		{ LOC_PANIC_TXT },
		{ LOC_TERRACE_TXT },
		{ LOC_ROOF_TXT },
	};
#if 0
void getType(long type, char *result) {
	switch (type) {
	case ZAHAP_ONOFF_SWITCH:
		result =  "On/Off Switch";
	case ZAHAP_LEVEL_CONTROL_SWITCH:
		result =  "Level Control Switch";
	case ZAHAP_ONOFF_OUTPUT:
		result =  "On/Off Output";
	case ZAHAP_LEVEL_CONTROLLABLE_OUTPUT:
		result =  "Level Controllable Output";
	case ZAHAP_SCENE_SELECTOR:
		result =  "Scene Selector";
	case ZAHAP_CONFIGURATION_TOOL:
		result =  "Configuration Tool";
	case ZAHAP_REMOTE_CONTROL:
		result =  "Remote Control";
	case ZAHAP_COMBINED_INTERFACE:
		result =  "Combined Interface";
	case ZAHAP_RANGE_EXTENDER:
		result =  "Range Extender";
	case ZAHAP_MAINS_POWER_OUTLET:
		result =  "Mains Power Outlet";
	case ZAHAP_DOOR_LOCK:
		result =  "Door Lock";
	case ZAHAP_DOOR_LOCK_CONTROLLER:
		result =  "Door Lock Controller";
	case ZAHAP_SIMPLE_SENSOR:
		result =  "Simple Sensor";
	case ZAHAP_ONOFF_LIGHT:
		result =  "On/Off Light";
	case ZAHAP_DIMMABLE_LIGHT:
		result =  "Dimmable Light";
	case ZAHAP_COLOR_DIMMABLE_LIGHT:
		result =  "Color Dimmable Light";
	case ZAHAP_ONOFF_LIGHT_SWITCH:
		result =  "On/Off Light Switch";
	case ZAHAP_DIMMER_SWITCH:
		result =  "Dimmer Switch";
	case ZAHAP_COLOR_DIMMER_SWITCH:
		result =  "Color Dimmer Switch";
	case ZAHAP_LIGHT_SENSOR:
		result =  "Light Sensor";
	case ZAHAP_OCCUPANCY_SENSOR:
		result =  "Occupancy Sensor";
	case ZAHAP_SHADE:
		result =  "Shade";
	case ZAHAP_SHADE_CONTROLLER:
		result =  "Shade Controller";
	case ZAHAP_WINDOW_COVERING_DEVICE:
		result =  "Window Covering Device";
	case ZAHAP_WINDOW_COVERING_CONTROLLER:
		result =  "Window Covering Controller";
	case ZAHAP_HEATINGCOOLING_UNIT:
		result =  "Heating/Cooling Unit";
	case ZAHAP_THERMOSTAT:
		result =  "Thermostat";
	case ZAHAP_TEMPERATURE_SENSOR:
		result =  "Temperature Sensor";
	case ZAHAP_PUMP:
		result =  "Pump";
	case ZAHAP_PUMP_CONTROLLER:
		result =  "Pump Controller";
	case ZAHAP_PRESSURE_SENSOR:
		result =  "Pressure Sensor";
	case ZAHAP_FLOW_SENSOR:
		result =  "Flow Sensor";
	case ZAHAP_IAS_CONTROL_AND_INDICATING_EQUIPMENT:
		result =  "Control and Indicating Equipment";
	case ZAHAP_IAS_ANCILLARY_CONTROL_EQUIPMENT:
		result =  "Ancillary Control Equipment";
	case ZAHAP_IAS_ZONE:
		result =  "Zone";
	case ZAHAP_IAS_WARNING_DEVICE:
		result =  "Warning Device";
	default:
		result =  "Unknown Device";
	}
#endif
