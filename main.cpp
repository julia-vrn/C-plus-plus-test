#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>


using namespace std;

struct Point {
    float x;
    float y;
};


float readFile(QString targetFile, Point p, Point t, float l, float h);
void printPoint (Point a);
void writeFile (Point a);


int main()
{

    QString targetFile = "PointsInBox.txt";
    QFile resFile ("pointsInside.txt");
    resFile.remove();
    Point P;
    Point T;
    float len;
    float hg;

    readFile(targetFile, P, T, len, hg);
    return 0;
}

float readFile(QString targetFile, Point p, Point t, float len, float hg){
    QString message;
    QFile file(targetFile);
    if (!file.exists()){
        message = "Can't find file %1 to read\n";
        message = message.arg(targetFile);
        qDebug() << message;
        return -1;
    }

    if(!file.open(QFile::ReadOnly | QFile::Text))  {
        message = "Can't open the file %1 for reading\n";
        message = message.arg(targetFile);
        qDebug() << message;
        return -1;
    }
    char buf[1024];
    int readCount;
    QString qsBuf;
    QStringList FirstLine;
    QStringList param;
    QString part1;
    QString part2;
    QString part3;
    readCount = file.readLine(buf, sizeof(buf));
    buf[readCount-1] = 0;
    qsBuf = buf;
    FirstLine = qsBuf.split(' ');
    part1 = FirstLine.at(0);
    part2 = FirstLine.at(1);
    part3 = FirstLine.at(2);
    int i = 0;
    len = part2.toFloat();
    cout << "length: " << len<<endl;
    hg = part3.toFloat();
    cout << "height: " << hg << endl;
    param = part1.split(';');
    p.x = param.at(0).toFloat();
    p.y = param.at(1).toFloat();
    cout << "P.x: " << p.x<< endl;
    cout << "P.y: " << p.y<< endl;
    Point A;
    A.x = p.x - len/2;
    A.y = p.y - hg/2;
    printPoint(A);
    Point B;
    B.x = p.x - len/2;
    B.y = p.y + hg/2;
    printPoint(B);
    Point D;
    D.x = p.x + len/2;
    D.y = p.y - hg/2;
    printPoint(D);

    QStringList CheckLine;

    while (!file.atEnd()){
        readCount = file.readLine(buf, sizeof(buf));
        buf[readCount-1] = 0;
        qsBuf = buf;
        CheckLine = qsBuf.split(';');
        t.x = CheckLine.at(0).toFloat();
        t.y = CheckLine.at(1).toFloat();
        /*cout << "Test point x: "<<t.x<<endl;
        cout << "Test point y: "<<t.y<<endl;*/
        if(t.x >=A.x&&t.x<=D.x){
            printPoint(t);
            cout << "The point is inside the figure on x axis." << endl;
            if(t.y>=A.y&&t.y<=B.y){
                printPoint(t);
                cout << "The point is inside the figure on y axis." << endl;
                writeFile(t);
            }
        } else {
            printPoint(t);
            cout <<"The point is OUTSIDE the figure."<<endl;
        }

    }
}


void printPoint (Point a){
    cout << "Point: " << a.x<< ";"<<a.y<<endl;
}

void writeFile (Point a){
    QFile resFile ("pointsInside.txt");
    if (resFile.open(QFile::WriteOnly |QFile::Append )){
        QTextStream out(&resFile);
        out<<"Points coordinates\r\n";
        out << "Point with coordinates " << a.x << ";" << a.y<< " is inside the figure.";
        out<<"\r\n";
    }}

