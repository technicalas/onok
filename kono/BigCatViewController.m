//
//  BigCatViewController.m
//  kono
//
//  Created by Sammy Long on 2011/6/10.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "BigCatViewController.h"

@implementation BigCatViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        bookItemGridVC = [[BookItemGridViewController alloc] init];
    }
    return self;
}

- (void)dealloc
{
    [bookItemGridVC release];
    [super dealloc];
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    bookItemGridVC.view.frame = self.view.bounds;
    [self.view addSubview:bookItemGridVC.view];
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
