#include <mutex>
#include <optional>

template<typename C, class Global = std::integral_constant<bool, true>, typename... Args>
class Singleton {
public:
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator=(Singleton&&) = delete;
	
  static C* GetInstance(Args... args)
  { 
    if(Global()) {
        static std::optional<C*> s_instance;
        static std::once_flag s_flag;
        std::call_once(s_flag, [args...]() { s_instance.emplace(new C(args...)); });
        return *s_instance;
    } else {
        thread_local static std::optional<C*> s_instance;
        thread_local static std::once_flag s_flag;
        std::call_once(s_flag, [args...]() { s_instance.emplace(new C(args...)); });
        return *s_instance;
    }
  }
protected:
  Singleton() = default;
};
