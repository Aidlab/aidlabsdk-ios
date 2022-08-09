//
//  AidlabInterop.hpp
//  Aidlab-SDK
//
//  Created by Kuba Domaszewicz on 10.11.2016.
//  Copyright © 2016-2020 Aidmed Sp. z o.o. All rights reserved.
//

#ifndef AIDLAB_INTEROP_HPP
#define AIDLAB_INTEROP_HPP

#import <Foundation/Foundation.h>
#include "AidlabEnum.h"

@protocol AidlabInteropDelegate
- (void) didReceiveECG: (uint64_t) timestamp values: (float*) values size: (int) size;
- (void) didReceiveRespiration: (uint64_t) timestamp values: (float*) values size: (int) size;
- (void) didReceiveBatteryLevel: (uint8_t) stateOfCharge;
- (void) didReceiveSteps: (uint64_t) timestamp value: (uint64_t) value;
- (void) didReceiveSkinTemperature: (uint64_t) timestamp value: (float) value;
- (void) didReceiveAccelerometer: (uint64_t) timestamp ax: (float) ax ay: (float) ay az: (float) az;
- (void) didReceiveGyroscope: (uint64_t) timestamp gx: (float) gx gy: (float) gy gz: (float) gz;
- (void) didReceiveMagnetometer: (uint64_t) timestamp mx: (float) mx my: (float) my mz: (float) mz;
- (void) didReceiveQuaternion: (uint64_t) timestamp qw: (float) qw qx: (float) qx qy: (float) qy qz: (float) qz;
- (void) didReceiveOrientation: (uint64_t) timestamp roll: (float) roll pitch: (float) pitch yaw: (float) yaw;
- (void) didReceiveBodyPosition: (uint64_t) timestamp bodyPosition: (BodyPosition) bodyPosition;
- (void) didReceiveHeartRate: (uint64_t) timestamp heartRate: (int) heartRate;
- (void) didReceiveRr: (uint64_t) timestamp rr: (int) rr;
- (void) didReceiveRespirationRate: (uint64_t) timestamp value: (uint32_t) value;
- (void) wearStateDidChange: (WearState) state;
- (void) didReceiveSoundVolume: (uint64_t) timestamp soundVolume: (uint16_t) soundVolume;
- (void) didDetectExercise: (Exercise) exercise;
- (void) didDetectActivity: (uint64_t) timestamp activity: (ActivityType) activity;
- (void) didReceiveCommand;
- (void) didReceivePressure: (uint64_t) timestamp values: (int32_t*) values size: (int) size;
- (void) pressureWearStateDidChange: (WearState) state;
- (void) didReceiveMessage: (NSString*) process message: (NSString*) message;
- (void) didDetectUserEvent: (uint64_t) timestamp;
- (void) didReceiveSoundFeatures: (float*) values size: (int) size;
- (void) didReceiveError: (NSString*) text;
- (void) didReceiveSignalQuality: (uint64_t) timestamp value: (int) value;
// AidlabSynchronizationDelegate
- (void) didReceivePastECG: (uint64_t) timestamp values: (float*) values size: (int) size;
- (void) didReceivePastRespiration: (uint64_t) timestamp values: (float*) values size: (int) size;
- (void) didReceivePastSkinTemperature: (uint64_t) timestamp value: (float) value;
- (void) didReceivePastHeartRate: (uint64_t) timestamp heartRate: (int) heartRate;
- (void) syncStateDidChange: (SyncState) syncState;
- (void) didReceiveUnsynchronizedSize: (uint32_t) unsynchronizedSize syncBytesPerSecond: (float) syncBytesPerSecond;
- (void) didReceivePastRespirationRate: (uint64_t) timestamp value: (uint32_t) value;
- (void) didReceivePastActivity: (uint64_t) timestamp activity: (ActivityType) activity;
- (void) didReceivePastSteps: (uint64_t) timestamp value: (uint64_t) value;
- (void) didReceivePastRr: (uint64_t) timestamp rr: (int) rr;
- (void) didReceivePastSoundVolume: (uint64_t) timestamp soundVolume: (uint16_t) soundVolume;
- (void) didReceivePastPressure: (uint64_t) timestamp values: (int32_t*) values size: (int) size;
- (void) didReceivePastSoundFeatures: (float*) values size: (int) size;
- (void) didReceivePastAccelerometer: (uint64_t) timestamp ax: (float) ax ay: (float) ay az: (float) az;
- (void) didReceivePastGyroscope: (uint64_t) timestamp gx: (float) gx gy: (float) gy gz: (float) gz;
- (void) didReceivePastQuaternion: (uint64_t) timestamp qw: (float) qw qx: (float) qx qy: (float) qy qz: (float) qz;
- (void) didReceivePastOrientation: (uint64_t) timestamp roll: (float) roll pitch: (float) pitch yaw: (float) yaw;
- (void) didReceivePastMagnetometer: (uint64_t) timestamp mx: (float) mx my: (float) my mz: (float) mz;
- (void) didReceivePastBodyPosition: (uint64_t) timestamp bodyPosition: (BodyPosition) bodyPosition;
- (void) didDetectPastUserEvent: (uint64_t) timestamp;
- (void) didReceivePastSignalQuality: (uint64_t) timestamp value: (int) value;
// AidlabUpdateDelegate
- (void) didReceiveUpdateError: (UpdateError) error;
- (void) didReceiveUpdateProgress: (uint8_t) progress;
- (void) didFinishUpdate;
- (void) sendFirmwareChunk: (uint8_t*) buffer;

