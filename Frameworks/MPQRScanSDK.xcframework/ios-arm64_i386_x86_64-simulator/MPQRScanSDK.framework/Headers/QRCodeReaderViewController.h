/*
 * QRCodeReaderViewController
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

#import <UIKit/UIKit.h>
#import "QRCodeReaderDelegate.h"
#import "QRCodeReader.h"
#import "QRCodeReaderViewControllerBuilder.h"

@class QRToggleTorchButton;
/**
 * Convenient controller to display a view to scan/read 1D or 2D bar codes like
 * the QRCodes. It is based on the `AVFoundation` framework from Apple. It aims
 * to replace ZXing or ZBar for iOS 7 and over.
 */
@interface QRCodeReaderViewController : UIViewController

//amri
#pragma mark - To be overriden to create custom view controller
/**
 * @name To be overriden to create custom view controller
 */

/**
 * Captured area by the camera
 */
@property (strong, nonatomic) QRCodeReaderView      * _Nullable cameraView;

/**
 * Button to on-off torch or flash
 */
@property (strong, nonatomic) UIButton              * _Nullable toggleTorchButton;

/**
 * Button to close the view controller
 */
@property (strong, nonatomic) UIButton              * _Nullable cancelButton;

/**
 Flag to know whether the view controller start scanning the codes when the view will appear.
 */
@property (assign, nonatomic) BOOL                  startScanningAtLoad;

/// Size of region the camera will scan for qr code. It will be centered in the camera preview. If `.zero` then whole area will be scanneable.
@property (assign, nonatomic) CGSize                scanRegionSize;

/**
 Flag to display the toggle torch button. If the value is true and there is no torch the button will not be displayed.
 */
@property (assign, nonatomic) BOOL                  showTorchButton;

/**
 Flag to display the cancel button.
 */
@property (assign, nonatomic) BOOL                  showCancelButton;

/**
 Flag to display the guide view.
 */
@property (assign, nonatomic) BOOL                  showOverlayView;

/**
 Action correcpond to cancel button
 */
- (void)cancelAction:(UIButton * _Nullable)button;

/**
 Action correcpond to toggle torch button
 */
- (void)toggleTorchAction:(UIButton * _Nullable)button;

/**
 Function to create all necessary UI, and modify its property:
 - cameraView, overlay
 - cancelButton
 - toggleTorchButton
 */
- (void)setupUIComponentsWithCancelButtonTitle:(NSString * _Nullable)cancelButtonTitle cameraView:(QRCodeReaderView* _Nullable) cameraView;

/**
 Function to create auto-layout for the UI:
 - cameraView, overlay
 - cancelButton
 - toggleTorchButton
 */
- (void)setupAutoLayoutConstraints;

#pragma mark - Creating and Inializing QRCodeReader Controllers
/**
 * @name Creating and Inializing QRCode Reader Controllers
 */

/**
 * @note Abstract: Initializes a view controller to read QRCodes from a displayed
 * video preview and a cancel button to be go back.
 * @param cancelTitle The title of the cancel button.
 * @note Discussion: This convenient method is used to instanciate a reader with
 * only one supported metadata object types: the QRCode.
 * @see initWithCancelButtonTitle:metadataObjectTypes:
 * @note since 1.0.0
 */
- (nonnull id)initWithCancelButtonTitle:(nullable NSString *)cancelTitle;

/**
 * @note Abstract: Creates a view controller to read QRCodes from a displayed
 * video preview and a cancel button to be go back.
 * @param cancelTitle The title of the cancel button.
 * @see initWithCancelButtonTitle:
 * @note since 1.0.0
 */
+ (nonnull instancetype)readerWithCancelButtonTitle:(nullable NSString *)cancelTitle;

/**
 * @note Abstract: Initializes a reader view controller with a list of metadata
 * object types.
 * @param metadataObjectTypes An array of strings identifying the types of
 * metadata objects to process.
 * @see initWithCancelButtonTitle:metadataObjectTypes:
 * @note since 3.0.0
 */
- (nonnull id)initWithMetadataObjectTypes:(nonnull NSArray *)metadataObjectTypes;

/**
 * @note Abstract: Creates a reader view controller with a list of metadata object
 * types.
 * @param metadataObjectTypes An array of strings identifying the types of
 * metadata objects to process.
 * @see initWithMetadataObjectTypes:
 * @note since 3.0.0
 */
+ (nonnull instancetype)readerWithMetadataObjectTypes:(nonnull NSArray *)metadataObjectTypes;

/**
 * @note Abstract: Initializes a view controller to read wanted metadata object
 * types from a displayed video preview and a cancel button to be go back.
 * @param cancelTitle The title of the cancel button.
 * @param metadataObjectTypes The type (“symbology”) of barcode to scan.
 * @see initWithCancelButtonTitle:codeReader:
 * @note since 2.0.0
 */
- (nonnull id)initWithCancelButtonTitle:(nullable NSString *)cancelTitle metadataObjectTypes:(nonnull NSArray *)metadataObjectTypes;

/**
 * @note Abstract: Creates a view controller to read wanted metadata object types
 * from a displayed video preview and a cancel button to be go back.
 * @param cancelTitle The title of the cancel button.
 * @param metadataObjectTypes The type (“symbology”) of barcode to scan.
 * @see initWithCancelButtonTitle:metadataObjectTypes:
 * @note since 2.0.0
 */
