#include <iostream>
#include <fstream>

#include "all_classes.h"

using namespace std;

int main()
{
    // Data data("Hello world!", Data::Format::kHTML);
    // ofstream fout("file.txt");
    // saveToAsText(fout, data);
    //fout.close();

    PrintableHTML printableHTML ("Hello world!");
    cout << printableHTML.print() << endl;
    ofstream fout("file.txt");
    printableHTML.saveTo(fout);

    auto upprintableJSON = Printable("Hello world!", Printable::Format::kJSON).MakePrintable();
    cout << upprintableJSON->print() << endl;
    upprintableJSON->saveTo(fout);

    if(fout.is_open()){ fout.close();}


    return 0;
}
