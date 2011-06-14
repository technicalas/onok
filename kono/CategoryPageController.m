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
#define SCROLL_WIDTH 703
#define SCROLL_HEIGHT 916
   
    self.scrollView.frame = CGRectMake(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT -SWITCH_BAR_HEIGHT);// HARD CODE VALUE IS BAD
	self.scrollView.pagingEnabled = YES;
    //CONTENT SIZE IS SUBJECT TO CHANGE
    self.scrollView.contentSize = CGSizeMake(scrollView.frame.size.width * kNumberOfPages, scrollView.frame.size.height);
    self.scrollView.showsHorizontalScrollIndicator = NO;
    self.scrollView.showsVerticalScrollIndicator = NO;
    self.scrollView.scrollsToTop = NO;
    self.scrollView.delegate = self;
	
	[self loadScrollViewWithPage:0];
    [self loadScrollViewWithPage:1];
	
}

- (void)loadScrollViewWithPage:(int)page {
    if (page < 0) return;
    if (page >= kNumberOfPages) return;
	
    BookItemGridViewController *controller = [viewControllers objectAtIndex:page];
    if ((NSNull *)controller == [NSNull null]) {
        controller = [[BookItemGridViewController alloc] init];
        [self.viewControllers replaceObjectAtIndex:page withObject:controller];
        [controller release];
    }
	
    if (nil == controller.view.superview) {
        CGRect frame = self.scrollView.frame;
        frame.origin.x = frame.size.width * page;
        frame.origin.y = 0;
        controller.view.frame = frame;
        [self.scrollView addSubview:controller.view];
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
    self.scrollView = nil;
    self.viewControllers = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

@end
