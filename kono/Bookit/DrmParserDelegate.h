//
//  DrmParser.h
//  KoobeViewer
//
//  Created by Ivan on 2011/1/17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DrmParserDelegate : NSObject <NSXMLParserDelegate> {
	NSString *mContent;
}
@property (nonatomic, assign) NSString *mContent;
- (NSString*)getContent;
@end
