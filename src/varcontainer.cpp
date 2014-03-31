/*
 * varcontainer.cpp
 *
 *  Created on: Oct 9, 2009
 *      Author: fish
 */

#include "iHanClient/varcontainer.hpp"
#include "iHanClient/LogClass.hpp"
#include "win32_support.hpp"


typedef enum VSErrorType_t {
	EMPTY_RESULT,
	NULL_RESULT,
	UNKNOWN_ERROR
} VSErrorType_t;

class VS_Exception : public std::exception
{
public:
  VS_Exception(VSErrorType_t Error) : ErrorType(Error) {
  }
  ~VS_Exception() throw () {};
  virtual const VSErrorType_t Error() const throw() {
	  return ErrorType;
  }

private:
  VSErrorType_t ErrorType;
};



VarStorage_t::VarStorage_t() {
}

VarStorage_t::VarStorage_t(muscle::MessageRef msg) {
	this->importMuscleMsg(msg);
}
void VarStorage_t::operator()(muscle::MessageRef msg) {
	this->importMuscleMsg(msg);
}

VarStorage_t::VarStorage_t(VarStorage_t  &other) {
	std::map<std::string, Vals *>::iterator it;
	std::vector<StoredVals_t>::iterator it2;
	for (it=other.Variables.begin(); it != other.Variables.end(); it++) {
		Vals *myval = (it->second);
		Vals *newvals = new Vals;
		for (it2 = myval->begin(); it2 != myval->end(); it2++) {
			StoredVals_t actualval = *it2;
			StoredVals_r *othervals = actualval.get();
			StoredVals_r *values = new StoredVals_r(*othervals);
			//printf("old: %p new: %p\n", othervals, values);
			StoredVals_t NewVal(values);
			newvals->push_back(NewVal);
		}
		std::string name = it->first;
		this->Variables[name] = newvals;
	}
}

