//
//  QRCodeReaderViewOverlay.h
//  Pods
//
//  Created by Muchamad Chozinul Amri on 11/10/17.
//  Copyright © 2017 MasterCard. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * Draw rectangle area, the area is where object is placed to be scanned
 * - User can modify the color of the non scannable area
 * - User can modify the size of the area
 * - User can modify the corner color, length, and width
 */
IB_DESIGNABLE @interface QRCodeReaderViewOverlay : UIView
    
/// This is the size of the region that will have 4 corners and have a transparent background apart from the masked area
@property (nonatomic) IBInspectable CGSize indicatorSize;

/// Width of the corners of square overlay
@property (nonatomic) IBInspectable double cornerWidth;

/// Length of the corners of square overlay
@property (nonatomic) IBInspectable double cornerLength;

/// Corner of the corners of square overlay
@property (nonatomic, strong) IBInspectable UIColor* cornerColor;

/// Mask color. This color will be used to fill all the area other than the area in the center with size as specified in `indicatorSize`
@property (nonatomic,strong) IBInspectable UIColor* maskColor;

///Get rectangle position of the indicator
- (CGRect) getIndicatorRect;

@end
