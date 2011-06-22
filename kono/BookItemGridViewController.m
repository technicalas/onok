//
//  BookItemGridViewController.m
//  kono
//
//  Created by Sammy Long on 2011/6/9.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "BookItemGridViewController.h"
#import "BookItemGridViewCell.h"
#import "BookItem.h"
#import "KVConfig.h"

@implementation BookItemGridViewController
@synthesize bookFamilies;
@synthesize bookSalePageVC;

#pragma mark - View lifecycle

- (void) loadView
{
    AQGridView * aView = [[AQGridView alloc] initWithFrame: CGRectZero];
	self.gridView = aView;
	[aView release];
    self.gridView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	self.gridView.autoresizesSubviews = YES;
	self.gridView.delegate = self;
	self.gridView.dataSource = self;
    //self.gridView.backgroundColor = [UIColor colorWithRed:0.8 green:0.93 blue:1.0 alpha:1.0];// cute sky blue
    self.gridView.backgroundColor = [UIColor colorWithWhite: 0.95 alpha: 1.0];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
        // Do any additional setup after loading the view from its nib.
    
    // let's see how bookfamilies go
    [self.bookFamilies enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        BookFamily *bf = obj;
        NSLog(@"family name %@", bf.name);
        [bf.items enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            BookItem *item = obj;
            NSLog(@"product is %@",item.productId);
        }];
    }];
    [self.gridView reloadData];
   
    UIInterfaceOrientation or = [UIApplication sharedApplication].statusBarOrientation;
    orient = (UIInterfaceOrientationIsPortrait(or))?0:1;
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

- (void)handleRotation:(UIInterfaceOrientation)interfaceOrientation
{
    if (UIInterfaceOrientationIsPortrait(interfaceOrientation)) {
        self.bookSalePageVC.view.frame = CGRectMake(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) ;
    } else {
        self.bookSalePageVC.view.frame = CGRectMake(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);
    }
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    UIInterfaceOrientation oreo = UIInterfaceOrientationIsPortrait(fromInterfaceOrientation)?UIInterfaceOrientationLandscapeLeft:UIInterfaceOrientationPortrait;
    [self handleRotation:oreo];
    
    orient = (orient+1)%2;
}

#pragma mark -
#pragma mark Grid View Data Source

- (NSUInteger) numberOfItemsInGridView: (AQGridView *) aGridView
{
    return [self.bookFamilies count];
}

#define BOOK_ITEM_WIDTH  175//250
#define BOOK_ITEM_HEIGHT 234//334
- (AQGridViewCell *) gridView: (AQGridView *) aGridView cellForItemAtIndex: (NSUInteger) index
{
    static NSString * PlainCellIdentifier = @"PlainCellIdentifier";
   
    AQGridViewCell * cell = nil;
  
    BookItemGridViewCell * bookItemCell = (BookItemGridViewCell *)[aGridView dequeueReusableCellWithIdentifier: PlainCellIdentifier];
    if ( bookItemCell == nil )
    {
        bookItemCell = [[[BookItemGridViewCell alloc] initWithFrame: CGRectMake(0.0, 0.0, BOOK_ITEM_WIDTH, BOOK_ITEM_HEIGHT)
                                                          reuseIdentifier: PlainCellIdentifier] autorelease];
        //plainCell.selectionGlowColor = [UIColor blueColor];
    }
        
    //bookItemCell.image = [UIImage imageNamed: [_imageNames objectAtIndex: index]];
    BookFamily *bookFamily = [self.bookFamilies objectAtIndex:index];
    NSString *image = [bookFamily.name stringByAppendingString:@".jpeg"];
    bookItemCell.image = [UIImage imageNamed:image];
            
    cell = bookItemCell;
    return ( cell );
}

- (CGSize) portraitGridCellSizeForGridView: (AQGridView *) aGridView
{
    return ( CGSizeMake(BOOK_ITEM_WIDTH, BOOK_ITEM_HEIGHT) );
}

#pragma mark -
#pragma mark PresentSaleViewDelegate
-(void)salePageViewControllerDidFinished:(BookSalePageViewController *)bookSalePageVC
{
    self.bookSalePageVC = nil;
}

#pragma mark -
#pragma mark Grid View Delegate

-(void)displaySaleView 
{
    UIView *superview = [[self.view superview] superview];// this is the bookstore view
    //[self handleRotation:self.interfaceOrientation];// so ... bug here
    //UIInterfaceOrientation oreo = (orient == 0)? UIInterfaceOrientationPortrait:UIInterfaceOrientationLandscapeLeft;
    UIInterfaceOrientation oreo = [UIApplication sharedApplication].statusBarOrientation;
    [self handleRotation:oreo];
    [superview addSubview:self.bookSalePageVC.view];
}

// nothing here yet
- (void) gridView: (AQGridView *) gridView didSelectItemAtIndex: (NSUInteger) index
{
    BookSalePageViewController *bspvc = [[BookSalePageViewController alloc] initWithNibName:@"BookSalePageViewController" bundle:nil];
    bspvc.book = [self.bookFamilies objectAtIndex:index];
    bspvc.delegate = self;
    self.bookSalePageVC = [bspvc autorelease];
    //[self.view addSubview:bookSalePageVC.view];
    [self displaySaleView];
}

- (void)dealloc
{
    [bookFamilies release];
    [bookSalePageVC release];
    [_imageNames release];
    [super dealloc];
}

@end
