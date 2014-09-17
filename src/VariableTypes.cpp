/* ihand - VariableTypes.cpp
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

/** @file VariableTypes.cpp
 *  @brief
 */

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include "iHanClient/VariableTypes.hpp"

namespace iHanClient {

	typedef struct VariableTypes_t {
			uint32_t id;
			char name[32];
	} VariableTypes_t;

#define VARTYPE(x) {VarTypeHelper::x, {#x}}

	VariableTypes_t VarTypes[] {
			VARTYPE(CT_UNKNOWN),
			VARTYPE(CT_NAME),
			VARTYPE(CT_TYPE),
			VARTYPE(CT_SUBTYPE),
			VARTYPE(CT_LOCATION),
			VARTYPE(CT_ENABLED),
			VARTYPE(CT_SWITCH),
			VARTYPE(CT_TIME_SECONDS),
			VARTYPE(CT_DATE),
			VARTYPE(CT_STATUS_STRING),
			VARTYPE(CT_TEMP_F),
			VARTYPE(CT_TEMP_C),
			VARTYPE(CT_GENERAL),
			VARTYPE(CT_GENERAL_PERCENT),
			VARTYPE(CT_LUMINANCE_PERCENT),
			VARTYPE(CT_LUMINANCE_LUX),
			VARTYPE(CT_POWER_WATTS),
			VARTYPE(CT_POWER_BTU),
			VARTYPE(CT_HUMIDITY_PERCENT),
			VARTYPE(CT_VELOCITY_MS),
			VARTYPE(CT_VELOCITY_MPH),
			VARTYPE(CT_DIRECTION),
			VARTYPE(CT_ATMOSPHERIC_PRESSURE_KPA),
			VARTYPE(CT_ATMOSPHERIC_PRESSURE_IOM),
			VARTYPE(CT_BAROMETRIC_PRESSURE_KPA),
			VARTYPE(CT_BAROMETRIC_PRESSURE_IOM),
			VARTYPE(CT_SOLAR_WM2),
			VARTYPE(CT_DEW_C),
			VARTYPE(CT_DEW_F),
			VARTYPE(CT_RAIN_MMH),
			VARTYPE(CT_RAIN_INH),
			VARTYPE(CT_TIDE_M),
			VARTYPE(CT_TIDE_F),
			VARTYPE(CT_WEIGHT_KG),
			VARTYPE(CT_WEIGHT_POUNDS),
			VARTYPE(CT_VOLT_V),
			VARTYPE(CT_VOLT_MV),
			VARTYPE(CT_CURRENT_A),
			VARTYPE(CT_CURRENT_MA),
			VARTYPE(CT_CO2_PPM),
			VARTYPE(CT_AIRFLOW_M3H),
			VARTYPE(CT_AIRFLOW_CFM),
			VARTYPE(CT_TANK_L),
			VARTYPE(CT_TANK_CBM),
			VARTYPE(CT_TANK_USG),
			VARTYPE(CT_DISTANCE_M),
			VARTYPE(CT_DISTANCE_CM),
			VARTYPE(CT_DISTANCE_FEET),
			VARTYPE(CT_ANGLE_PERCENT),
			VARTYPE(CT_ANGLE_D_N),
			VARTYPE(CT_ANGLE_D_S),
			VARTYPE(CT_ROTATION_HZ),
			VARTYPE(CT_ROTATION_RPM),
			VARTYPE(CT_WATER_TEMP_C),
			VARTYPE(CT_WATER_TEMP_F),
			VARTYPE(CT_SOIL_TEMP_C),
			VARTYPE(CT_SOIL_TEMP_F),
			VARTYPE(CT_SEISMIC_INTENSITY_M),
			VARTYPE(CT_SEISMIC_INTENSITY_EUM),
			VARTYPE(CT_SEISMIC_INTENSITY_L),
			VARTYPE(CT_SEISMIC_MAGNITUDE_M),
			VARTYPE(CT_SEISMIC_MAGNITUDE_SW),
			VARTYPE(CT_SEISMIC_MAGNITUDE_BW),
			VARTYPE(CT_ULTRAVIOLET),
			VARTYPE(CT_ELECTRICAL_RESISTIVITY),
			VARTYPE(CT_ELECTRICAL_CONDUCTIVITY),
			VARTYPE(CT_LOUDNESS_DBA),
			VARTYPE(CT_LOUDNESS_DB),
			VARTYPE(CT_MOISTURE_PERCENT),
			VARTYPE(CT_MOISTURE_CONTENT),
			VARTYPE(CT_MOISTURE_KOHM),
			VARTYPE(CT_MOISTURE_WA),
			VARTYPE(CT_PERCENT),
			VARTYPE(CT_URL),
			VARTYPE(CT_LEVEL),
			VARTYPE(CT_TOD),
			VARTYPE(CT_ELECTRICAL_KWH),
			VARTYPE(CT_ELECTRICAL_KVAH),
			VARTYPE(CT_ELECTRICAL_WATTS),
			VARTYPE(CT_ELECTRICAL_POWER_FACTOR),
			VARTYPE(CT_METER_PULSES),
			VARTYPE(CT_WATERFLOW_CM),
			VARTYPE(CT_WATERFLOW_CF),
			VARTYPE(CT_WATERFLOW_USG),
			VARTYPE(CT_ENDOFLIST)
	};




