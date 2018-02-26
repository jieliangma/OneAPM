Pod::Spec.new do |s|
s.name             = "OneAPM"
s.version          = "2.2.5.6"
s.summary          = "OneAPM Analytics SDK for iOS."
s.description      = <<-DESC
						OneAPM library for iOS, Supports iPhone Simulator (i386), armv7, armv7s.
						DESC

s.homepage         = "https://www.oneapm.com"
s.license          = 'MIT'
s.author           = { "JieLiang Ma" => "majieliang@oneapm.com" }
s.source           = { :git => "https://github.com/jieliangma/OneAPM.git", :tag => s.version.to_s }

s.platform         = :ios, '6.0'
s.requires_arc     = true

s.vendored_framework = 'Frameworks/OneAPM.framework'
s.frameworks         = 'SystemConfiguration', 'CoreTelephony', 'CoreData'
s.libraries          = "z", "stdc++"

end
