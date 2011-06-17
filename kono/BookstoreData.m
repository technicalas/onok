//
//  BookstoreData.m
//  kono
//
//  Created by Sammy Long on 2011/6/16.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import "BookstoreData.h"
#import "BookItem.h"
#import "KVConfig.h"
#import "TBXML.h"
 
@implementation BookstoreData
@synthesize categories;
@synthesize bookItemsWithBookFamily;

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

-(NSDictionary *)bookItemsWithBookFamily 
{
    if (!bookItemsWithBookFamily ) {
        NSString *merchantID = [NSString stringWithUTF8String:MERCHANT_ID];
        NSString *urlStr = [NSString stringWithFormat:@"%@/_data/IAP/%@?merchantId=%@", HOST, WEB_API_GET_PRODUCT_LIST, merchantID];
        NSString* escapedUrlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding];	
        NSURL *url = [NSURL URLWithString:escapedUrlStr];
        NSURLRequest *request = [NSURLRequest requestWithURL:url];
        NSData *responseData = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
        
        if (responseData ==nil) {
            return nil;
        }    
        NSMutableDictionary *productList = [NSMutableDictionary dictionary];
        TBXML *tbxml = [[TBXML tbxmlWithXMLData:responseData] retain];
        TBXMLElement *koobeDataEle = tbxml.rootXMLElement;
        TBXMLElement *productListEle = [TBXML childElementNamed:@"productList" parentElement:koobeDataEle];
            
        //subscriptionEle
        TBXMLElement *subscriptionEle = [TBXML childElementNamed:@"subscription" parentElement:productListEle]; 
        TBXMLElement *subscriptionItemEle = [TBXML childElementNamed:@"item" parentElement:subscriptionEle];
        while (subscriptionItemEle) {
            // Init subscription products
            TBXMLElement *productEle = [TBXML childElementNamed:@"product" parentElement:subscriptionItemEle];
            TBXMLElement *titleEle = [TBXML childElementNamed:@"title" parentElement:subscriptionItemEle];		
                //TBXMLElement *descriptionEle = [TBXML childElementNamed:@"description" parentElement:subscriptionItemEle];
                //TBXMLElement *priceEle = [TBXML childElementNamed:@"price" parentElement:subscriptionItemEle];
                
            BookItem *book = [[[BookItem alloc] init] autorelease];
            NSString *productId = [TBXML textForElement:productEle];
            book.productId = productId;
            book.title = [TBXML textForElement:titleEle];
                
            //parse productid and put it in its family tree
            NSArray *words = [productId componentsSeparatedByString:@"."];
            NSString *bookFamily =  [words objectAtIndex:3];
            //use bookFamily to find the object
            NSMutableArray *itemsInFamily = [productList objectForKey:bookFamily];
            if (itemsInFamily == nil) {
                NSMutableArray *items = [NSMutableArray arrayWithObject:book];
                [productList setObject:items forKey:bookFamily];
            } else {
                [itemsInFamily addObject:book];
            }
                
            subscriptionItemEle = [TBXML nextSiblingNamed:@"item" searchFromElement:subscriptionItemEle];
        }
        [tbxml release];
        bookItemsWithBookFamily = [productList retain];
        //NSLog(@"bookItemsWithBookFamily = %@", bookItemsWithBookFamily);
        [bookItemsWithBookFamily enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
            NSLog(@"key %@", key);
            for (BookItem* item in (NSArray *)obj) {
                NSLog(@"book productId = %@",item.productId);
                NSLog(@"book title = %@", item.title);
            }
        }];
    }
   
    return bookItemsWithBookFamily;
}

-(void)dealloc
{
    [databasePath release];
    [categories release];
    [super dealloc];
}
@end
