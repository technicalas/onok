//
//  BookSalePageViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/19.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BookFamily.h"

@protocol PresentSaleViewDelegate;

@interface BookSalePageViewController : UIViewController {
    
    id <PresentSaleViewDelegate> delegate;
    BookFamily *book;
    IBOutlet UIImageView *imageView;
    IBOutlet UINavigationItem *nav;
}
@property (nonatomic, assign)id <PresentSaleViewDelegate> delegate;
@property (nonatomic, retain)BookFamily *book;
@property (nonatomic, retain)UIImageView *imageView;

-(IBAction)backButtonPressed;
@end

@protocol PresentSaleViewDelegate <NSObject>
-(void)salePageViewControllerDidFinished:(BookSalePageViewController *)bookSalePageVC;
@end