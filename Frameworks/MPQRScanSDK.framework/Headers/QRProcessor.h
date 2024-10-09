//
//  QRProcessor.h
//  MPQRScanSDK
//
//  Created by Saurabh Mendhe on 12/09/18.
//  Copyright © 2018 Muchamad Chozinul Amri. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QRScanDelegate.h"

/**
 * QR Processor class object provides the implementation for qr string without scanning the QR code with help of URL Scheme
 * @note since 2.0.2
 */
@interface QRProcessor : NSObject

/**
 * @name Managing the Delegate
 */

/**
 * @note Abstract: The object that acts as the delegate for receiving outcome from open-URL as qr string.
 * reader.
 * @note since 2.0.2
 */
@property (nonatomic, weak) id <QRScanDelegate> delegate;

/**
 * @note Abstract: Process the QR String from URL.
 * @param url : Holds the open-URL, the url holds the information about LocalURI/RemoteURI/QRString .
 * @note since 2.0.2
 */
-(void)processQRStringFromUrl:(NSURL *)url;

@end
