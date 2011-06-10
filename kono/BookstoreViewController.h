//
//  BookstoreViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface BookstoreViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>{
    IBOutlet UITableView *categoryTableView;
    NSArray *categories;
}

@end
