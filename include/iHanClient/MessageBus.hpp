/* ihand - MessageBus.h
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

/** @file MessageBus.h
 *  @brief
 */

#include "iHanClientDefs.hpp"
#include "varcontainer.hpp"
#include "MsgTypes.hpp"

#ifndef MESSAGEBUS_H_
#define MESSAGEBUS_H_


typedef struct vardef_t {
		char name[256];
		StoredType_t type;
} vardef_t;


/*! @brief This Class encapsulates all our Messages that we send between Devices and over the wire
 *
 * This Class is used to ensure we have a common format for all messages sent between devices
 * or over the wire.
 *
 * Use of this class is pretty basic. First, construct your messages using a VarStorage_t class and then
 * pass them to the create* methods on this class. You should ensure you check the return of each create method
 * to ensure it was accepted.
 *
 * You can also use the MessageBus_t::setDestination to direct this message to a particular device. (but the destination is dependant upon
 * the MessageType you are creating. Some messagetypes ignore destinations.)
 *
 * If you recieve a MessageBus_t message, you can use the MessageBus_t::getType first to figure out what type of message it is, then
 * use the get* methods to retrive the actual message.
 *
 */

class IHANCLIENT_EXPORT MessageBus_t {
public:
		/*! @brief Default Constructor of a MessageBus_t
		 *
		 * As the Internals use shared_ptr for all MessageBus_t messages, instead of creating a raw MessageBus_t
		 * you should use the Macro MessageBusFactory(x) (where x is the variable name) to create a shared Pointer
		 * that is already initilized with a MessageBus_t instance.
		 *
		 * @sa MessageBusFactory
		 */
		MessageBus_t();
		/*! @brief Default Destuctor
		 *
		 * As most of our MessageBus_t instances are managed via a Shared Pointer, there is no need to
		 * directly delete a MessageBus_t instance.
		 *
		 */
		virtual ~MessageBus_t();
		/*! @brief Create a Set Variable Message
		 *
		 * The Set Variable Message is used to send a message from one Device to another to change the target devices
		 * variables.
		 * The VarStorage_t variable you pass in is simply a list of the variables on the target device you want to change with
		 * their associated new values.
		 * Example:
		 * @code{.cpp}
		 *	VarContainerFactory(variables)
		 *	variables->setBoolValue("ENABLED", true);
		 *	MessageBusFactory(MsgBus);
		 *	MsgBus->createSetVar(variables, boost::uuids::to_string(this->getDeviceID());
		 *	MsgBus->setDestination(boost::uuids::to_string(target->getDeviceID());
		 * @endcode
		 *
		 * @sa MessageFlow
		 * @sa getSetVar
		 *
		 * @param[in] vars The Pre-Constructed list of Variables and their settings.
		 * @param[in] source The Source DeviceID of the Device Generating this message.
		 * @return success/failure of creating the SetVar Message
		 */
		bool createSetVar(VarStorage vars, std::string source);
		/*! @brief Create a Set Config Message
		 *
		 * The Set Config Message is used to send a message from one Device to another to change the target devices
		 * Configuration.
		 * The VarStorage_tvariable you pass in is simply a list of the Configuration Items on the target device you want to change with
		 * their associated new values.
		 * Example:
		 * @code{.cpp}
		 *	VarContainerFactory(config)
		 *	config->setBoolValue("ENABLED", true);
		 *	MessageBusFactory(MsgBus);
		 *	MsgBus->createSetConfig(variables, boost::uuids::to_string(this->getDeviceID());
		 *	MsgBus->setDestination(boost::uuids::to_string(target->getDeviceID());
		 * @endcode
		 *
		 * @sa MessageFlow
		 * @sa getSetConfig
		 *
		 * @param[in] config The Pre-Constructed list of Configuration Items and their settings.
		 * @param[in] source The Source DeviceID of the Device Generating this message.
		 * @return success/failure of creating the SetConfig Message
		 */
		bool createSetConfig(VarStorage config, std::string source);
		/*! @brief Create a Report Var Update Message
		 *
		 * The Report Var Message is used to send a update from a device to the messagebus (or over the wire) about a Variable
		 * value being updated. The Report Var Message can be triggered via either a SetVar Message, a actual change on the Device
		 * or directly on the client's variables.
		 *
		 * The structure of the ReportVar VarStorage_t is basically a list of Variables and their new values.
		 *
		 * Generally, you should not need to generate a ReportVar Message, as this should be taken care of by the iHanD software
		 * instead.
		 *
		 * @sa MessageFlow
		 * @sa createSetVar
		 * @sa getReportVar
		 *
		 * @param[in] vars The Pre-Constructed list of Variables and their new settings.
		 * @param[in] source The Source DeviceID of the Device Generating this message.
		 * @return success/failure of creating the ReportVar Message
		 */
		bool createReportVar(VarStorage vars, std::string source);
		/*! @brief Create a Report Configuration Update Message
		 *
		 * The Report Config Message is used to send a update from a device to the messagebus (or over the wire) about a Configuration
		 * value being updated. The Report Config Message can be triggered via either a SetConfig Message, a actual change on the Device
		 * or directly on the client's Configuration.
		 *
		 * The structure of the ReportConfig VarStorage_t is basically a list of Variables and their new values.
		 *
		 * Generally, you should not need to generate a ReportConfig Message, as this should be taken care of by the iHanD software
		 * instead.
		 *
		 * @sa MessageFlow
		 * @sa createSetConfig
		 * @sa getReportConfig
		 *
		 * @param[in] vars The Pre-Constructed list of Variables and their new settings.
		 * @param[in] source The Source DeviceID of the Device Generating this message.
		 * @return success/failure of creating the ReportConfig Message
		 */
		bool createReportConfig(VarStorage, std::string);
		/*! @brief Create a message about a new Client that has been added.
		 *
		 * This Method is used to communicate about new Clients that have been added to the iHanD software.
		 *
		 * The createNewDevice method should be called with the new clients details as follows:
		 * @code{.cpp}
		 *  MessageBusFactory(newClient);
		 *  newClient->createNewDevice(c->createClientInformPacket(), boost::uuids::to_string(this->getDeviceID()));
		 * @endcode
		 *
		 * @sa Ctlr::Clients::createClientInformPacket
		 * @sa getNewDevice
		 * @sa MessageFlow
		 *
		 * @param newclient A VarStorage variable returned from Ctlr::Clients::createClientInformPacket
		 * @param source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the newDevice Message
		 */
		bool createNewDevice(VarStorage newclient, std::string source);
		/*! @brief Create a message about a new Config Variable that has been added to a Client.
		 *
		 * This Method is used to communicate about new Config Variables that have been added to a Client.
		 *
		 * The createNewConfig method should be called when new Config values are added to a Client:
		 * @code{.cpp}
		 *  MessageBusFactory(newConfig);
		 *  VarStorage config = c->getConfigDescriptors()
		 *  VarStorage configvaluedescriptor;
		 *  config->getValueAsVarStorage("name", configvaluedescriptor);
		 *  newClient->createNewConfig(configvaluedescriptor, boost::uuids::to_string(this->getDeviceID()));
		 * @endcode
		 *
		 * @sa Ctlr::Clients::createClientInformPacket
		 * @sa getNewDevice
		 * @sa MessageFlow
		 *
		 * @param newconfigdescriptor A HashVal variable thats extracted from the Config Descriptor
		 * @param source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the createNewConfig Message
		 */
		bool createNewConfig(HashVals newconfigdescriptor, std::string source);
		/*! @brief Create a message about a new Var Variable that has been added to a Client.
		 *
		 * This Method is used to communicate about new Var Variables that have been added to a Client.
		 *
		 * The createNewVar method should be called when new Var values are added to a Client:
		 * @code{.cpp}
		 *  MessageBusFactory(newVar);
		 *  VarStorage vars = c->getConfigDescriptors()
		 *  VarStorage varvaluedescriptor;
		 *  vars->getValueAsVarStorage("name", varvaluedescriptor);
		 *  newClient->createNewVar(varvaluedescriptor, boost::uuids::to_string(this->getDeviceID()));
		 * @endcode
		 *
		 * @sa Ctlr::Clients::createClientInformPacket
		 * @sa getNewDevice
		 * @sa MessageFlow
		 *
		 * @param newvardescriptor A VarStorage variable thats extracted from the Config Descriptor
		 * @param source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the createNewConfig Message
		 */
		bool createNewVar(HashVals newvardescriptor, std::string source);
		/*! @brief Create a message about a Config Variable that has been deleted from a Client.
		 *
		 * This Method is used to communicate about Config Variables that have been Deleted from a Client.
		 *
		 * @sa createNewConfig
		 * @sa MessageFlow
		 *
		 * @param config The Config variable that has been deleted from the Config Descriptor
		 * @param source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the createDelConfig Message
		 */
		bool createDelConfig(std::string config, std::string source);
		/*! @brief Create a message about a Var Variable that has been deleted from a Client.
		 *
		 * This Method is used to communicate about Var Variables that have been Deleted from a Client.
		 *
		 * @sa createNewVar
		 * @sa MessageFlow
		 *
		 * @param config The Var variable that has been deleted from the Config Descriptor
		 * @param source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the createDelVar Message
		 */
		bool createDelVar(std::string var, std::string source);

