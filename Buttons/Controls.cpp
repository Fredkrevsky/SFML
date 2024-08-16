#pragma once
#include "controls.h"
#include <algorithm>

using std::max;

TLabel::TLabel() {
    visible = true;
    text.setString("");
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setFillColor(Color::Black);
    text.setPosition(0, 0);
}
void TLabel::setText(std::string txt) {
    text.setString(txt);
}
void TLabel::setPos(int x, int y) {
    text.setPosition(x, y);
}
void TLabel::draw(RenderWindow& win) {
    if (visible) {
        win.draw(text);
    }
}
void TLabel::setVisible(bool toSet) {
    visible = toSet;
}
void TLabel::setThickness(int thick) {
    text.setOutlineThickness(thick);
}
void TLabel::setFontSize(int fontSize) {
    text.setCharacterSize(fontSize);
}
void TLabel::setColor(Color color) {
    text.setFillColor(color);
}
void TLabel::setOutlineColor(Color color) {
    text.setOutlineColor(color);
}

TObject::TObject() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    background.setFillColor(Color(230, 230, 230));
    background.setPosition(0, 0);
    background.setSize(Vector2f(0, 0));
    background.setOutlineColor(Color(30, 30, 30));
    visible = true;
}
void TObject::setPos(int tx, int ty) {
    x = tx;
    y = ty;
    background.setPosition(Vector2f(x, y));
}
void TObject::setSize(int twidth, int theight) {
    width = twidth;
    height = theight;
    background.setSize(Vector2f(width, height));
}
void TObject::setColor(Color _color) {
    color = _color;
    background.setFillColor(_color);
}
void TObject::setThickness(int thickness) {
    background.setOutlineThickness(thickness);
}
void TObject::draw(RenderWindow& win) {
    if (visible) {
        win.draw(background);
    }
}
void TObject::setVisible(bool toSet) {
    visible = toSet;
}

bool TClickable::isPressed(Vector2f& pos) {
    pressPos = pos;
    return visible && (pos.x >= x) && (pos.x <= x + width) && (pos.y >= y) && (pos.y <= y + height);
}
TClickable::TClickable() : TObject() {}
void TClickable::onPress() {
    if (onPressFunc) onPress();
}
void TClickable::onRelease() {
    if (onReleaseFunc) onRelease();
}
void TClickable::setOnPress(std::function<void()> func) {
    onPressFunc = func;
}
void TClickable::setOnRelease(std::function<void()> func) {
    onReleaseFunc = func;
}

void TButton::normText() {
    text.setPosition(x + (width - len * fontSize / 2) / 2 + 4, y + (height - fontSize) / 2 - 4);
}
TButton::TButton() : TClickable() {
    len = 0;
    text.setPosition(0, 0);
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setFillColor(Color::Black);
}
void TButton::setText(std::string toSet) {
    text.setString(toSet);
    len = toSet.size();
    normText();
}
void TButton::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);
    normText();
}
void TButton::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);
    normText();
}
void TButton::draw(RenderWindow& win) {
    if (visible) {
        TObject::draw(win);
        win.draw(text);
    }
}
void TButton::onPress() {
    TClickable::onPress();
    int r{ color.r }, b{ color.b }, g{ color.g }, a{color.a};
    background.setFillColor(Color(max(0, r - blackout), max(0, g - blackout), max(0, b - blackout), a));
}
void TButton::onRelease() {
    background.setFillColor(color);
}

TChoice::TChoice() : TClickable() {
    background.setFillColor(Color::White);
    isSelected = false;
    setSize(20, 20);
    setThickness(2);
    in.setFillColor(Color(30, 30, 30));
}
void TChoice::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);
    in.setPosition(tx + width / 4, ty + height / 4);
}
void TChoice::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);
    in.setPosition(x + twidth / 4, y + theight / 4);
    in.setSize(Vector2f(twidth / 2, theight / 2));
}
void TChoice::draw(RenderWindow& win) {
    if (visible) {
        TObject::draw(win);
        if (isSelected) {
            win.draw(in);
        }
    }
}
void TChoice::setStatus(bool status) {
    isSelected = status;
}
bool TChoice::getStatus() {
    return isSelected;
}

