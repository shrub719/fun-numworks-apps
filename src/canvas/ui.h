enum cursorColor {
    BLACK,
    ORANGE,
    RED,
    GREEN,
    BLUE
};

class Cursor {
    public:
        Cursor();
        void move(int dx, int dy);
        cursorColor color;
    private:
        void update_covering();
        void draw(bool erase = false);
        int x;
        int y;
        int cLength = 13;
        int covering[13][3];
};

class Bar {
    public:
        Bar();
        void update_color(cursorColor newColor);
        void update_message(char text[]);
    private:
        cursorColor color;
};
