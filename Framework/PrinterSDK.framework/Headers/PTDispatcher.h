/*!
 *  \~chinese
 *  @header     PTDispatcher.h
 *  @abstract   通讯协议
 *
 *  \~english
 *  @header     PTDispatcher.h
 *  @abstract   Protocol
 */

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "SDKDefine.h"
#import "PTPrinter.h"


/// 连接模式
typedef NS_ENUM(NSInteger, PTDispatchMode) {
    /// 蓝牙
    PTDispatchModeBLE        = 0,
    
    /// 无线
    PTDispatchModeWiFi       = 1
};

/// 手机蓝牙状态
typedef NS_ENUM(NSInteger, PTBluetoothState) {
    /// 未授权，请前往系统设置授权
    PTBluetoothStateUnauthorized  = 0,
    /// 蓝牙未开
    PTBluetoothStatePoweredOff  = 1,
    /// 正常
    PTBluetoothStatePoweredOn  = 2,
};

/// 打印完成后打印机返回的状态
typedef NS_ENUM(NSInteger, PTPrintState) {
    
    /// 打印成功
    PTPrintStateSuccess             = 0xcc00,
    
    /// 打印失败（缺纸）
    PTPrintStateFailurePaperEmpty   = 0xcc01,
    
    /// 打印失败（开盖）
    PTPrintStateFailureLidOpen      = 0xcc02
};

/// 返回连接的错误类型
typedef NS_ENUM(NSInteger, PTConnectError) {
    
    /// 连接超时
    PTConnectErrorBleTimeout                  = 0,
    
    /// 获取服务超时
    PTConnectErrorBleDisvocerServiceTimeout   = 1,
    
    /// 验证超时
    PTConnectErrorBleValidateTimeout          = 2,
    
    /// 未知设备
    PTConnectErrorBleUnknownDevice            = 3,
    
    /// 系统错误,由coreBluetooth框架返回
    PTConnectErrorBleSystem                   = 4,
    
    /// 验证失败
    PTConnectErrorBleValidateFail             = 5,
    
    /// 无线连接超时
    PTConnectErrorWifiTimeout                 = 6,
    
    /// socket错误
    PTConnectErrorWifiSocketError             = 7
};

/// 返回固件升级错误
typedef NS_ENUM(NSInteger, PTUpgradeFirmwareState) {
    
    /// 升级成功
    PTUpgradeFirmwareStateSuccess                   = 0,
    
    /// 升级失败，数据长度错误
    PTUpgradeFirmwareStateFailureDataLengthError,
    
    /// 升级失败，验证或者校验失败
    PTUpgradeFirmwareStateFailureValidateFail,
    
    /// 升级失败，写入超时
    PTUpgradeFirmwareStateFailureWriteTimout,
    
    /// 升级失败，包序号错误
    PTUpgradeFirmwareStateFailurePackageNumberError,
    
    /// 升级失败，包长度错误
    PTUpgradeFirmwareStateFailurePackageLengthError,
    
    /// 升级失败，写入失败
    PTUpgradeFirmwareStateFailureWriteFail,
    
    /// 升级失败
    PTUpgradeFirmwareStateFail
};

@class PTPrinter;

typedef void(^PTPrinterMutableArrayBlock)(NSMutableArray<PTPrinter *> *printerArray);
typedef void(^PTEmptyParameterBlock)(void);
typedef void(^PTBluetoothConnectFailBlock)(PTConnectError error);
typedef void(^PTNumberParameterBlock)(NSNumber *number);
typedef void(^PTDataParameterBlock)(NSData *data);
typedef void(^PTPrintStateBlock)(PTPrintState state);
typedef BOOL(^PTPeripheralFilterBlock)(CBPeripheral *peripheral, NSDictionary<NSString *,id> *advertisementData, NSNumber *RSSI);
typedef void(^PTUnconnectBlock)(NSNumber *number, BOOL isActive);
typedef void(^PTSendSuccessParameterBlock)(int64_t dataCount, double time);
typedef void(^PTUpgradeFirmwareStateBlock)(PTUpgradeFirmwareState state);

@interface PTDispatcher : NSObject