TBar::TBar() : TObject() {
    value = 0.5;
    posX = width * value;

    first.setPosition(x, y);
    first.setSize(Vector2f(posX, height));
    first.setFillColor(Color::Green);

    second.setPosition(x + posX, y);
    second.setSize(Vector2f(height - posX, height));
    second.setFillColor(Color::White);

    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition(0, 0);
    text.setCharacterSize(fontSize);
    text.setString("");

}
void TBar::setFirstColor(Color color) {
    first.setFillColor(color);
}
void TBar::setSecondColor(Color color) {
    second.setFillColor(color);
}
void TBar::draw(RenderWindow& win) {
    if (visible) {
        TObject::draw(win);
        win.draw(first);
        win.draw(second);
        win.draw(text);
    }
}

inline void TProgressBar::setWidth() {
    posX = width * value;
}
inline void TProgressBar::setTextPosition() {
    text.setPosition(x + 4, y + (height - fontSize) / 2 - 3);
}
inline void TProgressBar::setString() {
    int toSet = std::round(abs(value) * 100);
    std::string result = std::to_string(toSet);
    result.push_back('%');
    text.setString(result);
}
TProgressBar::TProgressBar() : TBar() { }
void TProgressBar::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);

    first.setPosition(tx, ty);
    second.setPosition(tx + posX, ty);

    setTextPosition();
}
void TProgressBar::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);

    first.setSize(Vector2f(twidth, theight));

    second.setSize(Vector2f(width - posX, height));
    second.setPosition(x + posX, y);

    setTextPosition();
}
void TProgressBar::setValue(float toSet) {
    value = toSet;
    setWidth();
    setString();
    setTextPosition();
    first.setSize(Vector2f(posX, height));
    second.setPosition(x + posX, y);
    second.setSize(Vector2f(width - posX, height));
}

inline void TAssessBar::setHeight() {
    if (abs(value) < 0.2) {
        posX = height / 2;
    }
    else if (value > 5) {
        posX = height;
    }
    else if (value < -5) {
        posX = 0;
    }
    else {
        posX = height * (value + 5) / 10;
    }
    posX = height - posX;
    first.setSize(Vector2f(width, posX));
    second.setPosition(x, y + posX);
    second.setSize(Vector2f(width, height - posX));
}
inline void TAssessBar::setTextColor() {
    if (value < 0) {
        text.setFillColor(second.getFillColor());
    }
    else {
        text.setFillColor(first.getFillColor());
    }
}
inline void TAssessBar::setTextPosition() {
    if (value < 0) {
        text.setPosition(x + 8, y + 4);
    }
    else {
        text.setPosition(x + 8, y + height - fontSize - 4);
    }
}
inline void TAssessBar::setString() {
    float toSet = std::round(abs(value) * 100) / 100;
    std::string result = "";
    if (toSet > 0.15) {
        if (toSet > 99) {
            result = "win";
        }
        else {
            result = std::to_string(toSet);
            int dot = result.find('.');
            result = result.substr(0, dot + 2);
        }
    }
    text.setString(result);
}
TAssessBar::TAssessBar() : TBar() {
    isFlip = false;
    text.setCharacterSize(fontSize - 6);
    text.setOutlineThickness(1);
}
void TAssessBar::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);
    first.setPosition(tx, ty);
    second.setPosition(tx, ty + posX);
    setTextPosition();
}
void TAssessBar::setSize(int twidth, int theight) {
    TObject::setSize(twidth, theight);
    first.setSize(Vector2f(twidth, theight));
    second.setSize(Vector2f(width, height - posX));
    second.setPosition(x, y + posX);
    setTextPosition();
}
void TAssessBar::setValue(float toSet) {
    if (isFlip) {
        value = -toSet;
    }
    else {
        value = toSet;
    }
    setHeight();
    setString();
    setTextColor();
    setTextPosition();
}
void TAssessBar::flip() {
    isFlip = !isFlip;
    value = -value;
    setHeight();
    setTextPosition();
    Color temp;
    temp = first.getFillColor();
    first.setFillColor(second.getFillColor());
    second.setFillColor(temp);
}

