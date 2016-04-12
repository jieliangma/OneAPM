//
//  OneAPMActionAnalytics.h
//  OneAPM
//
//  Created by yuxr on 16/3/17.
//  Copyright © 2016年 OneAPM. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OneAPMActionAnalytics : NSObject

# pragma mark basics

/**
 *  启动用户行为分析功能
 */
+ (void)startActionAnalytics;

/**
 *  设置app的版本号，默认取CFBundleShortVersionString，可以设置其他自定义版本号
 */
+ (void)setAppVersion:(NSString *)appVersion;
/**
 *  当App进入活跃状态时，是否从OneAPM获取新的可视化埋点配置
 */
+ (void)setCheckForEventBindingsOnActive:(BOOL)enable;

/**
 *  当App进入后台时，是否将数据发送到OneAPM
 */
+ (void)setFlushBeforeEnterBackground:(BOOL)enable;

/**
 * @property
 *
 * @abstract
 * 两次数据发送的最小时间间隔，单位毫秒
 *
 * @discussion
 * 默认值为60 * 1000毫秒，DEBUG模式下为1 * 1000毫秒
 * 在每次调用track、signUp以及profileSet等接口的时候，都会检查如下条件，以判断是否向服务器上传数据:
 * 1. 当前是否是WIFI/3G/4G网络条件
 * 2. 与上次发送的时间间隔是否大于flushInterval
 * 如果满足这两个条件，则向服务器发送一次数据；如果不满足，则把数据加入到队列中，等待下次检查时把整个队列的内容一并发送。
 * 需要注意的是，为了避免占用过多存储，队列最多只缓存10000条数据。
 */
+ (void)setFlushInterval:(UInt64)msecond;



# pragma mark track event

/**
 * @abstract
 * 设置当前用户的distinctId
 *
 * @discussion
 * 一般情况下，如果是一个注册用户，则应该使用注册系统内的user_id
 * 如果是个未注册用户，则可以选择一个不会重复的匿名ID，如设备ID等
 * 如果客户没有设置indentify，则使用SDK自动生成的匿名ID
 * SDK会自动将设置的distinctId保存到文件中，下次启动时会从中读取
 *
 * @param distinctId 当前用户的distinctId
 */
+ (void)identify:(NSString *)distinctId;

/**
 * 提供一个接口，用来在用户注册的时候，用注册ID来替换用户以前的匿名ID
 *
 * @param newDistinctId    用户完成注册后生成的注册ID
 * @param propertieDict    event的属性
 */
+ (void)signUp:(NSString *)newDistinctId withProperties:(NSDictionary *)propertyDict;

+ (void)signUp:(NSString *)newDistinctId;

/**
 * 事件追踪相关方法
 *
 * @param event        要追踪的事件名
 * @param propertyDict 事件相关属性
 */
+ (void)track:(NSString *)event withProperties:(NSDictionary *)propertyDict;

+ (void)track:(NSString *)event;

/**
 * @abstract
 * 用来设置每个事件都带有的一些公共属性
 *
 * @discussion
 * 当track的Properties，superProperties和SDK自动生成的automaticProperties有相同的key时，遵循如下的优先级：
 *    track.properties > superProperties > automaticProperties
 * 另外，当这个接口被多次调用时，是用新传入的数据去merge先前的数据，并在必要时进行merger
 * 例如，在调用接口前，dict是@{@"a":1, @"b": "bbb"}，传入的dict是@{@"b": 123, @"c": @"asd"}，则merge后的结果是
 * @{"a":1, @"b": 123, @"c": @"asd"}，同时，SDK会自动将superProperties保存到文件中，下次启动时也会从中读取
 *
 * @param propertyDict 传入merge到公共属性的dict
 */
+ (void)registerSuperProperties:(NSDictionary *)propertyDict;

/**
 * 从superProperty中删除某个property
 *
 * @param property 待删除的property的名称
 */
+ (void)unregisterSuperProperty:(NSString *)property;

/**
 * 删除当前所有的superProperty
 */
+ (void)clearSuperProperties;

/**
 *  获得当前所有的superProperty
 */
+ (NSDictionary *)currentSuperProperties;


#pragma mark profile
/**
 * @abstract
 * 直接设置用户的一个或者几个Profiles
 *
 * @discussion
 * 这些Profile的内容用一个NSDictionary来存储
 * 其中的key是Profile的名称，必须是NSString
 * Value则是Profile的内容，只支持 NSString,NSNumber,NSDate这些类型
 *
 * 特别的，NSSet类型的value中目前只支持其中的元素是NSString
 * 如果某个Profile之前已经存在了，则这次会被覆盖掉；不存在，则会创建
 *
 * @param profileDict 要替换的那些Profile的内容
 */
+ (void)set:(NSDictionary *)profileDict;

/**
 * @abstract
 * 首次设置用户的一个或者几个Profiles
 *
 * @discussion
 * 与set接口不同的是，如果该用户的某个Profile之前已经存在了，会被忽略；不存在，则会创建
 *
 * @param profileDict 要替换的那些Profile的内容
 */
+ (void)setOnce:(NSDictionary *)profileDict;

/**
 * @abstract
 * 设置用户的单个Profile的内容
 *
 * @discussion
 * 如果这个Profile之前已经存在了，则这次会被覆盖掉；不存在，则会创建
 *
 * @param profile Profile的名称
 * @param content Profile的内容
 */
+ (void)set:(NSString *) profile to:(id)content;

/**
 * @abstract
 * 首次设置用户的单个Profile的内容
 *
 * @discussion
 * 与set类接口不同的是，如果这个Profile之前已经存在了，则这次会被忽略；不存在，则会创建
 *
 * @param profile Profile的名称
 * @param content Profile的内容
 */
+ (void)setOnce:(NSString *) profile to:(id)content;


/**
 * @abstract
 * 删除某个Profile的全部内容
 *
 * @discussion
 * 如果这个Profile之前不存在，则直接忽略
 *
 * @param profile Profile的名称
 */
+ (void)unset:(NSString *) profile;

/**
 * @abstract
 * 给一个数值类型的Profile增加一个数值
 *
 * @discussion
 * 只能对NSNumber类型的Profile调用这个接口，否则会被忽略
 * 如果这个Profile之前不存在，则初始值当做0来处理
 *
 * @param profile  待增加数值的Profile的名称
 * @param amount   要增加的数值
 */
+ (void)increment:(NSString *)profile by:(NSNumber *)amount;

/**
 * @abstract
 * 给多个数值类型的Profile增加数值
 *
 * @discussion
 * profileDict中，key是NSString，value是NSNumber
 * 其它与-(void)increment:by:相同
 *
 * @param profileDict 多个
 */
+ (void)increment:(NSDictionary *)profileDict;

/**
 * @abstract
 * 向一个NSSet类型的value添加一些值
 *
 * @discussion
 * 如前面所述，这个NSSet的元素必须是NSString，否则，会忽略
 * 同时，如果要append的Profile之前不存在，会初始化一个空的NSSet
 *
 * @param profile
 */
+ (void)append:(NSString *)profile by:(NSSet *)content;

/**
 * 删除当前这个用户的所有记录
 */
+ (void)deleteUser;

@end
