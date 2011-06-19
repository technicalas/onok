//
//  BookSalePageViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/19.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BookFamily.h"

@interface BookSalePageViewController : UIViewController {
    BookFamily *book;
    IBOutlet UIImageView *imageView;
    IBOutlet UINavigationItem *nav;
}
@property (nonatomic, retain)BookFamily *book;
@property (nonatomic, retain)UIImageView *imageView;
@end
