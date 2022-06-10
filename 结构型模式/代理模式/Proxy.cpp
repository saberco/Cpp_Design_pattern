//实例为采用代理模式在第三方视频库添加延迟初始化和缓存。
//程序库提供了视频下载类。但是该类的效率非常低。
//如果客户端程序多次请求同一视频，程序库会反复下载该视频，而不会将首次下载的文件缓存下来复用。

//代理类实现和原下载器相同的接口，并将所有工作委派给原下载器。
//不过，代理类会保存所有的文件下载记录，如果程序多次请求同一文件，它会返回缓存的文件。


#include <string>
#include <iostream>
#include <cstdio>


using namespace std;
//服务器接口，提供视频列表和获取视频信息
class ThirdPartyTVLib {
 public:
    virtual string listVideos() = 0;
    virtual string getVideoInfo(int id) = 0;
};

// 视频下载类
// 该类的方法可以向远程视频后端服务请求信息, 请求速度取决于用户和服务器的网络状况
// 如果同时发送大量请求, 即使所请求的信息一模一样, 程序的速度依然会变慢
class ThirdPartyTVClass : public ThirdPartyTVLib {
 public:
    virtual string listVideos() override {
        // 向远程视频后端服务发送一个API请求获取视频信息, 这里忽略实现
        return "video list";
    }

    virtual string getVideoInfo(int id) override {
        // 向远程视频后端服务发送一个API请求获取某个视频的元数据, 这里忽略实现
        return "video info";
    }
};


//代理类，将请求缓存并保存，接收到真实请求后才将其委派给服务对象
class CachedTVClass : public ThirdPartyTVLib {
public:
    explicit CachedTVClass(ThirdPartyTVLib* service): 
        m_service(service), m_need_reset(false), m_list_cache(""), m_video_cache(""){}

    void reset(){
        m_need_reset = true;
    }

    virtual string listVideos()override{
        if(m_list_cache == "" || m_need_reset){
            m_list_cache = m_service->listVideos();
        }
        return m_list_cache;
    }


    virtual string getVideoInfo(int id)override{
        if(m_video_cache == "" || m_need_reset){
            m_video_cache = m_service->getVideoInfo(id);
        }
        return m_video_cache;
    }
private:
    ThirdPartyTVLib* m_service;
    string m_list_cache;
    string m_video_cache;
    bool m_need_reset;
};


//客户端类
class TVManager{
public:
    explicit TVManager(ThirdPartyTVLib* s) : m_service(s){}
    //渲染视频页面
    void renderVideoPage(int id) {
        string video_info = m_service->getVideoInfo(id);
        // 渲染视频页面, 这里忽略实现
        printf("渲染视频页面: %s\n", video_info.c_str());
        return;
    }
    //渲染缩略图表
    void renderListPanel() {
        string videos = m_service->listVideos();
        // 渲染视频缩略图列表, 这里忽略实现
        printf("渲染视频缩略图列表: %s\n", videos.c_str());
        return;
    }

private:
    ThirdPartyTVLib* m_service;
};


int main() {
    ThirdPartyTVClass* aTVService = new ThirdPartyTVClass();
    CachedTVClass* aTVProxy = new CachedTVClass(aTVService);
    TVManager* manager = new TVManager(aTVProxy);

    manager->renderVideoPage(1);
    manager->renderListPanel();

    delete aTVService;
    delete aTVProxy;
    delete manager;
}