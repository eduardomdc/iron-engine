#ifndef event_manager_hpp
#define event_manager_hpp

#include <functional>
#include <vector>

class EventManager {
public:
    using resize_callback = std::function<void(int width, int height)>;
    using mouse_move_callback = std::function<void(double x, double y)>;

    void register_resize_callback(const resize_callback& callback){
        resize_callbacks.push_back(callback);
    }
    void register_mouse_move_callback(const mouse_move_callback& callback){
        mouse_move_callbacks.push_back(callback);
    }

    void trigger_resize(int width, int height){
        for (auto& callback : resize_callbacks)
            callback(width,height);
    }
    void trigger_mouse_move(double x, double y){
        for (auto& callback : mouse_move_callbacks)
            callback(x,y);
    }
private:
    std::vector<resize_callback> resize_callbacks;
    std::vector<mouse_move_callback> mouse_move_callbacks;
};

#endif
