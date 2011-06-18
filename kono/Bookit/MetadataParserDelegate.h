//
//  MetadataParserDelegate.h
//  KoobeViewer
//
//  Created by Ivan on 2011/1/17.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MetadataParserDelegate : NSObject <NSXMLParserDelegate> {
	NSMutableString *mContent;
	BOOL isAppendString;
}
@property (nonatomic, assign) NSMutableString *mContent;
- (NSString*)getContent;

@end
