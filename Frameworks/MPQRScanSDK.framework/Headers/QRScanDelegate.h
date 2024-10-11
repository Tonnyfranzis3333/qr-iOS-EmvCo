//
//  QRScanDelegate.h
//  MPQRScanSDK
//
//  Created by Saurabh Mendhe on 12/09/18.
//  Copyright © 2018 Muchamad Chozinul Amri. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * This protocol defines delegate methods for objects that implements the
 * `QRScanDelegate`. The methods of the protocol allow the delegate to be
 * notified when user revieves/reads the QR string from open-url or some error has occured.
 */
@protocol QRScanDelegate <NSObject>

/**
 * @name Listening for QRScan Outcome for QRString inside open-url
 */

/**
 * @note Abstract: Tells the delegate that the reader did recieve the QR string from open-url.
 * @param qrString The string holds the content of QRcode image.
 * @param isError Boolen value when error has occured otherwise False.
 * @param statusText The status text when some error has occured otherwise empty.
 * @note since 1.0.0
 */
-(void)onQRScanOutcomeforQrString:(NSString *) qrString
                                 isError:(Boolean) isError
                              statusText:(NSString *)statusText;
@end