void VarStorage_t::importMuscleMsg(muscle::MessageRef msg) {
	muscle::String fieldname;
	uint32 type, size, i;
	muscle::MessageFieldNameIterator it = msg()->GetFieldNameIterator();
	for (; it.HasData(); it++ ) {
		fieldname = it.GetFieldName();
		msg()->GetInfo(fieldname, &type, &size);
		switch (type) {
		   case B_FLOAT_TYPE: {
			   float val;
			   for (i = 0; i < size; i++) {
				   msg()->FindFloat(fieldname, i, val);
				   this->addFloatValue(fieldname.Cstr(), (float)val);
			   }
		   }
		   break;
		   case B_INT64_TYPE: {
			   uint64 val;
			   for (i = 0; i < size; i++) {
				   msg()->FindInt64(fieldname, i, val);
				   this->addLongLongValue(fieldname.Cstr(), (long long)val);
			   }
		   }
		   break;
		   case B_INT32_TYPE: {
			   uint32 val;
			   for (i = 0; i < size; i++) {
				   msg()->FindInt32(fieldname, i, val);
				   this->addLongValue(fieldname.Cstr(), (long)val);
			   }
		   }
		   break;
		   case B_INT16_TYPE: {
			   uint16 val;
			   for (i = 0; i < size; i++) {
				   msg()->FindInt16(fieldname, i, val);
				   this->addIntValue(fieldname.Cstr(), (int)val);
			   }
		   }
		   break;
		   case B_STRING_TYPE: {
			   muscle::String val;
			   for (i = 0; i < size; i++) {
				   msg()->FindString(fieldname, i, val);
				   this->addCharValue(fieldname.Cstr(), (char *)val.Cstr());
			   }
		   }
		   break;
		   case B_BOOL_TYPE: {
			   bool val;
			   for (i = 0; i < size; i++) {
				   msg()->FindBool(fieldname, i, val);
				   this->addBoolValue(fieldname.Cstr(), (bool)val);
			   }
		   }
		   break;
		   case B_MESSAGE_TYPE: {
			   for (i = 0; i < size; i++) {
				   muscle::MessageRef msgMsg;
				   msg()->FindMessage(fieldname, (uint32)i, msgMsg);
				   switch(msgMsg()->what) {
					   case ST_HASH: {
						   muscle::String Hashfieldname;
						   uint32 Hashtype, Hashsize;
						   HashVals newHashVals;
						   muscle::MessageFieldNameIterator hit = msgMsg()->GetFieldNameIterator();
						   for (; hit.HasData(); hit++ ) {
							   Hashfieldname = hit.GetFieldName();
							   msgMsg()->GetInfo(Hashfieldname, &Hashtype, &Hashsize);
							   switch (Hashtype) {
								   case B_FLOAT_TYPE: {
									   float val;
									   msgMsg()->FindFloat(Hashfieldname, 0, val);
									   newHashVals[Hashfieldname.Cstr()] = (float)val;
								   }
								   break;
								   case B_INT64_TYPE: {
									   uint64 val;
									   msgMsg()->FindInt64(Hashfieldname, 0, val);
									   newHashVals[Hashfieldname.Cstr()] = (long long)val;
								   }
								   break;
								   case B_INT32_TYPE: {
									   uint32 val;
									   msgMsg()->FindInt32(Hashfieldname, 0, val);
									   newHashVals[Hashfieldname.Cstr()]= (long)val;
								   }
								   break;
								   case B_INT16_TYPE: {
									   uint16 val;
									   msgMsg()->FindInt16(Hashfieldname, 0, val);
									   newHashVals[Hashfieldname.Cstr()] =  (int)val;
								   }
								   break;
								   case B_STRING_TYPE: {
									   muscle::String val;
									   msgMsg()->FindString(Hashfieldname, 0, val);
									   newHashVals[Hashfieldname.Cstr()] = std::string(val.Cstr());
								   }
								   break;
								   case B_MESSAGE_TYPE: {
									   muscle::MessageRef DateMsgRef;
									   muscle::String val;
									   msgMsg()->FindMessage(Hashfieldname, 0, DateMsgRef);
									   DateMsgRef()->FindString("DATE", 0, val);
									   try {
										   newHashVals[Hashfieldname.Cstr()] = boost::posix_time::from_iso_string(val.Cstr());
									   } catch (std::exception &e) {
										   newHashVals[Hashfieldname.Cstr()] = boost::posix_time::not_a_date_time;
									   }
								   }
								   break;
							   }
							}
							this->addHashValue(fieldname.Cstr(), newHashVals);
					   }
					   break;
					   case ST_DATETIME: {
						   muscle::String val;
						   msgMsg()->FindString("DATE",0, val);
						   try {
							   this->addTimeValue(fieldname.Cstr(), boost::posix_time::from_iso_string(val.Cstr()));
						   } catch(std::exception &e) {
							   this->addTimeValue(fieldname.Cstr(), boost::posix_time::not_a_date_time);
						   }
					   }
					   break;
					   case ST_VARSTORAGE: {
						   VarContainerFactory(newVarCon);
						   newVarCon->importMuscleMsg(msgMsg);
						   this->addVarStorageValue(fieldname.Cstr(), newVarCon);
					   }
					   break;
				   }
			   }
		   }
		   break;
		   case B_OBJECT_TYPE:
		   case B_RAW_TYPE:
		   case B_MIME_TYPE:
		   case B_INT8_TYPE:
		   case B_POINTER_TYPE:
		   case B_POINT_TYPE:
		   case B_RECT_TYPE:
		   case B_ANY_TYPE:
		   case B_DOUBLE_TYPE:
				  break;
		}
	}
}
VarStorage_t::~VarStorage_t() {
//	this->Variables.clear();
	std::map<std::string, Vals *>::iterator it;
	for (it=this->Variables.begin(); it != this->Variables.end(); it++) {
		delete (*it).second;
	}
	this->Variables.clear();
}
int VarStorage_t::addValueP(std::string FieldName, StoredVals_t SV) {
	if (this->Variables.find(FieldName) != this->Variables.end()) {
		if (this->Variables[FieldName]->front()->StoredType == SV->StoredType) {
			Vals *storedval = this->Variables[FieldName];
			storedval->push_back(SV);
			return storedval->size();
		} else {
			iHanClient::Logging::LogError(std::string("Fieldname " + FieldName + " is a " + getType(this->Variables[FieldName]->front()) + " But Value is a " + getType(SV)));
			//delete SV;
			return -1;
		}
	} else {
		Vals *storedval = new Vals;
		storedval->push_back(SV);
		this->Variables[FieldName] = storedval;
		return storedval->size();
	}
}

int VarStorage_t::addCharValue(std::string FieldName, char *val) {
	return this->addStringValue(FieldName, std::string(val));
}

