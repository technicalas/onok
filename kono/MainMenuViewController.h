//
//  MainMenuViewController.h
//  kono
//
//  Created by Sammy Long on 2011/6/8.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BookstoreViewController.h"

@interface MainMenuViewController : UIViewController {
    BookstoreViewController *bookstorevc;
    IBOutlet UIView *space;
}
@property (nonatomic, retain) BookstoreViewController *bookstorevc;
@property (nonatomic, retain) UIView *space;
- (IBAction) bookstoreButtonPressed;
@end
