//
//  roundedRectView.h
//  ApexLearnApp
//
//  Created by TsengE on 2010/8/18.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface RoundedRectView : UIView {
    CGFloat edgeWidth;
}
@property CGFloat edgeWidth;
- (void)drawRect:(CGRect)rect;
 
@end
