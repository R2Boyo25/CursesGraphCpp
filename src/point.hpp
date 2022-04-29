namespace point {
    class Point {
        public:
            float x;
            float y;
            int   color;
            bool  rem = false;

            Point(float x = 0, float y = 0, int color = 0);

            int operator > (Point o);
    };
}

