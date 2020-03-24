//
//  EFF_Types.h
//  effervescence-core
//
//  Created by Nerrons on 24/3/20.
//  Copyright © 2020 nerrons. All rights reserved.
//

#ifndef EFF_Types_h
#define EFF_Types_h

// System Includes
#include <CoreAudio/AudioServerPlugIn.h>

// STL Includes
#if defined(__cplusplus)
#include <stdexcept>
#endif


#pragma mark Project URLs

static const char* const kEFFProjectURL = "https://github.com/nerrons/effervescence";
static const char* const kEFFIssueTrackerURL = "https://github.com/nerrons/effervescence/issues";


#pragma mark IDs

// TODO: Change these and the other defines to const strings?
#define kEFFDriverBundleID           "com.nerrons.effervescence.driver"
#define kEFFAppBundleID              "com.nerrons.effervescence.app"
#define kEFFXPCHelperBundleID        "com.nerrons.effervescence.xpchelper"

#define kEFFDeviceUID                "EFFDevice"
#define kEFFDeviceModelUID           "EFFDeviceModelUID"
#define kEFFDeviceUID_UISounds       "EFFDevice_UISounds"
#define kEFFDeviceModelUID_UISounds  "EFFDeviceModelUID_UISounds"
#define kEFFNullDeviceUID            "EFFNullDevice"
#define kEFFNullDeviceModelUID       "EFFNullDeviceModelUID"

// The object IDs for the audio objects this driver implements.
//
// EFFDevice always publishes this fixed set of objects (except when EFFDevice's volume or mute
// controls are disabled). We might need to change that at some point, but so far it hasn't caused
// any problems and it makes the driver much simpler.

enum
{
    kObjectID_PlugIn                            = kAudioObjectPlugInObject,
    // EFFDevice
    kObjectID_Device                            = 2,   // Belongs to kObjectID_PlugIn
    kObjectID_Stream_Input                      = 3,   // Belongs to kObjectID_Device
    kObjectID_Stream_Output                     = 4,   // Belongs to kObjectID_Device
    kObjectID_Volume_Output_Master              = 5,   // Belongs to kObjectID_Device
    kObjectID_Mute_Output_Master                = 6,   // Belongs to kObjectID_Device
    // Null Device
    kObjectID_Device_Null                       = 7,   // Belongs to kObjectID_PlugIn
    kObjectID_Stream_Null                       = 8,   // Belongs to kObjectID_Device_Null
    // EFFDevice for UI sounds
    kObjectID_Device_UI_Sounds                  = 9,   // Belongs to kObjectID_PlugIn
    kObjectID_Stream_Input_UI_Sounds            = 10,  // Belongs to kObjectID_Device_UI_Sounds
    kObjectID_Stream_Output_UI_Sounds           = 11,  // Belongs to kObjectID_Device_UI_Sounds
    kObjectID_Volume_Output_Master_UI_Sounds    = 12,  // Belongs to kObjectID_Device_UI_Sounds
};

// AudioObjectPropertyElement docs: "Elements are numbered sequentially where 0 represents the
// master element."
static const AudioObjectPropertyElement kMasterChannel = kAudioObjectPropertyElementMaster;


#pragma mark EFFPlugIn Custom Properties

enum
{
    // A CFBoolean. True if the null device is enabled. Settable, false by default.
    kAudioPlugInCustomPropertyNullDeviceActive = 'nuld'
};


#pragma mark EFFDevice Custom Properties


#pragma mark XPC Return Codes

enum {
    kEFFXPC_Success,
    kEFFXPC_MessageFailure,
    kEFFXPC_Timeout,
    kEFFXPC_EFFAppStateError,
    kEFFXPC_HardwareError,
    kEFFXPC_ReturningEarlyError,
    kEFFXPC_InternalError
};


#pragma mark Exceptions

#if defined(__cplusplus)

class EFF_InvalidClientException : public std::runtime_error {
public:
    EFF_InvalidClientException() : std::runtime_error("InvalidClient") { }
};

class EFF_InvalidClientPIDException : public std::runtime_error {
public:
    EFF_InvalidClientPIDException() : std::runtime_error("InvalidClientPID") { }
};

class EFF_InvalidClientRelativeVolumeException : public std::runtime_error {
public:
    EFF_InvalidClientRelativeVolumeException() : std::runtime_error("InvalidClientRelativeVolume") { }
};

class EFF_InvalidClientPanPositionException : public std::runtime_error {
public:
    EFF_InvalidClientPanPositionException() : std::runtime_error("InvalidClientPanPosition") { }
};

class EFF_DeviceNotSetException : public std::runtime_error {
public:
    EFF_DeviceNotSetException() : std::runtime_error("DeviceNotSet") { }
};

#endif

// Assume we've failed to start the output device if it isn't running IO after this timeout expires.
//
// Currently set to 30s because some devices, e.g. AirPlay, can legitimately take that long to start.
//
// TODO: Should we have a timeout at all? Is there a notification we can subscribe to that will tell us whether the
//       device is still making progress? Should we regularly poll mOutputDevice.IsAlive() while we're waiting to
//       check it's still responsive?
static const UInt64 kStartIOTimeoutNsec = 30 * NSEC_PER_SEC;


#endif /* EFF_Types_h */
