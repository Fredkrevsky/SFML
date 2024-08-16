#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

using namespace sf;
extern Font font;
const int fontSize = 24;

class TLabel {
    Text text;
    bool visible;
public:
    TLabel();
    void setText(std::string txt);
    void setPos(int x, int y);
    void draw(RenderWindow& win);
    void setVisible(bool toSet);
    void setThickness(int thick);
    void setFontSize(int fontSize);
    void setColor(Color color);
    void setOutlineColor(Color color);
};

class TObject
{
protected:
    Color color;
    RectangleShape background;
    int x, y, width, height;
    TObject();
    bool visible;
public:
    void setVisible(bool toSet);
    virtual ~TObject() {}
    virtual void setPos(int tx, int ty);
    virtual void setSize(int twidth, int theight);
    void setColor(Color color);
    void setThickness(int thickness);
    virtual void draw(RenderWindow& win);
};

class TClickable : public TObject {
protected:
    std::function<void()> onPressFunc;
    std::function<void()> onReleaseFunc;
    Vector2f pressPos;
public:
    bool isPressed(Vector2f& pos);
    virtual void onPress();
    virtual void onRelease();
    void setOnPress(std::function<void()> func);
    void setOnRelease(std::function<void()> func);
    TClickable();
};

class TButton : public TClickable {
    const int blackout = 100;
    Text text;
    int len;
    void normText();
public:
    TButton();
    void onPress() override;
    void onRelease() override;
    void setText(std::string toSet);
    void setPos(int tx, int ty) override;
    void setSize(int twidth, int theight);
    void draw(RenderWindow& win);
};

class TChoice : public TClickable {
    bool isSelected;
    RectangleShape in;
public:
    TChoice();
    void setPos(int tx, int ty) override;
    void setSize(int twidth, int theight) override;
    void draw(RenderWindow& win);
    void setStatus(bool status);
    bool getStatus();
};

class TBar : public TObject {
protected:
    RectangleShape first;
    float value;
    int posX;
    RectangleShape second;
    Text text;

    virtual void setValue(float toSet) = 0;
    TBar();
public:
    void setFirstColor(Color color);
    void setSecondColor(Color color);
    void draw(RenderWindow& win);
};

class TProgressBar : public TBar {
    inline void setWidth();
    inline void setTextPosition();
    inline void setString();
public:
    TProgressBar();
    void setPos(int tx, int ty) override;
    void setSize(int twidth, int theight) override;
    void setValue(float toSet);
};

class TAssessBar : public TBar {

    inline void setHeight();
    inline void setTextColor();
    inline void setTextPosition();
    inline void setString();
    bool isFlip;
public:
    TAssessBar();
    void setPos(int tx, int ty) override;
    void setSize(int twidth, int theight) override;
    void setValue(float toSet);
    void flip();
};

class TClock : public TObject {
    volatile bool gameIsGoing;
    volatile bool yourTurn;
    sf::Thread* thread;
    int value;
    Text text;
    std::string getStringTime(int seconds);
    void tictac();
public:
    TClock();
    void update(int seconds);
    void start();
    void pause();
    void draw(RenderWindow& win);
    void setPos(int tx, int ty) override;
    void release();
    void stop();
};

class TInput : public TObject {
    bool isSelected;
    Text text;
    int limit;
    bool checkchar(char toCheck);
public:
    bool letters = false;
    bool dot = false;
    bool numbers = false;
    TInput();
    void onKeyPress(char pressed);
    void draw(RenderWindow& win) override;
    void setPos(int x0, int y0) override;
    void setSize(int w, int h) override;
    void select(int posx, int posy);
    void deselect(int posx, int posy);
    void setLimit(int lim);
    std::string getText();
};

class TWait {
    const float s3 = 1.73205;

    CircleShape mas[6];
    int current = 0;
    int radius = 100;
    int x = 0, y = 0;
    bool visible = true;

    void setPos();
public:
    TWait();
    void setNext();
    void setPos(int tx, int ty);
    void setRadius(int tradius);
    void setVisible(bool toSet);
    void draw(RenderWindow& win);
};
