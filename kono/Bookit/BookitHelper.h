//
//  BookitHelper.h
//  KoobeViewer
//
//  Created by Ivan on 2011/1/14.
//  Copyright 2011 Koobe Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "bookit.h"

@class DBHelper;
@protocol BookitHelperDelegate;

/**
 * @brief BookitHelper 的簡易說明...
 *
 * BookitHelper 的詳細說明...
 * ...
 */
@interface BookitHelper : NSObject {
	NSData *mData;	
    Bookit *mBookit;
	DBHelper *mDBHelper;
	NSString *mAdLink;
	NSInteger mChunkSize;
    id<BookitHelperDelegate> mDelegate;
}

@property (nonatomic, assign) NSData *mData;
@property (nonatomic, assign) Bookit *mBookit;
@property (nonatomic, assign) DBHelper *mDBHelper;
@property (nonatomic, assign) NSString *mAdLink;
@property (nonatomic, assign) NSInteger mChunkSize;
@property (nonatomic, assign) id<BookitHelperDelegate> delegate;

/**
 Get a signleton instance
 @returns a signleton instance
 */
+ (BookitHelper*) newInstance;

/**
 Synchronize book list with koobe system
 @param username input the string for username
 @param password input the string for password
 @param errMsg output the error message
 @returns a boolean value indicates the result
 */
- (BOOL) syncBookListByUsername:(NSString*)username withPassword:(NSString*)password forErrMsg:(NSString**)errMsg;

/**
 Get the drm dead line and write it into database 
 @param bookPath input the string for kep path
 */
- (void) getDrmDeadline:(NSString*)bookPath;

/**
 Get the rest of the reading time
 @param endDateStr input the string for end date
 @returns a boolean value indicates the result 
 */
- (double) calculateDrmDeadline:(NSString*)endDateStr;

/**
 Get DRM error message
 @param errorBookit input the error code for Bookit
 @param errorKoobeSystem input the error code for Koobe System
 @returns a string indicates the DRM error message;
 */
- (NSString*) showDRMfailureMsg:(int)errorBookit forKoobeSystemErrorCode:(int)errorKoobeSystem;

/**
 Is the flip order from right to left ?
 @param bookPath input the string for kep path
 @returns a boolean value indicates the result 
 */
- (BOOL) isLeftFlip:(NSString*)kepPath;

/**
 Get the book path from kep file.
 @param kepPath input the string for kep path
 @returns a string for book path
 */
- (NSString*) getBookPath:(NSString*)kepPath;

/**
 Get all thumbnail in kep file
 @param kepPath input the string for kep path
 @param numberOfPages the number of pages in kep
 @returns a array that keep all thumbmail images
 */
- (NSMutableArray*) getThumbnails:(NSString*)kepPath withNumberOfPages:(NSInteger)numberOfPages;
@end

@protocol BookitHelperDelegate <NSObject>
-(void)onSyncBookList:(NSDictionary*)info;
@end
