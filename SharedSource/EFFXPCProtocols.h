//
//  EFFXPCProtocols.h
//  effervescence-driver
//
//  Created by Nerrons on 24/3/20.
//  Copyright © 2020 nerrons. All rights reserved.
//

#ifndef EFFXPCProtocols_h
#define EFFXPCProtocols_h


// Local Includes
#include "EFF_Types.h"

// System Includes
#import <Foundation/Foundation.h>


#pragma clang assume_nonnull begin

static NSString* kEFFXPCHelperMachServiceName = @kEFFXPCHelperBundleID;

// The protocol that EFFXPCHelper will vend as its XPC API.
@protocol EFFXPCHelperXPCProtocol

// Tells EFFXPCHelper that the caller is EFFApp and passes a listener endpoint that EFFXPCHelper can use to create connections to EFFApp.
// EFFXPCHelper may also pass the endpoint on to EFFDriver so it can do the same.
- (void) registerAsEFFAppWithListenerEndpoint:(NSXPCListenerEndpoint*)endpoint reply:(void (^)(void))reply;
- (void) unregisterAsEFFApp;

// EFFDriver calls this remote method when it wants EFFApp to start IO. EFFXPCHelper passes the message along and then passes the response
// back. This allows EFFDriver to wait for the audio hardware to start up, which means it can let the HAL know when it's safe to start
// sending us audio data from the client.
//
// If EFFApp can be reached, the error it returns will be passed the reply block. Otherwise, the reply block will be passed an error with
// one of the kEFFXPC_* error codes. It may have an underlying error using one of the NSXPCConnection* error codes from FoundationErrors.h.
- (void) startEFFAppPlayThroughSyncWithReply:(void (^)(NSError*))reply forUISoundsDevice:(BOOL)isUI;

// EFFXPCHelper will set the system's default output device to deviceID if it loses its connection
// to EFFApp and EFFApp has left EFFDevice as the default device. It waits for a short time first to
// give EFFApp a chance to fix the connection.
//
// This is so EFFDevice isn't left as the default device if EFFApp crashes or otherwise terminates
// abnormally. If audio is played to EFFDevice and EFFApp isn't running, the user won't hear it.
- (void) setOutputDeviceToMakeDefaultOnAbnormalTermination:(AudioObjectID)deviceID;
    
@end


// The protocol that EFFApp will vend as its XPC API.
@protocol EFFAppXPCProtocol

- (void) startPlayThroughSyncWithReply:(void (^)(NSError*))reply forUISoundsDevice:(BOOL)isUI;

@end


#endif /* EFFXPCProtocols_h */
