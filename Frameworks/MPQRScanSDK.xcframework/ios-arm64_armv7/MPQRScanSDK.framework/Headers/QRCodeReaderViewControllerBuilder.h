//
//  QRCodeReaderViewControllerBuilder.h
//  QRProjectO
//
//  Created by Muchamad Chozinul Amri on 12/10/17.
//  Copyright © 2017 MasterCard. All rights reserved.
//

#import <UIKit/UIKit.h>

@class QRCodeReader;
@class QRCodeReaderView;
@class QRCodeReaderViewOverlay;
@class QRCodeReaderViewController;
@class QRCodeReaderViewControllerBuilder;

typedef void(^QRCodeReaderViewControllerBuilderBlock)(QRCodeReaderViewControllerBuilder* _Nonnull builder);

/**
 The QRCodeViewControllerBuilder aims to create a simple configuration object for
 the QRCode view controller.
 */
@interface QRCodeReaderViewControllerBuilder : NSObject
// MARK: - Configuring the QRCodeViewController Objects

/**
 The title to use for the cancel button.
 */
@property (nonatomic, strong) NSString* _Nullable cancelButtonTitle;

/**
 The code reader object used to scan the bar code.
 */
@property (nonatomic, strong) QRCodeReader* _Nonnull reader;

/**
 The reader view used to display the video capture and the UI components.
 */
@property (nonatomic, strong) QRCodeReaderView* _Nonnull readerView;

/**
 Flag to know whether the view controller start scanning the codes when the view will appear.
 */
@property (nonatomic) BOOL startScanningAtLoad;

/**
 Flag to display the cancel button.
 */
@property (nonatomic) BOOL showCancelButton;

/**
 Flag to display the toggle torch button. If the value is true and there is no torch the button will not be displayed.
 */
@property (nonatomic) BOOL showTorchButton;

/**
 Flag to display the guide view.
 */
@property (nonatomic) BOOL showOverlayView;

/// Convenince property for overlay view
@property (nonatomic, strong) QRCodeReaderViewOverlay* _Nullable overlayView;

/// Size of region the camera will scan for qr code. It will be centered in the camera preview. If `.zero` then whole area will be scanneable.
@property (nonatomic) CGSize scanRegionSize;

// MARK: - Initializers
/**
 Initialize a QRCodeReaderViewController builder with default values.
 
 - parameter buildBlock: A QRCodeReaderViewController builder block to configure itself.
 */
- (_Nonnull id) initWithBuilderBlock:(QRCodeReaderViewControllerBuilderBlock _Nonnull) buildBlock;

@end
