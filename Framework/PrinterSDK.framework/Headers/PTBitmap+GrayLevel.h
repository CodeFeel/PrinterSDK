/*!
 *  \~chinese
 *  @header     GrayLevel.h
 *  @abstract   图片的灰度处理
 *
 *  \~english
 *  @header     GrayLevel.h
 *  @abstract   Image gray manager
 */

#import "PTBitmap.h"
#import <UIKit/UIKit.h>

@interface PTBitmap (GrayLevel)


/// 获取图像的灰度数据
/// @param image 图片
+ (NSData *)graylevel256Datas:(UIImage *)image;

/// 获取图像的灰度数据
/// @param image 图片
/// @param needReverse 是否反转灰度值 0->255 254->1
+ (NSData *)graylevel256Datas:(CGImageRef)image reverse:(BOOL)needReverse;


/// 从灰度图片数据获取图像
/// @param data 灰度数据，每个字节代表每个像素的256阶灰度值
/// @param width 图片宽度
+ (UIImage *)imageWithGraylevel256Data:(NSData *)data width:(NSUInteger)width;

/// 灰度数据锐化
/// @param data 灰度数据，每个字节代表每个像素的256阶灰度值
/// @param width 图片宽度
+ (NSData *)sharpenGraylevel256Data:(NSData *)data width:(NSUInteger)width;


/// 获取经过热补偿处理的数据
/// @param data 灰度数据，每个字节代表每个像素的256阶灰度值
/// @param width 图片宽度
+ (NSData *)historyCompensateGraylevel256Data:(NSData *)data width:(NSUInteger)width;


/// 返回黑白图像数据
/// @param data 灰度数据，每个字节代表每个像素的256阶灰度值
/// @param width 图片宽度
+ (NSData *)binaryDataOneBytePerPixelGraylevel256Data:(NSData *)data width:(NSUInteger)width;


/// 将图片导入设备灰度空间获取的灰度数据
/// @param image 图片
+ (NSData *)systemGraylevel256Datas:(UIImage *)image;

/// 将bitmap数据转成图片
/// @param bitmap 位图数据
/// @param height 图片高度
+ (UIImage *)image:(NSData *)bitmap height:(size_t)height;

/// 动态获取二值化的阈值
/// @param data 256灰阶数据
/// @param width 图片宽度
/// @param height 图片高度
+ (NSUInteger)getThresholdForBinaryByGrayData:(NSData *)data width:(NSUInteger)width height:(NSUInteger)height;

/// 获取图像的灰度数据
/// @param image 输入数据
+ (NSData *)grayscaleImageForImage:(CGImageRef)image;

@end


@interface PTBitmap(Printer)

+ (NSData *)binaryDataOneBitPerPixelGraylevel256Data:(NSData *)data width:(NSUInteger)width;

+ (NSData *)binaryDataOneBitPerPixelGraylevel256Data:(NSData *)data width:(NSUInteger)width valve:(NSUInteger)valve;

+ (NSData *)ditheredBinaryDataOneBitPerPixelGraylevel256Data:(NSData *)data width:(NSUInteger)width;

+ (NSData *)meiKaLePrinterData:(NSData *)graylevel256Data;

@end
