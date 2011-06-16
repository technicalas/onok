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
#define SCREEN_PORTRAIT_WIDTH 768
#define SCREEN_PORTRAIT_HEIGHT 1024
#define TOP_BAR_PORTRAIT_HEIGHT 45
#define STATUS_BAR_HEIGHT 20
- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
     self.bookstorevc = [[BookstoreViewController alloc] initWithNibName:@"BookstoreViewController" bundle:nil];
    [bookstorevc release];     
}

- (IBAction) bookstoreButtonPressed
{
    [self.space addSubview:self.bookstorevc.view];
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
