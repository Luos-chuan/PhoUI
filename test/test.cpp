#include <PWidget/PMainApplication/PMainApplication.hpp>

#include <iostream>

namespace {

bool expect(bool condition, const char* message) {
    if (condition) {
        return true;
    }

    std::cerr << "FAIL: " << message << '\n';
    return false;
}

} // namespace
class test : public ui::PMainApplication {
    public:
    test() {
        
    }
    ~test() {

    }
};
int main() {
    test* app = new test();
    app->run();
    return 1;
}