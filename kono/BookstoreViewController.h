//
//  BookstoreViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BigCatViewController.h"
#import "CategoryPageController.h"
 
@interface BookstoreViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>{
    IBOutlet UITableView *categoryTableView;
    NSArray *categories;
    NSMutableArray *bigCatVCs;
    CategoryPageController *currBigCatVC;// to be replaced
    
}

@end
