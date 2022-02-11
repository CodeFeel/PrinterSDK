#
# Be sure to run `pod lib lint PrinterSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'PrinterSDK'
  s.version          = '1.4.3'
  s.summary          = 'A repository for bluetooth and printer communications.'
  s.description      = 'A library for bluetooth and printer communication. Bluetooth connection, data processing, and sending data are encapsulated in the library, and the API can be called directly'
                        
  s.homepage         = 'https://github.com/CodeFeel/PrinterSDK'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'CodeFeel' => '492262370@qq.com' }
  s.source           = { :git => 'https://github.com/CodeFeel/PrinterSDK.git', :tag => "#{s.version}" }
  s.ios.deployment_target = '9.0'

  s.frameworks = 'UIKit', 'CoreBluetooth', 'Foundation', 'CoreGraphics', 'SystemConfiguration'
  s.ios.vendored_frameworks = 'Framework/PrinterSDK.framework'
  s.vendored_frameworks = 'PrinterSDK.framework'
end
