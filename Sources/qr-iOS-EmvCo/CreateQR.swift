//
//  CreateQR.swift
//  EmvCoQR
//
//  Created by Tonny Franzis on 31/10/23.
//

import Foundation
import MPQRCoreSDK

public class QRCodeGenerator {
    
    public init() {
        // Initialize any properties or setup code here if needed
    }
    
    public func generatePushPaymentQR(transactionCurrencyCode: String,city: String,merchantCategoryCode: String,countryCode: String,firstName: String,lastName: String,postalCode: String,adUserMerchantMasterId: Int) -> UIImage? {
        do {
            // Generate
            let pushPaymentData = PushPaymentData()
            pushPaymentData.payloadFormatIndicator = "00"
            pushPaymentData.pointOfInitiationMethod = "01"
            pushPaymentData.merchantIdentifierVisa02 = String(adUserMerchantMasterId)
            pushPaymentData.merchantCategoryCode = merchantCategoryCode
            pushPaymentData.transactionCurrencyCode = transactionCurrencyCode
            pushPaymentData.countryCode = countryCode
            pushPaymentData.merchantName = firstName + lastName
            pushPaymentData.merchantCity = city
            pushPaymentData.postalCode = postalCode
            let qrCodeString = try pushPaymentData.generatePushPaymentString()
            let Enckey256 = "JzI0Fpt9Qap7tDiK5JyuGsVgE3BbbFH1"
            let iv = randomString(length: 16)
            let aes256 = AES(key: Enckey256, iv: iv)
            let encryptedReqBody = aes256?.encrypt(string: qrCodeString)
            print("test")
            guard let encbase64 = encryptedReqBody?.base64EncodedString() else {
                // Handle the case where encryption fails, e.g., log an error
                return nil
            }
            
            let encrpRequest = iv + encbase64
            
            print("encrpRequest \(encrpRequest)")
            if let qrImage = self.generateQRCode(from: encrpRequest) {
                return qrImage
            } else {
                // Handle the case where QR code generation fails, e.g., log an error
                return nil
            }
        } catch {
            print("Error occurred while creating PushPaymentData object \(error)")
        }
        
        return nil
    }
    
    public func generateQRCode(from qrCodeString: String) -> UIImage? {
        if let data = qrCodeString.data(using: .utf8) {
            let filter = CIFilter(name: "CIQRCodeGenerator")
            filter?.setValue(data, forKey: "inputMessage")

            if let qrCodeImage = filter?.outputImage {
                let scaleX = 200 / qrCodeImage.extent.size.width
                let scaleY = 200 / qrCodeImage.extent.size.height
                let transformedImage = qrCodeImage.transformed(by: CGAffineTransform(scaleX: scaleX, y: scaleY))

                if let cgImage = CIContext().createCGImage(transformedImage, from: transformedImage.extent) {
                    return UIImage(cgImage: cgImage)
                }
            }
        }
        return nil
    }
}
