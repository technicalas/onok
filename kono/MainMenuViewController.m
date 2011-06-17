//
//  MainMenuViewController.m
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "MainMenuViewController.h"
 
@implementation MainMenuViewController
@synthesize bookstorevc;
@synthesize space;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

#pragma mark - View lifecycle
 
#define STATUS_BAR_HEIGHT 20
- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    UIInterfaceOrientation or = [UIApplication sharedApplication].statusBarOrientation;
    if (UIInterfaceOrientationIsPortrait(or)) {
        self.view.frame = CGRectMake(0, STATUS_BAR_HEIGHT, [[UIScreen mainScreen] bounds].size.width, [[UIScreen mainScreen] bounds].size.height);
    } 
    
    self.bookstorevc = [[BookstoreViewController alloc] initWithNibName:@"BookstoreViewController" bundle:nil];
    [bookstorevc release];   
    [self.space addSubview:self.bookstorevc.view];
}

- (IBAction) bookstoreButtonPressed
{
    if ([self.bookstorevc.view superview] == nil) {
        [self.space addSubview:self.bookstorevc.view];
    }
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

- (void)dealloc
{
    [bookstorevc release];
    [super dealloc];
}

@end
