#include <Fl/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <Fl/Fl_Box.H>
#include <chrono>
#include <string>
#include <fstream>
//#include "Tail.cxx"

bool didstart = 0,ended = 0;

Fl_Double_Window *w;
Fl_Box *SecMil;
Fl_Box *Mins;
Fl_Box *Separator;

void rtawindow() {
    w = new Fl_Double_Window(155,175);
    w->box(FL_BORDER_BOX);
    w->color(FL_FOREGROUND_COLOR);
    w->labelcolor(FL_BACKGROUND2_COLOR);
    
    Mins = new Fl_Box(10, 110, 40, 30, "");
    //Mins->labelfont(4);
    Mins->labelsize(32);
    Mins->labelcolor((Fl_Color)2);
    Mins->align(Fl_Align(FL_ALIGN_RIGHT+FL_ALIGN_INSIDE));

    SecMil = new Fl_Box(55, 110, 100, 30, "");
    //SecMil->labelfont(4);
    SecMil->labelsize(32);
    SecMil->labelcolor((Fl_Color)2);
    SecMil->align(Fl_Align(FL_ALIGN_RIGHT+FL_ALIGN_INSIDE));

    Separator = new Fl_Box(38, 108, 20, 30, ":");
    Separator->labelsize(32);
    Separator->labelcolor((Fl_Color)2);

    w->end();
}

int main() {
    rtawindow();
    w->show();
    FILE* pFile = fopen("out.txt", "w");
    fclose(pFile);
    std::chrono::high_resolution_clock::time_point started = std::chrono::high_resolution_clock::now();
    int mins, last_position=-1/*, cycle = 1*/;
    double timeri;
    char txttimer[10], txtmins[3];
    std::string input;
    while (Fl::wait(0)) {
        std::ifstream in("out.txt");
/*        int position = find_last_linefeed(in);

        if(position > last_position) {
          in.seekg(position,std::ios::beg);
          in >> input;
        }
        last_position=position;*/
        size_t p = 0;
        in.seekg(p);

        while(getline(in, input)) p = in.tellg();
        if (input == "s" && didstart==false) {started = std::chrono::high_resolution_clock::now();didstart=true;}
            /*else if (input == "1") split(lvl)*/
            else if (input == "e") {didstart=false; ended=true;};
        if (didstart){
            mins = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - started).count();
            sprintf(txtmins, "%00d", mins);
            Mins->label(txtmins);
            timeri = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - started).count() - mins*60;
            sprintf(txttimer, "%.3f", timeri);
            SecMil->label(txttimer);
        } else if (didstart == false && ended == true) {Mins->labelcolor(FL_YELLOW);/*Separator->labelcolor(FL_YELLOW);*/SecMil->labelcolor(FL_YELLOW);};
        /*cycle = w->visible();*/
    };
    return 1;
}