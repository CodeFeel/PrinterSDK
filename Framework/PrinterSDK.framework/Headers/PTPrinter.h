/*!
 *  \~chinese
 *  @header     PTPrinter.h
 *  @abstract   打印机属性
 *
 *  \~english
 *  @header     PTPrinter.h
 *  @abstract   Printer properties
 */

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "PTRouter.h"

/// 打印机的连接模块
typedef NS_ENUM(NSInteger, PTPrinterModule) {
    
    PTPrinterModuleBLE        = 0,  /// 蓝牙
    PTPrinterModuleWiFi       = 1,  /// 无线
};

@interface PTPrinter : NSObject<NSCoding>

/// 打印机名称
@property(strong,nonatomic,readwrite) NSString *name;
/// 打印机mac地址
@property(strong,nonatomic,readwrite) NSString *mac;
/// 打印机蓝牙模块
@property(assign,nonatomic,readwrite) PTPrinterModule module;
/// 发现蓝牙时获取到的广播信息
@property(strong,nonatomic,readwrite) NSDictionary *advertisement;
/// 蓝牙外设UUID
@property(strong,nonatomic,readwrite) NSString *uuid;
/// 发现外设时获取到的信号强度值，单位分贝
@property(strong,nonatomic,readwrite) NSNumber *rssi;
/// 信号强度等级分0-5级
@property(strong,nonatomic,readwrite) NSNumber *strength;
/// 由信号强度计算的距离
@property(strong,nonatomic,readwrite) NSNumber *distance;
/// 蓝牙外设
@property(strong,nonatomic,readwrite) CBPeripheral *peripheral;
/// 外设的ip地址
@property(strong,nonatomic,readwrite) NSString *ip;
/// 端口
@property(strong,nonatomic,readwrite) NSString *port;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *,id> *)advertisementData RSSI:(NSNumber *)RSSI;

@end
