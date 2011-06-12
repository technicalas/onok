//
//  BigCatViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/10.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BookItemGridViewController.h"

@interface CategoryPageController : UIViewController <UIScrollViewDelegate>{
    
    UIScrollView *scrollView;
    int kNumberOfPages;
    NSMutableArray *viewControllers;
}
@property (nonatomic, retain) UIScrollView *scrollView;
@property (nonatomic, retain) NSMutableArray *viewControllers;
// page control related
- (void)loadScrollViewWithPage:(int)page;
- (void)scrollViewDidScroll:(UIScrollView *)sender;

@end
