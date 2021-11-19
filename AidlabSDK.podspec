Pod::Spec.new do |spec|

  spec.name              = 'AidlabSDK'
  spec.version           = '1.0.0'
  spec.summary           = 'Sample Spec'
  spec.homepage          = 'https://www.aidlab.com'

  spec.author            = { 'Szymon Gesicki' => 'szymon.gesicki@aidlab.com' }
  spec.license = { :type => "MIT", :text => "MIT License" }

  spec.platform          = :ios
  spec.source       = { :git => "https://github.com/AidlabSDK/AidlabSDK.git", :tag => "#{spec.version}" }
  spec.ios.deployment_target = '10.0'
  spec.ios.vendored_frameworks = 'AidlabSDK.xcframework' 

end
