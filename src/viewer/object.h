class Object {
    public:
        Object();
        void rotate(float (&matrix)[3][3]);
        void draw();
        void erase();
    private:
        float points[62][3];
};