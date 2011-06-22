//
//  BookItemGridViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/9.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridViewController.h"
#import "BookFamily.h"
#import "BookSalePageViewController.h"

@interface BookItemGridViewController : AQGridViewController <AQGridViewDelegate, AQGridViewDataSource, PresentSaleViewDelegate> {
    
    BookSalePageViewController *bookSalePageVC;
    NSArray * _imageNames;
    NSArray *bookFamilies;
}
@property (nonatomic, retain)NSArray *bookFamilies;
@property (nonatomic, retain)BookSalePageViewController *bookSalePageVC;
-(void)salePageViewControllerDidFinished:(BookSalePageViewController *)bookSalePageVC;
@end