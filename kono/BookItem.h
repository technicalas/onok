//
//  BookItem.h
//  kono
//
//  Created by Sammy Long on 2011/6/17.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface BookItem : NSObject {
    NSString *productId;
    NSString *title;
}
@property (nonatomic, copy)NSString *productId;
@property (nonatomic, copy)NSString *title;
@end
