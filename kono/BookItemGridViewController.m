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
#import "BookSalePageViewController.h"

@implementation BookItemGridViewController
@synthesize bookFamilies;

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
    
        
    NSArray * paths = [NSBundle pathsForResourcesOfType: @"jpeg" inDirectory: [[NSBundle mainBundle] bundlePath]];
    NSMutableArray * allImageNames = [[NSMutableArray alloc] init];
    
    for ( NSString * path in paths )
    {
        [allImageNames addObject: [path lastPathComponent]];
    }

    [allImageNames release];
    [self.gridView reloadData];
   
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

#pragma mark -
#pragma mark Grid View Data Source

- (NSUInteger) numberOfItemsInGridView: (AQGridView *) aGridView
{
    //return ( [_imageNames count] );
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
#pragma mark Grid View Delegate

// nothing here yet
- (void) gridView: (AQGridView *) gridView didSelectItemAtIndex: (NSUInteger) index
{
    UIView *top = [[self.view subviews] objectAtIndex:0];
    if (top) {
        [top removeFromSuperview];
    }
    BookSalePageViewController *bookSalePageVC = [[BookSalePageViewController alloc] initWithNibName:@"BookSalePageViewController" bundle:nil];
    bookSalePageVC.book = [self.bookFamilies objectAtIndex:index];
    [self.view addSubview:bookSalePageVC.view];
    [bookSalePageVC release];
}

- (void)dealloc
{
    [_imageNames release];
    [super dealloc];
}

@end
