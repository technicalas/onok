//
//  BookFamily.h
//  kono
//
//  Created by Sammy Long on 2011/6/17.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface BookFamily : NSObject {
    NSString *name;
    NSArray *items;
}
@property (nonatomic, copy)NSString *name;
@property (nonatomic, retain)NSArray *items;
@end
