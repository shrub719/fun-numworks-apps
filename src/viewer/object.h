class Object {
    public:
        Object();
        void rotate(float (&matrix)[3][3]);
        void toCoords();
        void draw();
        void erase();
    private:
        float points[62][3];
        int coords[62][3];
        int scale;
        int size;
};