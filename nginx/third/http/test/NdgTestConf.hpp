// Copyright (c) 2015
// Author: Chrono Law
#ifndef _NDG_TEST_CONF_HPP
#define _NDG_TEST_CONF_HPP

#include "NgxAll.hpp"

class NdgTestConf final
{
public:
    typedef NdgTestConf this_type; //自身类型定义
public:
    NdgTestConf() = default;
    ~NdgTestConf() = default;
public:
    ngx_flag_t enabled = NgxUnsetValue::get(); //标志变量 构造时初始化
public:
    static void* create(ngx_conf_t* cf) //创建配置数据结构
    {
        return NgxPool(cf).alloc<this_type>();//／由内存池分配内存，构造对象
    }

    static char* merge(ngx_conf_t *cf, void *parent, void *child)
    { //当“ndg_test”指令出现在 http 块或者 server 块中时Nginx 会调用 merge （） 函数，合井两个配置结构数组里的值
        boost::ignore_unused(cf);

        auto prev = reinterpret_cast<this_type*>(parent);
        auto conf = reinterpret_cast<this_type*>(child);

        NgxValue::merge(conf->enabled, prev->enabled, 0);

        return NGX_CONF_OK;
    }
};

NGX_MOD_INSTANCE(NdgTestModule, ndg_test_module, NdgTestConf) //模块单件定义

#endif  //_NDG_TEST_CONF_HPP
