/* ihand - VariableTypes.hpp
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
** ihand SVN Identification:
** $Rev$
*/

/** @file VariableTypes.hpp
 *  @brief
 */


#include <iHanClient/varcontainer.hpp>

#ifndef VARIABLETYPES_HPP_
#define VARIABLETYPES_HPP_




namespace iHanClient {





class VarTypeHelper {
	public:
		static VarTypeHelper *Get();
		static VarTypeHelper *Create(HashVals vars);
		static void Destroy();
		HashVals VarTypeToVarStorage();
		std::string VarTypetoName(uint32_t id);
		uint32_t InsertVarType(std::string name);
		uint32_t VarTypeNametoID(std::string name);
		typedef enum ConfigType {
		    /* Unknown Type */
		    CT_UNKNOWN = 0x00,
		    /* The name of the device  (String) */
		    CT_NAME,
		    /* The Type of Device (DeviceType - int/enum ) */
		    CT_TYPE,
		    /* The SubType of the Device ( Dependant on DeviceType - int )*/
		    CT_SUBTYPE,
		    /* The Location of the Device (String) */
		    CT_LOCATION,
		    /* Is Device Enabled (Bool) */
		    CT_ENABLED,
		    /* A On/Off Switch (Bool) */
		    CT_SWITCH,
		    /* A Time Value Represented in Seconds (int) */
		    CT_TIME_SECONDS,
		    /* A Date Value Represented as a String (string) */
		    CT_DATE,
		    /* A Generic Status String (string)*/
		    CT_STATUS_STRING,
		    /* A Temp Represented in Farienhight (int)*/
		    CT_TEMP_F,
		    /* A Temp Represented in Centigrade (int)*/
		    CT_TEMP_C,
		    /* a General Purpose Value (int)*/
		    CT_GENERAL,
		    /* a General Purpose Value (%) */
		    CT_GENERAL_PERCENT,
		    /* Luminance Value (%) */
		    CT_LUMINANCE_PERCENT,
		    /* Luminance Value (Lux) */
		    CT_LUMINANCE_LUX,
		    /* power in watts (int) */
		    CT_POWER_WATTS,
		    /* power in Btu/H (int) */
		    CT_POWER_BTU,
		    /* Relative Humidity (int) */
		    CT_HUMIDITY_PERCENT,
		    /* Velocity in m/s (int) */
		    CT_VELOCITY_MS,
		    /* Velocity in miles per hour */
		    CT_VELOCITY_MPH,
		    /* Direction in degrees (int) */
		    CT_DIRECTION,
		    /* Atmostpheric Pressure in kPa (int) */
		    CT_ATMOSPHERIC_PRESSURE_KPA,
		    /* Atmostpheric Pressure in inches of Mercury */
		    CT_ATMOSPHERIC_PRESSURE_IOM,
		    /* Barometric Pressure in kPa (int) */
		    CT_BAROMETRIC_PRESSURE_KPA,
		    /* Barometric Pressure in inches of Mercury */
		    CT_BAROMETRIC_PRESSURE_IOM,
		    /* Solar Radition in W/m2*/
		    CT_SOLAR_WM2,
		    /* Dew Point in Celsius */
		    CT_DEW_C,
		    /* Dew Point in Fahrenheit */
		    CT_DEW_F,
		    /* Rain Rate in mm/h */
		    CT_RAIN_MMH,
		    /* Rain Rate in in/h */
		    CT_RAIN_INH,
		    /* Tide Level in Meters */
		    CT_TIDE_M,
		    /* Tide Level in Feet */
		    CT_TIDE_F,
		    /* Weight in kg */
		    CT_WEIGHT_KG,
		    /* weight in pounds */
		    CT_WEIGHT_POUNDS,
		    /* Voltage in V */
		    CT_VOLT_V,
		    /* Voltage in mV */
		    CT_VOLT_MV,
		    /* Current in A */
		    CT_CURRENT_A,
		    /* Current in mA */
		    CT_CURRENT_MA,
		    /* OC2-Level in ppm */
		    CT_CO2_PPM,
		    /* Air Flow in m3/h */
		    CT_AIRFLOW_M3H,
		    /* Air Flow in cfm */
		    CT_AIRFLOW_CFM,
		    /* Tank Capacity in liters */
		    CT_TANK_L,
		    /* Tank Capacity in cbm */
		    CT_TANK_CBM,
		    /* Tank Capacity in US gallons */
		    CT_TANK_USG,
		    /* Distance in m */
		    CT_DISTANCE_M,
		    /* Distance in cm */
		    CT_DISTANCE_CM,
		    /* Distance in Feet */
		    CT_DISTANCE_FEET,
		    /* Angle Position in Percentage*/
		    CT_ANGLE_PERCENT,
		    /* Angle Position in Degrees North */
		    CT_ANGLE_D_N,
		    /* Angle Position in Degrees South */
		    CT_ANGLE_D_S,
		    /* Rotation Speed in Hertz*/
		    CT_ROTATION_HZ,
		    /* Rotation Speed in RPM */
		    CT_ROTATION_RPM,
		    /* Water Temperature in Celsius */
		    CT_WATER_TEMP_C,
		    /* Water Temp in Fahrenheit */
		    CT_WATER_TEMP_F,
		    /* Soil Temp in C */
		    CT_SOIL_TEMP_C,
		    /* Soil Temp in F */
		    CT_SOIL_TEMP_F,
		    /* Seismic Intensity in mercalli */
		    CT_SEISMIC_INTENSITY_M,
		    /* Seismic Intensity in EU macroseismic */
		    CT_SEISMIC_INTENSITY_EUM,
		    /* Seismic Intensity in liedu */
		    CT_SEISMIC_INTENSITY_L,
		    /* Seismic Intensity in shindo */
		    CT_SEISMIC_INTENSITY_S,
		    /* Seismic Magnitude in local */
		    CT_SEISMIC_MAGNITUDE_L,
		    /* Seismic Magnitude in moment */
		    CT_SEISMIC_MAGNITUDE_M,
		    /* Seismic Magnitude in surface wave */
		    CT_SEISMIC_MAGNITUDE_SW,
		    /* Seismic Magnitude in body wave */
		    CT_SEISMIC_MAGNITUDE_BW,
		    /* Ultraviolet Light Radition */
		    CT_ULTRAVIOLET,
		    /* Electrical Resistivity */
		    CT_ELECTRICAL_RESISTIVITY,
		    /* Electrical Conductivity */
		    CT_ELECTRICAL_CONDUCTIVITY,
		    /* Loudness in dBA */
		    CT_LOUDNESS_DBA,
		    /* Loudness in DB */
		    CT_LOUDNESS_DB,
		    /* Moisture in percentage */
		    CT_MOISTURE_PERCENT,
		    /* Moisture in content */
		    CT_MOISTURE_CONTENT,
		    /* Moisture in KiloOhms */
		    CT_MOISTURE_KOHM,
		    /* Moisture in water activity */
		    CT_MOISTURE_WA,
		    /* A Percentage (int) */
		    CT_PERCENT,
		    /* A URL (string) */
		    CT_URL,
		    /* A Level Value (255 Max) */
		    CT_LEVEL,
		    /* Time of Day */
		    CT_TOD,
		    /* kWh */
		    CT_ELECTRICAL_KWH,
		    /* kVAh */
		    CT_ELECTRICAL_KVAH,
		    /* WATTS */
		    CT_ELECTRICAL_WATTS,
		    /* Power Factor */
		    CT_ELECTRICAL_POWER_FACTOR,
		    /* Meter Pulses */
		    CT_METER_PULSES,
		    /* Water Flow - Cubic Meters */
		    CT_WATERFLOW_CM,
		    /* Water Flow - Cubic Feed */
		    CT_WATERFLOW_CF,
		    /* Water Flow - US Galons */
		    CT_WATERFLOW_USG,
		    /* End of List */
		    CT_ENDOFLIST = 20000
		} ConfigType;
	private:
		VarTypeHelper();
		VarTypeHelper(HashVals vars);
		virtual ~VarTypeHelper();
		VarTypeHelper(VarTypeHelper const&);
		VarTypeHelper & operator=(VarTypeHelper const&);
		std::map<uint32_t, std::string> mapping;
		static VarTypeHelper *instance;
		uint32_t customid;
};

}

#endif /* VARIABLETYPES_HPP_ */
