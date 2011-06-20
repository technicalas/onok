//
//  konoAppDelegate.h
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MainMenuViewController.h"
#import "LoginDialogViewController.h"

@interface konoAppDelegate : NSObject <UIApplicationDelegate> {

    LoginDialogViewController *login;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@end
