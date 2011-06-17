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

@interface BookItemGridViewController : AQGridViewController <AQGridViewDelegate, AQGridViewDataSource> {
    NSArray * _orderedImageNames;
    NSArray * _imageNames;
    NSArray *bookFamilies;
}
@property (nonatomic, retain)NSArray *bookFamilies;

@end
