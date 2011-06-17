//
//  BookstoreData.m
//  kono
//
//  Created by Sammy Long on 2011/6/16.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "BookstoreData.h"
 
@implementation BookstoreData
@synthesize categories;

-(void) checkAndCreateDatabase{
	// Check if the SQL database has already been saved to the users phone, if not then copy it over
	BOOL success;
    
	// Create a FileManager object, we will use this to check the status
	// of the database and to copy it over if required
	NSFileManager *fileManager = [NSFileManager defaultManager];
    
	// Check if the database has already been created in the users filesystem
	success = [fileManager fileExistsAtPath:databasePath];
    
	// If the database already exists then return without doing anything
	if(success) return;
    
	// If not then proceed to copy the database from the application to the users filesystem
    
	// Get the path to the database in the application package
	NSString *databasePathFromApp = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:databaseFileName];
    
	// Copy the database from the package to the users filesystem
	[fileManager copyItemAtPath:databasePathFromApp toPath:databasePath error:nil];
    
	[fileManager release];
}


-(void)openDatabase
{
    databaseFileName = @"BookCategory.sql";
    // Get the path to the documents directory and append the databaseName
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDir = [documentPaths objectAtIndex:0];
	databasePath = [[documentsDir stringByAppendingPathComponent:databaseFileName] retain];
    
    [self checkAndCreateDatabase];
}


-(NSArray *)getCategoriesFromDB
{
    NSMutableArray *ret = [NSMutableArray array];
    if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
		const char *sqlStatement = "select distinct category from categories";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
				// Read the data from the result row
				NSString *category = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 0)];
                
				// Add the animal object to the animals Array
				[ret addObject:category];
            }
            // Release the compiled statement from memory
            sqlite3_finalize(compiledStatement);
            
        }
        sqlite3_close(database);
        return ret;
    }
    return nil;
}

-(NSArray *)categories
{
    if (!categories) {
        [self openDatabase];
        categories = [[self getCategoriesFromDB] retain];
    }
    return categories;
}

-(void)dealloc
{
    [databasePath release];
    [categories release];
    [super dealloc];
}
@end
