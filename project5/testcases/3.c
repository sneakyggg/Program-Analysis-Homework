double baz(double z) {
    double t = z * 3.14;    // DEAD 
    double x = z * 2;       // DEAD 
    double s = z * 2.0;     
    return s;
}