		/*! @brief Create a message about a Client that has been deleted.
		 *
		 * This Method is used to communicate about Clients that have been deleted to the iHanD software.
		 *
		 * The createDelDevice method should be called with the deleted clients DeviceID as follows:
		 * @code{.cpp}
		 * MessageBusFactory(delClient);
		 * delClient->createDelDevice(boost::uuids::to_string(c->getDeviceID()), boost::uuids::to_string(this->getDeviceID()));
		 * @endcode
		 *
		 * @sa getDelDevice
		 * @sa MessageFlow
		 *
		 * @param DeviceID a String containing the DeviceID of the deleted client
		 * @param Source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the DelDevice Message
		 */

		bool createDelDevice(std::string DeviceID, std::string Source);
		/*! @brief Create a Setup Message
		 *
		 * This Method is used to communicate to Devices Certian non-device specific information. It is mainly used
		 * with TCP Clients and sends lists of Terms (for Scripting) or Variable Type Mappings (eg, temperture etc)
		 *
		 * The createSetup method should be called for each type of Generic Information you wish to pass.
		 * Bear in mind, not all Clients will understand your Setup Message. It requires explict code on the Client Side to parse
		 * the Setup Messages.
		 *
		 * @code{.cpp}
		 * VarContainerFactory(VarTypes);
		 * VarTypes->addHashValue("VarTypes", VarTypeHelper::Get()->VarTypeToVarStorage());
		 * VarTypes->setWhat(MSB_SETUP);
		 * MessageBusFactory(msg);
		 * msg->createSetup(VarTypes, boost::uuids::to_string(this->parent->getDeviceID()));
		 * @endcode
		 *
		 * @sa getSetup
		 * @sa MessageFlow
		 *
		 * @param[in] setup The Pre-Constructed list of Setup Messages. Stored as a Single Element.
		 * @param[in] Source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the createSetup Message
		 */