int VarStorage_t::addStringValue(std::string FieldName, std::string val) {
	StoredVals_t SV(new StoredVals_r);
	SV->StrVal = val;
	SV->StoredType = ST_STRING;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addIntValue(std::string FieldName, int val) {
	StoredVals_t SV(new StoredVals_r);
	SV->IntVal = val;
	SV->StoredType = ST_INT;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addLongValue(std::string FieldName, long val) {
	StoredVals_t SV(new StoredVals_r);
	SV->LongVal = val;
	SV->StoredType = ST_LONG;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addLongLongValue(std::string FieldName, long long val) {
	StoredVals_t SV(new StoredVals_r);
	SV->LongLongVal = val;
	SV->StoredType = ST_LONGLONG;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addFloatValue(std::string FieldName, float val) {
	StoredVals_t SV(new StoredVals_r);
	SV->FloatVal = val;
	SV->StoredType = ST_FLOAT;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addHashValue(std::string FieldName, HashVals val) {
	StoredVals_t SV(new StoredVals_r);
	SV->HashVal = val;
	SV->StoredType = ST_HASH;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addBoolValue(std::string FieldName, bool val) {
	StoredVals_t SV(new StoredVals_r);
	SV->BoolVal = val;
	SV->StoredType = ST_BOOL;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addTimeValue(std::string FieldName, boost::posix_time::ptime val) {
	StoredVals_t SV(new StoredVals_r);
	SV->DateTimeVal = val;
	SV->StoredType = ST_DATETIME;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::addVarStorageValue(std::string FieldName, VarStorage &val) {
	StoredVals_t SV(new StoredVals_r);
	SV->VarVal = val;
	SV->StoredType = ST_VARSTORAGE;
	return this->addValueP(FieldName, SV);
}
int VarStorage_t::replaceValueP(std::string FieldName, StoredVals_t SV, int pos) {
	Vals *storedval;
	if (this->Variables.find(FieldName) != this->Variables.end()) {
		if (this->Variables[FieldName]->front()->StoredType == SV->StoredType) {
			storedval = this->Variables[FieldName];
		} else {
			iHanClient::Logging::LogError(std::string("Fieldname " + FieldName + " is a " + getType(this->Variables[FieldName]->front()) + " But Replacement Value is a " + getType(SV)));
			//delete SV;
			return -1;
		}
	} else {
		/* Doesn't exist, add it at the start */
		return this->addValueP(FieldName, SV);
	}
	/* XXX TODO: Check we not tring to make a hole */
	if ((unsigned int)pos >= storedval->size()) {
		storedval->push_back(SV);
		return pos;
	}

	storedval->at(pos) = SV;
	return pos;
}

int VarStorage_t::replaceCharValue(std::string FieldName, char *val, int pos) {
	return this->replaceStringValue(FieldName, std::string(val), pos);
}
int VarStorage_t::replaceStringValue(std::string FieldName, std::string val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->StrVal = val;
	SV->StoredType = ST_STRING;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceIntValue(std::string FieldName, int val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->IntVal = val;
	SV->StoredType = ST_INT;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceLongValue(std::string FieldName, long val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->LongVal = val;
	SV->StoredType = ST_LONG;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceLongLongValue(std::string FieldName, long long val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->LongLongVal = val;
	SV->StoredType = ST_LONGLONG;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceFloatValue(std::string FieldName, float val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->FloatVal = val;
	SV->StoredType = ST_FLOAT;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceHashValue(std::string FieldName, HashVals val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->HashVal = val;
	SV->StoredType = ST_HASH;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceBoolValue(std::string FieldName, bool val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->BoolVal = val;
	SV->StoredType = ST_BOOL;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceTimeValue(std::string FieldName, boost::posix_time::ptime val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->DateTimeVal = val;
	SV->StoredType = ST_DATETIME;
	return this->replaceValueP(FieldName, SV, pos);
}
int VarStorage_t::replaceVarStorageValue(std::string FieldName, VarStorage &val, int pos) {
	StoredVals_t SV(new StoredVals_r);
	SV->VarVal = val;
	SV->StoredType = ST_VARSTORAGE;
	return this->replaceValueP(FieldName, SV, pos);
}
StoredType_t VarStorage_t::getType(std::string FieldName) {
	if (this->Variables.find(FieldName) != this->Variables.end()) {
		Vals *storedval = this->Variables[FieldName];
		StoredVals_t SV = storedval->at(0);
		return SV->StoredType;
	}
	return ST_INVALID;
}

StoredVals_t VarStorage_t::getValueP(std::string FieldName, StoredType_t type, int pos) {
	if (this->Variables.find(FieldName) != this->Variables.end()) {
		Vals *storedval = this->Variables[FieldName];
		StoredVals_t SV = storedval->at(pos);
		if (SV->StoredType != type) {
			iHanClient::Logging::LogError(std::string("Field " + FieldName + " is not of type " + getType(type) + " (" + lexical_cast<std::string>(type) + ") but type " + getType(SV) + " (" + lexical_cast<std::string>(SV->StoredType) + ")"));
			return StoredVals_t(new StoredVals_r);
		}
		return SV;
	}
	BOOST_THROW_EXCEPTION(VS_Exception(EMPTY_RESULT));
}

bool VarStorage_t::getCharValue(std::string FieldName, char *value, int pos) {
	std::string Result;
	if (this->getStringValue(FieldName, Result, pos) == true) {
		value = (char *)Result.c_str();
		return true;
	}
	return false;
}

bool VarStorage_t::getStringValue(std::string FieldName, std::string &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_STRING, pos);
		value = val->StrVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getIntValue(std::string FieldName, int &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_INT, pos);
		value = val->IntVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getLongValue(std::string FieldName, long &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_LONG, pos);
		value = val->LongVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getLongLongValue(std::string FieldName, long long &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_LONGLONG, pos);
		value = val->LongLongVal;
		return true;
	} catch(VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getFloatValue(std::string FieldName, float &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_FLOAT, pos);
		value = val->FloatVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getHashValue(std::string FieldName, HashVals &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_HASH, pos);
		value = val->HashVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getBoolValue(std::string FieldName, bool &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_BOOL, pos);
		value = val->BoolVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getTimeValue(std::string FieldName, boost::posix_time::ptime &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName,  ST_DATETIME, pos);
		value = val->DateTimeVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}
bool VarStorage_t::getVarStorageValue(std::string FieldName, VarStorage &value, int pos) {
	StoredVals_t val;
	try {
		val = this->getValueP(FieldName, ST_VARSTORAGE, pos);
		value = val->VarVal;
		return true;
	} catch (VS_Exception &e) {
		return false;
	}
}


unsigned int VarStorage_t::getSize(std::string FieldName) {
	if (this->Variables.find(FieldName) != this->Variables.end())
		return this->Variables[FieldName]->size();
	else
		return 0;
}
unsigned int VarStorage_t::getSize() {
	return this->Variables.size();
}

#define DOTAB for (int tabs = 0; tabs != tab; tabs++) cerr << "\t"


void VarStorage_t::printToStream(int tab) {
	std::map<std::string, Vals *>::iterator it;
	Vals::iterator it2;
	int i;
	for (it=this->Variables.begin(); it != this->Variables.end(); it++) {
		DOTAB;
		cerr << "Variable: " << (*it).first << " size: " << (*it).second->size() << " Type: " << getType((*it).second->front()) << std::endl;
		i = 0;
		for (it2 = (*it).second->begin(); it2 != (*it).second->end(); it2++) {
			DOTAB;
			cerr << "\tPos: " << i++ << " Value: ";
			if ((*it2)->StoredType == ST_STRING) {
					cerr << (*it2)->StrVal << std::endl;
			} else if ((*it2)->StoredType == ST_INT) {
					cerr << (*it2)->IntVal << std::endl;
			} else if ((*it2)->StoredType == ST_LONG) {
					cerr << (*it2)->LongVal << std::endl;
			} else if ((*it2)->StoredType == ST_LONGLONG) {
					cerr << (*it2)->LongLongVal << std::endl;
			} else if ((*it2)->StoredType == ST_FLOAT) {
					cerr << (*it2)->FloatVal << std::endl;
			} else if ((*it2)->StoredType == ST_HASH) {
					cerr << "Hash Variables:" <<  std::endl;
					{
						HashVals hv = (*it2)->HashVal;
						std::map<std::string, HashValsVariant_t>::const_iterator hvit;
						for (hvit = hv.begin(); hvit != hv.end(); hvit++) {
							DOTAB;
							cout << "\t\t" << (*hvit).first << "=" << (*hvit).second << std::endl;
						}
					}
			} else if ((*it2)->StoredType == ST_BOOL) {
					cerr << (*it2)->BoolVal << std::endl;
			} else if ((*it2)->StoredType == ST_DATETIME) {
					cerr << (*it2)->DateTimeVal << std::endl;
			} else if ((*it2)->StoredType == ST_VARSTORAGE) {
					cerr << "{" << std::endl;
					(*it2)->VarVal->printToStream(tab+1);
					DOTAB;
					cerr <<"\t}" << std::endl;
			} else {
					cerr << "Unprintable Type" << std::endl;
			}
		}
	}
}

muscle::MessageRef VarStorage_t::toMuscle() {
	std::map<std::string, Vals *>::iterator it;
	Vals::iterator it2;
	muscle::MessageRef newMsg = muscle::GetMessageFromPool(0);
	for (it=this->Variables.begin(); it != this->Variables.end(); it++) {
		for (it2 = (*it).second->begin(); it2 != (*it).second->end(); it2++) {
			if ((*it2)->StoredType == ST_STRING) {
				newMsg()->AddString((*it).first.c_str(), (*it2)->StrVal.c_str());
			} else if ((*it2)->StoredType == ST_INT) {
				newMsg()->AddInt16((*it).first.c_str(), (*it2)->IntVal);
			} else if ((*it2)->StoredType == ST_LONG) {
				newMsg()->AddInt32((*it).first.c_str(), (*it2)->LongVal);
			} else if ((*it2)->StoredType == ST_LONGLONG) {
				newMsg()->AddInt64((*it).first.c_str(), (*it2)->LongLongVal);
			} else if ((*it2)->StoredType == ST_FLOAT) {
				newMsg()->AddFloat((*it).first.c_str(), (*it2)->FloatVal);
			} else if ((*it2)->StoredType == ST_HASH) {
				muscle::MessageRef HashMsg = muscle::GetMessageFromPool(ST_HASH);
				HashVals hv = (*it2)->HashVal;
				std::map<std::string, HashValsVariant_t>::const_iterator hvit;
				for (hvit = hv.begin(); hvit != hv.end(); hvit++) {
					if ((*hvit).second.type() == typeid(std::string)) {
						HashMsg()->AddString((*hvit).first.c_str(), boost::get<std::string>((*hvit).second).c_str());
					} else if ((*hvit).second.type() == typeid(int)) {
						HashMsg()->AddInt16((*hvit).first.c_str(), boost::get<int>((*hvit).second));
					} else if ((*hvit).second.type() == typeid(long)) {
						HashMsg()->AddInt32((*hvit).first.c_str(), boost::get<long>((*hvit).second));
					} else if ((*hvit).second.type() == typeid(long long)) {
						HashMsg()->AddInt64((*hvit).first.c_str(), boost::get<long long>((*hvit).second));
					} else if ((*hvit).second.type() == typeid(float)) {
						HashMsg()->AddFloat((*hvit).first.c_str(), boost::get<float>((*hvit).second));
					} else if ((*hvit).second.type() == typeid(boost::posix_time::ptime)) {
						{
							muscle::MessageRef DateMsg = muscle::GetMessageFromPool(ST_DATETIME);
							DateMsg()->AddString("DATE", boost::posix_time::to_iso_string(boost::get<boost::posix_time::ptime>((*hvit).second)).c_str());
							HashMsg()->AddMessage((*hvit).first.c_str(), DateMsg);
						}
					} else {
						cout << "Unknown Type: " << (*hvit).second.type().name() << std::endl;
					}
				}
				newMsg()->AddMessage((*it).first.c_str(), HashMsg);
			} else if ((*it2)->StoredType == ST_BOOL) {
				newMsg()->AddBool((*it).first.c_str(), (*it2)->BoolVal);
			} else if ((*it2)->StoredType == ST_DATETIME) {
				{
					muscle::MessageRef DateMsg = muscle::GetMessageFromPool(ST_DATETIME);
					DateMsg()->AddString("DATE", boost::posix_time::to_iso_string((*it2)->DateTimeVal).c_str());
					newMsg()->AddMessage((*it).first.c_str(), DateMsg);
				}
			} else if ((*it2)->StoredType == ST_VARSTORAGE) {
				{
					muscle::MessageRef VarMsg = (*it2)->VarVal->toMuscle();
					VarMsg()->what = ST_VARSTORAGE;
					newMsg()->AddMessage((*it).first.c_str(), VarMsg);
				}
			} else {
					cerr << "Unprintable Type\n";
			}
		}
	}
//	this->printToStream();
//	newMsg()->PrintToStream();
	return newMsg;
}

bool VarStorage_t::is_empty() {
	if (this->getSize() == 0) return true;
	return false;
}

#if 0
std::string VarStorage_t::getType(const char *name) const {
#ifndef WIN32
	size_t len;
    int s;
    return abi::__cxa_demangle(name, 0, &len, &s);
#else
	return std::string(name);
#endif
}
#endif

std::vector<std::string> *VarStorage_t::getFields() {
	std::vector<std::string> *fields = new std::vector<std::string>;
	std::map<std::string, Vals *>::iterator it;
	for (it=this->Variables.begin(); it != this->Variables.end(); it++) {
		fields->push_back((*it).first);
	}
	return fields;
}



std::string VarStorage_t::getType(StoredVals_t SV) const {
	return getType(SV->StoredType);
}
std::string VarStorage_t::getType(StoredType_t type) const {

	switch (type) {
		case ST_STRING:
			return "std::string";
		break;
		case ST_INT:
			return "int";
		break;
		case ST_LONG:
			return "Long";
		break;
		case ST_LONGLONG:
			return "LongLong";
		break;
		case ST_FLOAT:
			return "Float";
		break;
		case ST_HASH:
			return "Hash";
		break;
		case ST_BOOL:
			return "Bool";
		break;
		case ST_DATETIME:
			return "DateTime";
		case ST_VARSTORAGE:
			return "VarStorage_t";
		break;
		case ST_INVALID:
			return "Invalid Entry";
		break;
	}
	return "";
}
std::ostream& operator<<(std::ostream &os, const VarStorage &ptr) {
        os << *ptr.get();
	return os;
}


#undef DOTAB
int tab = 0;
#define DOTAB for (int tabs = 0; tabs != tab; tabs++) stream << "\t"

std::ostream& operator<<(std::ostream &stream, const VarStorage_t &vs) {
	Variables_t vars = vs.Variables;
	Variables_t::iterator it;
	Vals::iterator it2;
	int i;
	for (it=vars.begin(); it != vars.end(); it++) {
		DOTAB;
		stream << "Variable: " << (*it).first << " size: " << (*it).second->size() << " Type: " << vs.getType((*it).second->front()) << std::endl;
		i = 0;
		for (it2 = (*it).second->begin(); it2 != (*it).second->end(); it2++) {
			DOTAB;
			stream << "\tPos: " << i++ << " Value: ";
			if ((*it2)->StoredType == ST_STRING) {
					stream << (*it2)->StrVal << std::endl;
			} else if ((*it2)->StoredType == ST_INT) {
					stream << (*it2)->IntVal << std::endl;
			} else if ((*it2)->StoredType == ST_LONG) {
					stream << (*it2)->LongVal << std::endl;
			} else if ((*it2)->StoredType == ST_LONGLONG) {
					stream << (*it2)->LongLongVal << std::endl;
			} else if ((*it2)->StoredType == ST_FLOAT) {
					stream << (*it2)->FloatVal << std::endl;
			} else if ((*it2)->StoredType == ST_HASH) {
					stream << "Hash Variables:" <<  std::endl;
					{
						HashVals hv = (*it2)->HashVal;
						std::map<std::string, HashValsVariant_t>::const_iterator hvit;
						for (hvit = hv.begin(); hvit != hv.end(); hvit++) {
							DOTAB;
							cout << "\t\t" << (*hvit).first << "=" << (*hvit).second << std::endl;
						}
					}
			} else if ((*it2)->StoredType == ST_BOOL) {
					stream << (*it2)->BoolVal << std::endl;
			} else if ((*it2)->StoredType == ST_DATETIME) {
					stream << (*it2)->DateTimeVal << std::endl;
			} else if ((*it2)->StoredType == ST_VARSTORAGE) {
					tab = tab +1;
					stream << "{" << std::endl;
					stream << (*it2)->VarVal;
					//DOTAB;
					stream <<"\t}" << std::endl;
					tab = tab -1;
			} else {
					stream << "Unprintable Type" << std::endl;
			}
		}
	}
	return stream;
}
