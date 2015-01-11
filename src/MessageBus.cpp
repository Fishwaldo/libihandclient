/* ihand - MessageBus.cpp
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

/** @file MessageBus.cpp
 *  @brief
 */

#include "iHanClient/MessageBus.hpp"
#include "iHanClient/LogClass.hpp"


vardef_t clncapcheck[] = {
		{MSGB_CLNCAP_AUTHUSER, ST_STRING},
		{MSGB_CLNCAP_AUTHKEY, ST_STRING},
		{MSGB_CLNCAP_CAPDEVICE, ST_LONG},
		{MSGB_CLNCAP_HOSTID, ST_LONG},
		{MSGB_CLNCAP_FLAGS, ST_LONGLONG},
		{"", ST_INVALID}
};



MessageBus_t::MessageBus_t() {

}

MessageBus_t::~MessageBus_t() {
}

bool MessageBus_t::createSetVar(VarStorage var, std::string source) {
	if (var) {
		this->message = var;
		this->message->setWhat(MSB_SET_VAR);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}
bool MessageBus_t::createSetConfig(VarStorage config, std::string source) {
	if (config) {
		this->message = config;
		this->message->setWhat(MSB_SET_CONFIG);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;

}
bool MessageBus_t::createReportVar(VarStorage var, std::string source) {
	if (var) {
		this->message = var;
		this->message->setWhat(MSB_REPORT_VAR);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;

}
bool MessageBus_t::createReportConfig(VarStorage config, std::string source) {
	if (config) {
		this->message = config;
		this->message->setWhat(MSB_REPORT_CONFIG);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}
bool MessageBus_t::createNewDevice(VarStorage config, std::string source) {
	if (config) {
		if (!this->checkNewDevice(config))
			return false;
		this->message = config;
		this->message->setWhat(MSB_NEW_DEVICE);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}

bool MessageBus_t::createNewConfig(HashVals newconfigdescriptor, std::string source) {
	VarContainerFactory(newConfig);
	newConfig->addHashValue("ConfigDescriptor", newconfigdescriptor);

	if (newConfig) {
		this->message = newConfig;
		this->message->setWhat(MSB_ADD_CONFIG);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}
bool MessageBus_t::createNewVar(HashVals newvardescriptor, std::string source) {
	VarContainerFactory(newVar);
	newVar->addHashValue("VarDescriptor", newvardescriptor);

	if (newVar) {
		this->message = newVar;
		this->message->setWhat(MSB_ADD_CONFIG);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}

bool MessageBus_t::createDelConfig(std::string config, std::string source) {
	VarContainerFactory(delConfig);
	delConfig->addStringValue("DelConfig", config);
	if (delConfig) {
		this->message = delConfig;
		this->message->setWhat(MSB_DEL_CONFIG);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}

bool MessageBus_t::createDelVar(std::string config, std::string source) {
	VarContainerFactory(delVar);
	delVar->addStringValue("delVar", config);
	if (delVar) {
		this->message = delVar;
		this->message->setWhat(MSB_DEL_VAR);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;

}

bool MessageBus_t::createDelDevice(std::string DeviceID, std::string source) {
	if (DeviceID.length() > 0) {
		VarContainerFactory(delDevice);
		delDevice->addStringValue(SRVCAP_ENDPT_SERIAL, DeviceID);
		this->message = delDevice;
		this->message->setWhat(MSB_DEL_DEVICE);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}

bool MessageBus_t::createSetup(VarStorage setup, std::string source) {
	if (setup) {
		this->message = setup;
		this->message->setWhat(MSB_SETUP);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}
bool MessageBus_t::createClientCap(VarStorage cap, std::string source) {
	if (cap) {
		if (!this->checkVars(cap, clncapcheck)) {
			iHanClient::Logging::LogWarn(std::string("Check createClientCap Failed"));
			return false;
		}
		this->message = cap;
		this->message->setWhat(MSB_CLIENT_CAP);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}
bool MessageBus_t::createServerCap(VarStorage cap, std::string source) {
	if (cap) {
		this->message = cap;
		this->message->setWhat(MSB_SERVER_CAP);
		this->source = source;
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Var Passed"));
	return false;
}

MSG_BUS_TYPES MessageBus_t::getType() {
	if (this->message)
		return (MSG_BUS_TYPES)this->message->getWhat();

	iHanClient::Logging::LogWarn(std::string("MessageBus has not been Created Yet"));
	return MSB_UNKNOWN;
}
std::string MessageBus_t::getTypeAsString() {
	if (this->message) {
		switch ((MSG_BUS_TYPES)this->message->getWhat()) {
			case MSB_SET_CONFIG:
				return "SetConfig";
			case MSB_SET_VAR:
				return "SetVar";
			case MSB_REPORT_CONFIG:
				return "ReportConfig";
			case MSB_REPORT_VAR:
				return "ReportVar";
			case MSB_NEW_DEVICE:
				return "NewDevice";
			case MSB_DEL_DEVICE:
				return "DelDevice";
			case MSB_SETUP:
				return "Setup";
			case MSB_CLIENT_CAP:
				return "ClientCap";
			case MSB_SERVER_CAP:
				return "ServerCap";
			case MSB_ADD_CONFIG:
				return "AddConfigDescriptor";
			case MSB_ADD_VAR:
				return "AddVarDescriptor";
			case MSB_DEL_CONFIG:
				return "DelConfigVar";
			case MSB_DEL_VAR:
				return "DelVarVar";
			case MSB_UNKNOWN:
				return "Unknown";
		}
		return "Unknown (Out of Range)";
	}
	iHanClient::Logging::LogWarn(std::string("MessageBus has not been Created Yet"));
	return "Unknown (Not Set)";
}

bool MessageBus_t::setType(MSG_BUS_TYPES type) {
	if (this->message) {
		this->message->setWhat(type);
		return true;
	}
	iHanClient::Logging::LogWarn(std::string("MessageBus has not been Created Yet"));
	return false;
}
std::string MessageBus_t::getSource() {
	return this->source;
}

bool MessageBus_t::setDestination(std::string dst) {
	this->destination = dst;
	return true;
}
std::string MessageBus_t::getDestination() {
	return this->destination;
}
bool MessageBus_t::setBroadcast() {
	// XXX TODO
	return false;
}
bool MessageBus_t::setMultiCast() {
	// XXX TODO
	return false;
}

VarStorage MessageBus_t::getSetVar() {
	if (this->message) {
		if (this->message->getWhat() == MSB_SET_VAR)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a SET Var Message: " +  this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}
VarStorage MessageBus_t::getSetConfig() {
	if (this->message) {
		if (this->message->getWhat() == MSB_SET_CONFIG)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a SET Config Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}
VarStorage MessageBus_t::getReportVar() {
	if (this->message) {
		if (this->message->getWhat() == MSB_REPORT_VAR) {
			/* add the Source */
			return this->message;
		}
		iHanClient::Logging::LogWarn(std::string("Not a Report Var Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}
VarStorage MessageBus_t::getReportConfig() {
	if (this->message) {
		if (this->message->getWhat() == MSB_REPORT_CONFIG)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a Report Config Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}
VarStorage MessageBus_t::getNewDevice() {
	if (this->message) {
		if (this->message->getWhat() == MSB_NEW_DEVICE)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a new Device Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}

VarStorage MessageBus_t::getNewConfig() {
	if (this->message) {
		if (this->message->getWhat() == MSB_ADD_CONFIG)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a new Config Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}

VarStorage MessageBus_t::getNewVar() {
	if (this->message) {
		if (this->message->getWhat() == MSB_ADD_VAR)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a new Var Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}

VarStorage MessageBus_t::getDelConfig() {
	if (this->message) {
		if (this->message->getWhat() == MSB_DEL_CONFIG)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a Del Config Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}
VarStorage MessageBus_t::getDelVar() {
	if (this->message) {
		if (this->message->getWhat() == MSB_DEL_VAR)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a Del Var Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}

std::string MessageBus_t::getDelDevice() {
	std::string DeviceID;
	if (this->message) {
		if (this->message->getWhat() == MSB_DEL_DEVICE) {
			this->message->getStringValue(SRVCAP_ENDPT_SERIAL, DeviceID);
			return DeviceID;
		}
		iHanClient::Logging::LogWarn(std::string("Not a Del Device Message:" + this->getTypeAsString()));
		return DeviceID;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return DeviceID;
}

VarStorage MessageBus_t::getSetup() {
	if (this->message) {
		if (this->message->getWhat() == MSB_SETUP)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a Setup Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}

VarStorage MessageBus_t::getClientCap() {
	if (this->message) {
		if (this->message->getWhat() == MSB_CLIENT_CAP)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a ClientCap Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}
VarStorage MessageBus_t::getServerCap() {
	if (this->message) {
		if (this->message->getWhat() == MSB_SERVER_CAP)
			return this->message;
		iHanClient::Logging::LogWarn(std::string("Not a ServerCap Message:" + this->getTypeAsString()));
		return VarStorage(new VarStorage_t());
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return VarStorage(new VarStorage_t());
}


VarStorage MessageBus_t::getTransportVarStorage() {
	VarContainerFactory(vars);
	if (this->message) {
		vars->addStringValue(MSGB_FROM, this->source);
		if (this->destination.length() >0)
			vars->addStringValue(MSGB_TO, this->destination);
		vars->setWhat(this->message->getWhat());
		switch ((MSG_BUS_TYPES)this->message->getWhat()) {
			case MSB_SET_VAR:
			case MSB_REPORT_VAR:
				vars->addVarStorageValue(SRVCAP_ENDPT_VARS, this->message);
				break;
			case MSB_SET_CONFIG:
			case MSB_REPORT_CONFIG:
				vars->addVarStorageValue(SRVCAP_ENDPT_CONFIG, this->message);
				break;
			case MSB_NEW_DEVICE:
				if (!this->checkNewDevice(this->message)) {
					return vars;
				}
				vars = this->message;
				break;
			case MSB_DEL_DEVICE:
				vars = this->message;
				break;
			case MSB_SETUP:
				vars = this->message;
				break;
			case MSB_CLIENT_CAP:
				vars = this->message;
				break;
			case MSB_SERVER_CAP:
				vars = this->message;
				break;
			case MSB_ADD_CONFIG:
				vars->addVarStorageValue(SRVCAP_ENDPT_CONFIG_DESC, this->message);
				break;
			case MSB_ADD_VAR:
				vars->addVarStorageValue(SRVCAP_ENDPT_VARS_DESC, this->message);
				break;
			case MSB_DEL_CONFIG:
				vars->addVarStorageValue(SRVCAP_ENDPT_CONFIG_DESC, this->message);
				break;
			case MSB_DEL_VAR:
				vars->addVarStorageValue(SRVCAP_ENDPT_VARS_DESC, this->message);
				break;
			case MSB_UNKNOWN:
				/* Empty */
				break;
		}
		return vars;
	}
	iHanClient::Logging::LogWarn(std::string("Invalid Message"));
	return vars;
}

bool MessageBus_t::importTransportVarStorage(VarStorage msg) {
	if (msg == NULL) {
		iHanClient::Logging::LogWarn(std::string("Invalid Message"));
		return false;
	}
	bool ret = false;
	switch ((MSG_BUS_TYPES)msg->getWhat()) {
		case MSB_SET_VAR:
		case MSB_REPORT_VAR:
			ret = msg->getVarStorageValue(SRVCAP_ENDPT_VARS, this->message);
			if (!ret) {
				iHanClient::Logging::LogWarn(std::string("Failed to get EndPt Vars from Message"));
				return false;
			}
			this->message->setWhat(msg->getWhat());
			break;
		case MSB_SET_CONFIG:
		case MSB_REPORT_CONFIG:
			ret = msg->getVarStorageValue(SRVCAP_ENDPT_CONFIG, this->message);
			if (!ret) {
				iHanClient::Logging::LogWarn(std::string("Failed to get EndPt Vars from Message"));
				return false;
			}
			this->message->setWhat(msg->getWhat());
			break;
		case MSB_NEW_DEVICE:
			if (!this->checkNewDevice(msg)) {
				return false;
			}
			this->message = msg;
			this->message->setWhat(msg->getWhat());
			/* No Further Processing Required */
			return true;
			break;
		case MSB_DEL_DEVICE:
			/* Check the Fields */
			if (msg->getSize(SRVCAP_PARENT_SERIAL) != 1)
				return false;
			this->message = msg;
			this->message->setWhat(MSB_DEL_DEVICE);
			return true;
		case MSB_SETUP:
			this->message = msg;
			this->message->setWhat(MSB_SETUP);
			return true;
		case MSB_CLIENT_CAP:
			this->message = msg;
			this->message->setWhat(MSB_CLIENT_CAP);
			return true;
		case MSB_SERVER_CAP:
			this->message = msg;
			this->message->setWhat(MSB_SERVER_CAP);
			return true;
		case MSB_ADD_CONFIG:
			ret = msg->getVarStorageValue(SRVCAP_ENDPT_CONFIG_DESC, this->message);
			if (!ret) {
				iHanClient::Logging::LogWarn(std::string("Failed to get EndPt Config Vars from Message"));
				return false;
			}
			this->message->setWhat(msg->getWhat());
			return true;
		case MSB_ADD_VAR:
			ret = msg->getVarStorageValue(SRVCAP_ENDPT_VARS_DESC, this->message);
			if (!ret) {
				iHanClient::Logging::LogWarn(std::string("Failed to get EndPt Vars from Message"));
				return false;
			}
			this->message->setWhat(msg->getWhat());
			return true;
		case MSB_DEL_CONFIG:
			ret = msg->getVarStorageValue(SRVCAP_ENDPT_CONFIG_DESC, this->message);
			if (!ret) {
				iHanClient::Logging::LogWarn(std::string("Failed to get EndPt Config Vars from Message"));
				return false;
			}
			this->message->setWhat(msg->getWhat());
			return true;
		case MSB_DEL_VAR:
			ret = msg->getVarStorageValue(SRVCAP_ENDPT_VARS_DESC, this->message);
			if (!ret) {
				iHanClient::Logging::LogWarn(std::string("Failed to get EndPt Vars from Message"));
				return false;
			}
			this->message->setWhat(msg->getWhat());
			return true;
		case MSB_UNKNOWN:
			return false;
	}
	if (!ret)
		return false;
	if (!msg->getStringValue(MSGB_FROM, this->source)) {
		iHanClient::Logging::LogWarn(std::string("Source is not Set"));
		return false;
	}
	if (!msg->getStringValue(MSGB_TO, this->destination)) {
		if (MsgIsSet((MSG_BUS_TYPES)this->message->getWhat())) {
			iHanClient::Logging::LogWarn(std::string("Destination is Not Set"));
			return false;
		}
	}
	return true;
}

bool MessageBus_t::checkNewDevice(VarStorage msg) {
	if (!msg) {
		iHanClient::Logging::LogWarn(std::string("Invalid Message"));
		return false;
	}
	/* Check The necessary Fields */
	if (msg->getSize(SRVCAP_PARENT_SERIAL) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing Parent Serial Field"));
		return false;
	}
	if (msg->getSize(SRVCAP_ENDPT_TYPE) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing End Point Type Field"));
		return false;
	}
	if (msg->getSize(SRVCAP_ENDPT_SERIAL) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing Serial Field"));
		return false;
	}
	if (msg->getSize(SRVCAP_ENDPT_NAME) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing Name Field"));
		return false;
	}
	if (msg->getSize(SRVCAP_ENDPT_CONFIG_DESC) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing Config Descriptor Field"));
		return false;
	}
	if (msg->getSize(SRVCAP_ENDPT_CONFIG) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing Config Field"));
		return false;
	}
	if (msg->getSize(SRVCAP_ENDPT_VARS_DESC) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing Vars Descriptor Field"));
		return false;
	}
	if (msg->getSize(SRVCAP_ENDPT_VARS) != 1) {
		iHanClient::Logging::LogWarn(std::string("MSB_NEW_DEVICE - Missing Vars Field"));
		return false;
	}
	return true;
}





bool MessageBus_t::checkVars(VarStorage msg, vardef_t *checks) {
	while (checks->type != ST_INVALID) {
		if (msg->getSize(checks->name) != 1) {
			iHanClient::Logging::LogWarn(std::string("checkVars - Field Invalid: " + std::string(checks->name)));
			return false;
		}
		if (msg->getType(checks->name) != checks->type) {
			iHanClient::Logging::LogWarn(std::string("checkVars - Wrong Field Type: " + checks->type));
			return false;
		}
		checks++;
	}
	return true;
}



bool MsgIsReport(MSG_BUS_TYPES type) {
	switch (type) {
		case MSB_REPORT_VAR:
		case MSB_REPORT_CONFIG:
			return true;
		case MSB_SET_VAR:
		case MSB_SET_CONFIG:
		case MSB_NEW_DEVICE:
		case MSB_DEL_DEVICE:
		case MSB_SETUP:
		case MSB_CLIENT_CAP:
		case MSB_SERVER_CAP:
		case MSB_ADD_CONFIG:
		case MSB_ADD_VAR:
		case MSB_DEL_CONFIG:
		case MSB_DEL_VAR:
		case MSB_UNKNOWN:
			return false;
	}
	return false;
}
bool MsgIsSet(MSG_BUS_TYPES type) {
	switch (type) {
		case MSB_REPORT_VAR:
		case MSB_REPORT_CONFIG:
			return false;
		case MSB_SET_VAR:
		case MSB_SET_CONFIG:
			return true;
		case MSB_NEW_DEVICE:
		case MSB_DEL_DEVICE:
		case MSB_SETUP:
		case MSB_CLIENT_CAP:
		case MSB_SERVER_CAP:
		case MSB_ADD_CONFIG:
		case MSB_ADD_VAR:
		case MSB_DEL_CONFIG:
		case MSB_DEL_VAR:
		case MSB_UNKNOWN:
			return false;
	}
	return false;
}


std::ostream& operator<<(std::ostream &os, const MessageBus &ptr) {
        os << *ptr.get();
	return os;
}


std::ostream& operator<<(std::ostream &stream, MessageBus_t &vs) {
	stream << "MessageBus Type: " << vs.getTypeAsString() << std::endl;
	stream << "Source: " << vs.getSource() << " Destination: " << vs.getDestination() << std::endl;
	stream << "Content: " << vs.message << std::endl;
	return stream;
}


