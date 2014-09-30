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

#include "varcontainer.hpp"
#include "MsgTypes.hpp"

#ifndef MESSAGEBUS_H_
#define MESSAGEBUS_H_

class MessageBus_t {
public:
		MessageBus_t();
		virtual ~MessageBus_t();
		bool createSetVar(VarStorage, std::string);
		bool createSetConfig(VarStorage, std::string);
		bool createReportVar(VarStorage, std::string);
		bool createReportConfig(VarStorage, std::string);
		bool createNewDevice(VarStorage, std::string);
		bool createDelDevice(std::string, std::string);
		bool createSetup(VarStorage, std::string);
		bool createClientCap(VarStorage, std::string);
		bool createServerCap(VarStorage, std::string);
		MSG_BUS_TYPES getType();
		std::string getTypeAsString();
		bool setType(MSG_BUS_TYPES type);
		std::string getSource();
		bool setDestination(std::string);
		std::string getDestination();
		bool setBroadcast();
		bool setMultiCast();
		VarStorage getSetVar();
		VarStorage getSetConfig();
		VarStorage getReportVar();
		VarStorage getReportConfig();
		VarStorage getNewDevice();
		VarStorage getSetup();
		std::string getDelDevice();
		VarStorage getClientCap();
		VarStorage getServerCap();
		VarStorage getTransportVarStorage();
		bool importTransportVarStorage(VarStorage);
private:
		friend std::ostream& operator<<(std::ostream&, MessageBus_t &);
		bool checkNewDevice(VarStorage msg);
		VarStorage message;
		std::string source;
		std::string destination;
};

bool MsgIsReport(MSG_BUS_TYPES);
bool MsgIsSet(MSG_BUS_TYPES);

typedef boost::shared_ptr<MessageBus_t> MessageBus;

#define MessageBusFactory(x) MessageBus x(new MessageBus_t());

std::ostream& operator<<(std::ostream&, const MessageBus_t &);
std::ostream& operator<<(std::ostream &os, const MessageBus &ptr);


#endif /* MESSAGEBUS_H_ */
