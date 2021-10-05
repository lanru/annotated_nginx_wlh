// Copyright (c) 2015
// Author: Chrono Law
#ifndef _NDG_TEST_INIT_HPP
#define _NDG_TEST_INIT_HPP

#include "NdgTestConf.hpp"
#include "NdgTestHandler.hpp"

class NdgTestInit final
{
public:
    typedef NdgTestConf conf_type;
    typedef NdgTestHandler handler_type;
    typedef NdgTestInit this_type;
public:
    static ngx_command_t* cmds()
    {
        static ngx_command_t n[] =
        { //配置指令数组
            {
                ngx_string("ndg_test"),
                NgxTake(NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG, 1),//／指令的作用域和类型
                ngx_conf_set_flag_slot,//／解析函数指针
                NGX_HTTP_LOC_CONF_OFFSET,//／数据的存储位置
                offsetof(conf_type, enabled),
                0
            },

            ngx_null_command //数组的最后必须是 ngx null command ，起到哨兵的作用，相当于 Nginx使用它来标识命令数组的结束。
        };

        return n;
    }
public:
    static ngx_http_module_t* ctx()
    {
        static ngx_http_module_t c =
        {
            NGX_MODULE_NULL(1),

            &handler_type::init,

            NGX_MODULE_NULL(4),

            &conf_type::create,
            &conf_type::merge,
        };

        return &c;
    }
public:
    static const ngx_module_t& module() //模块定义
    {
        static ngx_module_t m =
        {
            NGX_MODULE_V1,

            ctx(),
            cmds(),

            NGX_HTTP_MODULE,
            NGX_MODULE_NULL(7),
            NGX_MODULE_V1_PADDING
        };

        return m;
    }
};

#endif  //_NDG_TEST_INIT_HPP

