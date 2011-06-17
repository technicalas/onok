//
//  BookstoreData.h
//  kono
//
//  Created by Sammy Long on 2011/6/16.
//  Copyright 2011年 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sqlite3.h>

@interface BookstoreData : NSObject {
    NSString *databaseFileName;
    NSString *databasePath;
    NSArray *categories;
    NSDictionary *productsDictionary;
    sqlite3 *database;
}
@property (nonatomic, retain) NSArray *categories;
@property (nonatomic, readonly)NSDictionary *productsDictionary;
-(NSArray *)bookFamiliesInCategory:(NSString *)category;
@end
