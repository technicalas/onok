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
@property (nonatomic, readonly)NSArray *categoriesCh;
@property (nonatomic, readonly)NSDictionary *categoryDictionary;
@property (nonatomic, readonly)NSMutableArray *bigCatVCs;
@property (nonatomic, retain)BookItemGridViewController *currBigCatVC;
@end

@implementation BookstoreViewController
@synthesize categories, categoriesCh, categoryDictionary;
@synthesize bigCatVCs, currBigCatVC;
@synthesize space;

#define CATEGORY_SIZE 11
- (NSArray *)categories
{
    return brain.categories;
}

- (NSArray *)categoriesCh
{
    if (!categoriesCh){
        NSMutableArray *arr = [NSMutableArray array];
        for (id name in self.categories) {
            [arr addObject:[self.categoryDictionary objectForKey:name]];
        }
        categoriesCh = [arr retain];
    }
    return categoriesCh;
}

- (NSDictionary *)categoryDictionary
{
    if (!categoryDictionary) {
        NSArray *ch = [NSArray arrayWithObjects:@"財經企管", @"新聞時事", @"運動競技", @"休閒生活", nil];
        NSArray *en = [NSArray arrayWithObjects:@"finance", @"news", @"sports", @"life", nil];
        categoryDictionary = [[NSDictionary alloc] initWithObjects:ch forKeys:en];
    }
    return categoryDictionary;
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
    [brain release];
    [categories release];
    [categoriesCh release];
    [categoryDictionary release];
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
    
    //generate data
    brain = [[BookstoreData alloc] init];
    
    //
    self.view.autoresizesSubviews = YES;
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
 
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    [self.currBigCatVC didRotateFromInterfaceOrientation:fromInterfaceOrientation];
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
    return [self.categoriesCh objectAtIndex:indexPath.row];
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
/*
- (BookItemGridViewController *)bigCatVCAtIndexPath:(NSIndexPath *)indexPath
{
    int index = indexPath.row;
    if ([self.bigCatVCs objectAtIndex:index] == [NSNull null]) {
        
        BookItemGridViewController *bigCatVC = [[BookItemGridViewController alloc] init];
        bigCatVC.bookFamilies = [brain bookFamiliesInCategory:[self.categories objectAtIndex:index]];
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
    self.currBigCatVC.view.frame = self.space.bounds;  
    [self.space addSubview:self.currBigCatVC.view];
    
}
*/

- (void)spinnerStart
{
    spinnerView.hidden = NO;
    [spinnerView startAnimating];
    loadingButton.title = @"Loading ..."; 
    [self.view setNeedsDisplay];
}

- (void)spinnerStop
{
    [spinnerView stopAnimating];
    spinnerView.hidden = YES;
    loadingButton.title = @"";
    [self.view setNeedsDisplay];
}

- (void)putBigCatVCAtIndexPath:(NSIndexPath *)indexPath
{
    static BOOL isFirstTime = YES;//because now only the first time connects to server; will change in the future
    int index = indexPath.row;
    if ([self.bigCatVCs objectAtIndex:index] == [NSNull null]) {
        // use thread b/c the product list has not been fetched
        if (isFirstTime) {
            [self spinnerStart];
            dispatch_queue_t downloadQueue = dispatch_queue_create("Koobe Product List Fetcher", NULL);
                dispatch_async(downloadQueue, ^{
                    NSArray *bookFamilies = [brain bookFamiliesInCategory:[self.categories objectAtIndex:index]];
                    dispatch_async(dispatch_get_main_queue(), ^{
                        BookItemGridViewController *bigCatVC = [[BookItemGridViewController alloc] init];
                        bigCatVC.bookFamilies = bookFamilies;
                        [self.bigCatVCs replaceObjectAtIndex:index withObject:bigCatVC];
                        [bigCatVC release];
                        self.currBigCatVC = [self.bigCatVCs objectAtIndex:index];
                        self.currBigCatVC.view.frame = self.space.bounds;  
                        [self.space addSubview:self.currBigCatVC.view];
                        [self spinnerStop];
                    });
                });
            dispatch_release(downloadQueue);
            isFirstTime = NO;
            return;
        }
        BookItemGridViewController *bigCatVC = [[BookItemGridViewController alloc] init];
        bigCatVC.bookFamilies = [brain bookFamiliesInCategory:[self.categories objectAtIndex:index]];
        [self.bigCatVCs replaceObjectAtIndex:index withObject:bigCatVC];
        [bigCatVC release];
        
    }
    
    self.currBigCatVC = [self.bigCatVCs objectAtIndex:index];
    self.currBigCatVC.view.frame = self.space.bounds;  
    [self.space addSubview:self.currBigCatVC.view];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    if (self.currBigCatVC) {
        [self.currBigCatVC.view removeFromSuperview];
    }
    [self putBigCatVCAtIndexPath:indexPath];
    
    // Pass the selected object to the new view controller.
    
}

@end
