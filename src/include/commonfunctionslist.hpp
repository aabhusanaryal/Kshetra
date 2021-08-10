// Demo/ Standard Functions
double std1X(double x,double y){
    return -y;
}
double std1Y(double x,double y){
    return x;
}

double std2X(double x,double y){
    float r = sqrt(pow(x,2) + pow(y,2));
    float phi;
    if(x>=0 && y>=0) //First quad
        phi = atan(y/x);
    else if(x<0 && y>=0) //Second quad
        phi = 3.1415+atan(y/x);
    else if(x<0 && y<0) //Third quad
        phi = 3.1415 + atan(y/x);
    else if(x>=0 && y<0) //Fourth quad
        phi = atan(y/x);
    return (1/r)*cos(phi);
}
double std2Y(double x,double y){
    float r = sqrt(pow(x,2) + pow(y,2));
    float phi;
    if(x>=0 && y>=0) //First quad
        phi = atan(y/x);
    else if(x<0 && y>=0) //Second quad
        phi = 3.1415+atan(y/x);
    else if(x<0 && y<0) //Third quad
        phi = 3.1415 + atan(y/x);
    else if(x>=0 && y<0) //Fourth quad
        phi = atan(y/x);
    return (1/r)*sin(phi);
}

double std3X(double x,double y){
    return -x;
}
double std3Y(double x,double y){
    return -y;
}

double std4X(double x,double y){
    return x;
}
double std4Y(double x,double y){
    return x;
}