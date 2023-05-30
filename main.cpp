#include <string>
#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>

const char* labels[9]
{
    "3600 mA",
    "3000 mA",
    "2500 mA",
    "2000 mA",
    "1500 mA",
    "1200 mA",
    " 900 mA",
    " 700 mA",
    " 500 mA",
};

// Level can be between 0-8

auto getLevel() -> unsigned
{
    auto ret = std::system("su -c 'exit $(cat /sys/devices/platform/soc/c440000.qcom,spmi/spmi-0/spmi0-00/c440000.qcom,spmi:qcom,pm6150@0:qcom,qpnp-smb5/power_supply/battery/charge_control_limit)'");
    return WEXITSTATUS(ret); //above command returns level via exit code
}

void setLevel(unsigned x)
{
    char cmd[] = "su -c 'echo x > /sys/devices/platform/soc/c440000.qcom,spmi/spmi-0/spmi0-00/c440000.qcom,spmi:qcom,pm6150@0:qcom,qpnp-smb5/power_supply/battery/charge_control_limit'";
    cmd[12] = '0' + x; //manual formatting ;)
    std::system(cmd);
}

int main()
{    
    sf::Font font;
    font.loadFromFile("resources/WhiteRabbit.otf");
    
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Hanoip Charge Control");
    window.setFramerateLimit(10);
    
    auto title_text = sf::Text("Current Limit :", font, 100);
    auto textRect = title_text.getLocalBounds();
    title_text.setOrigin(textRect.width/2, textRect.height);
    title_text.setPosition(sf::Vector2f(window.getSize().x / 2, 200));
    title_text.setFillColor(sf::Color::Green);
    
    auto credits_text = sf::Text(" Made for hanoip by 0xB00B, ROOT Required, Hanoip Charge Control v2.0", font, 28);
    
    std::vector<sf::Text> texts;
    std::vector<sf::RectangleShape> boxes;
    
    // creating the buttons
    for (int i{0} ; i < 9 ; ++i)
    {
        auto text = sf::Text(labels[i], font, 64);
        auto textRect = text.getLocalBounds();
        text.setOrigin(textRect.width/2, textRect.height);
        text.setPosition(sf::Vector2f(window.getSize().x / 2, 250 + window.getSize().y/12.f*(i+1)));
        texts.push_back(text);
        
        auto box = sf::RectangleShape({600.f, 100.f});
        box.setFillColor(sf::Color::Blue);
        auto boxRect = box.getLocalBounds();
        box.setOrigin(boxRect.width/2, boxRect.height/2);
        box.setPosition(sf::Vector2f(window.getSize().x / 2, 250 + window.getSize().y/12.f*(i+1)));
        boxes.push_back(box);
    }
    
    // load current setting
    boxes[getLevel()].setFillColor(sf::Color::Red);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ;;;; if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View{{0,0, event.size.width, event.size.height}});
            }
            else if (event.type == sf::Event::LostFocus)
            {
                window.setActive(false); // fixes black screen issue on app switching
            }
            else if (event.type == sf::Event::TouchBegan)
            {
                for (int i{0} ; i < 9 ; ++i)
                {
                    if (boxes[i].getGlobalBounds().contains({event.touch.x, event.touch.y}))
                    {
                        setLevel(i);
                        
                        // set last clicked button to red
                        boxes[i].setFillColor(sf::Color::Red);
                        
                        // reset all other buttons to blue
                        for (int j{0} ; j < 9 ; ++j) if (i != j)
                            boxes[j].setFillColor(sf::Color::Blue);
                        
                        break; // we don't want multitouch
                    }
                }
            }
        }
        
        window.clear();
        window.draw(title_text);
        
        for (int i{0} ; i < 9 ; ++i)
        {
            window.draw(boxes[i]);
            window.draw(texts[i]);
        }
        
        window.draw(credits_text);
        window.display();
    }
}