	//extern VariableTypes_t VarTypes[];



#define ConfigTypeSize() (sizeof(VarTypes)/sizeof(*VarTypes))


	VarTypeHelper *VarTypeHelper::instance = NULL;

	VarTypeHelper *VarTypeHelper::Get() {
		if (instance)
			return instance;
		instance = new VarTypeHelper();
		return instance;
	}

	VarTypeHelper *VarTypeHelper::Create(HashVals vars) {
		if (instance)
			delete instance;
		instance = new VarTypeHelper(vars);
		return instance;
	}

	void VarTypeHelper::Destroy() {
		delete instance;
		instance = NULL;
	}


	VarTypeHelper::VarTypeHelper() : customid(1000){
		unsigned int i;
		for (i  = 0; i < ConfigTypeSize(); i++) {
			//this->mapping[VarTypes[i].id] = VarTypes[i].name;
			this->mapping.insert(std::pair<uint32_t, std::string>(VarTypes[i].id, VarTypes[i].name));
		}
	}

	VarTypeHelper::VarTypeHelper(HashVals vals) : customid(1000) {
		//std::cout << vals << std::endl;
		ListOptions lv = boost::get<ListOptions>(vals["VarType"]);
		int i = 0;
		while (lv[i].index != -1) {
			this->mapping.insert(std::pair<uint32_t, std::string>(lv[i].index, lv[i].desc));
			i++;
		}
	}


	VarTypeHelper::~VarTypeHelper() {
		this->mapping.clear();
	}

	HashVals VarTypeHelper::VarTypeToVarStorage() {
		unsigned int i;
		CreateListOptions(ConfigTypeLV, ConfigTypeSize());
		for (i = 0; i < ConfigTypeSize(); i++) {
			AddListOptions(ConfigTypeLV, i, VarTypes[i].id, VarTypes[i].name);
		}
		FinishListOptions(ConfigTypeLV, i++);
		HashVals hv;
		hv["VarType"] = (ListOptions)ConfigTypeLV;
		return hv;
	}

	std::string VarTypeHelper::VarTypetoName(uint32_t id) {
		if (this->mapping.find(id) != this->mapping.end())
			return this->mapping.at(id);
		else
			return "";
	}
	uint32_t VarTypeHelper::InsertVarType(std::string name) {
		this->mapping.insert(std::pair<uint32_t, std::string>(this->customid, name));
		return this->customid++;
	}
	uint32_t VarTypeHelper::VarTypeNametoID(std::string name) {
		for (std::map<uint32_t, std::string>::iterator iter = this->mapping.begin(); iter != this->mapping.end(); ++iter) {
			if (boost::iequals((*iter).second,name)) {
				return (*iter).first;
			}
		}
		return 0;
	}



} /* namespace */
