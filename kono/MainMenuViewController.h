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
}
@property (nonatomic, retain) BookstoreViewController *bookstorevc;
- (IBAction) bookstoreButtonPressed;
@end
