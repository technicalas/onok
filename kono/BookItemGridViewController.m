//
//  BookItemGridViewController.m
//  kono
//
//  Created by Sammy Long on 2011/6/9.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "BookItemGridViewController.h"
#import "BookItemGridViewCell.h"

@implementation BookItemGridViewController
  
#pragma mark - View lifecycle

- (void) loadView
{
    AQGridView * aView = [[AQGridView alloc] initWithFrame: CGRectMake(0.0, 0.0, 703, 912)];
	self.gridView = aView;
	[aView release];
    self.gridView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	self.gridView.autoresizesSubviews = YES;
	self.gridView.delegate = self;
	self.gridView.dataSource = self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
        // Do any additional setup after loading the view from its nib.
    if ( _orderedImageNames != nil )
        return;
    
    NSArray * paths = [NSBundle pathsForResourcesOfType: @"jpeg" inDirectory: [[NSBundle mainBundle] bundlePath]];
    NSMutableArray * allImageNames = [[NSMutableArray alloc] init];
    
    for ( NSString * path in paths )
    {
        [allImageNames addObject: [path lastPathComponent]];
    }

    _orderedImageNames =  [allImageNames copy];
    _imageNames = [_orderedImageNames copy];

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
    NSLog(@"count = %d", [_imageNames count]);
    return ( [_imageNames count] );
}

#define BOOK_ITEM_WIDTH  250
#define BOOK_ITEM_HEIGHT 334
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
        
    bookItemCell.image = [UIImage imageNamed: [_imageNames objectAtIndex: index]];
            
    cell = bookItemCell;
    return ( cell );
}

#define GRID_CELL_WIDTH  175
#define GRID_CELL_HEIGHT 234

- (CGSize) portraitGridCellSizeForGridView: (AQGridView *) aGridView
{
    return ( CGSizeMake(GRID_CELL_WIDTH, GRID_CELL_HEIGHT) );
}

#pragma mark -
#pragma mark Grid View Delegate

// nothing here yet

- (void)dealloc
{
    [_imageNames release];
    [_orderedImageNames release];
    [super dealloc];
}

@end
