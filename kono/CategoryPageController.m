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
        
        self.scrollView =  [[[UIScrollView alloc] init] autorelease];
        [self.view addSubview:self.scrollView];
    }
    return self;
}

- (void)dealloc
{
    [viewControllers release];
    [scrollView release];
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
#define SWITCH_BAR_HEIGHT 44
    scrollView.frame = CGRectMake(0, 0, 703, 916 -SWITCH_BAR_HEIGHT);// HARD CODE VALUE IS BAD
	scrollView.pagingEnabled = YES;
    scrollView.contentSize = CGSizeMake(scrollView.frame.size.width * kNumberOfPages, scrollView.frame.size.height);
    scrollView.showsHorizontalScrollIndicator = NO;
    scrollView.showsVerticalScrollIndicator = NO;
    scrollView.scrollsToTop = NO;
    scrollView.delegate = self;
	
	[self loadScrollViewWithPage:0];
    [self loadScrollViewWithPage:1];
	
}

- (void)loadScrollViewWithPage:(int)page {
    if (page < 0) return;
    if (page >= kNumberOfPages) return;
	
    BookItemGridViewController *controller = [viewControllers objectAtIndex:page];
    if ((NSNull *)controller == [NSNull null]) {
        controller = [[BookItemGridViewController alloc] init];
        [viewControllers replaceObjectAtIndex:page withObject:controller];
        [controller release];
    }
	
    if (nil == controller.view.superview) {
        CGRect frame = scrollView.frame;
        frame.origin.x = frame.size.width * page;
        frame.origin.y = 0;
        controller.view.frame = frame;
        [scrollView addSubview:controller.view];
    }
}

- (void)scrollViewDidScroll:(UIScrollView *)sender {
    
    CGFloat pageWidth = scrollView.frame.size.width;
    int page = floor((scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    
    [self loadScrollViewWithPage:page - 1];
    [self loadScrollViewWithPage:page];
    [self loadScrollViewWithPage:page + 1];
	
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