TInput::TInput() : TObject() {
    text.setPosition(3, 3);
    text.setCharacterSize(fontSize);
    text.setFont(font);
    text.setFillColor(Color::Black);
    setColor(Color::White);
    text.setString("");

    limit = 15;
    isSelected = false;
}
bool TInput::checkchar(char toCheck) {
    return (toCheck >= '0') && (toCheck <= '9') || (toCheck >= 'a') && (toCheck <= 'z') || (toCheck >= 'A') && (toCheck <= 'Z') || (toCheck == '_');
}
void TInput::select(int posx, int posy) {
    if (posx >= x && posx <= x + width && posy >= y && posy <= y + height) isSelected = visible;
}
void TInput::deselect(int posx, int posy) {
    if (posx < x || posx > x + width || posy < y || posy > y + height) isSelected = false;
}
void TInput::onKeyPress(char inputChar) {

    if (isSelected) {
        std::string temp = text.getString();

        if (letters && inputChar >= 0 && inputChar <= 25) {
            if (temp.size() < limit) {
                temp.push_back('A' + inputChar);
            }
        }
        else if (numbers && inputChar >= 26 && inputChar <= 35) {
            if (temp.size() < limit) {
                temp.push_back('0' + inputChar - 26);
            }
        }
        else if (dot && inputChar == 50) {
            if (temp.size() < limit) {
                temp.push_back('.');
            }
        }
        else if (inputChar == 59 && !temp.empty()) {
            temp.pop_back();
        }
        text.setString(temp);

    }
}
void TInput::draw(RenderWindow& win) {
    if (visible) {
        TObject::draw(win);
        win.draw(text);
    }
}
void TInput::setPos(int x0, int y0) {
    TObject::setPos(x0, y0);
    text.setPosition(x0 + 3, y0 + (height - fontSize) / 2 - 4);
}
void TInput::setSize(int w, int h) {
    TObject::setSize(w, h);
}
void TInput::setLimit(int lim) {
    limit = lim;
}
std::string TInput::getText() {
    return text.getString();
}

TWait::TWait() {
    for (int i = 0; i < 6; ++i) {
        mas[i].setFillColor(Color::White);
        mas[i].setRadius(30);
        mas[i].setOutlineColor(Color::Black);
        mas[i].setOutlineThickness(3);
    }
    setPos();
}
void TWait::setNext() {
    mas[current].setFillColor(Color::White);
    current = (current + 1) % 6;
    mas[current].setFillColor(Color::Green);
}
void TWait::setPos(int tx, int ty) {
    x = tx;
    y = ty;
    setPos();
}
void TWait::setRadius(int tradius) {
    radius = tradius;
    setPos();
}
void TWait::setPos() {
    mas[0].setPosition(x + radius * s3 / 2, y);
    mas[1].setPosition(x + radius * s3, y + radius / 2);
    mas[2].setPosition(x + radius * s3, y + 3 * radius / 2);
    mas[3].setPosition(x + radius * s3 / 2, y + 2 * radius);
    mas[4].setPosition(x, y + 3 * radius / 2);
    mas[5].setPosition(x, y + radius / 2);
}
void TWait::draw(RenderWindow& win) {
    if (visible) {
        for (int i = 0; i < 6; ++i) {
            win.draw(mas[i]);
        }
    }
}
void TWait::setVisible(bool toSet) {
    visible = toSet;
}

void TClock::tictac() {
    while (gameIsGoing && value > 0) {
        sf::sleep(sf::milliseconds(1000));
        if (yourTurn) {
            value--;
            text.setString(getStringTime(value));
        }
    }
}
std::string TClock::getStringTime(int seconds) {
    return std::to_string(seconds / 60) + ":" + std::to_string(seconds % 60 / 10) + std::to_string(seconds % 10);
}
TClock::TClock() : TObject() {
    value = 0;
    setThickness(3);
    background.setFillColor(Color::White);
    text.setString(getStringTime(0));
    text.setFillColor(Color::Black);
    text.setCharacterSize(32);
    text.setFont(font);
    thread = new sf::Thread(&TClock::tictac, this);
    setSize(150, 50);
}
void TClock::update(int seconds) {
    value = seconds;
    text.setString(getStringTime(seconds));
}
void TClock::setPos(int tx, int ty) {
    TObject::setPos(tx, ty);
    text.setPosition(tx + 47, ty + 4);
}
void TClock::start() {
    gameIsGoing = true;
    yourTurn = true;
    thread->launch();
}
void TClock::pause() {
    background.setFillColor(Color(220, 220, 220));
    yourTurn = false;
}
void TClock::release() {
    background.setFillColor(Color::White);
    yourTurn = true;
}
void TClock::draw(RenderWindow& win) {
    TObject::draw(win);
    win.draw(text);
}
void TClock::stop() {
    gameIsGoing = false;
    thread->terminate();
}