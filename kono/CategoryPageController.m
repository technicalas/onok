//
//  BigCatViewController.m
//  kono
//
//  Created by Sammy Long on 2011/6/10.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "CategoryPageController.h"

@implementation CategoryPageController
@synthesize scrollView;
@synthesize viewControllers;

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
   
    kNumberOfPages = 5;// Hard code
	// create all viewController
	NSMutableArray *controllers = [[NSMutableArray alloc] init];
	for (int i=0; i< kNumberOfPages; i++) {
		[controllers addObject:[NSNull null]];
	}
	self.viewControllers = controllers;
	[controllers release];
	
	scrollView.pagingEnabled = YES;
    scrollView.contentSize = CGSizeMake(scrollView.frame.size.width * kNumberOfPages, scrollView.frame.size.height);
    scrollView.showsHorizontalScrollIndicator = NO;
    scrollView.showsVerticalScrollIndicator = NO;
    scrollView.scrollsToTop = NO;
    scrollView.delegate = self;
	
	[self loadScrollViewWithPage:0];
    [self loadScrollViewWithPage:1];
	
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
