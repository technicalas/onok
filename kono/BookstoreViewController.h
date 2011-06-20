//
//  BookstoreViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BookItemGridViewController.h"
#import "BookstoreData.h"
#import "BookSalePageViewController.h"

@interface BookstoreViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, PresentSaleViewDelegate>{
    IBOutlet UITableView *categoryTableView;
    IBOutlet UIView *space;
    NSArray *categories;
    NSArray *categoriesCh;
    NSMutableArray *bigCatVCs;
    BookItemGridViewController *currBigCatVC;
    
    BookstoreData *brain;
    NSDictionary *categoryDictionary;
}
@property (nonatomic, retain) UIView *space;
@end
