//
//  CreateQR.swift
//  EmvCoQR
//
//  Created by Tonny Franzis on 31/10/23.
//

import Foundation
import MPQRCoreSDK
import MPQRScanSDK
public class QRCodeGenerator {
    public var parsedData: [String: String] = [:]
    private let context = CIContext()
    public init() {
        // Initialize any properties
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
    
    public func processQRCodeImage(_ image: UIImage, completion: @escaping ([String: String]?) -> Void) {
        // Step 1: Extract QR code from the image
        guard let ciImage = CIImage(image: image) else {
            completion(nil)
            return
        }

        let options: [String: Any] = [CIDetectorAccuracy: CIDetectorAccuracyHigh]
        let qrDetector = CIDetector(ofType: CIDetectorTypeQRCode, context: nil, options: options)
        let features = qrDetector?.features(in: ciImage) ?? []

        // Step 2: Check if QR code is detected
        guard let qrFeature = features.first as? CIQRCodeFeature, let qrCode = qrFeature.messageString else {
            completion(nil) // No QR code detected
            return
        }

        // Step 3: Decrypt the detected QR code
        decryptQRCode(qrCode) { success in
            if success {
                // Step 4: Return the parsed data after decryption and parsing
                completion(self.parsedData)
            } else {
                completion(nil) // Decryption failed or QR code invalid
            }
        }
    }

    // Update decryptQRCode to return the decrypted data as well
    public func decryptQRCode(_ qrCode: String, completion: @escaping (Bool) -> Void) {
        // Split the IV and encrypted data
        let iv = String(qrCode.prefix(16)) // First 16 characters are IV
        let encryptedBase64 = String(qrCode.dropFirst(16)) // Remaining part is the encrypted data

        let aesKey = "JzI0Fpt9Qap7tDiK5JyuGsVgE3BbbFH1" // Your AES key
        
        // Initialize AES with the key and IV
        guard let aes = AES(key: aesKey, iv: iv) else {
            completion(false)
            return
        }

        // Decode the Base64 string
        guard let encryptedData = Data(base64Encoded: encryptedBase64) else {
            completion(false)
            return
        }

        // Decrypt the data
        if let decryptedText = aes.decrypt(data: encryptedData) {
            // Step 4: Parse the decrypted EMVCo string and update the parsed data
            self.parsedData = self.parseEMVCoString(decryptedText)
            completion(true)
        } else {
            completion(false)
        }
    }

    public func processQRCodeString(_ qrCode: String, completion: @escaping ([String: String]?) -> Void) {
        // Step 1: Decrypt the provided QR code
        decryptQRCode(qrCode) { success in
            if success {
                // Step 2: Return the parsed data after decryption and parsing
                completion(self.parsedData)  // Assuming parsedData is populated after decryption
            } else {
                completion(nil) // Decryption failed or QR code invalid
            }
        }
    }

    func parseEMVCoString(_ emvcoString: String) -> [String: String] {
        var result = [String: String]()
        var index = emvcoString.startIndex
        
        while index < emvcoString.endIndex {
            // Ensure there are enough characters left for tag and length
            guard index < emvcoString.endIndex,
                  let tagEnd = emvcoString.index(index, offsetBy: 2, limitedBy: emvcoString.endIndex),
                  let lengthEnd = emvcoString.index(tagEnd, offsetBy: 2, limitedBy: emvcoString.endIndex) else {
                print("Incomplete tag or length information.")
                break
            }
            
            let tag = String(emvcoString[index..<tagEnd])
            let lengthString = String(emvcoString[tagEnd..<lengthEnd])
            
            // Convert length to Int
            guard let length = Int(lengthString) else {
                print("Invalid length for tag \(tag): \(lengthString)")
                break
            }
            index = lengthEnd
            guard let valueEnd = emvcoString.index(index, offsetBy: length, limitedBy: emvcoString.endIndex) else {
                print("Incomplete value for tag \(tag). Expected length: \(length)")
                break
            }
            
            let value = String(emvcoString[index..<valueEnd])
            result[tag] = value
            
            index = valueEnd
        }
        
        return result
    }
}
