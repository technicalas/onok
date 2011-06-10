//
//  BookstoreViewController.m
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "BookstoreViewController.h"
#import "RoundedRectView.h"
#import "BookItemGridViewController.h"

@interface BookstoreViewController ()
@property (nonatomic, readonly)NSArray *categories;
@end

@implementation BookstoreViewController
@synthesize categories;

- (NSArray *)categories
{
    if (!categories) {
        categories = [[NSArray alloc] initWithObjects:@"女性", @"娛樂", @"家居", @"新聞", @"旅行",                                                                  @"汽車", @"生活", @"男性", @"科技", @"藝術", @"運動",nil];
    }
    return categories;
}

- (void)dealloc
{
    [categories release];
    [categoryTableView release];
    [super dealloc];
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
    
    /*
    CGRect frame =  CGRectMake(0.0, 0.0, 120, 956);
    RoundedRectView *rrv = [[RoundedRectView alloc] initWithFrame:frame];
    rrv.edgeWidth = 4.0;
    rrv.backgroundColor = [UIColor clearColor];
    [self.view addSubview:rrv];
    [rrv release];
    
#define OFFSET 2.0
    CGFloat offset = rrv.edgeWidth + OFFSET;
    CGRect tableFrame = CGRectMake(frame.origin.x + offset, 
                                   frame.origin.y + offset,
                                   frame.size.width - offset*2,
                                   frame.size.height - offset*2);
    categoryTableView = [[UITableView alloc] initWithFrame:tableFrame];
    categoryTableView.dataSource = self;
    categoryTableView.delegate = self;
    categoryTableView.backgroundColor = [UIColor colorWithRed:1.0 green:1.0 blue:0.8 alpha:1.0];
    
    [self.view addSubview:categoryTableView];
    */
    
    categoryTableView.dataSource = self;
    categoryTableView.delegate = self;
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
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // Return the number of rows in the section.
    return [self.categories count];
}

- (NSString *)categoryAtIndexPath:(NSIndexPath *)indexPath
{
    return [self.categories objectAtIndex:indexPath.row];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"BookstoreTableViewCell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
	cell.textLabel.text = [self categoryAtIndexPath:indexPath];
    return cell;
}

#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
	
    BookItemGridViewController *bookItemVC = [[BookItemGridViewController alloc] init];
     // ...
     // Pass the selected object to the new view controller.
    bookItemVC.view.frame = CGRectMake(65, 48, 703, 912);
    [self.view addSubview:bookItemVC.view];
	 
}

@end