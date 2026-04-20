#include <memory>
#include <iostream>

// singleton example of shared_from_this

class Widget
{
    struct Private { explicit Private() = default; };
public:
    Widget(Private p) {};

    static bool IsKeyPressed(int keycode);

    static std::shared_ptr<Widget> Create()
    {
        if (auto instance = s_widget) {
            return instance;
        } else {
            instance = std::make_shared<Widget>(Private());
            s_widget = instance;
            return instance;
        }
    }

    std::shared_ptr<Widget> GetWidget()
    {
        return s_widget;
    }

private:
    static std::shared_ptr<Widget> s_widget;
};

std::shared_ptr<Widget> Widget::s_widget;

class Tool : public Widget
{

};


int main()
{
    auto w1 = Widget::Create();
    std::cout << "w1 refs: " << w1.use_count() << ", address: " << w1.get() << std::endl;
    auto w2 = Widget::Create();
    std::cout << "w1 refs: " << w1.use_count() << ", address: " << w1.get() << std::endl;
    std::cout << "w2 refs: " << w2.use_count() << ", address: " << w2.get() << std::endl;
    auto w3 = w1->Create();
    std::cout << "w1 refs: " << w1.use_count() << ", address: " << w1.get() << std::endl;
    std::cout << "w2 refs: " << w2.use_count() << ", address: " << w2.get() << std::endl;
    std::cout << "w3 refs: " << w3.use_count() << ", address: " << w3.get() << std::endl;

    return 0;
}