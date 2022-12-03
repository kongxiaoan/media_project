//
//  ffmpeg-01.c
//  media_project
//
//  Created by mtkj on 2022/12/3.
// 
//
//

#include "ffmpeg-01.h"

int ffmpeg_log() {
    //1. 头文件 libavutil/log.h
    //2. 设置日志级别
    av_log_set_level(AV_LOG_DEBUG);
    //3. 打印日志
    av_log(NULL, AV_LOG_INFO, "ffmpeg_config info = %s", avutil_configuration());
    return 0;
}

/**
 删除文件
 */
int file_delete() {
    av_log_set_level(AV_LOG_ERROR);
    int result;
    //最新版本中移除了此方法
//    result = avpriv_io_delete("./test/test.txt");
    if(result < 0) {
        av_log(NULL, AV_LOG_ERROR, "删除文件失败");
        return -1;
    }
    
    return 0;
}

/**
 重命名
 */
int file_rename() {
    return 0;
}

/**
 模拟"ls"命令行指令
 */
void order_test(void) {
    int result;
    AVIODirContext *ctx = NULL;
    AVIODirEntry *entry = NULL;
    av_log_set_level(AV_LOG_INFO);
    
    result = avio_open_dir(&ctx, "./",NULL);
    if(result < 0) {
        //av_err2str可以转换错误类型 ffmpeg默认实现的
        av_log(NULL, AV_LOG_ERROR, "打开目录失败 %s\n", av_err2str(result));
        return;
    }
    while (1) {
        result = avio_read_dir(ctx, &entry);
        if(result < 0) {
            //av_err2str可以转换错误类型 ffmpeg默认实现的
            av_log(NULL, AV_LOG_ERROR, "读取失败 %s\n", av_err2str(result));
            //不建议经常使用
            goto _fail;
        }
        //entry == null 证明最后一项处理完成
        if(!entry) {
            break;
        }
        av_log(NULL
            ,AV_LOG_INFO, "%12"PRId64" %s \n",
               entry ->size,
               entry->name);
        //释放entry
        avio_free_directory_entry(&entry);
    }
    
_fail:
    avio_close_dir(&ctx);
    
}

/**
 操作目录
 */
int dir_use() {
    //打开目录
//    avio_open_dir(<#AVIODirContext **s#>, <#const char *url#>, <#AVDictionary **options#>)
    //读取目录中的信息
//    avio_read_dir(<#AVIODirContext *s#>, <#AVIODirEntry **next#>)
    //释放
//    avio_close_dir(<#AVIODirContext **s#>)

//    AVIODirContext 操作目录的上下文
//   AVIODirEntry 目录项（属性 大小等）
    order_test();
    return 0;
}
