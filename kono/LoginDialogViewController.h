//
//  LoginDialogViewController.h
//  kono
//
//  Created by Kono Kono on 2011/6/19.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "FBConnect.h"
#import <UIKit/UIKit.h>


@interface LoginDialogViewController : UIViewController <FBSessionDelegate>{
    
    Facebook *facebook;
    
    int current_login_method;
    
    IBOutlet UIButton *fb_connect_but;
    IBOutlet UILabel *login_descrip;
    IBOutlet UIButton *change_login_method;
    IBOutlet UILabel *account_label;
    IBOutlet UILabel *pass_label;
    IBOutlet UITextField *account_textfield;
    IBOutlet UITextField *pass_textfield;
    IBOutlet UIButton *kono_login_but;
    IBOutlet UIButton *kono_register_but;
    
    
}

@property (nonatomic, retain) Facebook *facebook;

- (IBAction)fbLogin:(id)sender;
- (IBAction)change_login_way_press:(id)sender;

@end