@property (assign, nonatomic) PTDispatchMode                          mode;
@property (strong, nonatomic, readwrite) PTPrinter                    *printerConnected;  //该属性表示连接后的打印机对象
@property (copy, nonatomic, readwrite) PTSendSuccessParameterBlock    sendSuccessBlock;
@property (copy, nonatomic, readwrite) PTEmptyParameterBlock          sendFailureBlock;
@property (copy, nonatomic, readwrite) PTNumberParameterBlock         sendProgressBlock;
@property (copy, nonatomic, readwrite) PTDataParameterBlock           receiveDataBlock;
@property (copy, nonatomic, readwrite) PTPrintStateBlock              printStateBlock;
@property (copy, nonatomic, readwrite) PTPrinterMutableArrayBlock     findAllPeripheralBlock;
@property (copy, nonatomic, readwrite) PTEmptyParameterBlock          connectSuccessBlock;
@property (copy, nonatomic, readwrite) PTBluetoothConnectFailBlock    connectFailBlock;
@property (copy, nonatomic, readwrite) PTUnconnectBlock               unconnectBlock;
@property (copy, nonatomic, readwrite) PTNumberParameterBlock         readRSSIBlock;
@property (copy, nonatomic, readwrite) PTPeripheralFilterBlock        peripheralFilterBlock;
@property (copy, nonatomic, readwrite) PTUpgradeFirmwareStateBlock    upgradeFirmwareStateBlock;

/// 创建单例对象
+ (instancetype)share;

/// 发送数据
- (void)sendData:(NSData *)data;

/// 开始扫描蓝牙
- (void)scanBluetooth;

/// 停止扫描蓝牙，连接成功后SDK会自动停止扫描
- (void)stopScanBluetooth;

/// 扫描Wi-Fi wifi的端口是9100, 如果需要获得路由的名称以及mac地址信息， ios12+需要Access WiFi Information的权限，iOS13+以后要开启定位权限
- (void)scanWiFi:(PTPrinterMutableArrayBlock)wifiAllBlock;

/// 获取已发现的所有打印机
- (void)whenFindAllBluetooth:(PTPrinterMutableArrayBlock)bluetoothBlock;

/// 获取蓝牙的rssi信号强度
- (void)whenReadRSSI:(PTNumberParameterBlock)readRSSIBlock;

/// 连接打印机，传入的是打印机对象
- (void)connectPrinter:(PTPrinter *)printer;

/// 断开打印机连接
- (void)disconnect;

/// 连接成功回调，连接成功后，会停止扫码设备
- (void)whenConnectSuccess:(PTEmptyParameterBlock)connectSuccessBlock;

/// 连接失败的回调
- (void)whenConnectFailureWithErrorBlock:(PTBluetoothConnectFailBlock)connectFailBlock;

/// 断开连接的回调，调用unconnectPrinter断开打印机后，会调用该方法
- (void)whenUnconnect:(PTUnconnectBlock)unconnectBlock;

/// 数据发送成功的回调，数据发送完成后，会调用该方法
- (void)whenSendSuccess:(PTSendSuccessParameterBlock)sendSuccessBlock;

/// 数据发送失败的回调
- (void)whenSendFailure:(PTEmptyParameterBlock)sendFailureBlock;

/// 数据发送进度的回调
- (void)whenSendProgressUpdate:(PTNumberParameterBlock)sendProgressBlock;

/// 接收到打印机返回的数据，比如获取打印机名称就是通过该方法返回
- (void)whenReceiveData:(PTDataParameterBlock)receiveDataBlock;

/// 接收到打印机打印状态回调，使用该方法前，需要保证打印机打开了状态回调的开关，比如CPCL指令集中的cpclTurnOnPrintStatusCallBack方法，ESC中的turnOnPrintStatusCallBack方法
- (void)whenUpdatePrintState:(PTPrintStateBlock)printStateBlock;

/// 设置蓝牙连接超时时间
- (void)setupBleConnectTimeout:(double)timeout;

/// 设置外设过滤，在发现打印机设备的回调中进行一些过滤，返回自己想要的机型
- (void)setupPeripheralFilter:(PTPeripheralFilterBlock)block;

/// 注册蓝牙中心，该接口用于兼容你自己实现的CoreBluetooth框架
- (void)registerCentralManager:(CBCentralManager *)manager delegate:(id<CBCentralManagerDelegate>)delegate;

/// 注销代理
- (void)unregisterDelegate;

/// 升级固件状态回调
- (void)whenUpgradeFirmwareStateBlock:(PTUpgradeFirmwareStateBlock)upgradeFirmwareStateBlock;

/// 手机的蓝牙状态,为了准确获取手机蓝牙状态，需要在app启动的时候初始化PTDispatcher
- (PTBluetoothState)getBluetoothStatus;

/// SDK打包时间
- (NSString *)SDKBuildTime;

@end
