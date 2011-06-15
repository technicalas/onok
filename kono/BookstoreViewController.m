//
//  BookstoreViewController.m
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "BookstoreViewController.h"

@interface BookstoreViewController ()
@property (nonatomic, readonly)NSArray *categories;
@property (nonatomic, readonly)NSMutableArray *bigCatVCs;
@property (nonatomic, assign) BookItemGridViewController *currBigCatVC;
@end

@implementation BookstoreViewController
@synthesize categories;
@synthesize bigCatVCs, currBigCatVC;

#define CATEGORY_SIZE 11
- (NSArray *)categories
{
    if (!categories) {
        // replace with database content
        categories = [[NSArray alloc] initWithObjects:@"女性", @"娛樂", @"家居", @"新聞", @"旅行",                                                                  @"汽車", @"生活", @"男性", @"科技", @"藝術", @"運動",nil];
    }
    return categories;
}

- (NSArray *)bigCatVCs
{
    if (!bigCatVCs) {
        bigCatVCs = [[NSMutableArray array] retain];
        for (int i=0; i<CATEGORY_SIZE; i++) {
            [bigCatVCs addObject:[NSNull null]];
        }
    }
    return bigCatVCs;
}

- (void)dealloc
{
    [categories release];
    [bigCatVCs release];
    [categoryTableView release];
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    categoryTableView.dataSource = self;
    categoryTableView.delegate = self;
    categoryTableView.backgroundColor = [UIColor colorWithWhite: 0.95 alpha: 1.0];
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

- (BookItemGridViewController *)bigCatVCAtIndexPath:(NSIndexPath *)indexPath
{
    int index = indexPath.row;
    if ([self.bigCatVCs objectAtIndex:index] == [NSNull null]) {
        BookItemGridViewController *bigCatVC = [[BookItemGridViewController alloc] initWithNibName:@"CategoryPageController" bundle:nil];
        [self.bigCatVCs replaceObjectAtIndex:index withObject:bigCatVC];
        [bigCatVC release];
    }
    return [self.bigCatVCs objectAtIndex:index];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    if (self.currBigCatVC) {
        [self.currBigCatVC.view removeFromSuperview];
    }
    self.currBigCatVC = [self bigCatVCAtIndexPath:indexPath];
     // Pass the selected object to the new view controller.
    self.currBigCatVC.view.frame = CGRectMake(130, 44, 638, 916);  //44   
    [self.view addSubview:self.currBigCatVC.view];
}

@end
