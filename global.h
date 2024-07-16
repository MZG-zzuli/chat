#ifndef GLOBAL_H
#define GLOBAL_H
#include<QWidget>
#include<QStyle>
#include<functional>
extern std::function<void(QWidget*)> repolish;
enum ReqId{
    ID_GET_VERIFY_CODE = 1001, //获取验证码
    ID_REG_USER = 1002, //注册用户
    ID_RESET_PWD = 1003, //重置密码
};
enum ClickLbState{
    Normal = 0,
    Selected = 1
};
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, //Json解析失败
    ERR_NETWORK = 2,        //网络错误
    VerifyExpired=1004,	// 验证码过期
    VerifyCodeErr=1005,	// 验证码错误
    UserExist=1006		// 用户已存在
};
enum Modules{
    REGISTERMOD = 0,        //注册模块
    RESETMOD = 1,           //重置密码模块
};
extern QString gate_url_prefix;

#endif // GLOBAL_H
