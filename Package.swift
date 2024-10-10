// swift-tools-version: 6.0
// The swift-tools-version declares the minimum version of Swift required to build this package.


import PackageDescription

let package = Package(
    name: "qr-iOS-EmvCo",
    products: [
        .library(
            name: "qr-iOS-EmvCo",
            targets: ["qr-iOS-EmvCo"]),
    ],
    targets: [
        .target(
            name: "qr-iOS-EmvCo",
            dependencies: ["MPQRCoreSDK", "MPQRScanSDK"]), // Add your dependencies here
        .binaryTarget(
            name: "MPQRCoreSDK",
            path: "Frameworks/MPQRCoreSDK.xcframework"),
        .binaryTarget(
            name: "MPQRScanSDK",
            path: "Frameworks/MPQRScanSDK.xcframework")
    ]
)
