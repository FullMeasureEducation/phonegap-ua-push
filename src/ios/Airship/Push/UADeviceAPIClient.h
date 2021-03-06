
/*
 Copyright 2009-2014 Urban Airship Inc. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binaryform must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided withthe distribution.

 THIS SOFTWARE IS PROVIDED BY THE URBAN AIRSHIP INC``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 EVENT SHALL URBAN AIRSHIP INC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>
@class UAHTTPRequest;
@class UADeviceRegistrationPayload;

#import "UAHTTPRequestEngine.h"

typedef void (^UADeviceAPIClientSuccessBlock)(void);
typedef void (^UADeviceAPIClientFailureBlock)(UAHTTPRequest *request);

/**
 * A high level abstraction for performing Device API registration and unregistration.
 */
@interface UADeviceAPIClient : NSObject


/**
 * Register the device.
 *
 * @param deviceToken the device token to register.
 * @param payload An instance of UADeviceRegistrationPayload.
 * @param successBlock A UADeviceAPIClientSuccessBlock that will be called if the registration was successful.
 * @param failureBlock A UADeviceAPIClientFailureBlock that will be called if the registration failed.
 *
 * Previous and pending registration data will be cached, and duplicates will be ignored.
 */
- (void)registerDeviceToken:(NSString *)deviceToken
                withPayload:(UADeviceRegistrationPayload *)payload
                  onSuccess:(UADeviceAPIClientSuccessBlock)successBlock
                  onFailure:(UADeviceAPIClientFailureBlock)failureBlock;


/**
 * Unregister the device.
 *
 * @param deviceToken the device token to unregister.
 * @param successBlock A UADeviceAPIClientSuccessBlock that will be called if the unregistration was successful.
 * @param failureBlock A UADeviceAPIClientFailureBlock that will be called if the unregistration was unsuccessful.
 *
 * Previous and pending registration data will be cached, and duplicates will be ignored.
 */
- (void)unregisterDeviceToken:(NSString *)deviceToken
                    onSuccess:(UADeviceAPIClientSuccessBlock)successBlock
                    onFailure:(UADeviceAPIClientFailureBlock)failureBlock;

/**
 * Cancels any pending and current requests.
 *
 * Note: This could prevent the onSuccess and onFailure callbacks from being triggered
 * in any current requests.
 */
- (void)cancelAllRequests;

/**
 * Indicates whether the client should attempt to automatically retry HTTP connections under recoverable conditions
 * (most 5xx status codes, reachability errors, etc). In this case, the client will perform exponential backoff and schedule
 * reconnections accordingly before calling back with a success or failure.  Defaults to `YES`.
 */
@property (nonatomic, assign) BOOL shouldRetryOnConnectionError;

@end
