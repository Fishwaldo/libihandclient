//
//  iHanCLientDefs.hpp
//  
//
//  Created by Justin Hammond on 11/10/14.
//  Copyright (c) 2014 DynamX. All rights reserved.
//

#ifndef iHanClientDefs_hpp
#define iHanClientDefs_hpp



#if (defined _WINDOWS || defined WIN32 || defined _MSC_VER) && !defined MINGW
#	if defined IHANCLIENT_MAKEDLL	// Create the dynamic library.
#		define IHANCLIENT_EXPORT    __declspec(dllexport)
#	elif defined IHANCLIENT_USEDLL	// Use the dynamic library
#		define IHANCLIENT_EXPORT    __declspec(dllimport)
#	else							// Create/Use the static library
#		define IHANCLIENT_EXPORT
#	endif
// Disable export warnings
#	define IHANCLIENT_EXPORT_WARNINGS_OFF	__pragma( warning(push) )\
											__pragma( warning(disable: 4251 4275) )
#	define IHANCLIENT_EXPORT_WARNINGS_ON		__pragma( warning(pop) )
#else
#	define IHANCLIENT_EXPORT
#	define IHANCLIENT_EXPORT_WARNINGS_OFF
#	define IHANCLIENT_EXPORT_WARNINGS_ON
#endif

#endif