@end

@interface AidlabInterop : NSObject

- (instancetype) init;
- (void) processECGPackage: (uint8_t*) sample size:(int) size;
- (void) processRespirationPackage: (uint8_t*) sample size:(int) size;
- (void) processTemperaturePackage: (uint8_t*) sample size:(int) size;
- (void) processMotionPackage: (uint8_t*) sample size:(int) size;
- (void) processBatteryPackage: (uint8_t*) sample size:(int) size;
- (void) processActivityPackage: (uint8_t*) sample size:(int) size;
- (void) processStepsPackage: (uint8_t*) sample size:(int) size;
- (void) processOrientationPackage: (uint8_t*) sample size:(int) size;
- (void) processHealthThermometerPackage: (uint8_t*) sample size:(int) size;
- (void) processHeartRatePackage: (uint8_t*) sample size:(int) size;
- (void) processCommandPackage: (uint8_t*) sample size:(int) size;
- (void) processSoundVolumePackage: (uint8_t*) sample size:(int) size;
- (void) processNasalCannulaPackage: (uint8_t*) sample size:(int) size;
- (void) setHardwareRevision: (unsigned char*) hwRevision size:(int) size;
- (void) setFirmwareRevision: (unsigned char*) fwRevision size:(int) size;
- (void) processSoundFeaturesPackage: (uint8_t*) sample size:(int) size;
- (void) setAggressiveECGFiltration: (bool) value;
- (void) setUserCallback;
- (void) didConnect;
- (void) didDisconnect;
- (void) kill;
- (uint32_t) getTime;
- (uint8_t*) prepareCommand: (NSString *) command;
- (uint8_t*) prepareCommand: (uint8_t*) buffer size:(int) size command: (NSString *) command;
- (uint8_t*) prepareCollectCommand: (uint8_t*) realTimesignals realSize:(int) realSize syncTimesignals: (uint8_t*) realTimesignals syncSize:(int) syncSize;

- (NSString*) version;
- (void) startFirmwareUpdate: (uint8_t*) firmware firmwareSize: (int) firmwareSize;

@property (nonatomic, weak) id <AidlabInteropDelegate> aidlabInteropDelegate;
@end

#endif /* AIDLAB_INTEROP_HPP */
