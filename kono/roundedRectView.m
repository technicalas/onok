//
//  roundedRectView.m
//  ApexLearnApp
//
//  Created by TsengE on 2010/8/18.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "RoundedRectView.h"

@implementation RoundedRectView
@synthesize edgeWidth;

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
		
    }
    return self;
}

- (void) drawRect: (CGRect)rect {
	
	CGContextRef context = UIGraphicsGetCurrentContext();
    // want to draw a frame
	double strokeWidth = self.edgeWidth;
	CGContextSetLineWidth(context,strokeWidth);
	
	CGRect rrect = [self bounds];
	
	// want to preset the border of the rect 
    CGFloat xoffset = 3.0;
    CGFloat yoffset = 3.0;
	
	rrect.size.width = rrect.size.width - 2*xoffset ;   
	rrect.size.height = rrect.size.height - 2*yoffset; 
	rrect.origin.x = rrect.origin.x + xoffset; 
	rrect.origin.y = rrect.origin.y + yoffset; 
	
	CGContextSetAllowsAntialiasing(context, true);
	CGContextSetStrokeColorWithColor(context, [UIColor colorWithRed:0.2 green:0.8 blue:0.2 alpha:1.0].CGColor);
	
	CGFloat radius = 3.0;
	
	CGFloat minx = CGRectGetMinX(rrect), midx = CGRectGetMidX(rrect), maxx = CGRectGetMaxX(rrect);
	CGFloat miny = CGRectGetMinY(rrect), midy = CGRectGetMidY(rrect), maxy = CGRectGetMaxY(rrect);
	
	CGContextMoveToPoint(context, minx, midy);
	CGContextAddArcToPoint(context, minx, miny, midx, miny, radius);
	CGContextAddArcToPoint(context, maxx, miny, maxx, midy, radius);
	CGContextAddArcToPoint(context, maxx, maxy, midx, maxy, radius);
	CGContextAddArcToPoint(context, minx, maxy, minx, midy, radius);
	CGContextClosePath(context);
	CGContextDrawPath(context, kCGPathStroke); 
	
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (void)dealloc {
    [super dealloc];
}


@end
