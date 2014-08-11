//
//  DeviceTypes.hpp
//  xBeeHome
//
//  Created by Justin Hammond on 23/12/11.
//  Copyright (c) 2011 DynamX. All rights reserved.
//

#ifndef DeviceTypes_hpp
#define DeviceTypes_hpp

enum DeviceType {
    DEVICE_TYPE_SWITCH = 0x1,
    DEVICE_TYPE_SENSORMULTILEVEL,
    DEVICE_TYPE_METER,
    DEVICE_TYPE_GENERIC,
    DEVICE_TYPE_DOORLOCK,
    DEVICE_TYPE_USERPIN,
    DEVICE_TYPE_RGBW,
    DEVICE_TYPE_MULTILEVELSWITCH
};

enum DeviceSwitchSubType {
    DEVICE_GENERIC = 0
};

enum DeviceRGBWSubType {
    DEVICE_SUBTYPE_FIBARO = 0x01
};

#endif
