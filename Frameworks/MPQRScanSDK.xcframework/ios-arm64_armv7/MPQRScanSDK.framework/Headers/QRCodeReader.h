/*
 * QRCodeReader
 *
 * Copyright 2014-present Yannick Loriot.
 * http://yannickloriot.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

/**
 * Reader object base on the `AVCaptureDevice` to read / scan 1D and 2D codes.
 */
@interface QRCodeReader : NSObject

#pragma mark - Creating and Inializing QRCode Readers
/**
 * @name Creating and Inializing QRCode Readers
 */

/**
 * @note Abstract: Initializes a reader with the `QRCode` metadata object type.
 * @note since 4.1.0
 */
- (nonnull id)init;

/**
 * @note Abstract: Initializes a reader with a list of metadata object types.
 * @param metadataObjectTypes An array of strings identifying the types of
 * metadata objects to process.
 * @note since 3.0.0
 */
- (nonnull id)initWithMetadataObjectTypes:(nonnull NSArray *)metadataObjectTypes;

/**
 * @note Abstract: Creates a reader with a list of metadata object types.
 * @param metadataObjectTypes An array of strings identifying the types of
 * metadata objects to process.
 * @see initWithMetadataObjectTypes:
 * @note since 3.0.0
 */
+ (nonnull instancetype)readerWithMetadataObjectTypes:(nonnull NSArray *)metadataObjectTypes;

#pragma mark - Checking the Reader Availabilities
/**
 * @name Checking the Reader Availabilities
 */

/**
 * @note Abstract: Returns whether the reader is available with the current device.
 * @return a Boolean value indicating whether the reader is available.
 * @note since 3.0.0
 */
+ (BOOL)isAvailable;

/**
 Checks and return whether the qr code is supported by the current device.
 
 @return A boolean value that indicates whether the device supports qr code.
 */
+ (BOOL)supportsQRCode;

/**
 * @note Abstract: Checks and return whether the given metadata object types are
 * supported by the current device.
 * @return a Boolean value indicating whether the given metadata object types
 * are supported by the current device.
 * @note since 3.2.0
 */
+ (BOOL)supportsMetadataObjectTypes:(nonnull NSArray *)metadataObjectTypes;

#pragma mark - Checking the Metadata Items Types
/**
 * @name Checking the Metadata Items Types
 */

/**
 * @note Abstract: An array of strings identifying the types of metadata objects to
 * process.
 * @note since 3.0.0
 */
@property (strong, nonatomic, readonly) NSArray * _Nonnull metadataObjectTypes;

#pragma mark - Viewing the Camera
/**
 * @name Viewing the Camera
 */

/**
 * @note Abstract: CALayer that you use to display video as it is being captured
 * by an input device.
 * @note since 3.0.0
 */
@property (strong, nonatomic, readonly) AVCaptureVideoPreviewLayer * _Nonnull previewLayer;

#pragma mark - Controlling the Reader
/**
 * @name Controlling the Reader
 */

/**
 * @note Abstract: Starts scanning the codes.
 * @note since 3.0.0
 */
- (void)startScanning;

/**
 * @note Abstract: Stops scanning the codes.
 * @note since 3.0.0
 */
- (void)stopScanning;

/**
 * @note Abstract: Indicates whether the session is currently running.
 * @note Discussion: The value of this property is a Bool indicating whether the
 * receiver is running.
 * Clients can key value observe the value of this property to be notified
 * when the session automatically starts or stops running.
 * @note since 3.3.0
 */
- (BOOL)running;

/**
 * @note Abstract: Returns true whether a torch is available.
 * @return true if a torch is available.
 * @note since 4.0.0
 */
- (BOOL)isTorchAvailable;

/**
 * @note Abstract: Toggles torch on the default device.
 * @note since 4.0.0
 */
- (void)toggleTorch;

#pragma mark - Getting Inputs and Outputs
/**
 * @name Getting Inputs and Outputs
 */

/**
 * @note Abstract: Accessing to the `AVCaptureDeviceInput` object representing 
 * the default device input (generally the back camera).
 * @note since 3.5.0
 */
@property (readonly) AVCaptureDeviceInput * _Nonnull defaultDeviceInput;

/**
 * @note Abstract: Accessing to the `AVCaptureDeviceInput` object representing
 * the front device input.
 * @note since 3.5.0
 */
@property (readonly) AVCaptureDeviceInput * _Nullable frontDeviceInput;

/**
 * @note Abstract: Accessing to the `AVCaptureMetadataOutput` object.
 * @note Discussion: It allows you to configure the scanner to restrict the area of
 * the scan to the overlay one for example.
 * @note since 3.5.0
 */
@property (readonly) AVCaptureMetadataOutput * _Nonnull metadataOutput;

#pragma mark - Managing the Orientation
/**
 * @name Managing the Orientation
 */

/**
 * @note Abstract: Returns the video orientation correspongind to the given interface
 * orientation.
 * @param interfaceOrientation An interface orientation.
 * @return the video orientation correspongind to the given device orientation.
 * @note since 3.1.0
 */
+ (AVCaptureVideoOrientation)videoOrientationFromInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;

#pragma mark - Managing the Block
/**
 * @name Managing the Block
 */

/**
 * @note Abstract: Sets the completion with a block that executes when a QRCode
 * or when the user did stopped the scan.
 * @param completionBlock The block to be executed. This block has no
 * return value and takes one argument: the `resultAsString`. If the user
 * stop the scan and that there is no response the `resultAsString` argument
 * is nil.
 * @note since 3.0.0
 */
- (void)setCompletionWithBlock:(nullable void (^) (NSString * _Nullable resultAsString))completionBlock;

//amri
/**
 * Update the scan of the region. Currently it is used to match the overlay rectangle region.
 *
 * @param rect The limited rectangle that we want the QR read
 * @note Should not be called from main queue
 */
- (void) updateScanRegion:(CGRect) rect;

@end
