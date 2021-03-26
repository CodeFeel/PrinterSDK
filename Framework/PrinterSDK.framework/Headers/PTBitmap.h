/*!
 *  \~chinese
 *  @header     PTBitmap.h
 *  @abstract   图片处理
 *
 *  \~english
 *  @header     PTBitmap.h
 *  @abstract   Image manager
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SDKDefine.h"

/// 压缩模式
typedef NS_ENUM(NSInteger,PTBitmapCompressMode) {
    
    PTBitmapCompressModeNone = 0,   /*! *\~chinese 不压缩 *\~english None */
    PTBitmapCompressModeZPL2 = 16,  /*! *\~chinese ZPL2压缩算法 *\~english ZPL2 compress */
    PTBitmapCompressModeTIFF = 32,  /*! *\~chinese TIFF压缩算法 *\~english TIFF compress */
    PTBitmapCompressModeLZO = 48,   /*! *\~chinese LZO压缩算法 *\~english LZO compress */
};

/// 图片效果
typedef NS_ENUM(NSInteger, PTBitmapMode) {
    
    PTBitmapModeBinary = 0,     /*! *\~chinese 黑白二值图像 *\~english Binary */
    PTBitmapModeDithering = 1,  /*! *\~chinese 灰阶抖动图像 *\~english Dithering */
    PTBitmapModeColumn = 2,     /*! *\~chinese 无效 *\~english not supported */
};

@interface PTBitmap : NSObject

/// 生成打印机打印图片数据
/// @param image 图片
/// @param mode  图片效果
/// @param compress 压缩模式
/// @param package 数据是否分包
/// @param inversion 数据是否需要取反
+ (NSData *)getImageData:(CGImageRef)image mode:(PTBitmapMode)mode compress:(PTBitmapCompressMode)compress package:(BOOL)package inversion:(BOOL)inversion;


/// 用column算法生成的图片数据
/// @param sourceBitmap 输入数据
+ (NSData *)generateColumnData:(CGImageRef)sourceBitmap;
    

/// 将bitmap数据转成图片
/// @param image 图片
/// @param mode 生成的位图数据类型 简单的黑白二值化或者抖动处理
+ (UIImage *)generateRenderingWithImage:(CGImageRef)image mode:(PTBitmapMode)mode;
    
@end




