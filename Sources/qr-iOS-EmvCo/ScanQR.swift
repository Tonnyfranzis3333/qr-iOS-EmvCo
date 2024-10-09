//
//  ScanQR.swift
//  EmvCoQR
//
//  Created by Tonny Franzis on 31/10/23.
//

import Foundation
import MPQRScanSDK
import Vision
import UIKit
import CoreImage

public class QRCodeReader {
//    public var recognizedCodes: [String] = []
    public var parsedData: [String: String] = [:]
    private let context = CIContext()

    public init() {
        // Initialize any setup code here if needed
    }

    public func readQRCodeFromImage(_ image: UIImage, completion: @escaping ([String]) -> Void) {
        guard let ciImage = CIImage(image: image) else {
            completion([])
            return
        }

        let options: [String: Any] = [CIDetectorAccuracy: CIDetectorAccuracyHigh]
        let qrDetector = CIDetector(ofType: CIDetectorTypeQRCode, context: context, options: options)
        let features = qrDetector?.features(in: ciImage) ?? []

        var recognizedCodes: [String] = []
        for feature in features {
            if let qrFeature = feature as? CIQRCodeFeature, let message = qrFeature.messageString {
                recognizedCodes.append(message)
            }
        }

        completion(recognizedCodes)
    }


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
                // Parse the decrypted EMVCo string and update the published variable
                self.parsedData = parseEMVCoString(decryptedText)
                completion(true)
            } else {
                completion(false)
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
                
                // Move index to start of value
                index = lengthEnd
                
                // Calculate end index of value
                guard let valueEnd = emvcoString.index(index, offsetBy: length, limitedBy: emvcoString.endIndex) else {
                    print("Incomplete value for tag \(tag). Expected length: \(length)")
                    break
                }
                
                let value = String(emvcoString[index..<valueEnd])
                result[tag] = value
                
                // Move index to the next tag
                index = valueEnd
            }
            
            return result
        }

}
