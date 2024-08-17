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
    ID_LOGIN_USER=1004, //登录
    ID_CHAT_LOGIN=1005, //登陆聊天服务器
    ID_CHAT_LOGIN_RSP= 1006, //登陆聊天服务器回包
    ID_SEARCH_USER_REQ = 1007, //用户搜索请求
    ID_SEARCH_USER_RSP = 1008, //搜索用户回包
    ID_ADD_FRIEND_REQ = 1009,  //添加好友申请
    ID_ADD_FRIEND_RSP = 1010, //申请添加好友回复
    ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //通知用户添加好友申请
    ID_AUTH_FRIEND_REQ = 1013,  //认证好友请求
    ID_AUTH_FRIEND_RSP = 1014,  //认证好友回复
    ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //通知用户认证好友申请
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
    LOGINMOD=2,             //登录
};
struct ServerInfo{
    QString Host;
    QString Port;
    QString Token;
    int Uid;
};
extern QString gate_url_prefix;

#endif // GLOBAL_H
