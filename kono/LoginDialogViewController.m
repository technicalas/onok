//
//  LoginDialogViewController.m
//  kono
//
//  Created by Kono Kono on 2011/6/19.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "LoginDialogViewController.h"


@implementation LoginDialogViewController

@synthesize facebook;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }

    current_login_method = 0;
    
    return self;
}

- (void)fbDidLogin {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:[facebook accessToken] forKey:@"FBAccessTokenKey"];
    [defaults setObject:[facebook expirationDate] forKey:@"FBExpirationDateKey"];
    [defaults synchronize];
    
    [self.view removeFromSuperview];    
    
}

- (void)fbDidNotLogin:(BOOL)cancelled
{
    NSLog(@"fb did not login");
}

- (void)dealloc
{
    [facebook release];
    [super dealloc];
}

- (IBAction)change_login_way_press:(id)sender
{


    if(current_login_method == 0){
        
    
        login_descrip.text = @"使用Kono帳號登入";
        fb_connect_but.hidden = YES;
        [change_login_method setTitle:@"使用facebook登入" forState:UIControlStateNormal];
        account_label.hidden = NO;
        account_textfield.hidden = NO;
        pass_label.hidden = NO;
        pass_textfield.hidden = NO;
        kono_login_but.hidden = NO;
        kono_register_but.hidden = NO;
        
        current_login_method = 1;
    }else if(current_login_method == 1){
        
        login_descrip.text = @"使用facebook帳號註冊及登入";
        fb_connect_but.hidden = NO;
        [change_login_method setTitle:@"沒有facebook帳號？" forState:UIControlStateNormal];
        account_label.hidden = YES;
        account_textfield.hidden = YES;
        pass_label.hidden = YES;
        pass_textfield.hidden = YES;
        kono_login_but.hidden = YES;
        kono_register_but.hidden = YES;
        
        current_login_method = 0;    
    
    }

    
    
}


- (IBAction)fbLogin:(id)sender
{
    
    NSLog ( @"The current date and time is:");
    
    facebook = [[Facebook alloc] initWithAppId:@"168317523232714"];    
    //facebook.sessionDelegate = self;
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    if ([defaults objectForKey:@"FBAccessTokenKey"] 
        && [defaults objectForKey:@"FBExpirationDateKey"]) {
        facebook.accessToken = [defaults objectForKey:@"FBAccessTokenKey"];
        facebook.expirationDate = [defaults objectForKey:@"FBExpirationDateKey"];
    }
    
    if (![facebook isSessionValid]) {
        [facebook authorize:nil delegate:self];
    }
    
    
    
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

@end