		bool createSetup(VarStorage setup, std::string Source);
		/*! @brief create a Client Capabilities Message
		 *
		 * This Method is used to create a Client Capabilities Message. It is used typically when a device is just joining
		 * the iHanD Server and wishes to communicate certian capabilities to the software. (such as Supporting SSL Encryption)
		 * or what Setup Messages it can parse.)
		 *
		 * @sa getClientCap
		 * @sa MessageFlow
		 *
		 * @param[in] caps a VarStorage_t variable contianing details about the clients capabilities.
		 * @param[in] Source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the createClientCap Message
		 */
		bool createClientCap(VarStorage caps, std::string Source);
		/*! @brief create a Server Capabilities Message
		 *
		 * This Method is used to create a Server Capabilities Message. It is used typically when a device is just joining
		 * the iHanD Server and the server needs to communicate certian capabilities to the software. (such as Supporting SSL Encryption)
		 * or what Setup Messages it can parse.)
		 *
		 * @param[in] caps a VarStorage_t variable contianing details about the Servers capabilities.
		 * @param[in] Source the Source DeviceID of the device Generating this message.
		 * @return success/failure of creating the createClientCap Message
		 */
		bool createServerCap(VarStorage caps, std::string Source);
		/*! @brief get the Type of Message this MessageBus_t contains
		 *
		 *  returns the Type of Message this instance of the MessageBus_t contains.
		 *
		 *  @sa MSG_BUS_TYPES
		 *  @sa setType
		 *
		 * @return the Type of Message or MSB_UNKNOWN if its invalid
		 */
		MSG_BUS_TYPES getType();
		/*! @brief get the Type of Message this MessageBus_t contians as a string
		 *
		 *  returns a string representation of the type of Message this instance of a MessageBus_t contains
		 *
		 *  @sa MSG_BUS_TYPES
		 *	@sa setType
		 *
		 * @return a String representing the type
		 */
		std::string getTypeAsString();
		/*! @brief Changes the Type of message this MessageBus_t contains
		 *
		 * this is used to change the type of Message the MessageBus_t contains.
		 * @warning No Conversion of Messages is attempted. You can not use this to change a SetConfig to a NewClient message for example
		 *
		 * @sa MSG_BUS_TYPES
		 * @sa getType
		 * @sa getTypeAsString
		 *
		 * @param type the new Type of message
		 * @return success/failure of the change.
		 */

		bool setType(MSG_BUS_TYPES type);
		/*! @brief Get the Source of this message
		 *
		 * Return the Source DeviceID of the client that originally generated this message
		 *
		 * @return the DeviceID of the client that generated this message, or a empty string on failure
		 */

