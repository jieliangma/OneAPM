Pod::Spec.new do |s|
  s.name             = "OneAPM"
  s.version          = "2.2.1-bitcode-disabled"
  s.summary          = "OneAPM Analytics SDK for iOS."
  s.description      = <<-DESC
                        OneAPM library for iOS, Supports iPhone Simulator (i386), armv7, armv7s.
                          DESC

  s.homepage         = "http://www.oneapm.com"
  s.license          = 'MIT'
  s.author           = { "JieLiang Ma" => "majieliang@oneapm.com" }
  s.source           = { :git => "https://github.com/jieliangma/OneAPM.git", :tag => s.version.to_s }

  s.platform         = :ios, '6.0'
  s.requires_arc     = true

  #s.resource_bundles    = { 'OneAPM' => ['Pod/Assets/*.png'] }
  #s.public_header_files = 'Pod/Classes/**/*.h'
  #s.source_files       = 'Pod/Classes/OneAPM.h'
  s.vendored_framework = 'Pod/Classes/**/*.framework'
  s.frameworks         = 'SystemConfiguration', 'CoreTelephony', 'CoreData'
  s.libraries          = "z", "stdc++"

end
