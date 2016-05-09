//
//  main.m
//  OneAPM
//
//  Created by JieLiang Ma on 05/09/2016.
//  Copyright (c) 2016 JieLiang Ma. All rights reserved.
//

@import UIKit;
#import "BLAppDelegate.h"
#import "OneAPM/OneAPM.h"

int main(int argc, char * argv[])
{
    @autoreleasepool {
        [OneAPM startWithApplicationToken:@"token_string_get_from_oneapm"];
        
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([BLAppDelegate class]));
    }
}