		std::string getSource();
		/*! @brief Set the Destination for this message
		 *
		 * Sets the Destination for this message. Not all MessageTypes require a Destination.
		 *
		 * @sa MessageFlow
		 * @sa getDestination
		 * @sa setSource
		 * @sa getSource
		 *
		 * @param DeviceID the DeviceID of the client that should process this message
		 * @return success/failure
		 */
		bool setDestination(std::string DeviceID);
		/*! @brief Get the Destination for this message
		 *
		 * Gets the Destination for this message. Not all MessageTypes require a Destination.
		 *
		 * @sa MessageFlow
		 * @sa setDestination
		 * @sa setSource
		 * @sa getSource
		 *
		 * @return the DeviceID who this message is intended for
		 */
		std::string getDestination();
		/*! @brief Set this message as a Broadcast
		 *
		 * @todo This needs to be implemented.
		 *
		 * @return
		 */
		bool setBroadcast();
		/*! @brief Set this message as a MultiCast
		 *
		 * @todo This needs to be implemented
		 *
		 * @return
		 */
		bool setMultiCast();
		/*! @brief get a SetVar Message
		 *
		 * Gets a SetVar Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The SetVar Message is simply a list of Variables and their new values.
		 *
		 * @sa createSetVar
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing the list of Variables and the new values, or a empty VarStorage_t on failure
		 */
		VarStorage getSetVar();
		/*! @brief get a SetConfig Message
		 *
		 * Gets a SetConfig Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The SetConfig Message is simply a list of Configuration Items and their new values.
		 *
		 * @sa createSetConfig
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing the list of Configuration Items and the new values, or a empty VarStorage_t on failure
		 */

		VarStorage getSetConfig();
		/*! @brief get a ReportVar Message
		 *
		 * Gets a ReportVar Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The ReportVar Message is simply a list of Updated Variables and their new values.
		 *
		 * @sa createReportVar
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing the list of Updated Variables and their new values, or a empty VarStorage_t on failure
		 */
		VarStorage getReportVar();
		/*! @brief get a ReportConfig Message
		 *
		 * Gets a ReportConfig Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The ReportConfig Message is simply a list of Updated Configuration Items and their new values.
		 *
		 * @sa createReportConfig
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing the list of Updated Configuration Items and their new values, or a empty VarStorage_t on failure
		 */

		VarStorage getReportConfig();
		/*! @brief get a NewDevice Message
		 *
		 * Gets a NewDevice Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The NewDevice Message is contains details about the new device (Name, Serial Number, Parent Serial Number and Type) as well
		 * as a list of Config Variables (and Config Descriptors) and Variables (and associated Variable Descriptors)
		 *
		 * @sa setNewDevice
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing details about the new device, or a empty VarStorage_t on failure
		 */
		VarStorage getNewDevice();
		/*! @brief get a New Config Variable Message
		 *
		 * Gets a New Config Variable Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The New Config Variable Message is contains details about a new Config Variable that has been added to a client.
		 * the Contents is a Config Descriptors describing the new Config Variable.
		 *
		 * @sa setNewDevice
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing a VarDescriptor for the new Config Variable, or a empty VarStorage_t on failure
		 */
		VarStorage getNewConfig();
		/*! @brief get a New Var Variable Message
		 *
		 * Gets a New Var Variable Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The New Var Variable Message is contains details about a new Config Variable that has been added to a client.
		 * the Contents is a Config Descriptors describing the new Config Variable.
		 *
		 * @sa setNewDevice
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing a VarDescriptor for the new Var Variable, or a empty VarStorage_t on failure
		 */
		VarStorage getNewVar();
		/*! @brief get a Del Config Variable Message
		 *
		 * Gets a Del Config Variable Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The Del Config Variable Message is contains details about a Config Variable that has been deleted from a client.
		 * the Contents is a VarStorage containing the Variable Deleted in a String variable called DelConfig.
		 *
		 * @sa createDelConfig
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing a VarContainer for the Deleted Config Variable, or a empty VarStorage_t on failure
		 */
		VarStorage getDelConfig();
		/*! @brief get a Del Var Variable Message
		 *
		 * Gets a Del Var Variable Message from the MessageBus_t message. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * The Del Var Variable Message is contains details about a Var Variable that has been deleted from a client.
		 * the Contents is a VarStorage containing the Variable Deleted in a String variable called DelVar.
		 *
		 * @sa createDelConfig
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing a VarContainer for the Deleted Var Variable, or a empty VarStorage_t on failure
		 */
		VarStorage getDelVar();