+ (nonnull instancetype)readerWithCancelButtonTitle:(nullable NSString *)cancelTitle metadataObjectTypes:(nonnull NSArray *)metadataObjectTypes;

/**
 * @note Abstract: Initializes a view controller using a cancel button title and
 * a code reader.
 * @param cancelTitle The title of the cancel button.
 * @param codeReader The reader to decode the codes.
 * @see initWithCancelButtonTitle:codeReader:startScanningAtLoad:
 * @note since 3.0.0
 */
- (nonnull id)initWithCancelButtonTitle:(nullable NSString *)cancelTitle codeReader:(nonnull QRCodeReader *)codeReader;

/**
 * @note Abstract: Initializes a view controller using a cancel button title and
 * a code reader.
 * @param cancelTitle The title of the cancel button.
 * @param codeReader The reader to decode the codes.
 * @see initWithCancelButtonTitle:codeReader:
 * @note since 3.0.0
 */
+ (nonnull instancetype)readerWithCancelButtonTitle:(nullable NSString *)cancelTitle codeReader:(nonnull QRCodeReader *)codeReader;

/**
 * @note Abstract: Initializes a view controller using a cancel button title and
 * a code reader.
 * @param cancelTitle The title of the cancel button.
 * @param codeReader The reader to decode the codes.
 * @param startScanningAtLoad Flag to know whether the view controller start
 * scanning the codes when the view will appear.
 * @see initWithCancelButtonTitle:codeReader:
 * @note since 3.0.0
 */
- (nonnull id)initWithCancelButtonTitle:(nullable NSString *)cancelTitle codeReader:(nonnull QRCodeReader *)codeReader startScanningAtLoad:(BOOL)startScanningAtLoad;

/**
 * @note Abstract: Initializes a view controller using a cancel button title and
 * a code reader.
 * @param cancelTitle The title of the cancel button.
 * @param codeReader The reader to decode the codes.
 * @param startScanningAtLoad Flag to know whether the view controller start
 * scanning the codes when the view will appear.
 * @see initWithCancelButtonTitle:codeReader:startScanningAtLoad:showTorchButton:
 * @note since 3.0.0
 */
+ (nonnull instancetype)readerWithCancelButtonTitle:(nullable NSString *)cancelTitle codeReader:(nonnull QRCodeReader *)codeReader startScanningAtLoad:(BOOL)startScanningAtLoad;

/**
 * @note Abstract: Initializes a view controller using a cancel button title and
 * a code reader.
 * @param cancelTitle The title of the cancel button.
 * @param codeReader The reader to decode the codes.
 * @param startScanningAtLoad Flag to know whether the view controller start
 * scanning the codes when the view will appear.
 * @param showTorchButton Flag to know whether the view controller start
 * scanning the codes when the view will appear.
 * @note since 4.0.0
 */
- (nonnull id)initWithCancelButtonTitle:(nullable NSString *)cancelTitle codeReader:(nonnull QRCodeReader *)codeReader startScanningAtLoad:(BOOL)startScanningAtLoad showTorchButton:(BOOL)showTorchButton;

/**
 * @note Abstract: Initializes a view controller using a cancel button title and
 * a code reader.
 * @param cancelTitle The title of the cancel button.
 * @param codeReader The reader to decode the codes.
 * @param startScanningAtLoad Flag to know whether the view controller start
 * scanning the codes when the view will appear.
 * @param showTorchButton Flag to know whether the view controller start
 * scanning the codes when the view will appear.
 * @see initWithCancelButtonTitle:codeReader:startScanningAtLoad:showTorchButton:
 * @note since 4.0.0
 */
+ (nonnull instancetype)readerWithCancelButtonTitle:(nullable NSString *)cancelTitle codeReader:(nonnull QRCodeReader *)codeReader startScanningAtLoad:(BOOL)startScanningAtLoad showTorchButton:(BOOL)showTorchButton;


//Amri
/**
 Initialize view controller using builder
 
 @param builder The builder that contain configuration of this view controller.
 */
- (nonnull id)initWithBuilder:(nonnull QRCodeReaderViewControllerBuilder * ) builder;

//Amri
/**
 Initialize view controller using builder block, user can modify the configuration inside the builder block.
 
 @param block The builder that contain configuration of this view controller
 */
+ (nonnull instancetype) readerWithBuilderBlock:(nonnull QRCodeReaderViewControllerBuilderBlock)block;

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

#pragma mark - Managing the Delegate
/**
 * @name Managing the Delegate
 */

/**
 * @note Abstract: The object that acts as the delegate of the receiving QRCode
 * reader.
 * @note since 1.0.0
 */
@property (nonatomic, weak) id<QRCodeReaderDelegate> __nullable delegate;

/**
 * @note Abstract: Sets the completion with a block that executes when a QRCode
 * or when the user did stopped the scan.
 * @param completionBlock The block to be executed. This block has no
 * return value and takes one argument: the `resultAsString`. If the user
 * stop the scan and that there is no response the `resultAsString` argument
 * is nil.
 * @note since 1.0.1
 */
- (void)setCompletionWithBlock:(nullable void (^) (NSString * __nullable resultAsString))completionBlock;

#pragma mark - Managing the Reader
/**
 * @name Managing the Reader
 */

/**
 * @note Abstract: The default code reader created with the controller.
 * @note since 3.0.0
 */
@property (strong, nonatomic) QRCodeReader          * _Nullable codeReader;

@end