		/*! @brief get a Setup Message
		 *
		 * Gets a setup message from the device. The format/layout of a Setup message is user defined.
		 *
		 * @sa setSetup
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable contianing details about the Setup, or a empty VarStorage_t on failure
		 */
		VarStorage getSetup();
		/*! @brief get the Serial Number of a Deleted Device.
		 *
		 * returns the Serial Number (DeviceID) of a Deleted Device. You should first check the MessageType with getType to determine
		 * what type of message this MessageBus contains.
		 *
		 * @sa setDelDevice
		 * @sa MessageFlow
		 *
		 * @return the Serial Number (DeviceID) fo a Deleted Device or a emtpy string on failure.
		 */
		std::string getDelDevice();
		/*! @brief get a Client Capabilities Message
		 *
		 * Returns a Client Capabilities Message of the Device. It is used typically when a device is just joining
		 * the iHanD Server and wishes to communicate certian capabilities to the software. (such as Supporting SSL Encryption)
		 * or what Setup Messages it can parse.)
		 *
		 * @sa setClientCap
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t variable containing the Client Capabilities, or a empty VarStorage_t on failure
		 */
		VarStorage getClientCap();
		/*! @brief get a Server Capabilities Message
		 *
		 * Gets a Server Capabilities Message sent by the Server. It is used typically when a device is just joining
		 * the iHanD Server and wishes to communicate certian capabilities to the software. (such as Supporting SSL Encryption)
		 * or what Setup Messages it can parse.)
		 *
		 * @sa setServerCap
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t Variable containing the Server Capabilities, or a empty VarStorage_t on failure
		 */
		VarStorage getServerCap();
		/*! @brief get a VarStorage_t Representation of this MessageBus_t instance
		 *
		 * The function is used to retrieve a serialize the MessageBus_t instance to a VarStorage_t variable that is suitable
		 * for tranmission over the wire to remove devices or the server.
		 *
		 * @sa importTransportVarStorage
		 * @sa MessageFlow
		 *
		 * @return a VarStorage_t representation of this MessageBus_t instance, or a empty VarStorage_t on failure
		 */
		VarStorage getTransportVarStorage();
		/*! @brief Import a VarStorage_t Variable that was created by MessageBus_t::getTransportVarStorage
		 *
		 * this method takes a VarStorage_t Varaible created by MessageBus_t::getTransportVarStorage() and de-serializes it back
		 * to a MessageBus_t instance. This is used to transmit MessageBus_t instances over the wire.
		 *
		 * @sa getTransportVarStorage
		 * @sa MessageFlow
		 *
		 * @param[in] msg the VarStorage_t Variable created with MessageBus_t::getTransportVarStorage
		 * @return success/failure to de-serialize the message
		 */
		bool importTransportVarStorage(VarStorage msg);
private:
		friend std::ostream& operator<<(std::ostream&, MessageBus_t &);
		bool checkNewDevice(VarStorage msg);
		bool checkVars(VarStorage msg, vardef_t *checks);
		IHANCLIENT_EXPORT_WARNINGS_OFF
		VarStorage message;
		std::string source;
		std::string destination;
		IHANCLIENT_EXPORT_WARNINGS_ON
};

/*! @brief Test if the Message is a Report Type Message
 *
 * @param[in] type The MessageBus_t Type, retrieved via MessageBus_t::GetType()
 * @return true if its a Report type message, false for all others.
 */
IHANCLIENT_EXPORT bool MsgIsReport(MSG_BUS_TYPES type);
/*! @brief Test if the message is a Set Type Message
 *
 * @param[in] type the MessageBus_t Type, retrieved via MessageBus_t::GetType()
 * @return true if its a Set Type message, false for all others.
 */
IHANCLIENT_EXPORT bool MsgIsSet(MSG_BUS_TYPES type);

/*! @brief TypeDef defining a shared pointer for MessageBus_t instances
 *
 * all MessageBus_t instances are wrapped in a shared pointer for memory management requirements. You should not create
 * a MessageBus_t instance, but rather a Shared Pointer via the MessageBusFactory macro
 */
typedef boost::shared_ptr<MessageBus_t> MessageBus;

/*! @brief Create a new MessageBusy Instance
 *
 * @param x the Name of the new variable
 */
#define MessageBusFactory(x) MessageBus x(new MessageBus_t());


IHANCLIENT_EXPORT std::ostream& operator<<(std::ostream&, const MessageBus_t &);
IHANCLIENT_EXPORT std::ostream& operator<<(std::ostream &os, const MessageBus &ptr);


#endif /* MESSAGEBUS_H_ */
